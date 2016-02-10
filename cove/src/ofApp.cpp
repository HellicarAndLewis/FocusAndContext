//
//  ofApp.cpp
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//  Edited by Jason Walters on 10/02/2016.
//
//

#include "ofApp.h"
#include "glmGeo.h"
#include "glmGeom.h"

void ofApp::setup() {
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableAlphaBlending();
    
    // camera draw distance
    cam.setFarClip(90000);
    
    // init world colors
    setupWorldColors();
    
    meshPosition.set(0);
    
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
    
    // for billboards
    ofDisableArbTex();
    
    // tile loader loads multiple tiles from json files in the specified directory
    // it automatically sets the tile builder offset based on the position and zoom of the first tile it reads
    tileLoader.setup();
    tileLoader.loadDir("content/tiles");
    routeLoad(0); // defaults to "Crossrail"
    
    // setup gui
    setupGui();
    showGui();
}

void ofApp::setupGui() {
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addFRM();
    
    gui->addToggle("toggle fullscreen", false);
    gui->addToggle("automated system", false);
    gui->addToggle("invert colors", false);
    
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
    folder->addSlider("location theshold", 0, 1, 0.0)->setPrecision(4);
    folder->addSlider("location lerp", 0, 0.1, 0.01)->setPrecision(4);
    
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
    gui->addLabel("* Press Arrow Keys to jump to Route Points *");
    
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

void ofApp::setupWorldColors() {
    
    // directional light - even spread across all objects
    light.setDirectional();
    light.setOrientation(ofVec3f(180, 0, 0));
    
    // color for world objects
    if (!bColorInvert) {
        ofBackground(ofColor::black);
        
        materialEarth.setAmbientColor(ofFloatColor(.1));
        materialEarth.setDiffuseColor(ofFloatColor(.15));
        materialRoads.setAmbientColor(ofFloatColor(.6, .6, .6));
        materialRoads.setDiffuseColor(ofFloatColor(.65, .65, .65));
        materialBuildings.setAmbientColor(ofFloatColor(.2, .2, .2));
        materialBuildings.setDiffuseColor(ofFloatColor(.4, .4, .4));
        materialBuildingsActive.setAmbientColor(ofFloatColor(.8, .0, .0));
        materialBuildingsActive.setDiffuseColor(ofFloatColor(.7, .0, .0));
    }
    else {
        ofBackground(ofColor::white);
        
        materialEarth.setAmbientColor(ofFloatColor(1-.1));
        materialEarth.setDiffuseColor(ofFloatColor(1-.15));
        materialRoads.setAmbientColor(ofFloatColor(1-.6, 1-.6, 1-.6));
        materialRoads.setDiffuseColor(ofFloatColor(1-.65, 1-.65, 1-.65));
        materialBuildings.setAmbientColor(ofFloatColor(1-.2, 1-.2, 1-.2));
        materialBuildings.setDiffuseColor(ofFloatColor(1-.4, 1-.4, 1-.4));
        materialBuildingsActive.setAmbientColor(ofFloatColor(1-.8, 1-.0, 1-.0));
        materialBuildingsActive.setDiffuseColor(ofFloatColor(1-.7, 1-.0, 1-.0));
    }
    
    materialWater.setAmbientColor(ofFloatColor(0,.8,1));
    materialWater.setDiffuseColor(ofFloatColor(0,.8,1));
}

void ofApp::routeLoad(int _selection) {
    
    // starting location point
    pointJump = -1;
    
    // select between routes
    switch (_selection) {
        case 0:
            route.load("content/crossrail", tileLoader.builder.getOffset());
            break;
            
        case 1:
            route.load("content/hs1", tileLoader.builder.getOffset());
            break;
    }
    
    // clear the bottom scroller before we get the route
    if (scroller.ticks.size() > 0) scroller.ticks.clear();
    
    // load and init route
    Location & location = *route.getLocation();
    for (int i=0; i<route.locations.size();  i++) {
        if (location.title != "" && location.title != "Camera") {
            scroller.ticks.push_back(route.locations[i].routePercent);
        }
        scroller.ticks.push_back(route.locations[i].routePercent);
    }
    setLon(location.getLon());
    setLat(location.getLat());
    scroller.scrollTo(location.routePercent);
    
    // clear POI vector if previously in use
    if (intPoints.size() > 0) intPoints.clear();
    // copy POI into vector
    for (auto &location: route.locations) {
        if (location.title != "" && location.title != "Camera"){
            intPoints.push_back(InterestPoints(location.title,
                                               location.getLat(),
                                               location.getLon(),
                                               location.camDistance,
                                               location.camRotation));
        }
    }
}

void ofApp::autoSystem() {
    
    // we use delta time, the time between frames
    if (!systemTimerPaused)
        elapsedTime += ofGetLastFrameTime();
    
    if (elapsedTime >= maxTime) {
        // advance to next interval
        currentInterval++;
        if (currentInterval > maxInterval) {
            // advance to next route
            routeSelection++;
            if (routeSelection > 1) {
                routeSelection = 0;
            }
            
            // load route
            routeLoad(routeSelection);
            
            // reset intervals
            currentInterval = 0;
        }
        
        // reset elapsed time to zero
        elapsedTime = 0.0;
    }
    
    if (currentInterval != 0) {
        // get the active tile and colour it
        ofPoint activeTilePos = route.getLocation()->tilePos;
        tileLoader.setActive(activeTilePos.x, activeTilePos.y);
    }
    
    Location & location = *route.getLocation();
    switch (currentInterval) {
        case 0:
            location.isAlphaLabel = true;
            if (location.getLon() == intPoints[currentInterestPoint].lon &&
                location.getLat() == intPoints[currentInterestPoint].lat) {
                
                systemTimerPaused = true;
                
                // pause for 5 seconds
                elapsedTimeInterestPoints += ofGetLastFrameTime();
                if (elapsedTimeInterestPoints >= 5.0) {
                    currentInterestPoint++;
                    
                    // reset counter
                    elapsedTimeInterestPoints = 0.0;
                    // resume timer
                    systemTimerPaused = false;
                }
            }
            else {
                // travel through the route
                setLon(location.getLon());
                setLat(location.getLat());
                scroller.scrollTo(ofMap(elapsedTime, 0.0, 30.0, 0.0, 1.0));
            }
            
            // reset route selected to false
            if (routeSelected) routeSelected = false;
            
            route.isAlpha = false;
            break;
            
        case 1:
            // wait x seconds before jumping to a random POI
            if (elapsedTime > 6.0 && !routeSelected) {
                pointJump = ofRandom(0, intPoints.size()-1);
                
                // don't repeat the same POI in a row
                if (currentPoint == pointJump) return;
                
                // activate location and scroll to POI
                setLon(intPoints[pointJump].lon);
                setLat(intPoints[pointJump].lat);
                
                // route has been selected
                routeSelected = true;
                
            } else if (routeSelected) {
                // sync points of interest
                if (currentPoint != pointJump) currentPoint = pointJump;
            }
            break;
            
        case 2:
            route.isAlpha = true;
            route.isAlphaLabel = false;
            
            // reset current interest points
            currentInterestPoint = 0;
            break;
    }
}

void ofApp::update(){
        
    if (ofGetFrameNum() == 2) cam.disableMouseInput();
    
    route.update(scroller.getValue());
    
    /*
    // get the active tile and colour it
    ofPoint activeTilePos = route.getLocation()->tilePos;
    tileLoader.setActive(activeTilePos.x, activeTilePos.y);
     */
    
    // update mesh target and if we're scrolling
    if (scroller.isScrolling) meshTarget = route.getPosition(true);
    
    float amount = gui->getSlider("location lerp")->getValue();
    if (scroller.isEnabled()) {
        // update camera settings based on our nearest location
        cam.setDistance(ofLerp(cam.getDistance(), route.getLocation()->camDistance, amount));
        sceneRotation.x = ofLerp(sceneRotation.x, route.getLocation()->camRotation.x, amount);
        sceneRotation.z = ofLerp(sceneRotation.z, route.getLocation()->camRotation.z, amount);
    }
    
    // lerp the actual mesh position to the target
    meshPosition.x = ofLerp(meshPosition.x, meshTarget.x, amount);
    meshPosition.y = ofLerp(meshPosition.y, meshTarget.y, amount);
    
    if(bShader) {
        fbo.begin();
        ofClear(0,0,0,0);
        drawScene();
        fbo.end();
    }
    
    // if auto system is active, run
    if (systemActive) autoSystem();
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
        if (cam.getDistance() < 2000) tiles = &tileLoader.microTiles;
        
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
    }
    else if (e.target->is("invert colors")) {
        bColorInvert = !bColorInvert;
        setupWorldColors();
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
        routeLoad(0);
    else if (e.target->getLabel() == "HIGH SPEED 1")
        routeLoad(1);
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
            setLon(intPoints[pointJump].lon);
            setLat(intPoints[pointJump].lat);
            break;
            
        case OF_KEY_LEFT:
            pointJump--;
            if (pointJump < 0) pointJump = intPoints.size()-1;
            setLon(intPoints[pointJump].lon);
            setLat(intPoints[pointJump].lat);
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
}

void ofApp::windowResized(int w, int h){
    fbo.allocate(w,h);
    scroller.setup();
}

void ofApp::gotMessage(ofMessage msg){
}

void ofApp::dragEvent(ofDragInfo dragInfo){
}