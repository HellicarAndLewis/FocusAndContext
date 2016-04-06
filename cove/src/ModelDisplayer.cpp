//
//  ModelDisplayer.cpp
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#include "ModelDisplayer.h"

ModelDisplayer::ModelDisplayer() {
    ContentDisplayer();
    manager = new ofxFBXManager();
    camMaxZoom = 6000;
    camMinZoom = 250;
    camZoom = camMinZoom;
}

void ModelDisplayer::update() {
    ContentDisplayer::update();
    if(isActive) {
        //update the light position
        light->setPosition(cam->getPosition());
        light->setOrientation(cam->getOrientationEuler());
        //zoom in the model
        camZoom = ofLerp(camZoom, camMinZoom, 0.1);
    } else {
        //zoom out the model
        camZoom = ofLerp(camZoom, camMaxZoom, 0.1);
    }
}

void ModelDisplayer::draw(float x, float y) {
    if(scale > 0.01f) {
        ContentDisplayer::draw(x, y);
        ofSetColor(255);
        float camPan = 0.5;
        cam->pan(camPan);
        cam->setDistance(camZoom);
        ofEnableDepthTest();
        cam->begin();
        ofEnableLighting();
        light->enable();
        ofSetColor(255, 255, 255);
        manager->draw();
        light->disable();
        ofDisableLighting();
        cam->end();
        ofDisableDepthTest();
    }
}