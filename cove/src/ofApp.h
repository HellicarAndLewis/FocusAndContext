//
//  ofApp.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Scrollable.h"
#include "TileLoader.h"
#include "Location.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void setupGui();
    void update();
    void draw();
    
    void drawScene();
    void startScene();
    void endScene();
    void showGui(bool show = true);
    void setLat(float lat);
    void setLon(float lon);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // rendering
    ofEasyCam cam;
    ofLight light;
    ofMaterial materialRoads;
    ofMaterial materialBuildings;
    ofFbo fbo;
    ofShader shader;
    bool bShader;
    ofVec2f meshPosition;
    ofVec2f meshTarget;
    float mapX;
    float mapY;
    
    ofTrueTypeFont titleFont;
    vector<Location> locations;
    ofPolyline route, routeInverse;
    
    // tiles
    TileLoader tileLoader;
    
    // scroller
    IFS::Scrollable scroller;
    
    // GUI
    ofxDatGui* gui;
    ofxDatGuiSlider* guiTileAlpha;
    
    ofxDatGui2dPad* guiPositionPad;
    ofxDatGuiSlider* guiMapX;
    ofxDatGuiSlider* guiMapY;
    
    void onButtonEvent(ofxDatGuiButtonEvent e);
    void onSliderEvent(ofxDatGuiSliderEvent e);
    void on2dPadEvent(ofxDatGui2dPadEvent e);
    
};
