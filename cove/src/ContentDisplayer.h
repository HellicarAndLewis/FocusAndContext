//
//  contentDisplayer.h
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#pragma once

#include "ofMain.h"
#include "Playhead.h"
#include "Globals.h"
#include "InteractiveObject.h"

class ContentDisplayer {
public:
    // Constructor
    ContentDisplayer();
    // Destructor
    virtual ~ContentDisplayer() { };
    
    // Setters
    void setBackgroundImage(ofImage* _image) { backgroundImage = _image; };
    void setTextImage(ofImage* _image) { textImage = _image; };
    bool setTextImage(string _imageLocation) {
        textImage = new ofImage();
        return textImage->load(_imageLocation);
    };
    
    void setPlayhead(Playhead* _playhead) { playhead = _playhead; };
    void setContentLocation(string _location) { contentLocation = _location; };
    void setAlpha(float _alpha) { alpha = _alpha; };
    virtual void setIsActive(bool _isActive) {
        isActive = _isActive;
        if(isActive) Globals::vignetteOn = true;
        else Globals::vignetteOn = false;
    };
    void setCons(vector<InteractiveObject*> _cons) { cons = _cons; };
    void setIsSpecial(bool _isSpecial) { isSpecial = _isSpecial; };
    
    // Getters
    ofImage* getBackgroundImage() { return backgroundImage; };
    ofImage* getTextImage() { return textImage; };
    float getScale() { return scale; };
    string getContentLocation() { return contentLocation; };
    void getAlpha() { return alpha; };
    bool getIsActive() { return isActive; };
    bool getIsSpecial() { return isSpecial; };
    
    // Functionality
    virtual void update();
    virtual void draw(float x, float y);
    
    enum ContentTypes {
        IMAGE,
        AUDIO,
        VIDEO,
        MODEL
    };
    
protected:
    ofImage* backgroundImage;
    ofImage* textImage;
    float scale;
    float alpha;
    Playhead* playhead;
    string contentLocation;
    float lerpBig;
    float lerpSmall;
    float alphaLerp;
    bool isActive;
    
    int type;
    
    int isSpecial;
    
    vector<InteractiveObject*> cons;
    
};

