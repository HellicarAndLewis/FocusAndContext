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
        if(alpha >= 0.99) {
            video->play();
        }
        video->update();
        if(video->getPosition() >= 0.99) {
            setIsActive(false);
            for(int i = 0; i < cons.size(); i++) {
                cons[i]->isSelected = false;
            }
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
        ofSetColor(255, 255, 255, 86);
        ofDrawRectRounded(x, y, (width + 60) * scale, (height + 120) * scale, 20 * scale);
        ofSetColor(255, 255, 255);
        video->draw(x, y, width * scale, height * scale);
        playhead->setAlpha(alpha);
        //playhead->draw(x, y + height/2 + playheadYOffset, width * scale, playheadHeight * scale, percent);
        ofPopStyle();
    }
}