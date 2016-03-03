//
//  ofApp.cpp
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//  Last edited by Jason Walters on 2/03/2016.
//
//

#include "ofApp.h"
#include "glmGeo.h"
#include "glmGeom.h"
#include "Globals.h"

void ofApp::setup()
{
    //ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableAlphaBlending();
    
    // camera draw distance
    cam.setFarClip(300000);
    cam.setDistance(206000);
    
    // center mesh on launch
    meshPosition.set(-16156.9, 11756.6);

    // FBO to render scene into shader
    ofFbo::Settings settings;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    settings.internalformat = GL_RGB;
    settings.numSamples = 0;
    settings.useDepth = true;
    settings.useStencil = true;
    settings.depthStencilAsTexture = true;
#ifdef TARGET_OPENGLES
    settings.textureTarget = GL_TEXTURE_2D;
#else
    settings.textureTarget = ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
#endif
    fbo.allocate(settings);
    shader.load("", "shader.frag");
    // waterShader.load("shadersGL2/water.vert", "shadersGL2/water.frag");
    buildingsShader.load("shadersGL2/buildings.vert", "shadersGL2/buildings.frag");
    roadsShader.load("shadersGL2/roads.vert", "shadersGL2/roads.frag");
    bShader = false;
    
    // scroller
    scroller.accMax = 2;
    scroller.velMax = 12;
    scroller.setup();
    scroller.disable();
    
    // for billboards
    ofDisableArbTex();
    
    // tile loader loads multiple tiles from json files in the specified directory
    // it automatically sets the tile builder offset based on the position and zoom of the first tile it reads
    tileLoader.setup();
    tileLoader.loadDir("content/tiles");
    
    // load both project routes
    route.loadLeft("content/hs1", tileLoader.builder.getOffset());
    route.loadRight("content/crossrail", tileLoader.builder.getOffset());
    
    // setup gui
    setupGui();
    showGui(!gui->getVisible());
    
    // load default route
    loadProject(0); // 0: High Speed 1, 1: Crossrail
    
    // default to cove setup
    bCove = true;
    // configure menu for screen shape
    menuSetup(ofGetWidth(), ofGetHeight());
    // configure content
    contentSetup(ofGetWidth(), ofGetHeight());
}

void ofApp::setupGui()
{
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addFRM();
    
    gui->addToggle("toggle cove", true);
    gui->addToggle("toggle fullscreen", false);
    gui->addToggle("automated system", false);
    gui->addToggle("show debug", false);
    
    // Camera control
    gui->addToggle("cam mouse", false);
    auto slider = gui->addSlider("cam rot x", -180, 180);
    slider->bind(sceneRotation.x, -180, 180);
    slider = gui->addSlider("cam rot y", -180, 180);
    slider->bind(sceneRotation.y, -180, 180);
    slider = gui->addSlider("cam rot z", -180, 180);
    slider->bind(sceneRotation.z, -180, 180);
    
    // Route selection
    vector<string> routes = {"High Speed 1", "Crossrail"};
    gui->addDropdown("Select a Route", routes);
    gui->onDropdownEvent(this, &ofApp::onDropdownEvent);
    
    // Animation
    ofxDatGuiFolder* folder = gui->addFolder("Animation", ofColor::pink);
    folder->addSlider("location theshold", 0, 1, 0.1)->setPrecision(4);
    folder->addSlider("location lerp", 0, 0.1, 0.1)->setPrecision(4);
    
    // Navigation
    folder = gui->addFolder("Navigation", ofColor::white);
    // Lat/Lon navigation
    // Set limits based on the route bounds
    guiMapX = folder->addSlider("longitude", route.lonRange.getMin(), route.lonRange.getMax());
    guiMapX->setPrecision(4);
    guiMapX->bind(mapX, route.lonRange.getMin(), route.lonRange.getMax());
    guiMapY = folder->addSlider("latitude", route.latRange.getMin(), route.latRange.getMax());
    guiMapY->setPrecision(4);
    guiMapY->bind(mapY, route.latRange.getMin(), route.latRange.getMax());
    gui->addLabel("* Press Spacebar to close GUI *");
    
    /*
     // Water shader
     folder = gui->addFolder("Water", ofColor::blue);
     slider = folder->addSlider("water time", 0, 1, 0.02);
     slider->setPrecision(4);
     folder->addSlider("water mult x", 0, 1000, 65);
     folder->addSlider("water mult y", 0, 1000, 65);
     */
    
    // GUI event listeners
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
}

