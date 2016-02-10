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
    ofPoint tilePos;
    string title;
    bool isActive;
    bool hasLabel;
    bool isAlpha;
    bool isAlphaLabel;
    float percentOpen;
    float percentOpenLabel;
    float alphaTarget;
    ofTrueTypeFont* titleFont;
    
    ofShader billboardShader;
    ofFbo fbo;
    
    ofImage labelImage;
    ofImage contentImage;
    vector<ofImage*> contentImages;
    
    int index;
    float routePercent;
    
    ofVec3f camRotation;
    float camDistance;

protected:  
private:
    
};