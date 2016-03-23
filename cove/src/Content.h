//
//  Content.h
//  Cove
//
//  Created by Jason Walters on 10/03/2016.
//  Last edited by Jason Walters on 10/03/2016.
//
//

#pragma once

#include "ofMain.h"
//#include "ofxOBJModel.h"
#include "ofxFBX.h"

class Content
{
public:
    void setup();
    void fileLocation();
    void update();
    void scaling();
    void draw();
    void load(int _project, int _point, int _item);
    void stop();
    
    // content locations
    string path[2][5][5];
    
    // content type
    ofImage img[5];
    ofVideoPlayer vid[2][5];
    //ofxOBJModel model;
    
    ofxFBXScene scene;
    ofEasyCam cam;
    ofxFBXManager model;
    
    ofLight light;
    
    //ofEasyCam cam;
    float camZoom;
    float camXaxis;
    
    float scale[5];
    float screenWidth;
    
    int project;
    int point;
    int item;
    
    bool loadData;
    bool clear;
};
