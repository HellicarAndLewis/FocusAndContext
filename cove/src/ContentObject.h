//
//  ContentObject.h
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 21/02/2016.
//
//

#pragma once

#include "ofxMSAInteractiveObject.h"


class ContentObject : public ofxMSAInteractiveObject {
public:
    
    ofTrueTypeFont font;
    string title;
    float color;
    bool isSelected;
    bool isDraw;
    
	void setup() {
		enableMouseEvents();
		enableKeyEvents();
        
        font.load("fonts/PlainMed", 12);
	}
	
	void exit() {
	}
	
	
	void update() {
	}
	
	void draw() {
        
        if (isDraw) {
            
            if (isSelected) color = ofLerp(color, 255, 0.2);
            else color = ofLerp(color, 225, 0.2);
            
            ofSetColor(color);
            ofDrawRectangle(x, y, width, height);
            
            ofSetColor(0);
            font.drawString(title, x + 10, y + 20);
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