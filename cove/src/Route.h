//
//  Route.h
//  Cove
//
//  Created by Chris Mullany on 19/01/2016.
//  Edited by Jason Walters on 15/02/2016.
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
    
    void loadLeft(string path, ofVec3f posOffset);
    void loadRight(string path, ofVec3f posOffset);
    Location* getLocation();
    ofPoint getPosition(bool doInvert = false);
	
    
    ofTrueTypeFont titleFont;
    vector<Location> locationsLeft;
    vector<Location> locationsRight;
    ofPolyline routeLeft, routeInverseLeft, routeRenderLeft;
    ofPolyline routeRight, routeInverseRight, routeRenderRight;
    
    
    Location* activeLocation;
    int activeProject;
    int activeIndex;
    float percentToActive;
    float percent;
    float length;
    float locationThreshold;
    bool isAlpha;
    bool isAlphaLabel;
    
    ofParameter<float> latRange;
    ofParameter<float> lonRange;

protected:  
private:
    
    void populateLocationsLeft();
    void populateLocationsRight();
    
    string folderPath;
    ofxXmlSettings xml;
    ofImage contentImages[5];
    
};