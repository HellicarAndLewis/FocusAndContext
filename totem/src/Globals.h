//
//  Globals.h
//  Cove
//
//  Created by Jason Walters on 3/03/2016.
//  Last edited by Jason Walters on 11/03/2016.
//
//

#pragma once

#include "ofMain.h"

class Globals
{
public:
    
    // content launch
    static bool buttonPressed;
    // content vignette
    static bool vignetteOn;
    
    // project selected
    static bool programType;
    static bool autoRoute;
    static int project;
    
    static float mY;
    static float mX;
};