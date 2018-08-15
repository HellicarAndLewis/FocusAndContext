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
    void transform();
    void onLabelClicked(string & title);
    void activateLeftContent(int index);
    void activateRightContent(int index);
    void activateLeftLocation(int index);
    void activateRightLocation(int index);
    void transformLeftContent0();
    void transformLeftContent1();
    void transformLeftContent2();
    void transformLeftContent3();
    void transformLeftContent4();
    void transformRightContent0();
    void transformRightContent1();
    void transformRightContent2();
    void transformRightContent3();
    void transformRightContent4();
    void pressedLocation();
    void pressedContent();
    
    // content menu right
    InteractiveObject rCon4HLine;
    InteractiveObject rCon4VLine;
    InteractiveObject rCon4[BUTTON_AMT];
    InteractiveObject rCon3HLine;
    InteractiveObject rCon3VLine;
    InteractiveObject rCon3[BUTTON_AMT];
    InteractiveObject rCon2HLine;
    InteractiveObject rCon2VLine;
    InteractiveObject rCon2[BUTTON_AMT];
    InteractiveObject rCon1HLine;
    InteractiveObject rCon1VLine;
    InteractiveObject rCon1[BUTTON_AMT];
    InteractiveObject rCon0HLine;
    InteractiveObject rCon0VLine;
    InteractiveObject rCon0[BUTTON_AMT];
    
    // content menu left
    InteractiveObject lCon4HLine;
    InteractiveObject lCon4VLine;
    InteractiveObject lCon4[BUTTON_AMT];
    InteractiveObject lCon3HLine;
    InteractiveObject lCon3VLine;
    InteractiveObject lCon3[BUTTON_AMT];
    InteractiveObject lCon2HLine;
    InteractiveObject lCon2VLine;
    InteractiveObject lCon2[BUTTON_AMT];
    InteractiveObject lCon1HLine;
    InteractiveObject lCon1VLine;
    InteractiveObject lCon1[BUTTON_AMT];
    InteractiveObject lCon0HLine;
    InteractiveObject lCon0VLine;
    InteractiveObject lCon0[BUTTON_AMT];
    
    // main menu stuff
    InteractiveObject lLine;
    InteractiveObject rLine;
    InteractiveObject lPoints[BUTTON_AMT];
    InteractiveObject rPoints[BUTTON_AMT];
    InteractiveObject leftMain;
    InteractiveObject rightMain;
    
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
    ofVec2f posLCon0[BUTTON_AMT];
    ofVec2f posLCon1[BUTTON_AMT];
    ofVec2f posLCon2[BUTTON_AMT];
    ofVec2f posLCon3[BUTTON_AMT];
    ofVec2f posLCon4[BUTTON_AMT];
    float sizeLCon0[BUTTON_AMT];
    float sizeLCon1[BUTTON_AMT];
    float sizeLCon2[BUTTON_AMT];
    float sizeLCon3[BUTTON_AMT];
    float sizeLCon4[BUTTON_AMT];
    
    // right content positions and sizes
    ofVec2f posRCon0[BUTTON_AMT];
    ofVec2f posRCon1[BUTTON_AMT];
    ofVec2f posRCon2[BUTTON_AMT];
    ofVec2f posRCon3[BUTTON_AMT];
    ofVec2f posRCon4[BUTTON_AMT];
    float sizeRCon0[BUTTON_AMT];
    float sizeRCon1[BUTTON_AMT];
    float sizeRCon2[BUTTON_AMT];
    float sizeRCon3[BUTTON_AMT];
    float sizeRCon4[BUTTON_AMT];
    
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
