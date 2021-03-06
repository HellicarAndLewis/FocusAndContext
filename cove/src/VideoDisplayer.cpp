//
//  VideoDisplayer.cpp
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#include "VideoDisplayer.h"

VideoDisplayer::VideoDisplayer() {
    ContentDisplayer();
    type = ContentTypes::VIDEO;
}

void VideoDisplayer::update() {
    ContentDisplayer::update();
    if(isActive) {
        if(alpha >= 0.99 && video->getPosition() < 0.001) {
            video->play();
        }
        video->update();
        if(video->getPosition() >= 0.995) {
            setIsActive(false);
            for(int i = 0; i < cons.size(); i++) {
                cons[i]->isSelected = false;
            }
            video->setPosition(0.0);
        }
    }
}

void VideoDisplayer::draw(float x, float y) {
    if(scale > 0.01f) {
        ofPushStyle();
        ofSetColor(255);
        ContentDisplayer::draw(x, y);
        float width = video->getWidth();
        float height = video->getHeight();
        float playheadYOffset = 5;
        float playheadHeight = 10;
        float percent = video->getPosition();
        video->draw(x, y, width * scale, height * scale);
        playhead->setAlpha(alpha);
        playhead->draw(x, y + height/2 + playheadYOffset, width * scale, playheadHeight * scale, percent);
        int numLines;
        ofSetColor(0, 0, 0, alpha);
        textFont->drawMultiLineColumn(text, 18, x - width/2 + 5, y + height/2 + 30 + playheadYOffset + playheadHeight, width * textCutoffPercent, numLines);
        ofPopStyle();
    }
}