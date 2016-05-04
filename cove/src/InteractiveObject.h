//
//  InteractiveObject.h
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 21/02/2016.
//  Last edited by James Bentley on 28/04/2016.
//
//

#pragma once

#include "ofxMSAInteractiveObject.h"
#include "ofxNestedFileLoader.h"

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
    ofImage image;
    
    void setup()
    {
        enableMouseEvents();
        enableKeyEvents();
        
        // default color is darkened white
        color = 240;
        
        ofxNestedFileLoader loader;
        string location = "content/Google Drive/Arup/Research/Content/" + title + "/MenuButton";
        vector<string> path = loader.load(location);

        if(path.size() > 0) {
            for(int i = 0; i < path.size(); i++) {
                vector<string> stringSplit = ofSplitString(path[i], "/");
                if( !(stringSplit[stringSplit.size()-1] == "Icon\r") ) {
                    image.load(path[i]);
                    break;
                }
            }
        } else {
            image.load("content/Google Drive/Arup/Research/Content/Placeholder/no_data.png");
        }
    }
    
    void exit() {
    }
    
    
    void update() {
    }
    
    void draw() {
        
        if (isDraw) {
            switch (drawType) {
                case 0: //Tiles
                    // when selected, lerp to white
                    if (isSelected) color = ofLerp(color, 255, 0.2);
                    else color = ofLerp(color, 240, 0.2);
                    
                    ofSetColor(color);
                    ofDrawRectRounded(x, y, width, height, 10);
                    
                    // fades content titles
                    if (fadeLabel) alpha = ofLerp(alpha, 0, 0.1);
                    else alpha = ofLerp(alpha, 255, 0.2);
                    //ofSetColor(255);
                    ofSetColor(255, alpha);
                    // draws menu tiles
                    image.draw(x, y, width, height);
                    break;
                    
                case 1:
                    // left menu line
                    // line thickness
                    ofSetLineWidth(3);
                    // menu line color
                    ofSetColor(255, 130, 0);
                    ofDrawLine(x, y+height/2, x+lineLength, y+height/2);
                    break;
                    
                case 2:
                    // right menu line
                    // line thickness
                    ofSetLineWidth(3);
                    // menu line color
                    ofSetColor(255, 130, 0);
                    ofDrawLine(x-lineLength, y+height/2, x, y+height/2);
                    break;
                    
                case 3:
                    // vertical content menu line
                    // line thickness
                    ofSetLineWidth(3);
                    // menu line color
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