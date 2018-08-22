//
//  InteractiveTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef InteractiveTile_h
#define InteractiveTile_h

#include "ofMain.h"
#include "ofxFontStash.h"
//#include "ofxMSAInteractiveObject.h"

class InteractiveTile {
public:
    InteractiveTile* parentTile = nullptr;
    
    vector<InteractiveTile*> allTiles;
    
    ofVec2f size;
    
    ofxFontStash* font;
    Content* c;

    ofVec2f position;
    ofVec2f target;
    string title;
    
    int animationStep = -1;
    
    ofColor color;
    
    void setup() {
        ofAddListener(ofEvents().mousePressed, this, &InteractiveTile::_mousePressed);
        
        // set default color to darkened white
        color = ofColor(240);
        
        title = "Test Test Test";
    }
    
    // Return true if the interactive object is near where it should be;
    bool isNearTarget() {
        if(ofDist(position.x, position.y, target.x, target.y) < 0.5) {
            return true;
        }
        return false;
    }
    
    // Draw this tile
    void draw() {
        ofPushMatrix();
        float newX = position.x;
        float newY = position.y;
        if(parentTile != nullptr) {
            if(parentTile->parentTile != nullptr) {
                newX += parentTile->parentTile->position.x;
                newY += parentTile->parentTile->position.y;
            }
            newX += parentTile->position.x;
            newY += parentTile->position.y;
        }
        ofSetColor(color);
        ofDrawRectRounded(newX, newY, size.x, size.y, 10);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetColor(0);
        int numLines;
        int textBuffer = 10;
        string test = "A";
        ofRectangle r = font->drawMultiLineColumn(test, 12, newX + textBuffer, newY + textBuffer, size.x - textBuffer, numLines, true);
        font->drawMultiLineColumn(title, 12, newX + textBuffer, newY + r.height + textBuffer, size.x - textBuffer, numLines);
        ofPopMatrix();
    }
    
    // Update performs the transforms of the animations and steps through positions withint the current animation state.
    void update(float easing) {
        position.x = ofLerp(position.x, target.x, easing);
        position.y = ofLerp(position.y, target.y, easing);

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
    
    void deactivateAllContent() {
        for(auto location = c->hs1Displayers.begin(); location != c->hs1Displayers.end(); location++) {
            for(auto content = location->second.begin(); content != location->second.end(); content++) {
                (*content)->setIsActive(false);
            }
        }
        for(auto location = c->crossrailDisplayers.begin(); location != c->crossrailDisplayers.end(); location++) {
            for(auto content = location->second.begin(); content != location->second.end(); content++) {
                (*content)->setIsActive(false);
            }
        }
    }
    
    //--------------------------------------------------------------
    bool hitTest(int tx, int ty) const {
        float newX = position.x;
        float newY = position.y;
        if(parentTile != nullptr) {
            if(parentTile->parentTile != nullptr) {
                newX += parentTile->parentTile->position.x;
                newY += parentTile->parentTile->position.y;
            }
            newX += parentTile->position.x;
            newY += parentTile->position.y;
        }
        return ((tx > newX) && (tx < newX + size.x) && (ty > newY) && (ty < newY + size.y));
    }
    
    // Do something when pressed
    virtual void onPress(int x, int y, int button) {
        cout<<"Tile Pressed!"<<endl;
    }
};

#endif
