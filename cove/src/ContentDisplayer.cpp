//
//  contentDisplayer.cpp
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#include "ContentDisplayer.h"

ContentDisplayer::ContentDisplayer() {
    alpha = 0.f;
    scale = 0.f;
    contentLocation = "";
    lerpBig = 0.05;
    lerpSmall = 0.1;
    alphaLerp = 0.4;
    isActive = false;
    textImage = NULL;
    
    isSpecial = false;
}

void ContentDisplayer::update() {
    if(isActive) {
        if(scale < 0.99) {
            scale = ofLerp(scale, 1.0, lerpBig);
        } else {
            alpha = ofLerp(alpha, 255.0, alphaLerp);
        }
    } else if(!isActive) {
        if( scale > 0.01 ) {
            scale = ofLerp(scale, 0.0, lerpSmall);
            alpha = ofLerp(alpha, 0.0, alphaLerp);
        }
    }
}

void ContentDisplayer::draw(float x, float y) {
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    float width = backgroundImage->getWidth();
    float height = backgroundImage->getHeight();
    ofDrawRectRounded(x, y, width * scale, height * scale, 20);
    //backgroundImage->draw(x, y, width * scale, height * scale);
    ofSetColor(255, 255, 255, alpha);
    if(textImage != NULL) {
        textImage->draw(x, y, width * scale, height * scale);
    }
}