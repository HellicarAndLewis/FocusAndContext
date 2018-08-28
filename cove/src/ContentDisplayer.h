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
#include "ofxFontStash.h"

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
//    void setCons(vector<InteractiveObject*> _cons) { cons = _cons; };
    void setIsSpecial(bool _isSpecial) { isSpecial = _isSpecial; };
    void setTitleFont(ofxFontStash* font) { titleFont = font; };
    void setTextFont(ofxFontStash* font) { textFont = font; };
    void setSourceFont(ofxFontStash* font) { sourceFont = font; };
    void setTitle(string _title) { title = _title; };
    void setText(string _text) { text = _text; };
    void setSource(string _source) { source = _source; };
    void setTextCutoffPercent(float _percent) { textCutoffPercent = _percent; };

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
    ofxFontStash* titleFont;
    ofxFontStash* textFont;
    ofxFontStash* sourceFont;
    string title;
    string text;
    string source;
    float scale;
    float alpha;
    Playhead* playhead;
    string contentLocation;
    float lerpBig;
    float lerpSmall;
    float alphaLerp;
    bool isActive;
    float textCutoffPercent;
    
    int type;
    
    int isSpecial;
    
//    vector<InteractiveObject*> cons;
    
};

