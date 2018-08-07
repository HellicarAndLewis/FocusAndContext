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
    type = ContentTypes::MODEL;

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
        ofSetColor(255, 255, 255, alpha);
        textImage->draw(x, y);
        ofSetColor(255);
        float camPan = 0.5;
        cam->pan(camPan);
        cam->setDistance(camZoom);
        cam->setPosition(cam->getPosition().x, 40, cam->getPosition().z);
        cam->lookAt(ofVec3f(0, 0, 0));
        ofEnableDepthTest();
        cam->begin();
        ofEnableLighting();
        light->enable();
        ofSetColor(255, 255, 255);
        //manager->setOrientation(ofVec3f(0, 0, 30));
        manager->draw();
        light->disable();
        ofDisableLighting();
        cam->end();
        ofDisableDepthTest();
        int numLines;
        ofSetColor(0, 0, 0, alpha);
        textFont->drawMultiLineColumn(text, 18, x - 909/2 + 5, y + 566/2 + 30, 909 * textCutoffPercent, numLines);
    }
}