void ofApp::projectColors()
{
    float colorLerp = 0.1;
    
    // project is hs1, then...
    if (route.activeProject == 0)
    {
        if (camTilt == 120) lightAngleDest = 180;
        else lightAngleDest = 180;
        lightAngle = ofLerp(lightAngle, 180, colorLerp);
        
        colBackground.lerp(ofColor::whiteSmoke, colorLerp);
        
        colEarth.lerp(ofColor(255 - 25.5), colorLerp);
        colEarthDiff.lerp(ofColor(255 - 38.25), colorLerp);
        colRoads.lerp(ofColor(255 - 153, 255 - 153, 255 - 153), colorLerp);
        colRoadsDiff.lerp(ofColor(255 - 165.75, 255 - 165.75, 255 - 165.75), colorLerp);
        colBuildings.lerp(ofColor(255 - 51, 255 - 51, 255 - 51), colorLerp);
        colBuildingsDiff.lerp(ofColor(255 - 102, 255 - 102, 255 - 102), colorLerp);
        colBuildingsActive.lerp(ofColor(255 - 204, 0, 0), colorLerp);
        colBuildingsActiveDiff.lerp(ofColor(255 - 178.5, 0, 0), colorLerp);
        
        colWater.lerp(ofColor(111, 201, 238), colorLerp);
    }
    else
    {
        if (camTilt == 120) lightAngleDest = 180;
        else lightAngleDest = 180;
        lightAngle = ofLerp(lightAngle, 180, colorLerp);
        
        colBackground.lerp(ofColor::black, colorLerp);
        
        colEarth.lerp(ofColor(25.5), colorLerp);
        colEarthDiff.lerp(ofColor(38.25), colorLerp);
        colRoads.lerp(ofColor(153, 153, 153), colorLerp);
        colRoadsDiff.lerp(ofColor(165.75, 165.75, 165.75), colorLerp);
        colBuildings.lerp(ofColor(51, 51, 51), colorLerp);
        colBuildingsDiff.lerp(ofColor(102, 102, 102), colorLerp);
        colBuildingsActive.lerp(ofColor(204, 0, 0), colorLerp);
        colBuildingsActiveDiff.lerp(ofColor(178.5, 0, 0), colorLerp);
        
        colWater.lerp(ofColor(111, 201, 238), colorLerp);
    }
    
    // directional light - even spread across all objects
    light.setDirectional();
    light.setOrientation(ofVec3f(lightAngle, 0, 0));
    // lighting color
    light.setDiffuseColor(ofFloatColor(0.84, 0.8, 0.79));
    
    // background color
    ofBackground(colBackground);
    
    // world materials
    materialEarth.setAmbientColor(colEarth);
    materialEarth.setDiffuseColor(colEarthDiff);
    materialRoads.setAmbientColor(colRoads);
    materialRoads.setDiffuseColor(colRoadsDiff);
    materialBuildings.setAmbientColor(colBuildings);
    materialBuildings.setDiffuseColor(colBuildingsDiff);
    materialBuildingsActive.setAmbientColor(colBuildingsActive);
    materialBuildingsActive.setDiffuseColor(colBuildingsActiveDiff);
    
    // water color
    materialWater.setAmbientColor(ofFloatColor(colWater));
    materialWater.setDiffuseColor(ofFloatColor(colWater));
    materialOcean.setAmbientColor(ofFloatColor(colWater));
    materialOcean.setDiffuseColor(ofFloatColor(colWater));
}

