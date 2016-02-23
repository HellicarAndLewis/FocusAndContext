//
//  Location.cpp
//  Cove
//
//  Created by Chris Mullany on 18/01/2016.
//  Edited by Jason Walters on 23/02/2016.
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
    
    percentOpen = 1.0;
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
}

void Location::draw(ofCamera& cam, float _alpha) {
    if (!hasLabel) return;
    
    ofSetColor(255, 255, 255, _alpha);
    
    // billboard height and size
    float height = 200;
    float size = 400;
    float length = ofMap(_alpha, 0, 255, 0, 1);
    
    // draw line from location up to billboard when open
    ofSetLineWidth(4);
    ofDrawLine(position.x, position.y, length * height/2.1, position.x, position.y, 0);
    ofSetLineWidth(1);
    
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
    int w = 300;
    int h = 300;
    int space = 60;
    int x = space;
    int y = ofGetHeight() - space - h;
    
    contentImages[0]->draw(x, y, w, h); //(x, y - h, w, h);
    contentImages[1]->draw(x, y, w, h);
    x += w + space;
    contentImages[2]->draw(x, y, w, h);
    x += w + space;
    contentImages[3]->draw(x, y, w, h);
    x += w + space;
    contentImages[4]->draw(x, y, w, h);
    
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