//
//  InteractiveMenu.h
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 16/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "InteractiveObject.h"

#define		BUTTON_AMT		5

class InteractiveMenu
{
public:
    void setup(float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut);
    void update();
    void drawLines();
    void transform();
    void pressed();
    
    InteractiveObject objLeftLine;
    InteractiveObject objRightLine;
    InteractiveObject objsLeft[BUTTON_AMT];
    InteractiveObject objsRight[BUTTON_AMT];
    InteractiveObject objLeft;
    InteractiveObject objRight;
    
    ofVec2f posLeft[BUTTON_AMT];
    ofVec2f posRight[BUTTON_AMT];
    float sizeLeft[BUTTON_AMT];
    float sizeRight[BUTTON_AMT];
    
    bool bLeftActive[BUTTON_AMT];
    bool bRightActive[BUTTON_AMT];
    bool leftOn;
    bool rightOn;
    bool buttonClicked;
    int length;
    float mainArea;
    float subArea;
    float areaDiff;
    float padding;
    float easeIn;
    float easeOut;
};
