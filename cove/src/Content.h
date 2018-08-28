//
//  Content.h
//  Cove
//
//  Created by Jason Walters on 10/03/2016.
//  Last edited by Jason Walters on 10/03/2016.
//  Last edited by James Bentley on 28/04/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxFBX.h"
#include "ofxNestedFileLoader.h"
#include "Playhead.h"
#include "Displayer.h"
#include "ofxFontStash.h"
#include "ofxXMLSettings.h"

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
    void stopLocationAudio();
    
    // content locations
    // string path[2][5][5][3];
    string introSoundPaths[2][5];
    
    // content type
    ofImage img[5];
    ofImage backgroundImage;
    ofImage titleTextImage[5];
    ofImage captionTextImage[5];
    ofVideoPlayer vid[2][5];
    ofSoundPlayer sound[2][5];
    ofSoundPlayer introSounds[2][5];
    //ofxOBJModel model;
    
    ofImage backgroundImage169;
    ofImage backgroundImageAudio;
    ofImage backgroundImage43;
    ofImage backgroundImage65;
    ofImage spinMeImage;
    
    map<string, vector<ContentDisplayer*> > hs1Displayers;
    map<string, vector<ContentDisplayer*> > crossrailDisplayers;
    
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
    float maxScale;
    float titleAndCaptionAlpha[5];
    float screenWidth;
    
    bool isAnythingPlaying;
        
    // Object for drawing the audio and video duration
    Playhead playhead;
    
    // Dictionary of locations, 1 is hs1 2 is crossrail, pair the index of the location with the name of the file that it's content is stored in and the name of the content type and the index it is stored in in the paths array
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
        hs1["Content"] = 0;
        hs1["Title"] = 1;
        hs1["Background"] = 2;
        finalVector.push_back(hs1);
        
        //Create crossrail map
        map<string, int> crossrail;
        crossrail["CanaryWharf"] = 0;
        crossrail["LiverpoolStreet"] = 1;
        crossrail["Barbican"] = 2;
        crossrail["TottenhamCourtRoad"] = 3;
        crossrail["Soho"] = 4;
        crossrail["Text"] = 4;
        crossrail["Image"] = 3;
        crossrail["Video"] = 2;
        crossrail["3dModel"] = 1;
        crossrail["Audio"] = 0;
        crossrail["Content"] = 0;
        crossrail["Title"] = 1;
        crossrail["Background"] = 2;
        finalVector.push_back(crossrail);
        
        return finalVector;
    }
    
    ofxFontStash titleFont;
    ofxFontStash textFont;
    ofxFontStash sourceFont;

    
    int project;
    int point;
    int item;
    
    bool loadData;
    bool clear;
};
