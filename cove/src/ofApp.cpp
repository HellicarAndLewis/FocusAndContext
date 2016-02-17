//
//  ofApp.cpp
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//  Last edited by Jason Walters on 16/02/2016.
//
//

#include "ofApp.h"
#include "glmGeo.h"
#include "glmGeom.h"

void ofApp::setup() {
    
    //ofSetLogLevel(OF_LOG_NOTICE);
    
    ofEnableAlphaBlending();
    bDebugMsg = true;
    
    // camera draw distance
    cam.setFarClip(120000);
    cam.setNearClip(0);
    cam.setDistance(16000);
    cam.setPosition(-1654.83, 1797.08, cam.getDistance());
    
    // center mesh on launch
    meshPosition.set(-54840.9, 39983.3);
    
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
    
    // setup menu
    menu.setup(112, 100, 40, 0.2, 0.2);
    menu.rightOn = false;
    menu.objRight.isSelected = false;
    menu.leftOn = true;
    menu.objLeft.isSelected = true;
    isCam = true;
    
    loadProject(0); // 0: High Speed 1, 1: Crossrail
}

void ofApp::setupGui() {
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addFRM();
    
    gui->addToggle("toggle fullscreen", false);
    gui->addToggle("automated system", false);
    gui->addToggle("show debug", false);
    
    // Camera control
    gui->addToggle("cam mouse", false);
    auto slider = gui->addSlider("cam rot x", -90, 90);
    slider->bind(sceneRotation.x, -90, 90);
    slider = gui->addSlider("cam rot y", -90, 90);
    slider->bind(sceneRotation.y, -90, 90);
    slider = gui->addSlider("cam rot z", -90, 90);
    slider->bind(sceneRotation.z, -90, 90);
    
    // Route selection
    vector<string> routes = {"Crossrail", "High Speed 1"};
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

void ofApp::projectColors() {
    
    // directional light - even spread across all objects
    light.setDirectional();
    light.setOrientation(ofVec3f(180, 0, 0));
    // lighting color
    light.setDiffuseColor(ofFloatColor(0.84, 0.8, 0.79));
    
    float colorLerp = 0.1;
    
    // project is hs1, then...
    if (route.activeProject == 0) {
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
    } else {
        colBackground.lerp(ofColor(1, 3, 38), colorLerp);
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
    
    ofBackground(colBackground);
    materialEarth.setAmbientColor(colEarth);
    materialEarth.setDiffuseColor(colEarthDiff);
    materialRoads.setAmbientColor(colRoads);
    materialRoads.setDiffuseColor(colRoadsDiff);
    materialBuildings.setAmbientColor(colBuildings);
    materialBuildings.setDiffuseColor(colBuildingsDiff);
    materialBuildingsActive.setAmbientColor(colBuildingsActive);
    materialBuildingsActive.setDiffuseColor(colBuildingsActiveDiff);
    materialWater.setAmbientColor(ofFloatColor(colWater));
    materialWater.setDiffuseColor(ofFloatColor(colWater));
}

void ofApp::loadProject(int selection) {
    
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
    
    if (selection == 0) {
        for (int i=0; i<route.locationsLeft.size();  i++) {
            if (location.title != "" && location.title != "Camera") {
                scroller.ticks.push_back(route.locationsLeft[i].routePercent);
            }
            scroller.ticks.push_back(route.locationsLeft[i].routePercent);
        }
        
        setLon(-0.009882);
        setLat(51.5443);
        
        scroller.scrollTo(location.routePercent);
        
        // clear POI vector if previously in use
        if (intPoints.size() > 0) intPoints.clear();
        // copy POI into vector
        for (auto &location: route.locationsLeft) {
            if (location.title != "" && location.title != "Camera"){
                intPoints.push_back(InterestPoints(location.title,
                                                   location.getLat(),
                                                   location.getLon(),
                                                   location.camDistance,
                                                   location.camRotation));
            }
        }
        
    } else {
        // load and init route
        Location & location = *route.getLocation();
        
        for (int i=0; i<route.locationsRight.size();  i++) {
            if (location.title != "" && location.title != "Camera") {
                scroller.ticks.push_back(route.locationsRight[i].routePercent);
            }
            scroller.ticks.push_back(route.locationsRight[i].routePercent);
        }
        
        setLon(-0.0347);
        setLat(51.504);
        scroller.scrollTo(location.routePercent);
        
        // clear POI vector if previously in use
        if (intPoints.size() > 0) intPoints.clear();
        // copy POI into vector
        for (auto &location: route.locationsRight) {
            if (location.title != "" && location.title != "Camera"){
                intPoints.push_back(InterestPoints(location.title,
                                                   location.getLat(),
                                                   location.getLon(),
                                                   location.camDistance,
                                                   location.camRotation));
            }
        }
    }
}

void ofApp::loadPoint(int point){
    setLon(intPoints[point].lon);
    setLat(intPoints[point].lat);
    
    // not a camera point
    isCam = false;
}

void ofApp::loadContent(int item){
    // content loading here...
}

void ofApp::worldTransform(float distance, float distEase, ofVec3f rotation, float rotEase){
    
    cam.setDistance(ofLerp(cam.getDistance(), distance, distEase));
    sceneRotation.x = ofLerp(sceneRotation.x, rotation.x, rotEase);
    sceneRotation.y = ofLerp(sceneRotation.y, rotation.y, rotEase);
    sceneRotation.z = ofLerp(sceneRotation.z, rotation.z, rotEase);
}

void ofApp::automatedSystem() {
    
    // we use delta time, the time between frames
    //if (!systemTimerPaused)
    elapsedTime += ofGetLastFrameTime();
    
    if (elapsedTime >= maxTime) {
        // advance to next interval
        currentInterval++;
        if (currentInterval > maxInterval) {
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
    switch (currentInterval) {
        case 0:
            // travel through the route
            setLon(location.getLon());
            setLat(location.getLat());
            scroller.scrollTo(ofMap(elapsedTime, 0.0, 30.0, 0.0, 1.0));
            
            waveDistance = 6000;
            camRotSinX = -65 - 10 * sin(elapsedTime);
            camRotSinZ = 85 + 5 * sin(elapsedTime * 0.5);
            worldTransform(waveDistance, 0.02, ofVec3f(camRotSinX, route.getLocation()->camRotation.y, camRotSinZ), 0.02);
            
            // reset route selected to false
            if (routeSelected) routeSelected = false;
            
            route.isAlpha = false;
            break;
            
        case 1:
            // wait x seconds before jumping to a random POI
            if (elapsedTime > 4.0 && !routeSelected) {
                pointJump = ofRandom(0, intPoints.size()-1);
                
                // don't repeat the same POI in a row
                if (currentPoint == pointJump) return;
                
                // activate location and scroll to POI
                loadPoint(pointJump);
                
                // route has been selected
                routeSelected = true;
                
            } else if (routeSelected) {
                // sync points of interest
                if (currentPoint != pointJump) currentPoint = pointJump;
                
                float dist = meshPosition.distance(meshTarget);
                if (dist <= 1000) {
                    worldTransform(5000, 0.02, ofVec3f(-60, 0, 0), 0.02);
                } else {
                    worldTransform(30000, 0.05, ofVec3f(0, 0, 0), 0.01);
                }
            }
            break;
            
        case 2:
            // reset current interest points
            if (currentInterestPoint != 0) currentInterestPoint = 0;
            break;
    }
}

void ofApp::update(){
    
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
    if (!systemActive) {
        // lerp the actual mesh position to the target
        posLerp = 0.02;
        
        if (isCam) {
            worldTransform(30000, 0.05, ofVec3f(0, 0, 0), 0.2);
        } else {
            float dist = meshPosition.distance(meshTarget);
            if (dist <= 1000) {
                worldTransform(6000, 0.02, ofVec3f(-60, 0, 0), 0.02);
            } else {
                worldTransform(30000, 0.05, ofVec3f(0, 0, 0), 0.2);
            }
        }
    } else {
        // lerp the actual mesh position to the target
        posLerp = 0.008;
    }
    
    meshPosition.x = ofLerp(meshPosition.x, meshTarget.x, posLerp);
    meshPosition.y = ofLerp(meshPosition.y, meshTarget.y, posLerp);
    
    if(bShader) {
        fbo.begin();
        ofClear(0,0,0,0);
        drawScene();
        fbo.end();
    }
    
    // if auto system is active, run
    if (systemActive) automatedSystem();
    
    // update menu
    menuUpdates();
}

void ofApp::menuUpdates(){
    menu.update();
    
    // menu button check
    for (int i = 0; i < BUTTON_AMT; i++) {
        if (menu.bLeftActive[i] && menu.buttonClicked){
            loadPoint(i);
            menu.buttonClicked = false;
        }
        
        if (menu.bRightActive[i] && menu.buttonClicked){
            loadPoint((BUTTON_AMT-1)-i);
            menu.buttonClicked = false;
        }
    }
}

void ofApp::draw(){
    if(bShader){
        shader.begin();
        shader.setUniformTexture("colorTex", fbo, 0);
        shader.setUniformTexture("depthTex", fbo.getDepthTexture(), 1);
        fbo.draw(0,0);
        shader.end();
    } else {
        drawScene();
    }
    
    if (!gui->getVisible()) tileLoader.labels.draw2D();
    if (bDebugMsg) drawDebugMsg();
}

void ofApp::drawDebugMsg(){
    
    ofSetColor(255, 255, 0);
    ofDrawBitmapString("TRANSFORMS ", ofGetWidth()-300, 20);
    ofDrawBitmapString("camDistance " + ofToString(camDistance), ofGetWidth()-300, 40);
    ofDrawBitmapString("cam.getDistance() " + ofToString(cam.getDistance()), ofGetWidth()-300, 60);
    ofDrawBitmapString("sceneRotation " + ofToString(sceneRotation), ofGetWidth()-300, 80);
    ofDrawBitmapString("meshTarget " + ofToString(meshTarget), ofGetWidth()-300, 100);
    ofDrawBitmapString("meshPosition " + ofToString(meshPosition), ofGetWidth()-300, 120);
    
    ofDrawBitmapString("SCROLLER ", ofGetWidth()-300, 160);
    ofDrawBitmapString("enabled " + ofToString(scroller.isEnabled()), ofGetWidth()-300, 180);
    ofDrawBitmapString("percent " + ofToString(scrollPercent), ofGetWidth()-300, 200);
    
    ofDrawBitmapString("AUTO SYSTEM ", ofGetWidth()-300, 240);
    ofDrawBitmapString("enabled " + ofToString(systemActive), ofGetWidth()-300, 260);
    ofDrawBitmapString("elapsedTime " + ofToString(elapsedTime), ofGetWidth()-300, 280);
    ofDrawBitmapString("currentInterval " + ofToString(currentInterval), ofGetWidth()-300, 300);
    ofDrawBitmapString("currentPoint " + ofToString(currentPoint), ofGetWidth()-300, 320);
    ofDrawBitmapString("current interest point " + ofToString(currentInterestPoint), ofGetWidth()-300, 340);
    ofDrawBitmapString("route selected " + ofToString(routeSelection), ofGetWidth()-300, 360);
    ofDrawBitmapString("camRotSinX " + ofToString(camRotSinX), ofGetWidth()-300, 380);
    
    
    ofDrawBitmapString("MENU ", ofGetWidth()-300, 420);
    ofDrawBitmapString("buttonClicked " + ofToString(menu.buttonClicked), ofGetWidth()-300, 440);
    ofDrawBitmapString("leftOn " + ofToString(menu.leftOn), ofGetWidth()-300, 460);
    ofDrawBitmapString("rightOn " + ofToString(menu.rightOn), ofGetWidth()-300, 480);
    ofDrawBitmapString("pointReached " + ofToString(pointReached), ofGetWidth()-300, 500);
    ofDrawBitmapString("isCam " + ofToString(isCam), ofGetWidth()-300, 520);
    ofDrawBitmapString("route.activeProject " + ofToString(route.activeProject), ofGetWidth()-300, 540);
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////

void ofApp::drawScene() {
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
        if (cam.getDistance() < 5000) tiles = &tileLoader.microTiles;
        
        // Roads
        materialRoads.begin();
        for (auto & tile : *tiles) tile.meshRoads.draw();
        materialRoads.end();
        
        // Buildings
        materialBuildings.begin();
        for (auto & tile : *tiles) {
            if (tile.isActive) {
                materialBuildings.end();
                materialBuildingsActive.begin();
                tile.meshBuildings.draw();
                materialBuildingsActive.end();
                materialBuildings.begin();
            }
            else {
                tile.meshBuildings.draw();
            }
        }
        materialBuildings.end();
        
        // Water
        materialWater.begin();
        for (auto & tile : *tiles) tile.meshWater.draw();
        materialWater.end();
        
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

void ofApp::startScene() {
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    light.enable();
}

void ofApp::endScene(){
    light.disable();
    ofDisableLighting();
    ofDisableDepthTest();
    cam.end();
}

void ofApp::showGui(bool show) {
    gui->setVisible(show);
}

void ofApp::setLat(float lat) {
    mapY = lat;
    meshTarget.y = (lat2y(lat) - tileLoader.builder.getOffset().y) * -1;
}

void ofApp::setLon(float lon) {
    mapX = lon;
    meshTarget.x = (lon2x(lon) - tileLoader.builder.getOffset().x) * -1;
}

//////////////////////////////////////////////////////////////////////////////////
// custom event handlers
//////////////////////////////////////////////////////////////////////////////////


void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target->is("toggle fullscreen")) {
        ofToggleFullscreen();
    }
    else if (e.target->is("automated system")) {
        systemActive = !systemActive;
        
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
    }
    else if (e.target->is("cam mouse")) {
        if (e.target->getEnabled()) {
            cam.enableMouseInput();
            scroller.disable();
        }
        else {
            cam.disableMouseInput();
            scroller.enable();
        }
    }
    else if (e.target->is("show debug")) {
        bDebugMsg = !bDebugMsg;
    }
    /*
    else {
        for (auto &location: route.locations) {
            if (e.target->is(location.title)) {
                location.isActive = true;
                setLon(location.getLon());
                setLat(location.getLat());
                scroller.scrollTo(location.routePercent);
            }
        }
    }
     */
    
    ofLogVerbose() << "onButtonEvent: " << e.target->getLabel() << " " << e.target->getEnabled() << endl;
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
    if (e.target->is("longitude")) {
        setLon(e.target->getValue());
    }
    else if (e.target->is("latitude")) {
        setLat(e.target->getValue());
    }
    else if (e.target->is("cam rot x")) {
        sceneRotation.x = e.target->getValue();
    }
    else if (e.target->is("cam rot y")) {
        sceneRotation.y = e.target->getValue();
    }
    else if (e.target->is("cam rot z")) {
        sceneRotation.z = e.target->getValue();
    }
    else if (e.target->is("location theshold")) {
        route.locationThreshold = e.target->getValue();
    }
}

void ofApp::onDropdownEvent(ofxDatGuiDropdownEvent e)
{
    if (e.target->getLabel() == "CROSSRAIL")
        loadProject(0);
    else if (e.target->getLabel() == "HIGH SPEED 1")
        loadProject(1);
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e) {
}


//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////

void ofApp::keyPressed(int key) {
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 's':
            bShader = !bShader;
            if(bShader){
                tileLoader.labels.setFontColor(ofColor::black, ofColor::white);
            } else {
                tileLoader.labels.setFontColor(ofColor::white, ofColor::black);
            }
            break;
            
        case ' ':
            showGui(!gui->getVisible());
            break;
            
        case OF_KEY_RIGHT:
            pointJump++;
            if (pointJump > intPoints.size()-1) pointJump = 0;
            loadPoint(pointJump);
            break;
            
        case OF_KEY_LEFT:
            pointJump--;
            if (pointJump < 0) pointJump = intPoints.size()-1;
            loadPoint(pointJump);
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

void ofApp::mouseReleased(int x, int y, int button){
    // loads hs1 project
    if (menu.objLeft.isMousePressed(0) == 1) {
        menu.rightOn = false;
        menu.objRight.isSelected = false;
        
        menu.leftOn = !menu.leftOn;
        menu.objLeft.isSelected = !menu.objLeft.isSelected;
        
        isCam = true;
        
        // HS1
        loadProject(0);
    }
    
    // loads crossrail project
    if (menu.objRight.isMousePressed(0) == 1) {
        menu.leftOn = false;
        menu.objLeft.isSelected = false;
        
        menu.rightOn = !menu.rightOn;
        menu.objRight.isSelected = !menu.objRight.isSelected;
        
        isCam = true;
        
        // Crossrail
        loadProject(1);
    }
}

void ofApp::windowResized(int w, int h){
    fbo.allocate(w,h);
    scroller.setup();
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}