void ofApp::loadProject(int selection)
{
    // set the active project first
    route.activeProject = selection;
    
    // adjust colors
    colorProject = true;
    
    // starting location point
    pointJump = -1;
    
    // clear the bottom scroller before we get the route
    if (scroller.ticks.size() > 0) scroller.ticks.clear();
    
    // load and init route
    Location & location = *route.getLocation();
    
    if (selection == 0)
    {
        for (int i=0; i<route.locationsLeft.size();  i++)
        {
            if (location.title != "" && location.title != "Camera")
            {
                scroller.ticks.push_back(route.locationsLeft[i].routePercent);
            }
            scroller.ticks.push_back(route.locationsLeft[i].routePercent);
        }
        
        // reset project starting point based on auto system
        setLon(0.4760);
        setLat(51.3742);
        scroller.scrollTo(location.routePercent);
        
        // clear POI vector if previously in use
        if (intPoints.size() > 0) intPoints.clear();
        // copy POI into vector
        for (auto &location: route.locationsLeft)
        {
            if (location.title != "" && location.title != "Camera")
            {
                intPoints.push_back(InterestPoints(location.title,
                                                   location.getLat(),
                                                   location.getLon(),
                                                   location.camDistance,
                                                   location.camRotation));
            }
        }
    }
    else
    {
        // load and init route
        Location & location = *route.getLocation();
        
        for (int i=0; i<route.locationsRight.size();  i++)
        {
            if (location.title != "" && location.title != "Camera")
            {
                scroller.ticks.push_back(route.locationsRight[i].routePercent);
            }
            scroller.ticks.push_back(route.locationsRight[i].routePercent);
        }
        
        // reset project starting point based on auto system
        setLon(-0.05501);
        setLat(51.52058);
        scroller.scrollTo(location.routePercent);
        
        // clear POI vector if previously in use
        if (intPoints.size() > 0) intPoints.clear();
        // copy POI into vector
        for (auto &location: route.locationsRight) {
            if (location.title != "" && location.title != "Camera")
            {
                intPoints.push_back(InterestPoints(location.title,
                                                   location.getLat(),
                                                   location.getLon(),
                                                   location.camDistance,
                                                   location.camRotation));
            }
        }
    }
}

void ofApp::loadPoint(int point)
{
    setLon(intPoints[point].lon);
    setLat(intPoints[point].lat);
    
    // not a camera point
    isCam = false;
}

void ofApp::loadContent(int item){
    // content loading here...
}

void ofApp::worldTransform(float distance, float distEase, ofVec3f rotation, float rotEase)
{
    //cam.setDistance(ofLerp(cam.getDistance(), distance, distEase));
    cam.setPosition(cam.getPosition().x, cam.getPosition().y, ofLerp(cam.getPosition().z, distance, distEase));
    
    sceneRotation.x = ofLerp(sceneRotation.x, rotation.x, rotEase);
    sceneRotation.y = ofLerp(sceneRotation.y, rotation.y, rotEase);
    sceneRotation.z = ofLerp(sceneRotation.z, rotation.z, rotEase);
}

void ofApp::autoSysSetup()
{
    // start timer active
    systemTimerPaused = false;
    
    // 30 second intervals
    maxTime = 30.0;
    elapsedTime = 0.0;
    
    // 3 - 30seconds intervals for a total of 90 seconds
    maxInterval = 2;
    currentInterval = 0;
    currentInterestPoint = 0;
    currentPoint = 0;
    
    // disable
    isSysSetup = false;
}

