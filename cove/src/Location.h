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
	void draw();
    
    float getLon();
    float getLat();
    
    ofPoint latlon;
    ofPoint position;
    string title;
    bool isActive;
    float percentOpen;
    ofTrueTypeFont* titleFont;
    
    ofVboMesh billboards;
    ofShader billboardShader;
    ofFbo fbo;
    
    int index;
    float routePercent;

protected:  
private:
    
};