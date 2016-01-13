#pragma once
#include "ofMain.h"
#include "Map.h"

class ofApp: public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    Map map;
};