void ofApp::autoSysUpdate()
{
    // we use delta time, the time between frames
    //if (!systemTimerPaused)
    elapsedTime += ofGetLastFrameTime();
    
    if (elapsedTime >= maxTime)
    {
        // advance to next interval
        currentInterval++;
        if (currentInterval > maxInterval)
        {
            // advance to next route
            routeSelection++;
            if (routeSelection > 1) routeSelection = 0;
            
            // load route
            loadProject(routeSelection);
            
            // reset intervals
            currentInterval = 0;
        }
        
        // reset elapsed time to zero
        elapsedTime = 0.0;
    }
    
    /*
     if (currentInterval != 0) {
     // get the active tile and colour it
     ofPoint activeTilePos = route.getLocation()->tilePos;
     tileLoader.setActive(activeTilePos.x, activeTilePos.y);
     }
     */
    
    Location & location = *route.getLocation();
    switch (currentInterval)
    {
        case 0:
            // travel through the route
            setLon(location.getLon());
            setLat(location.getLat());
            scroller.scrollTo(ofMap(elapsedTime, 4.1, 30.0, 0.0, 1.0));
            
            if (elapsedTime > 4)
            {
                camRotSinX = -70 - 10 * sin(elapsedTime);
                camRotSinY = 0 - 2 * sin(elapsedTime * 0.5);
                camRotSinZ = 100 + 10 * sin(elapsedTime * 0.5);
                waveDistance = 4000;
                worldTransform(waveDistance, 0.02, ofVec3f(camRotSinX, camRotSinY, camRotSinZ), 0.02);
                
            }
            else if (elapsedTime)
            {
                if (route.activeProject == 0)
                {
                    worldTransform(96000, 0.02, ofVec3f(0, 0, 0), 0.02);
                }
                else
                {
                    worldTransform(18000, 0.02, ofVec3f(0, 0, 0), 0.02);
                }
            }
            
            // reset route selected to false
            if (routeSelected) routeSelected = false;
            
            break;
            
        case 1:
            // wait x seconds before jumping to a random POI
            if (elapsedTime > 4.0 && !routeSelected)
            {
                pointJump = ofRandom(0, intPoints.size()-1);
                
                // don't repeat the same POI in a row
                if (currentPoint == pointJump) return;
                
                // activate location and scroll to POI
                loadPoint(pointJump);
                
                // route has been selected
                routeSelected = true;
            }
            else if (routeSelected)
            {
                // sync points of interest
                if (currentPoint != pointJump) currentPoint = pointJump;
                
                float dist = meshPosition.distance(meshTarget);
                if (dist >= 1000)
                {
                    camTilt = 0;
                    if (route.activeProject == 0) camDistance = 96000;
                    else camDistance = 18000;
                }
                else
                {
                    if (route.activeProject == 0) {
                        if (cam.getPosition().z > 4000) camTilt = 0;
                        else
                        {
                            camTilt = -60;
                        }
                    }
                    else
                    {
                        if (cam.getPosition().z > 4000) camTilt = 0;
                        else camTilt = -120;
                    }
                    
                    if (route.activeProject == 0) camDistance = 1000;
                    else camDistance = 1000;
                }
                
                worldTransform(camDistance, 0.02, ofVec3f(camTilt, 0, 0), 0.02);
            }
            break;
            
        case 2:
            // do stuff
            break;
    }
}

void ofApp::update()
{
    if (ofGetFrameNum() == 2) cam.disableMouseInput();
    
    if(colorProject) projectColors();
    
    route.update(scroller.getValue());
    
    /*
    // get the active tile and colour it
    ofPoint activeTilePos = route.getLocation()->tilePos;
    tileLoader.setActive(activeTilePos.x, activeTilePos.y);
     */
    
    // update mesh target and if we're scrolling
    if (scroller.isScrolling) meshTarget = route.getPosition(true);
    
    // zoom in/out of points based on distance
    if (!systemActive && bCove)
    {
        // lerp the actual mesh position to the target
        if (isCam)
        {
            camTilt = 0;
            
            if (route.activeProject == 0) camDistance = 206000;
            else camDistance = 42500;
        }
        else
        {
            float dist = meshPosition.distance(meshTarget);
            if (dist >= 1000)
            {
                camTilt = 0;
                
                if (route.activeProject == 0) camDistance = 206000;
                else camDistance = 42500;
            }
            else
            {
                if (route.activeProject == 0)
                {
                    if (cam.getPosition().z > 4000) camTilt = 0;
                    else
                    {
                        camTilt = -60;
                    }
                }
                else
                {
                    if (cam.getPosition().z > 4000) camTilt = 0;
                    else camTilt = -120;
                }
                
                if (route.activeProject == 0) camDistance = 1000;
                else camDistance = 1000;
            }
        }
        
        // draw content menu
        contentUpdate();
        
        // world translation stuff
        worldTransform(camDistance, 0.02, ofVec3f(camTilt, 0, 0), 0.02);
    }
    else if (!systemActive && !bCove)
    {
        if (route.activeProject == 0) camDistance = 96000;
        else camDistance = 18000;
        camTilt = 0;
        // world translation stuff
        worldTransform(camDistance, 0.02, ofVec3f(camTilt, 0, 0), 0.02);
    }
    
    // mesh moves around world
    posLerp = 0.02;
    meshPosition.x = ofLerp(meshPosition.x, meshTarget.x, posLerp);
    meshPosition.y = ofLerp(meshPosition.y, meshTarget.y, posLerp);
    
    if(bShader)
    {
        fbo.begin();
        ofClear(0,0,0,0);
        drawScene();
        fbo.end();
    }
    
    // update menu
    menuUpdates();
    
    // if auto system is active, run
    if (systemActive) autoSysUpdate();
}

