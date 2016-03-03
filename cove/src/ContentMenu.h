//
//  ContentMenu.h
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 3/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ContentObject.h"
#include "InteractiveMenu.h"

#define     POI             5
#define		CONTENT_AMT		5

class ContentMenu
{
public:
    void setup(int _w, int _h, float _area, float _padding);
    void update();
    void draw(int _project, int _point, bool _draw);
    void transform();
    void pressed();

    ContentObject contentLeft[POI][CONTENT_AMT];
    ContentObject contentRight[POI][CONTENT_AMT];
    
    ofVec2f posLeft[POI][CONTENT_AMT];
    ofVec2f posRight[POI][CONTENT_AMT];
    
    bool bLeftActive[POI][CONTENT_AMT];
    bool bRightActive[POI][CONTENT_AMT];
    
    bool leftOn;
    bool rightOn;
    bool buttonClicked;
    int width;
    int height;
    float area;
    float padding;
    
    InteractiveMenu menu;
};