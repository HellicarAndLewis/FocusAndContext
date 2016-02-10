//
//  InterestPoints.h
//  Cove
//
//  Created by Jason Walters on 7/02/2016.
//
//

#pragma once
#include "ofMain.h"

class InterestPoints {
public:
    
    string title;
    float lat = 0.0;
    float lon = 0.0;
    float distance = 0.0;
    ofVec3f rotation;
    
    InterestPoints();
    InterestPoints(string _title, float _lat, float _lon, float _distance, ofVec3f _rotation) {
        title = _title;
        lat = _lat;
        lon = _lon;
        distance = _distance;
        rotation = _rotation;
    }
};