void ofApp::menuSetup(int _w, int _h)
{
    menu.setup(_w, _h, 112, 100, 40, 0.08, 0.08);
    
    if (route.activeProject == 0)
    {
        menu.leftOn = true;
        menu.objLeft.isSelected = true;
        menu.rightOn = false;
        menu.objRight.isSelected = false;
    }
    else
    {
        menu.leftOn = false;
        menu.objLeft.isSelected = false;
        menu.rightOn = true;
        menu.objRight.isSelected = true;
    }
    
    isCam = true;
}

void ofApp::menuUpdates()
{
    // draw menu
    if (bCove)
    {
        isDraw = true;
        
        menu.update();
        
        // menu button check
        for (int i = 0; i < BUTTON_AMT; i++)
        {
            // based on left button, load point
            if (menu.bLeftActive[i] && menu.buttonClicked)
            {
                loadPoint(i);
                menu.buttonClicked = false;
            }
            
            // based on right button, load point
            if (menu.bRightActive[i] && menu.buttonClicked)
            {
                loadPoint((BUTTON_AMT-1)-i);
                menu.buttonClicked = false;
            }
        }
    }
    else
    {
        // disable draw menu
        isDraw = false;
    }
    
    menu.objLeftLine.isDraw = isDraw;
    menu.objRightLine.isDraw = isDraw;
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        menu.objsLeft[i].isDraw = isDraw;
        menu.objsRight[i].isDraw = isDraw;
    }
    menu.objLeft.isDraw = isDraw;
    menu.objRight.isDraw = isDraw;
}

void ofApp::contentSetup(int _w, int _h)
{
    content.setup(_w, _h, 100, 96);
}

void ofApp::contentUpdate()
{
    content.update();
    
    // display content menu
    if (cam.getPosition().z <= 1200)
    {
        if (route.activeProject == 0)
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                if (menu.bLeftActive[i] == true)
                {
                    content.draw(0, i, true);
                    content.draw(1, i, false);
                }
            }
            
            content.leftOn = true;
            content.rightOn = false;
            content.buttonClicked = false;
        }
        else
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                if (menu.bRightActive[i] == true)
                {
                    content.draw(0, i, false);
                    content.draw(1, i, true);
                }
            }
            
            content.leftOn = false;
            content.rightOn = true;
            content.buttonClicked = false;
        }
    }
    else
    {
        for (int i = 0; i < BUTTON_AMT; i++)
        {
            content.draw(0, i, false);
            content.draw(1, i, false);
        }
        
        content.leftOn = false;
        content.rightOn = false;
    }
}

void ofApp::draw()
{
    /*
    if(bShader){
        shader.begin();
        shader.setUniformTexture("colorTex", fbo, 0);
        shader.setUniformTexture("depthTex", fbo.getDepthTexture(), 1);
        fbo.draw(0,0);
        shader.end();
    } else {
        drawScene();
    }
     */
    
    drawScene();
    
    // draw ontop of all graphics
    //drawVignette();
    
    // draw project content
    content.drawContent();
    
    // if (!gui->getVisible()) tileLoader.labels.draw2D();
    if (bDebugMsg) drawDebugMsg();
}

