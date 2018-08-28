//
//  AudioDisplayer.cpp
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#include "AudioDisplayer.h"

AudioDisplayer::AudioDisplayer() {
    ContentDisplayer();
    type = ContentTypes::AUDIO;
}

void AudioDisplayer::update() {
    ContentDisplayer::update();
    if(isActive) {
        if(alpha >= 0.99) {
            if(!audio->isPlaying()) {
                audio->play();
                audio->setVolume(1.0);
            }
        }
        if(audio->getPosition() >= 0.99) {
            setIsActive(false);
//            for(int i = 0; i < cons.size(); i++) {
//                cons[i]->isSelected = false;
//            }
        }
    }
}

void AudioDisplayer::draw(float x, float y) {
    if(scale > 0.01f) {
        ofPushStyle();
        ContentDisplayer::draw(x, y);
        float width = 909.f;
        float height = 30.f;
        float yOffset = -19.f;
        float percentage = audio->getPosition();
        playhead->setAlpha(alpha);
        playhead->draw(x, y + yOffset, width * scale, height * scale, percentage);
        int numLines;
        ofSetColor(0, 0, 0, alpha);
        textFont->drawMultiLineColumn(text, 18, x - width/2 + 5, y + height/2 + 30, width * textCutoffPercent, numLines);
        ofPopStyle();
    }
}
