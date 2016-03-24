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
#include "ofxFBX.h"
#include "ofxNestedFileLoader.h"

class Content
{
public:
    void setup();
    void fileLocation();
    void update();
    void scaling();
    void draw();
    void load(int _project, int _point, int _item);
    void stopVideos();
    void stopAudio();
    
    // content locations
    string path[2][5][5];
    
    // content type
    ofImage img[5];
    ofImage backgroundImage;
    ofImage titleTextImage[2][5][5];
    ofImage captionTextImage[2][5][5];
    ofVideoPlayer vid[2][5];
    ofSoundPlayer sound[2][5];
    //ofxOBJModel model;
    
    ofxFBXScene scene;
    ofEasyCam cam;
    ofxFBXManager model;
        
    ofLight light;
    
    //ofEasyCam cam;
    float camZoom;
    float camMinZoom;
    float camMaxZoom;
    float camXaxis;
    
    float scale[5];
    float screenWidth;
    
    //Dictionary of locations, 1 is hs1 2 is crossrail, pair the index of the location with the name of the file that it's content is stored in and the name of the content type and the index it is stored in in the paths array
    static const vector<map<string, int>> locationsDictionary;
    
    static vector<map<string, int>> createMaps() {
        //Final vector to return
        vector<map<string, int>> finalVector;
        
        //Create HS1 map
        map<string, int> hs1;
        hs1["StPancras"] = 0;
        hs1["StratfordInternational"] = 1;
        hs1["EbbsfleetInternational"] = 2;
        hs1["MedwayViaduct"] = 3;
        hs1["AshfordInternational"] = 4;
        hs1["Text"] = 0;
        hs1["Image"] = 1;
        hs1["Video"] = 2;
        hs1["3dModel"] = 3;
        hs1["Audio"] = 4;
        finalVector.push_back(hs1);
        
        //Create crossrail map
        map<string, int> crossrail;
        crossrail["Soho"] = 0;
        crossrail["CanaryWharf"] = 1;
        crossrail["LiverpoolStreet"] = 2;
        crossrail["Barbican"] = 3;
        crossrail["TottenhamCourtRoad"] = 4;
        crossrail["Text"] = 4;
        crossrail["Image"] = 3;
        crossrail["Video"] = 2;
        crossrail["3dModel"] = 1;
        crossrail["Audio"] = 0;
        finalVector.push_back(crossrail);
        
        return finalVector;
    }
    
    int project;
    int point;
    int item;
    
    bool loadData;
    bool clear;
};
