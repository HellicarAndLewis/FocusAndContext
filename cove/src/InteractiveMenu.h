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
//#include "InteractiveObject.h"
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
    void setTilePositionsLandscape();
    void setTilePositionsPortrait();
    void setupTiles(vector<InteractiveTile*> allInteractiveTiles);
    void setTileTitlesAndContent();
    vector<InteractiveTile*> initializeTiles();
    void setFlipMouseInput(bool _flip);
    void update();
    void drawMenu();
    void drawContent();

    void onLabelClicked(string & title);
    void onMainButtonClicked(string & title);
    void activateLeftContent(int locationIndex, int contentIndex);
    void activateRightContent(int locationIndex, int contentIndex);
    void activateLeftLocation(int index);
    void activateRightLocation(int index);
    
    ofxFontStash titleFont;
    
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