void ofApp::drawVignette()
{
    if (route.activeProject == 0)
        colVignette.lerp(ofColor::white, 0.1);
    else
        colVignette.lerp(ofColor::black, 0.1);
    
    ofBackgroundGradient(ofColor(0,0,0,0), colVignette);
}

void ofApp::drawDebugMsg()
{
    if (route.activeProject == 1) colDebug.lerp(ofColor::yellow, 0.08);
    else colDebug.lerp(ofColor::red, 0.08);
    ofSetColor(colDebug);
    
    ofDrawBitmapString("TRANSFORMS", ofGetWidth()-300, 20);
    ofDrawBitmapString("cam.getPosition() " + ofToString(cam.getPosition()), ofGetWidth()-300, 40);
    ofDrawBitmapString("cam.getDistance() " + ofToString(cam.getDistance()), ofGetWidth()-300, 60);
    ofDrawBitmapString("sceneRotation " + ofToString(sceneRotation), ofGetWidth()-300, 80);
    ofDrawBitmapString("meshTarget " + ofToString(meshTarget), ofGetWidth()-300, 100);
    ofDrawBitmapString("meshPosition " + ofToString(meshPosition), ofGetWidth()-300, 120);
    
    ofDrawBitmapString("SCROLLER ", ofGetWidth()-300, 160);
    ofDrawBitmapString("enabled " + ofToString(scroller.isEnabled()), ofGetWidth()-300, 180);
    ofDrawBitmapString("percent " + ofToString(scrollPercent), ofGetWidth()-300, 200);
    
    ofDrawBitmapString("AUTO SYSTEM", ofGetWidth()-300, 240);
    ofDrawBitmapString("enabled " + ofToString(systemActive), ofGetWidth()-300, 260);
    ofDrawBitmapString("elapsedTime " + ofToString(elapsedTime), ofGetWidth()-300, 280);
    ofDrawBitmapString("currentInterval " + ofToString(currentInterval), ofGetWidth()-300, 300);
    ofDrawBitmapString("currentPoint " + ofToString(currentPoint), ofGetWidth()-300, 320);
    ofDrawBitmapString("current interest point " + ofToString(currentInterestPoint), ofGetWidth()-300, 340);
    ofDrawBitmapString("route selected " + ofToString(routeSelection), ofGetWidth()-300, 360);
    ofDrawBitmapString("camRotSinX " + ofToString(camRotSinX), ofGetWidth()-300, 380);
    
    ofDrawBitmapString("MENU", ofGetWidth()-300, 420);
    ofDrawBitmapString("buttonClicked " + ofToString(menu.buttonClicked), ofGetWidth()-300, 440);
    ofDrawBitmapString("leftOn " + ofToString(menu.leftOn), ofGetWidth()-300, 460);
    ofDrawBitmapString("rightOn " + ofToString(menu.rightOn), ofGetWidth()-300, 480);
    ofDrawBitmapString("pointReached " + ofToString(pointReached), ofGetWidth()-300, 500);
    ofDrawBitmapString("isCam " + ofToString(isCam), ofGetWidth()-300, 520);
    ofDrawBitmapString("route.activeProject " + ofToString(route.activeProject), ofGetWidth()-300, 540);
    ofDrawBitmapString("leftClose " + ofToString(menu.leftClose), ofGetWidth()-300, 560);
    ofDrawBitmapString("rightClose " + ofToString(menu.rightClose), ofGetWidth()-300, 580);
    
    ofDrawBitmapString("CONTENT", ofGetWidth()-300, 620);
    ofDrawBitmapString("leftOn " + ofToString(content.leftOn), ofGetWidth()-300, 640);
    ofDrawBitmapString("rightOn " + ofToString(content.rightOn), ofGetWidth()-300, 680);
    ofDrawBitmapString("category " + ofToString(content.category), ofGetWidth()-300, 700);
    ofDrawBitmapString("buttonClicked " + ofToString(content.buttonClicked), ofGetWidth()-300, 720);
    //ofDrawBitmapString("destroy " + ofToString(content.destroy), ofGetWidth()-300, 740);
    ofDrawBitmapString("display " + ofToString(content.display), ofGetWidth()-300, 760);
    ofDrawBitmapString("scales " + ofToString(content.scale[0]) + " " + ofToString(content.scale[1]) + " " + ofToString(content.scale[2]) + " " + ofToString(content.scale[3]) + " " + ofToString(content.scale[4]), ofGetWidth()-300, 780);
    ofDrawBitmapString("item[0] " + ofToString(content.item[0]), ofGetWidth()-300, 800);
    ofDrawBitmapString("item[1] " + ofToString(content.item[1]), ofGetWidth()-300, 820);
    ofDrawBitmapString("item[2] " + ofToString(content.item[2]), ofGetWidth()-300, 840);
    ofDrawBitmapString("item[3] " + ofToString(content.item[3]), ofGetWidth()-300, 860);
    ofDrawBitmapString("item[4] " + ofToString(content.item[4]), ofGetWidth()-300, 880);
    
    
    ofDrawBitmapString("IMAGE", ofGetWidth()-300, 920);
    //ofDrawBitmapString("allocated " + ofToString(content.img.isAllocated()), ofGetWidth()-300, 940);
//
//    ofDrawBitmapString("VIDEO", ofGetWidth()-300, 880);
//    ofDrawBitmapString("isLoaded " + ofToString(content.vid.isLoaded()), ofGetWidth()-300, 900);
//    ofDrawBitmapString("isPlaying " + ofToString(content.vid.isPlaying()), ofGetWidth()-300, 920);
    
    
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////

void ofApp::drawScene()
{
    startScene();
    ofPushMatrix();
    {
        // rotate and transform mesh
        // rotation is top down by default but can switch to an isometric style view for locations
        // the whole mesh moves along the route rather than moving the camera
        ofRotateX(sceneRotation.x);
        ofRotateY(sceneRotation.y);
        ofRotateZ(sceneRotation.z);
        ofTranslate(meshPosition);
        
        auto tiles = &tileLoader.tiles;
        // toggle tile layers based on zoom?
        //if (cam.getDistance() < 5000) tiles = &tileLoader.microTiles;
        
        /*
        // Earth
        ofPushMatrix();
        ofTranslate(0,0,-1000);
        materialEarth.begin();
        for (auto & tile : *tiles) tile.meshEarth.draw();
        materialEarth.end();
        ofPopMatrix();
         */
        
        // Roads
        materialRoads.begin();
        for (auto & tile : *tiles) tile.meshRoads.draw();
        materialRoads.end();
        
        // Buildings
        materialBuildings.begin();
        for (auto & tile : *tiles)
        {
            if (tile.isActive)
            {
                materialBuildings.end();
                materialBuildingsActive.begin();
                tile.meshBuildings.draw();
                materialBuildingsActive.end();
                materialBuildings.begin();
            }
            else
            {
                tile.meshBuildings.draw();
            }
        }
        materialBuildings.end();
        
        // Water
        materialWater.begin();
        for (auto & tile : *tiles) tile.meshWater.draw();
        materialWater.end();
        
        /*
        // Ocean
        materialOcean.begin();
        for (auto & tile : *tiles) tile.meshOcean.draw();
        materialOcean.end();
         */
        
        /*
        waterShader.begin();
        waterShader.setUniform1f("time", ofGetElapsedTimef() * gui->getSlider("water time")->getValue());
        waterShader.setUniform2f("noiseMult", gui->getSlider("water mult x")->getValue(), gui->getSlider("water mult y")->getValue());
        for (auto & tile : *tiles) tile.meshWater.draw();
        waterShader.end();
         */
        
        // draw the route and location content without lighting
        // this ensures consistent colour and legibility
        ofDisableLighting();
        route.draw(cam);
        ofEnableLighting();
    }
    ofPopMatrix();
    endScene();
    
    // draw the zoomed-in content for locations in 2D
    // this is outside of the camera so it can ignore perspective
    route.draw2d();
}

void ofApp::startScene()
{
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
}

void ofApp::endScene()
{
    light.disable();
    ofDisableLighting();
    ofDisableDepthTest();
    cam.end();
}

void ofApp::showGui(bool show)
{
    gui->setVisible(show);
}

void ofApp::setLat(float lat)
{
    mapY = lat;
    meshTarget.y = (lat2y(lat) - tileLoader.builder.getOffset().y) * -1;
}

void ofApp::setLon(float lon)
{
    mapX = lon;
    meshTarget.x = (lon2x(lon) - tileLoader.builder.getOffset().x) * -1;
}

//////////////////////////////////////////////////////////////////////////////////
// custom event handlers
//////////////////////////////////////////////////////////////////////////////////


void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    if (e.target->is("toggle fullscreen"))
    {
        ofToggleFullscreen();
    }
    else if (e.target->is("toggle cove"))
    {
        bCove = !bCove;
        
        if (bCove)
        {
            windowResized(1080, 1500);
            if (systemActive) systemActive = false;
        }
        else
        {
            windowResized(1920, 1080);
            autoSysSetup();
        }
    }
    else if (e.target->is("automated system"))
    {
        systemActive = !systemActive;
        
        // 30 second intervals
        autoSysSetup();
    }
    else if (e.target->is("cam mouse"))
    {
        if (e.target->getEnabled())
        {
            cam.enableMouseInput();
            scroller.disable();
        }
        else
        {
            cam.disableMouseInput();
            scroller.enable();
        }
    }
    else if (e.target->is("show debug"))
    {
        bDebugMsg = !bDebugMsg;
    }
    
    ofLogVerbose() << "onButtonEvent: " << e.target->getLabel() << " " << e.target->getEnabled() << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target->is("longitude"))
        setLon(e.target->getValue());
    else if (e.target->is("latitude"))
        setLat(e.target->getValue());
    else if (e.target->is("cam rot x"))
        sceneRotation.x = e.target->getValue();
    else if (e.target->is("cam rot y"))
        sceneRotation.y = e.target->getValue();
    else if (e.target->is("cam rot z"))
        sceneRotation.z = e.target->getValue();
    else if (e.target->is("location theshold"))
        route.locationThreshold = e.target->getValue();
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if (e.target->getLabel() == "HIGH SPEED 1")
        loadProject(0);
    else if (e.target->getLabel() == "CROSSRAIL")
        loadProject(1);
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e) {
}


