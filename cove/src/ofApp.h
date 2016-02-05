//
//  ofApp.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//  Edited by Jason Walters on 5/02/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Scrollable.h"
#include "TileLoader.h"
#include "Route.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void setupGui();
    void setupWorldColors();
    void routeLoad(int selection);
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
    ofVec3f sceneRotation;
    ofLight light;
    ofMaterial materialEarth;
    ofMaterial materialRoads;
    ofMaterial materialBuildings;
    ofMaterial materialBuildingsActive;
    ofMaterial materialWater;
    ofFbo fbo;
    ofShader shader;
    ofShader waterShader;
    ofShader buildingsShader;
    ofShader roadsShader;
    
    bool bShader;
    bool bColorInvert;
    ofVec2f meshPosition;
    ofVec2f meshTarget;
    float mapX;
    float mapY;
    
    Route route;
    
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
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    
};
