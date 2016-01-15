//
//  ofApp.cpp
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//

#include "ofApp.h"


void ofApp::setup(){
    
    ofEnableAlphaBlending();
    
    light.setDiffuseColor(ofFloatColor(0.9));
    light.setPosition(ofPoint(0,0,1000));
    
    //  labels
    labels.loadFont("Champagne & Limousines.ttf", 10);
    labels.setFontColor(ofColor::black, ofColor::white);
    builder.setLabelManager(&labels);
    
    //  Tiles
    // NYC
    //tile = builder.getFromWeb(19299,24631,16);
    // Gherkin
    //tile = builder.getFromWeb(51.514445, -0.080273, 16);
    // St pauls
    //tile = builder.getFromWeb(51.513777, -0.098491, 16);
    
    // This is important! Need to set the offset for the first tile manually!
    builder.setOffset(32747, 21789, 16);
    tile = builder.getFromFile(ofToDataPath("tiles/manhattan/16-32747-21789.json", true));
    // VBO from the tile
    tileMesh = tile.getMesh();
    
    tile2 = builder.getFromFile(ofToDataPath("tiles/manhattan/16-32747-21790.json", true));
    tileMesh2 = tile2.getMesh();
    
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
    
    setupGui();
}

void ofApp::setupGui() {
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->addFRM();
    guiTileAlpha = gui->addSlider("position X", 0, 255, 255);
    guiTileAlpha->setPrecision(0);
}


void ofApp::update(){
    labels.updateCameraPosition(cam.getPosition());
    fbo.begin();
    ofClear(0,0,0,0);
    startScene();
    tileMesh.draw();
    tileMesh2.draw();
    endScene();
    fbo.end();
}


void ofApp::draw(){
    ofBackground(ofColor::black);
    
    ofSetColor(255, 255, 255, 255);
    startScene();
    ofDrawSphere(0, 0, -50, 50);
    ofDrawCylinder(0, 0, -50, 10, 400);
    endScene();
    
    ofSetColor(255, 255, 255, guiTileAlpha->getValue());
    if(bShader){
        shader.begin();
        shader.setUniformTexture("colorTex", fbo, 0);
        shader.setUniformTexture("depthTex", fbo.getDepthTexture(), 1);
        fbo.draw(0,0);
        shader.end();
    } else {
        fbo.draw(0,0);
    }
    
    // labels.draw2D();
    
    if(bShader){
        ofSetColor(0);
    } else {
        ofSetColor(255);
    }
    ofDrawBitmapString(" 'p' : toogle point labels debug", 10,15);
    ofDrawBitmapString(" 'l' : toogle line labels debug", 10,35);
    ofDrawBitmapString(" 's' : toogle shader", 10,55);
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


void ofApp::keyPressed(int key){
    
    if(key == 'f'){
        ofToggleFullscreen();
    } else if (key == 'p'){
        labels.bDebugPoints = !labels.bDebugPoints;
    } else if (key == 'l'){
        labels.bDebugLines = !labels.bDebugLines;
    } else if (key == 's'){
        bShader = !bShader;
        
        if(bShader){
            labels.setFontColor(ofColor::black, ofColor::white);
        } else {
            labels.setFontColor(ofColor::white, ofColor::black);
        }
    } else if (key == ' '){
        gui->setVisible(!gui->getVisible());
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
