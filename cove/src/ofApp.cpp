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
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofEnableAlphaBlending();
    
//    light.setOrientation(ofVec3f(90, 90, 0));
//    light.setDirectional();
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(100,100,1000));
    
    materialRoads.setAmbientColor(ofFloatColor(.641176471));
    materialRoads.setDiffuseColor(ofFloatColor(.641176471));
    materialBuildings.setAmbientColor(ofFloatColor::grey);
    materialBuildings.setDiffuseColor(ofFloatColor(.247058824, .298039216, .988235294));
    
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
    bShader = false;
    
    // scroller
    scroller.accMax = 2;
    scroller.velMax = 12;
    scroller.setup();
    
    //
    ofDisableArbTex();
    titleFont.load("ofxdatgui_assets/font-verdana.ttf", 40);
    Location location1;
    location1.titleFont = &titleFont;
    location1.setup("St Pauls");
    location1.latlon.set(-0.09781, 51.51356);
    locations.push_back(location1);
    Location location2;
    location2.titleFont = &titleFont;
    location2.setup("Bank");
    location2.latlon.set(-0.08907, 51.51331);
    locations.push_back(location2);
    Location location3;
    location3.titleFont = &titleFont;
    location3.setup("Liverpool St");
    location3.latlon.set(-0.08122, 51.51877);
    locations.push_back(location3);
    Location location4;
    location4.titleFont = &titleFont;
    location4.setup("Aldgate");
    location4.latlon.set(-0.07577, 51.51421);
    locations.push_back(location4);
    
    for (auto &location: locations) {
        location.position.set((lon2x(location.getLon()) - tileLoader.builder.getOffset().x), (lat2y(location.getLat()) - tileLoader.builder.getOffset().y));
        route.addVertex(location.position);
        routeInverse.addVertex(location.position * -1);
    }
    
    setupGui();
    showGui();
}

void ofApp::setupGui() {
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
    gui->addFRM();
    guiTileAlpha = gui->addSlider("mesh alpha", 0, 255, 255);
    guiTileAlpha->setPrecision(0);
    
    gui->addToggle("cam mouse", false);
    
//    gui->addBreak();
//    guiPositionPad = gui->add2dPad("2d pad");
//    guiPositionPad->on2dPadEvent(this, &ofApp::on2dPadEvent);
//    ofRectangle bounds = ofRectangle(-1, -1, 2, 2);
//    guiPositionPad->setBounds(bounds);
//    gui->addBreak();
    
    // Set limits based on city of london
    // TODO: make limits dynamic based on dataset
    guiMapX = gui->addSlider("longitude", -0.1130, -0.0692);
    guiMapX->setPrecision(4);
    guiMapX->bind(&mapX, -0.1130, -0.0692);
    guiMapY = gui->addSlider("latitude", 51.5058, 51.5223);
    guiMapY->setPrecision(4);
    guiMapY->bind(&mapY, 51.5058, 51.5223);
    
    // buttons to jump places
    for (auto &location: locations) {
        gui->addButton(location.title);
    }
    
    
    gui->onButtonEvent(this, &ofApp::onButtonEvent);
    gui->onSliderEvent(this, &ofApp::onSliderEvent);
}


void ofApp::update(){
    
    if (ofGetFrameNum() == 2) {
        cam.disableMouseInput();
    }
    
    if (scroller.isScrolling) {
        meshTarget = routeInverse.getPointAtPercent(scroller.getValue());
    }
    
    float amount = 0.2;
    meshPosition.x = ofLerp(meshPosition.x, meshTarget.x, amount);
    meshPosition.y = ofLerp(meshPosition.y, meshTarget.y, amount);
    
    tileLoader.labels.updateCameraPosition(cam.getPosition());
    fbo.begin();
    ofClear(0,0,0,0);
    drawScene();
    fbo.end();
}


void ofApp::draw(){
    ofBackground(ofColor::white);
    
//    ofSetColor(255, 255, 255, 255);
//    startScene();
//    ofDrawSphere(0, 0, -50, 50);
//    ofDrawCylinder(0, 0, -50, 10, 400);
//    endScene();
    
    ofSetColor(255, 255, 255, guiTileAlpha->getValue());
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

void ofApp::drawScene() {
    startScene();
    ofPushMatrix();
    ofTranslate(meshPosition);
    materialRoads.begin();
    for (auto & localTile : tileLoader.tiles) {
        //localTile.mesh.draw();
        localTile.meshRoads.draw();
    }
    materialRoads.end();
    materialBuildings.begin();
    for (auto & localTile : tileLoader.tiles) {
        localTile.meshBuildings.draw();
    }
    materialBuildings.end();
    
    for (auto &location: locations) {
        location.draw();
    }
    
    ofDisableLighting();
    ofSetColor(200, 0, 0);
    ofPushMatrix();
    ofTranslate(0, 0, 20);
    ofSetLineWidth(5);
    route.draw();
    ofSetLineWidth(1);
    ofPopMatrix();
    ofSetColor(255);
    ofEnableLighting();
    
    //tileLoader.labels.draw3D();
    //tileLoader.labels.updateProjection();
    
    ofPopMatrix();
    
    endScene();
    
    
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
        if (e.target->getEnabled()) cam.enableMouseInput();
        else cam.disableMouseInput();
    }
    else {
        for (auto &location: locations) {
            if (e.target->is(location.title)) {
                location.isActive = true;
                setLon(location.getLon());
                setLat(location.getLat());
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
}


void ofApp::gotMessage(ofMessage msg){
    
}


void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
