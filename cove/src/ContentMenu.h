//
//  ContentMenu.h
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 21/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ContentObject.h"

#define     POINTS          5
#define		CONTENT_AMT		5

class ContentMenu
{
public:
    void setup(int _w, int _h, float _area, float _padding);
    void update();
    void draw(bool _draw);
    void transform();
    void pressed();

    ContentObject contentLeft[POINTS][CONTENT_AMT];
    ContentObject contentRight[POINTS][CONTENT_AMT];
    
    bool leftOn;
    bool rightOn;
    bool buttonClicked;
    int width;
    int height;
    float area;
    float padding;
};
