//
//  Playhead.cpp
//  PlayheadTest
//
//  Created by James Bentley on 3/27/16.
//
//

#include "Playhead.h"

Playhead::Playhead() {
    
}

void Playhead::draw(float x, float y, float width, float height, float percentage) {
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofSetColor(futureColor);
    ofDrawRectangle(x, y, width, height);
    
    ofSetColor(pastColor);
    ofDrawRectangle(x + width*percentage/2 - width/2, y, width*percentage, height);
    
    ofSetColor(barColor);
    ofDrawRectangle(x + width*percentage - width/2, y, 10, height + 10);
    ofPopStyle();
}