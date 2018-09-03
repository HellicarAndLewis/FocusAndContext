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
    void draw(ofVec3f meshPosition);
    void draw2d();
    void flushData();
    
    void setLocationMouseFlip(bool _flip);
    
    void setCamera(ofCamera* _cam) {
        cam = _cam;
        
    };
    
    void loadLeft(string path, ofVec3f posOffset);
    void loadRight(string path, ofVec3f posOffset);
    vector<Location*> getLeftPOIs();
    vector<Location*> getRightPOIs();
    Location* getLocation();
    ofPoint getPosition(bool doInvert = false);
    void AddListenersToLocations();
    
    int zoomLevel;
	
    
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
    float alphaLeft;
    float alphaRight;
    bool isAlpha;
    
    ofParameter<float> latRange;
    ofParameter<float> lonRange;

protected:  
private:
    
    void populateLocationsLeft();
    void populateLocationsRight();
    
    string folderPath;
    ofxXmlSettings xml;
    ofImage contentImages[5];
    ofCamera* cam;
    
};
