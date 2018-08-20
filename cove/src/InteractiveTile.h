//
//  InteractiveTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef InteractiveTile_h
#define InteractiveTile_h

#include "ofMain.h"

//#include "ofxMSAInteractiveObject.h"

class InteractiveTile {
public:
    enum Anim {expandFromMain = 0, collapseToMain = 1, expandFromLocation = 2, collapseToLocation = 3};
    
    struct animation {
        vector<ofVec2f> positions;
        float easing;
        int posIndex;
        vector< InteractiveTile* > objectsToCheckBeforeStarting;
    };
    
    InteractiveTile* parentTile = nullptr;
    
    ofTrueTypeFont fontMain;
    ofTrueTypeFont fontSub;
    string title;
    string subText;
    float color;
    ofColor debugColor;
    float alpha;
    bool isSelected;
    bool isDraw;
    bool fadeLabel;
    bool isAnimating;
    ofImage image;
    
    float x, y, width, height;
    
    int animIndex;
    vector< animation > animations;
    
    void setup() {
        ofAddListener(ofEvents().mousePressed, this, &InteractiveTile::_mousePressed);
        
        // set default color to darkened white
        color = 240;
        
        // Load the title of this content as an image.
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
//        objectsToCheck.push_back(this);
    }
    
    // Return true if the interactive object is near where it should be;
    bool isNearPosition() {
        vector<ofVec2f> positions = animations[animIndex].positions;
        if(positions.size() > 0) {
            float f = ofDist(x, y, positions[animations[animIndex].posIndex].x, positions[animations[animIndex].posIndex].y);
            return (f < 0.5);
        } else {
            return true;
        }
    }
    
    bool isInFinalPosition() {
        vector<ofVec2f> positions = animations[animIndex].positions;
        if(positions.size() > 0) {
            float f = ofDist(x, y, positions[positions.size()-1].x, positions[positions.size()-1].y);
            return (f < 0.5);
        } else {
            return true;
        }
    }
    
    // Set a list of objects whose animations should be checked. Don't move on to the next part of your animation until all these objects are in the correct position.
    void setObjectsToCheck(int animation, vector<InteractiveTile*> _objectsToCheck) {
        for(int i = 0; i < _objectsToCheck.size(); i++) {
            bool objectFound = false;
            for(int j = 0; j < animations[animation].objectsToCheckBeforeStarting.size(); j++) {
                if(animations[animation].objectsToCheckBeforeStarting[j] == _objectsToCheck[i]) {
                    objectFound = true;
                    break;
                }
            }
            if(!objectFound) {
                animations[animation].objectsToCheckBeforeStarting.push_back(_objectsToCheck[i]);
            }
        }
    }
    
    void set(float _x, float _y, float _w, float _h) {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
    }
    
    // Add an Animation Sequence to the list of animations.
    void addAnimation(vector<ofVec2f> positions, float easing) {
        animation anim;
        anim.positions = positions;
        anim.easing = easing;
        anim.posIndex = 0;
        animations.push_back(anim);
    }
    
    
    // Draw this tile
    void draw() {
        ofPushMatrix();
        float newX = x;
        float newY = y;
        if(parentTile != nullptr) {
            if(parentTile->parentTile != nullptr) {
                newX += parentTile->parentTile->x;
                newY += parentTile->parentTile->y;
            }
            newX += parentTile->x;
            newY += parentTile->y;
        }
        ofSetColor(debugColor);
        ofDrawRectangle(newX, newY, width, height);
        ofPopMatrix();
    }
    
    // Set the animation state and reset all animation positions to 0
    void setAnimation(int i) {
        animIndex = i;

        if(!isInFinalPosition()) {
            isAnimating = true;
            for(int i = 0; i < animations.size(); i++) {
                animations[i].posIndex = 0;
            }
        }


    }
    
    // Update performs the transforms of the animations and steps through positions withint the current animation state.
    void update() {
        if(animations.size() > 0) {
            bool allObjectsInPosition = true;
            for(int i = 0; i < animations[animIndex].objectsToCheckBeforeStarting.size(); i++) {
                if(animations[animIndex].objectsToCheckBeforeStarting[i]->isAnimating) {
                    allObjectsInPosition = false;
                    break;
                }
            }
            
            if(!isAnimating && allObjectsInPosition) {
                isAnimating = true;
            } else if(isAnimating && !allObjectsInPosition) {
                isAnimating = false;
            }

            if(isAnimating) {
                if(animations[animIndex].posIndex < animations[animIndex].positions.size()-1) {
                    if(isNearPosition()) {
                        animations[animIndex].posIndex++;
                    }
                }
              else {
                    isAnimating = false;
                }
                x = ofLerp(x, animations[animIndex].positions[animations[animIndex].posIndex].x, animations[animIndex].easing);
                y = ofLerp(y, animations[animIndex].positions[animations[animIndex].posIndex].y, animations[animIndex].easing);
            }
        }
    }
    
    //--------------------------------------------------------------
    void _mousePressed(ofMouseEventArgs &e) {
        int x = e.x;
        int y = e.y;
#ifdef TOUCH_ENABLED
        //HORRIBLE HACK JB 23/3/16
        /* HACK AREA */
        float xPercentage = (float)(e.x) / (float)(1080);
        float yPercentage = (float)(e.y) / (float)1920;
        x = 1080 - 1080 * yPercentage;
        y = 1920 * xPercentage;
        /* HACK AREA */
        // I'M SO SORRY!
#endif
        int button = e.button;
                
        if(hitTest(x, y)) {                        // if mouse is over
            onPress(x, y, button);                    // call onPress
        }
    }
    
    //--------------------------------------------------------------
    bool hitTest(int tx, int ty) const {
        float newX = x;
        float newY = y;
        if(parentTile != nullptr) {
            if(parentTile->parentTile != nullptr) {
                newX += parentTile->parentTile->x;
                newY += parentTile->parentTile->y;
            }
            newX += parentTile->x;
            newY += parentTile->y;
        }
        return ((tx > newX) && (tx < newX + width) && (ty > newY) && (ty < newY + height));
    }
    
    // Do something when pressed
    virtual void onPress(int x, int y, int button) {
        cout<<"Tile Pressed!"<<endl;
    }
    
};

#endif
