//
//  ofApp.cpp
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//

#include "ofApp.h"
#include "glmGeo.h"
#include "glmGeom.h"


void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableAlphaBlending();
    
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(100,100,1000));
    
    cam.setFarClip(90000);
    
    materialEarth.setAmbientColor(ofFloatColor(.1));
    materialEarth.setDiffuseColor(ofFloatColor(.15));
    materialRoads.setAmbientColor(ofFloatColor(.6, .6, .6));
    materialRoads.setDiffuseColor(ofFloatColor(.65, .65, .65));
    materialBuildings.setAmbientColor(ofFloatColor(.2, .2, .2));
    materialBuildings.setDiffuseColor(ofFloatColor(.4, .4, .4));
    materialBuildingsActive.setAmbientColor(ofFloatColor(.8, .0, .0));
    materialBuildingsActive.setDiffuseColor(ofFloatColor(.7, .0, .0));
    materialWater.setAmbientColor(ofFloatColor(0,0,0.6));
    materialWater.setDiffuseColor(ofFloatColor(0,0,1));
    
    
    // tile loader loads multiple tiles from json files in the specified directory
    // it automatically sets the tile builder offset based on the position and zoom of the first tile it reads
    tileLoader.setup();
    tileLoader.loadDir("content/crossrail/tiles");
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
    waterShader.load("shadersGL2/water.vert", "shadersGL2/water.frag");
    buildingsShader.load("shadersGL2/buildings.vert", "shadersGL2/buildings.frag");
    roadsShader.load("shadersGL2/roads.vert", "shadersGL2/roads.frag");
    bShader = false;
    
    // scroller
    scroller.accMax = 2;
    scroller.velMax = 12;
    scroller.setup();
    
    // for billboards
    ofDisableArbTex();
    
    // load and init route
    route.load("content/crossrail", tileLoader.builder.getOffset());
    for (int i=0; i<route.locations.size();  i++) {
        scroller.ticks.push_back(route.locations[i].routePercent);
    }
    Location & location = *route.getLocation();
    setLon(location.getLon());
    setLat(location.getLat());
    scroller.scrollTo(location.routePercent);
    
    setupGui();
    showGui();
}

void ofApp::update(){
    
    if (ofGetFrameNum() == 2) {
        cam.disableMouseInput();
    }
    
    route.update(scroller.getValue());
    
    // get the active tile and colour it
    ofPoint activeTilePos = route.getLocation()->tilePos;
    tileLoader.setActive(activeTilePos.x, activeTilePos.y);
    
    // update mesh target and if we're scrolling
    if (scroller.isScrolling) {
        meshTarget = route.getPosition(true);
    }
    
    float amount = gui->getSlider("location lerp")->getValue();
    if (scroller.isEnabled()) {
        // update camera settings based on our nearest location
        if (route.getLocation()->isActive) {
            cam.setDistance(ofLerp(cam.getDistance(), route.getLocation()->camDistance, amount));
            sceneRotation.x = ofLerp(sceneRotation.x, route.getLocation()->camRotation.x, amount);
            sceneRotation.z = ofLerp(sceneRotation.z, route.getLocation()->camRotation.z, amount);
        }
        else {
            cam.setDistance(ofLerp(cam.getDistance(), 2500, amount));
            sceneRotation.x = ofLerp(sceneRotation.x, 0, amount);
            sceneRotation.z = ofLerp(sceneRotation.z, 0, amount);
        }
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
}


void ofApp::draw(){
    ofBackground(ofColor::black);
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

void ofApp::setupGui() {
    
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addFRM();
    
    // Camera control
    gui->addToggle("cam mouse", false);
    auto slider = gui->addSlider("cam rot x", -90, 90);
    slider->bind(&sceneRotation.x, -90, 90);
    slider = gui->addSlider("cam rot y", -90, 90);
    slider->bind(&sceneRotation.y, -90, 90);
    slider = gui->addSlider("cam rot z", -90, 90);
    slider->bind(&sceneRotation.z, -90, 90);
    
    
    // Animation
    ofxDatGuiFolder* folder = gui->addFolder("Animation", ofColor::pink);
    folder->addSlider("location theshold", 0, 1, 0.05)->setPrecision(4);
    folder->addSlider("location lerp", 0, 1, 0.1)->setPrecision(4);
    
    // Navigation
    folder = gui->addFolder("Navigation", ofColor::white);
    // Lat/Lon navigation
    // Set limits based on the route bounds
    guiMapX = folder->addSlider("longitude", route.lonRange.getMin(), route.lonRange.getMax());
    guiMapX->setPrecision(4);
    guiMapX->bind(&mapX, route.lonRange.getMin(), route.lonRange.getMax());
    guiMapY = folder->addSlider("latitude", route.latRange.getMin(), route.latRange.getMax());
    guiMapY->setPrecision(4);
    guiMapY->bind(&mapY, route.latRange.getMin(), route.latRange.getMax());
    // buttons to jump places
    for (auto &location: route.locations) {
        folder->addButton(location.title);
    }
    
    // Water shader
    folder = gui->addFolder("Water", ofColor::blue);
    slider = folder->addSlider("water time", 0, 1, 0.02);
    slider->setPrecision(4);
    folder->addSlider("water mult x", 0, 1000, 65);
    folder->addSlider("water mult y", 0, 1000, 65);
    
    // GUI event listeners
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
}

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
        //if (cam.getDistance() < 2000) tiles = &tileLoader.microTiles;
        
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
        waterShader.begin();
        waterShader.setUniform1f("time", ofGetElapsedTimef() * gui->getSlider("water time")->getValue());
        waterShader.setUniform2f("noiseMult", gui->getSlider("water mult x")->getValue(), gui->getSlider("water mult y")->getValue());
        for (auto & tile : *tiles) tile.meshWater.draw();
        waterShader.end();
        
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

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e) {
}


//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////

void ofApp::keyPressed(int key){
    if(key == 'f') {
        ofToggleFullscreen();
    }
    else if (key == 's') {
        bShader = !bShader;
        if(bShader){
            tileLoader.labels.setFontColor(ofColor::black, ofColor::white);
        } else {
            tileLoader.labels.setFontColor(ofColor::white, ofColor::black);
        }
    }
    else if (key == ' ') {
        showGui(!gui->getVisible());
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
