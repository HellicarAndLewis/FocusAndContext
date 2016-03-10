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
#include "ofxOBJModel.h"

#define     POI             5
#define		CONTENT_AMT		5

class Content
{
public:
    void setup(int _w, int _h, float _area, float _padding);
    void update();
    void draw(int _project, int _point, bool _draw);
    
    // content
    ofImage img[CONTENT_AMT];
};
