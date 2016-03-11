//
//  InteractiveObject.h
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 21/02/2016.
//
//

#pragma once

#include "ofxMSAInteractiveObject.h"


class InteractiveObject : public ofxMSAInteractiveObject {
public:
    
    ofTrueTypeFont fontMain;
    ofTrueTypeFont fontSub;
    string title;
    float lineLength;
    float color;
    float alpha;
    int drawType;
    bool isMainTile;
    bool isSelected;
    bool isDraw;
    bool fadeLabel;
    
    void setup() {
        enableMouseEvents();
        enableKeyEvents();
        
        fontMain.load("fonts/Plain-Medium.ttf", 12);
        fontSub.load("fonts/Plain-Medium.ttf", 7);
        
        // default color is darkened
        color = 240;
    }
    
    void exit() {
    }
    
    
    void update() {
    }
    
    void draw() {
        
        if (isDraw) {
            switch (drawType) {
                case 0:
                    if (isSelected) color = ofLerp(color, 255, 0.2);
                    else color = ofLerp(color, 240, 0.2);
                    
                    ofSetColor(color);
                    ofDrawRectangle(x, y, width, height);
                    
                    if (fadeLabel) alpha = ofLerp(alpha, 0, 0.1);
                    else alpha = ofLerp(alpha, 255, 0.2);
                    ofSetColor(0, alpha);
                    if (isMainTile) fontMain.drawString(title, x + 10, y + 20);
                    else fontSub.drawString(title, x + 5, y + 10);
                    
                    break;
                    
                case 1:
                    ofSetLineWidth(3);
                    ofSetColor(255, 130, 0);
                    ofDrawLine(x, y+height/2, x+lineLength, y+height/2);
                    break;
                    
                case 2:
                    ofSetLineWidth(3);
                    ofSetColor(255, 130, 0);
                    ofDrawLine(x-lineLength, y+height/2, x, y+height/2);
                    break;
                    
                case 3:
                    ofSetLineWidth(3);
                    ofSetColor(255, 130, 0);
                    ofDrawLine(x, y+height/2, x, y+height/2-lineLength);
                    break;
            }
        }
    }
    
    virtual void onRollOver(int x, int y) {
    }
    
    virtual void onRollOut() {
    }
    
    virtual void onMouseMove(int x, int y){
    }
    
    virtual void onDragOver(int x, int y, int button) {
    }
    
    virtual void onDragOutside(int x, int y, int button) {
    }
    
    virtual void onPress(int x, int y, int button) {
    }
    
    virtual void onRelease(int x, int y, int button) {
    }
    
    virtual void onReleaseOutside(int x, int y, int button) {
    }
    
    virtual void keyPressed(int key) {
    }
    
    virtual void keyReleased(int key) {
    }
};