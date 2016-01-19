//
//  LocalTile.h
//  Cove
//
//  Created by Chris Mullany on 15/01/2016.
//
//

#pragma once
#include "ofMain.h"
#include "ofxVectorTile.h"

// tile layers are:
//    "earth", _tile, 0.0);
//    "landuse", _tile, .1);
//    "water", _tile, .2);
//    "buildings", _tile, .3);
//    "places", _tile, .4);
//    "roads", _tile, .5);
//    "pois", _tile, .6);

struct LocalTile {
public:
    ofxVectorTile tile;
    ofVboMesh meshEarth;
    ofVboMesh meshBuildings;
    ofVboMesh meshRoads;
    ofVboMesh meshWater;
    
    int x = 0;
    int y = 0;
    int zoom = 0;
    string fileName;
    bool isValid = false;
    
    LocalTile(string fileName, string delimiter = "-") {
        this->fileName = fileName;
        auto tokens = ofSplitString(fileName, delimiter);
        if (tokens.size() == 3) {
            zoom = ofToInt(tokens[0]);
            x = ofToInt(tokens[1]);
            y = ofToInt(tokens[2]);
            isValid = true;
        }
        else {
            ofLogError() << "in LocalTile, " << fileName << " is not in the expected tile name format of zoom-x-y.json";
        }
    }
};