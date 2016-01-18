//
//  Location.cpp
//  Cove
//
//  Created by Chris Mullany on 18/01/2016.
//
//

#include "Location.h"

Location::Location() {
    isActive = false;
    if(ofIsGLProgrammableRenderer()){
        billboardShader.load("shadersGL3/Billboard");
    }else{
        billboardShader.load("shadersGL2/Billboard");
    }
    billboards.getVertices().resize(1);
    billboards.getNormals().resize(1,ofVec3f(300));
    billboards.setUsage( GL_DYNAMIC_DRAW );
    billboards.setMode(OF_PRIMITIVE_POINTS);
}

void Location::setup(string title) {
    this->title = title;
    fbo.allocate(400, 400);
    fbo.begin();
    ofClear(0, 0, 0, 200);
    ofSetColor(255);
    titleFont->drawString(title, 20, 80);
    fbo.end();
}

void Location::update() {
}

void Location::draw() {
    
    float height = 200;
    ofPushStyle();
    ofSetColor(0);
    ofSetLineWidth(2);
    ofDrawLine(position.x, position.y, height, position.x, position.y, 0);
    ofPopStyle();
    ofSetColor(255);
    
    // billboard to face cam?
    billboards.getVertices()[0].set(position.x, position.y, height);
    billboardShader.begin();
    ofEnablePointSprites(); // not needed for GL3/4
    fbo.getTexture().bind();
    billboards.draw();
    fbo.getTexture().unbind();
    ofDisablePointSprites(); // not needed for GL3/4
    billboardShader.end();
    
    
//    ofPushMatrix();
//    ofTranslate(position.x, position.y, 60);
//    fbo.draw(0,0);
//    ofPopMatrix();
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////
float Location::getLon() {
    return latlon.x;
}
float Location::getLat() {
    return latlon.y;
}
//////////////////////////////////////////////////////////////////////////////////
// protected
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////////////////