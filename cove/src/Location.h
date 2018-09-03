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
	void draw(ofVec3f meshPosition, float _alpha, float _height);
    void draw2d();
    void setCamera(ofCamera* _cam) { cam = _cam; };
    void _mousePressed(ofMouseEventArgs &e);
    
    float getLon();
    float getLat();
    
    ofPoint latlon;
    ofPoint position;
    ofPoint tilePos;
    string title;
    bool flipMouseInput;
    bool isActive;
    bool hasLabel;
    bool isAlpha;
    bool isAlphaLabel;
    float percentOpen;
    float percentOpenLabelLeft;
    float percentOpenLabelRight;
    float alphaTarget;
    float alpha;
    float size;
    float lineHeight;
    float length;
    float height;
    int project;
    float verticalOffset;
    float verticalOffsetSaved;
    ofTrueTypeFont* titleFont;
    
    ofEvent<string> onLabelClicked;
    
    ofVec3f transformedP1;
    ofVec3f transformedP2;

    ofShader billboardShader;
    ofFbo fbo;
    
    ofImage labelImage;
    ofImage contentImage;
    vector<ofImage*> contentImages;
    
    int index;
    float routePercent;
    
    ofVec3f camRotation;
    ofVec3f meshPosition;
    ofCamera* cam;
    float camDistance;

protected:  
private:
    
};
