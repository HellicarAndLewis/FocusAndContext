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

class InteractiveTile {
public:
    InteractiveTile* parentTile = nullptr;
    
    vector<InteractiveTile*> allTiles;
    vector<InteractiveTile*> tilesToDrawLinesTo;

    ofVec2f size;
    ofVec2f sizeTarget;
    float textWidth;
    float textBuffer;
    
    ofxFontStash* font;
    Content* c;

    ofVec2f position;
    ofVec2f target;
    string title;
    
    ofSoundPlayer* sound;
    
    int animationStep = -1;
    
    ofColor color;
    ofColor colorTarget;
    
    bool flipMouseInput;
    
    void setup() {
        ofAddListener(ofEvents().mousePressed, this, &InteractiveTile::_mousePressed);
        
        // set default color to darkened white
        color = ofColor(240);
        colorTarget = ofColor(240);
        
        textWidth = size.x;
        
        textBuffer = ofGetWidth() * 8.0 / 1920.;
        
        flipMouseInput = false;
    }
    
    // Return true if the interactive object is near where it should be;
    bool isNearTarget() {
        if(ofDist(position.x, position.y, target.x, target.y) < 0.5) {
            return true;
        }
        return false;
    }
    
    bool isNearSizeTarget() {
        if(ofDist(size.x, size.y, sizeTarget.x, sizeTarget.y) < 0.5) {
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
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofDrawRectRounded(newX, newY, size.x, size.y, 10);
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofSetColor(0);
        int numLines;
        string test = "A";
        ofRectangle r = font->drawMultiLineColumn(test, 12, newX - size.x/2 + textBuffer, newY - size.y/2 + textBuffer, textWidth - textBuffer*2
                                                , numLines, true);
        font->drawMultiLineColumn(title, 12, newX - size.x/2 + textBuffer, newY - size.y/2 + r.height + textBuffer, textWidth - textBuffer*2, numLines);
        ofPopMatrix();
    }
    
    void drawLines() {
        for(int i = 0; i < tilesToDrawLinesTo.size(); i++) {
            ofSetLineWidth(3);
            ofSetColor(255, 130, 0);
            ofVec2f me = ofVec2f(position.x, position.y);
            ofVec2f other = ofVec2f(tilesToDrawLinesTo[i]->position.x, tilesToDrawLinesTo[i]->position.y);
            float newX = me.x;
            float newY = me.y;
            if(parentTile != nullptr) {
                if(parentTile->parentTile != nullptr) {
                    newX += parentTile->parentTile->position.x;
                    newY += parentTile->parentTile->position.y;
                }
                newX += parentTile->position.x;
                newY += parentTile->position.y;
            }
            me.x = newX;
            me.y = newY;
            
            newX = other.x;
            newY = other.y;
            InteractiveTile* otherParentTile = tilesToDrawLinesTo[i]->parentTile;
            if(otherParentTile != nullptr) {
                if(otherParentTile->parentTile != nullptr) {
                    newX += otherParentTile->parentTile->position.x;
                    newY += otherParentTile->parentTile->position.y;
                }
                newX += otherParentTile->position.x;
                newY += otherParentTile->position.y;
            }
            other.x = newX;
            other.y = newY;

            ofDrawLine(me.x, me.y, other.x, other.y);
        }
    }
    
    // Update performs the transforms of the animations and steps through positions withint the current animation state.
    void update(float easing) {
        if(animationStep == 3) {
            cout<<"Anim Step 3!"<<endl;
        }
        position.x = ofLerp(position.x, target.x, easing);
        position.y = ofLerp(position.y, target.y, easing);
        size.x = ofLerp(size.x, sizeTarget.x, easing);
        size.y = ofLerp(size.y, sizeTarget.y, easing);
        color = color.lerp(colorTarget, easing);
    }
    
    //--------------------------------------------------------------
    void _mousePressed(ofMouseEventArgs &e) {
        int x = e.x;
        int y = e.y;
        int button = e.button;
        
        if(flipMouseInput) { // Only use this in portrait mode!
            float xPercentage = (float)(e.x) / (float)(1080);
            float yPercentage = (float)(e.y) / (float)1920;
            x = 1080 - 1080 * yPercentage;
            y = 1920 * xPercentage;
        }
        
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
        return ((tx > newX - size.x/2) && (tx < newX + size.x/2) && (ty > newY-size.y/2) && (ty < newY + size.y/2));
    }
    
    // Do something when pressed
    virtual void onPress(int x, int y, int button) {
        cout<<"Tile Pressed!"<<endl;
    }
};

#endif