//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////

void ofApp::keyPressed(int key)
{
    switch (key)
    {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case ' ':
            showGui(!gui->getVisible());
            break;
    }
}

void ofApp::keyReleased(int key){
}

void ofApp::mouseMoved(int x, int y ){
}

void ofApp::mouseDragged(int x, int y, int button){
}

void ofApp::mousePressed(int x, int y, int button){
}

void ofApp::mouseReleased(int x, int y, int button)
{
    if (bCove)
    {
        // loads hs1 project
        if (menu.objLeft.isMousePressed(0) == 1)
        {
            menu.rightOn = false;
            menu.objRight.isSelected = false;
            
            menu.leftClose = true;
            
            menu.leftOn = true;
            menu.objLeft.isSelected = true;
            
            isCam = true;
            
            menu.buttonClicked = false;
            
            Globals::buttonPressed = true;
            
            // HS1
            loadProject(0);
        }
        
        // loads crossrail project
        if (menu.objRight.isMousePressed(0) == 1)
        {
            menu.leftOn = false;
            menu.objLeft.isSelected = false;
            
            menu.rightClose = true;
            
            menu.rightOn = true;
            menu.objRight.isSelected = true;
            
            isCam = true;
            
            menu.buttonClicked = false;
            
            Globals::buttonPressed = true;
            
            // Crossrail
            loadProject(1);
        }
    }
}

void ofApp::windowResized(int w, int h)
{
    //fbo.allocate(w,h);
    
    // resize window shape
    ofSetWindowShape(w, h);
    // reconfigure menu for new window shape
    menuSetup(w, h);
    // reconfigure content menu for new window shape
    contentSetup(w, h);
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}