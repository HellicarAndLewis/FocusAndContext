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
    
    materialEarth.setAmbientColor(ofFloatColor(.1));
    materialEarth.setDiffuseColor(ofFloatColor(.15));
    materialRoads.setAmbientColor(ofFloatColor(.6, .6, .6));
    materialRoads.setDiffuseColor(ofFloatColor(.65, .65, .65));
    materialBuildings.setAmbientColor(ofFloatColor(.2, .2, .2));
    materialBuildings.setDiffuseColor(ofFloatColor(.4, .4, .4));
    materialWater.setAmbientColor(ofFloatColor(0,0,0.6));
    materialWater.setDiffuseColor(ofFloatColor(0,0,1));
    
    
    // tile loader loads multiple tiles from json files in the specified directory
    // it automatically sets the tile builder offset based on the position and zoom of the first tile it reads
    tileLoader.setup();
    tileLoader.loadDir("tiles/smalltest");
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
    
    // update mesh target and if we're scrolling
    if (scroller.isScrolling) {
        meshTarget = route.getPosition(true);
    }
    
    // update camera settings based on our nearest location
    // distance
    float target = ofMap(route.percentToActive, 0, 0.5, route.getLocation()->camDistance, 800);
    cam.setDistance(ofLerp(cam.getDistance(), target, 0.1));
    // x rotation
    target = ofMap(route.percentToActive, 0, 0.5, route.getLocation()->camRotation.x, 0);
    sceneRotation.x = ofLerp(sceneRotation.x, target, 0.1);
    // z rotation
    target = ofMap(route.percentToActive, 0, 0.5, route.getLocation()->camRotation.z, 0);
    sceneRotation.z = ofLerp(sceneRotation.z, target, 0.1);
    
    // lerp the actual mesh position to the target
    float amount = 0.1;
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
    
//    ofSetColor(255, 255, 255, 255);
//    startScene();
//    ofDrawSphere(0, 0, -50, 50);
//    ofDrawCylinder(0, 0, -50, 10, 400);
//    endScene();
    
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
    guiTileAlpha = gui->addSlider("mesh alpha", 0, 255, 255);
    guiTileAlpha->setPrecision(0);
    gui->addToggle("cam mouse", false);
    
    // Set limits based on city of london
    // TODO: make limits dynamic based on dataset
    guiMapX = gui->addSlider("longitude", -0.1130, -0.0692);
    guiMapX->setPrecision(4);
    guiMapX->bind(&mapX, -0.1130, -0.0692);
    guiMapY = gui->addSlider("latitude", 51.5058, 51.5223);
    guiMapY->setPrecision(4);
    guiMapY->bind(&mapY, 51.5058, 51.5223);
    
    // buttons to jump places
    for (auto &location: route.locations) {
        gui->addButton(location.title);
    }
    
    auto slider = gui->addSlider("cam rot x", -90, 90);
    slider->bind(&sceneRotation.x, -90, 90);
    slider = gui->addSlider("cam rot y", -90, 90);
    slider->bind(&sceneRotation.y, -90, 90);
    slider = gui->addSlider("cam rot z", -90, 90);
    slider->bind(&sceneRotation.z, -90, 90);
    
    slider = gui->addSlider("water time", 0, 1, 0.02);
    slider->setPrecision(4);
    slider = gui->addSlider("water mult x", 0, 1000, 65);
    slider = gui->addSlider("water mult y", 0, 1000, 65);
    
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
}

void ofApp::drawScene() {
    startScene();
    ofPushMatrix();
    
    ofRotateX(sceneRotation.x);
    ofRotateY(sceneRotation.y);
    ofRotateZ(sceneRotation.z);
    
    ofTranslate(meshPosition);
    
    
    // Earth / ground
    //    materialEarth.begin();
    //    for (auto & localTile : tileLoader.tiles) {
    //        localTile.meshEarth.draw();
    //    }
    //    materialEarth.end();
    
    
    // Roads
    ofSetColor(255, 255, 255, guiTileAlpha->getValue());
    materialRoads.begin();
    //    roadsShader.begin();
    //    roadsShader.setUniform2f("u_resolution", 64.0f, 64.0f);
    //    roadsShader.setUniform2f("u_mouse", (float)ofGetMouseX(), (float)ofGetMouseY());
    //    roadsShader.setUniform1f("u_time", ofGetElapsedTimef() * gui->getSlider("water time")->getValue());
    for (auto & localTile : tileLoader.tiles) {
        localTile.meshRoads.draw();
    }
    //    roadsShader.end();
    materialRoads.end();
    
    
    // Buildings
    //buildingsShader.begin();
    //buildingsShader.setUniform2f("u_resolution", 64.0f, 64.0f);
    //buildingsShader.setUniform2f("u_mouse", (float)ofGetMouseX(), (float)ofGetMouseY());
    //buildingsShader.setUniform1f("u_time", ofGetElapsedTimef() * gui->getSlider("water time")->getValue());
    materialBuildings.begin();
    for (auto & localTile : tileLoader.tiles) {
        localTile.meshBuildings.draw();
    }
    //buildingsShader.end();
    materialBuildings.end();
    
    
    // Water
    waterShader.begin();
    waterShader.setUniform1f("time", ofGetElapsedTimef() * gui->getSlider("water time")->getValue());
    waterShader.setUniform2f("noiseMult", gui->getSlider("water mult x")->getValue(), gui->getSlider("water mult y")->getValue());
    for (auto & localTile : tileLoader.tiles) {
        localTile.meshWater.draw();
    }
    waterShader.end();
    
    
    ofDisableLighting();
    
    ofSetColor(255, 255, 255, 255);
    route.draw(cam);
    
    ofEnableLighting();
    ofPopMatrix();
    endScene();
    
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
    ofLogVerbose() << "onSliderEvent: " << e.target->getLabel() << " " << e.target->getValue() << endl;
    float amount = 0.01;
    if (e.target->is("longitude")) {
        setLon(e.target->getValue());
    }
    else if (e.target->is("latitude")) {
        //ofLogVerbose() << lat2y(e.target->getValue()) << ", back 2 lat: " << y2lat(lat2y(e.target->getValue()));
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
}

void ofApp::on2dPadEvent(ofxDatGui2dPadEvent e) {
    meshTarget.set(e.x * -1000, e.y * 1000);
    // convert our mesh offset to lat/lon
    // account for the tile loader offset by adding it back on
    mapX = x2lon(tileLoader.builder.getOffset().x) + x2lon(meshPosition.x);
    mapY = y2lat(tileLoader.builder.getOffset().y) + y2lat(meshPosition.y);
    //ofLogVerbose() << y2lat(meshPosition.y);
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
