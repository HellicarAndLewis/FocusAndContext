//
//  Scrollable.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//
#pragma once
#include "Interactive.h"

namespace IFS {
    class Scrollable : public Interactive {
    public:
        Scrollable() {
            isScrolling = false;
            scrollX = true;
            scrollY = false;
            isScrollWhenPressed = false;
            vel.set(0);
            pos.set(0);
            ppos.set(0);
            acc.set(0);
            value.set(0);
            rectSize.set(30);
            damping = 0.9;
            velMax = 100;
            accMax = 50;
        }
        
        float getValue() {
            return value.x;
        }
        
        void scrollTo(float percent) {
            value.x = percent;
            rect.x = percent * (bounds.getRight()-rect.width);
        }
        
        void setup() {
            rect.set(0, ofGetHeight()-rectSize.y, rectSize.x, rectSize.y);
            bounds.set(0, 0, ofGetWidth(), ofGetHeight());
            enable();
        }
        
        void update() {
            if(!isScrolling) {
                acc.limit(accMax);
                vel += acc;
                vel.limit(velMax);
                if(scrollX && fabs(vel.x) > 1.0) rect.x += floor(vel.x);
                if(scrollY && fabs(vel.y) > 1.0) rect.y += floor(vel.y);
                vel *= damping;
                acc.set(0);
            }
            // bounds check
            if (rect.x < bounds.x) rect.x = bounds.x;
            else if (rect.x > bounds.getRight()-rect.width) rect.x = bounds.getRight()-rect.width;
            // normalised value
            value.x = rect.x / (bounds.getRight()-rect.width);
        }
        
        void draw() {
            ofSetColor(20);
            ofDrawRectangle(0, ofGetHeight()-rectSize.y, bounds.width, rectSize.y);
            ofSetColor(80);
            float rad = rectSize.y * 0.5;
            for (auto tick: ticks) {
                ofDrawCircle(bounds.width * tick, ofGetHeight()-rad, rad);
            }
            ofSetColor(240,0,0);
            ofDrawRectangle(rect);
            ofSetColor(255);
        }
        
        void exit() {
            
        }
        
        
        float damping;
        float velMax, accMax;
        bool isScrollWhenPressed;
        bool isScrolling;
        vector<float> ticks;
        
    protected:
        
        // mouse events //////////////////////////////////////////////////////////////////////////
        
        void mouseDragged(int x, int y, int button) {
            //ofLogVerbose() << "Scrollable::mouseDragged x:" << x << " y:" << y;
            if(isScrolling != true) {
                isScrolling = true;
                ppos = ofPoint(x,y);
                vel.set(0,0);
            }
            else {
                pos = ofPoint(x, y);
                vel = pos-ppos;
                if(scrollX) rect.x +=vel.x;
                if(scrollY) rect.y +=vel.y;
                ppos = pos;
            }
        }
        
        void mousePressed(int x, int y, int button) {
            isScrolling = false;
            vel.set(0,0);
        }
        
        void mouseReleased(int x, int y, int button) {
            if(isScrolling) {
                isScrolling = false;
                pos = ofPoint(x,y);
            }
        }
        
        
        // touch events //////////////////////////////////////////////////////////////////////////
        
        void touchDown(ofTouchEventArgs& touch) {
            isScrolling = false;
            vel.set(0);
        }
        
        void touchMoved(ofTouchEventArgs& touch) {
            if(isScrolling != true) {
                isScrolling = true;
                ppos = ofPoint(touch.x,touch.y);
                vel.set(0);
            }
            else {
                pos = ofPoint(touch.x, touch.y);
                vel = pos-ppos;
                if(scrollX) rect.x +=vel.x;
                if(scrollY) rect.y +=vel.y;
                ppos = pos;
            }
        }
        
        void touchUp(ofTouchEventArgs& touch) {
            if(isScrolling) {
                isScrolling = false;
                pos = ofPoint(touch.x,touch.y);
            }
        }
        
        void touchCancelled(ofTouchEventArgs& touch) {
            if(isScrolling) {
                isScrolling = false;
                pos = ofPoint(touch.x,touch.y);
            }
        }
        
    private:
        
        ofRectangle rect;
        ofRectangle bounds;
        
        bool scrollX, scrollY;
        
        ofPoint pos;
        ofPoint ppos;
        ofPoint vel;
        ofPoint acc;
        ofPoint value;
        ofPoint rectSize;
        
        
    };
}