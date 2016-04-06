//
//  AudioDisplayer.h
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#pragma once

#include "ofMain.h"
#include "ContentDisplayer.h"

class AudioDisplayer : public ContentDisplayer {
public:
    //Constructor
    AudioDisplayer();
    
    // Setters
    void setAudio(ofSoundPlayer* _audio) { audio = _audio; };
    bool setAudio(string _audioLocation) {
        audio = new ofSoundPlayer();
        bool loaded = audio->load(_audioLocation);
        if(loaded) {
            audio->setVolume(1.0f);
            audio->setLoop(false);
        }
        return loaded;
    }
    
    virtual void setIsActive(bool _isActive) {
        ContentDisplayer::setIsActive(_isActive);
        if(!isActive && audio->isPlaying()) {
            audio->stop();
        }
    }
    
    // Getters
    ofSoundPlayer* getAudio() { return audio; };
    
    // Functionality
    virtual void draw(float x, float y);
    virtual void update();
    
private:
    ofSoundPlayer* audio;
};
