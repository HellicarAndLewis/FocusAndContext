//
//  Location.cpp
//  Cove
//
//  Created by Chris Mullany on 18/01/2016.
//  Edited by Jason Walters on 11/03/2016.
//
//

#include "Location.h"
#include "Globals.h"

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
    camDistance = 5000;
    
    percentOpen = 1.0;
    
    verticalOffset = 0;
    verticalOffsetSaved = 0;
    alpha = 0.0;
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

void Location::draw(ofCamera& cam, float _alpha, float _height)
{
    if (!hasLabel) return;
    
    // if in cove mode
    if (Globals::programType)
    {
        // if project is hs1
        if (Globals::project == 0)
        {
            height = ofMap(cam.getPosition().z, 10000, 4000, 0, -1150, true);
            size = ofMap(cam.getPosition().z, 10000, 4000, 200, 400, true);
        }
        else
        {
            height = ofMap(cam.getPosition().z, 10000, 4000, 0, -1600, true);
            size = ofMap(cam.getPosition().z, 10000, 4000, 200, 400, true);
        }
    }
    else
    {
        // if auto system is running...
        // if project is hs1
        if (Globals::project == 0)
        {
            // if traveling through auto route
            if (Globals::autoRoute)
            {
                height = ofLerp(height, 0, 0.2);
               // size = ofLerp(size, 0, 0.2);
            }
            else
            {
                height = ofMap(cam.getPosition().z, 10000, 4000, 0, -1150, true);
                
                //if (cam.getPosition().z > 10000) size = ofLerp(size, 30, 0.02);
                //else size = ofMap(cam.getPosition().z, 10000, 4000, 30, 400, true);
                size = ofMap(cam.getPosition().z, 10000, 4000, 200, 400, true);
            }
        }
        else
        {
            // if traveling through auto route
            if (Globals::autoRoute)
            {
                height = ofLerp(height, 0, 0.2);
                //size = ofLerp(size, 0, 0.2);
            }
            else
            {
                height = ofMap(cam.getPosition().z, 10000, 4000, 0, -1600, true);
                
                //if (cam.getPosition().z > 10000) size = ofLerp(size, 30, 0.02);
                //else size = ofMap(cam.getPosition().z, 10000, 4000, 30, 400, true);
                size = ofMap(cam.getPosition().z, 10000, 4000, 0, 400, true);
            }
        }
    }
    
    ofSetColor(255, 255, 255, _alpha);
    length = ofMap(_alpha, 0, 255, 0, 200, true);
    lineHeight = ofMap(_alpha, 0, 255, 0, 1600, true);
    //lineHeight = ofMap(cam.getPosition().z, 10000, 4000, 0, 1600, true);
    
    /*
    // draw line from location up to billboard when open
    ofSetLineWidth(3);
    if (Globals::project == 0)
    {
        ofDrawLine(position.x, position.y - lineHeight, 0, position.x, position.y - lineHeight + length, 0);
    }
    else if (Globals::project == 1) {
        ofDrawLine(position.x, position.y - lineHeight, 0, position.x, position.y - lineHeight - length * 1.8, 0);
    }
    ofSetLineWidth(1);
    */
    
    if(isActive) {
        alpha = ofLerp(alpha, 1.0, 0.05);
    } else {
        alpha = ofLerp(alpha, 0.0, 0.05);
        if(alpha < 0.1) alpha = 0.0;
    }
    
//    float inputAlpha = ofMap(_alpha, 0.0, 255.0, 0.0, 1.0);
    
//    float finalAlpha = (alpha < inputAlpha) ? alpha : inputAlpha;
    
    ofPushStyle();
    ofPushMatrix();
    ofSetLineWidth(3);
    ofSetColor(255, 255, 255, ofMap(alpha, 0., 1., 0., 255.));
    lineHeight = 1600;
    ofDrawLine(position.x, position.y, 0, position.x, position.y + height, + verticalOffset);
    ofNoFill();
    ofSetCircleResolution(50);
    ofDrawCircle(position.x, position.y, 500);
    ofPopMatrix();
    ofPopStyle();
    
    ofSetLineWidth(1);
    
    // billboard to face cam
    billboardShader.begin();
    billboardShader.setUniform1f("alpha", alpha);
    ofEnablePointSprites();
    labelImage.getTexture().bind();
    glBegin(GL_POINTS);
    glVertex3f(position.x, position.y + height,  verticalOffset);
    glNormal3f(size, 0, 0);
    glEnd();
    labelImage.getTexture().unbind();
    ofDisablePointSprites();
    billboardShader.end();
    
    ofSetColor(255);
}

void Location::draw2d() {
    
    /*
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
     */
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