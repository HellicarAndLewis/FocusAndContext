//
//  VideoDisplayer.h
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#pragma once

#include "ofMain.h"
#include "ContentDisplayer.h"

class VideoDisplayer : public ContentDisplayer {
public:
    //Constructor
    VideoDisplayer();
    
    // Setters
    void setVideo(ofVideoPlayer* _video) { video = _video; };
    bool setVideo(string _videoLocation) {
        video = new ofVideoPlayer();
        bool loaded = video->load(_videoLocation);
        if(loaded) {
            video->setLoopState(OF_LOOP_NONE);
        }
        return loaded;
    }
    
    virtual void setIsActive(bool _isActive) {
        ContentDisplayer::setIsActive(_isActive);
        if(!isActive && video->isPlaying()) {
            video->stop();
            video->setLoopState(OF_LOOP_NONE);
        } else if(isActive && !video->isPlaying()) {
//            video->play();
            video->setLoopState(OF_LOOP_NONE);
        }
    }
    
    // Getters
    ofVideoPlayer* getVideo() { return video; };
    
    virtual float getDuration() { return video->getDuration(); };
    
    // Functionality
    virtual void draw(float x, float y);
    virtual void update();
    
private:
    ofVideoPlayer* video;
};

