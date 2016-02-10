//
//  Route.h
//  Cove
//
//  Created by Chris Mullany on 19/01/2016.
//  Edited by Jason Walters on 5/02/2016.
//
//

#pragma once
#include "ofMain.h"
#include "Location.h"
#include "ofxXmlSettings.h"

class Route {
public:
    Route();
    
    void setup();
    void update(float percent = -1);
    void draw(ofCamera& cam);
    void draw2d();
    void flushData();
    
    void load(string path, ofVec3f posOffset);
    Location* getLocation();
    ofPoint getPosition(bool doInvert = false);
	
    
    ofTrueTypeFont titleFont;
    vector<Location> locations;
    ofPolyline route, routeInverse, routeRender;
    
    
    Location* activeLocation;
    int activeIndex;
    float percentToActive;
    float percent;
    float length;
    float locationThreshold;
    bool isAlpha;
    
    ofParameter<float> latRange;
    ofParameter<float> lonRange;

protected:  
private:
    
    void populateLocations();
    
    string folderPath;
    ofxXmlSettings xml;
    ofImage contentImages[5];
    
};