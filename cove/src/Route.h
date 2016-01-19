//
//  Route.h
//  Cove
//
//  Created by Chris Mullany on 19/01/2016.
//
//

#pragma once
#include "ofMain.h"
#include "Location.h"

class Route {
public:
    Route();
    
    void setup();
    void update(float percent = -1);
	void draw();
    
    void load(string path, ofVec3f posOffset);
    Location* getLocation();
    ofPoint getPosition(bool doInvert = false);
	
    
    ofTrueTypeFont titleFont;
    vector<Location> locations;
    ofPolyline route, routeInverse;
    
    
    Location* activeLocation;
    int activeIndex;
    float percentToActive;
    float percent;
    float length;

protected:  
private:
};