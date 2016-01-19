//
//  Location.h
//  Cove
//
//  Created by Chris Mullany on 18/01/2016.
//
//

#pragma once
#include "ofMain.h"

class Location {
public:
    Location();
    
	void setup(string title);
	void update();
	void draw(ofCamera& cam);
    void draw2d();
    
    float getLon();
    float getLat();
    
    ofPoint latlon;
    ofPoint position;
    string title;
    bool isActive;
    bool hasLabel;
    float percentOpen;
    ofTrueTypeFont* titleFont;
    
    ofShader billboardShader;
    ofFbo fbo;
    
    ofImage labelImage;
    ofImage contentImage;
    
    int index;
    float routePercent;
    
    ofVec3f camRotation;
    float camDistance;

protected:  
private:
    
};