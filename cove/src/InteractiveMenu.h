//
//  InteractiveMenu.h
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 8/03/2016.
//  Last edited by James Bentley on 28/04/2016.
//
//

#pragma once

#include "ofMain.h"
#include "InteractiveObject.h"
#include "Content.h"
#include "Location.h"
#include "ofxFontStash.h"

#include "MainTile.h"
#include "LocationTile.h"
#include "ContentTile.h"



#define		BUTTON_AMT		5

class InteractiveMenu
{
public:
    void setup(int _w, int _h, float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut, vector<Location*> _lLocations, vector<Location*> _rLocations);
    void setupLeftContent();
    void setupRightContent();
    void update();
    void drawMenu();
    void drawContentMenu();
    void drawContent();

    void onLabelClicked(string & title);
    void onMainButtonClicked(string & title);
    void activateLeftContent(int locationIndex, int contentIndex);
    void activateRightContent(int locationIndex, int contentIndex);
    void activateLeftLocation(int index);
    void activateRightLocation(int index);
    bool otherLeftHLinesAreInactive(int index);
    bool otherRightHLinesAreInactive(int index);
    
    ofxFontStash titleFont;
    
    // content menu right
    InteractiveObject rConHLines[BUTTON_AMT];
    InteractiveObject rConVLines[BUTTON_AMT];
    InteractiveObject rCon[BUTTON_AMT][BUTTON_AMT];
    
    // content menu left
    InteractiveObject lConHLines[BUTTON_AMT];
    InteractiveObject lConVLines[BUTTON_AMT];
    InteractiveObject lCon[BUTTON_AMT][BUTTON_AMT];
    
    // main menu stuff
    InteractiveObject lLine;
    InteractiveObject rLine;
    InteractiveObject lPoints[BUTTON_AMT];
    InteractiveObject rPoints[BUTTON_AMT];
    InteractiveObject leftMain;
    InteractiveObject rightMain;
    
    // interactive location tiles for left (ie HS1)
    vector< LocationTile* > hs1LocationTiles;
    vector< LocationTile* > crossrailLocationTiles;
    MainTile* hs1MainTile;
    MainTile* crossrailMainTile;
    vector< vector<ContentTile*> > hs1ContentTiles;
    vector< vector<ContentTile*> > crossrailContentTiles;
    
    bool loadHs1;
    bool loadCrossrail;
        
    // location labels
    Location* lLocations[BUTTON_AMT];
    Location* rLocations[BUTTON_AMT];
    
    bool bLLineH[BUTTON_AMT];
    bool bRLineH[BUTTON_AMT];
    bool bLPlace[BUTTON_AMT];
    bool bRPlace[BUTTON_AMT];
    string contentLLabels[BUTTON_AMT][BUTTON_AMT];
    string contentRLabels[BUTTON_AMT][BUTTON_AMT];
    
    // left content positions and sizes
    ofVec2f posLCon[BUTTON_AMT][BUTTON_AMT];
    float sizeLCon[BUTTON_AMT][BUTTON_AMT];
    
    // right content positions and sizes
    ofVec2f posRCon[BUTTON_AMT][BUTTON_AMT];
    float sizeRCon[BUTTON_AMT][BUTTON_AMT];
    
    //amalgam of all the Con objects
    vector<InteractiveObject*> allCons;
    
    // main menu positions and sizes
    ofVec2f posLeft[BUTTON_AMT];
    ofVec2f posRight[BUTTON_AMT];
    float sizeLeft[BUTTON_AMT];
    float sizeRight[BUTTON_AMT];
    
    // variables
    bool bLeftActive[BUTTON_AMT];
    bool bRightActive[BUTTON_AMT];
    bool leftOn, rightOn;
    bool leftSwitch, rightSwitch;
    bool leftClose, rightClose;
    bool buttonClicked;
    int length;
    int width;
    int height;
    float mainArea;
    float subArea;
    float areaDiff;
    float padding;
    float easeIn;
    float easeOut;
    float paddingVertical;
    float contentHeight;
    
    // content media system
    Content c;
    
    bool leftWasOn;
    
    float lastPressTime;
    
    // menu button sounds
    ofSoundPlayer snd1;
    ofSoundPlayer snd2;
    
    //HS! and cross-rail intro sounds
    ofSoundPlayer hs1Intro;
    ofSoundPlayer crossrailIntro;
};
