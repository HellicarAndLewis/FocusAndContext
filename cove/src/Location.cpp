//
//  Location.cpp
//  Cove
//
//  Created by Chris Mullany on 18/01/2016.
//  Edited by Jason Walters on 5/02/2016.
//
//

#include "Location.h"

// script for controlling the POI labels
Location::Location() {
    isActive = false;
    if(ofIsGLProgrammableRenderer()) {
        billboardShader.load("shadersGL3/Billboard");
    }
    else {
        billboardShader.load("shadersGL2/Billboard");
    }
    camRotation.set(-45, 0, 30);
    camDistance = 500;
}

void Location::setup(string title) {
    this->title = title;
    if (title != "" && title != "Camera") {
        hasLabel = true;
    }
    else {
        hasLabel = false;
    }
}

void Location::update() {
    if (isAlpha) percentOpen = ofLerp(percentOpen, 0, 0.1);
    else percentOpen = ofLerp(percentOpen, 1.0, 0.1);
}

void Location::draw(ofCamera& cam) {
    if (!hasLabel) return;
    
    ofSetColor(255, 255, 255, 255);
    
    // billboard height and size
    float height = 200;
    float size = 400;
    
    // draw line from location up to billboard when open
    /*
    ofSetLineWidth(4);
    ofDrawLine(position.x, position.y, percentOpen * height, position.x, position.y, 0);
    ofSetLineWidth(1);
    */
    
    // billboard to face cam
    billboardShader.begin();
    ofEnablePointSprites();
    labelImage.getTexture().bind();
    glBegin(GL_POINTS);
    glVertex3f(position.x, position.y, height);
    glNormal3f(size, 0, 0);
    glEnd();
    labelImage.getTexture().unbind();
    ofDisablePointSprites();
    billboardShader.end();
    
    ofSetColor(255);
}

void Location::draw2d() {
    
    if (!hasLabel)
        return;
    
    int alphaTarget = 255 - (percentOpen * 255);
    ofSetColor(255, 255, 255, alphaTarget);
    int w = 800;
    int h = 800;
    int x = ofGetWidth()/2;
    int y = ofGetHeight()/2;
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    //int selectContent = ofRandom(contentImages.size()-1);
    contentImages[2]->draw(x, y, w, h);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    ofSetColor(255);
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