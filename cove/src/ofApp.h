//
//  ofApp.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//  Edited by Jason Walters on 2/03/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Scrollable.h"
#include "TileLoader.h"
#include "Route.h"
#include "InterestPoints.h"
#include "InteractiveMenu.h"
#include "ContentMenu.h"

#define EASEING 0.08

class ofApp : public ofBaseApp{
public:
    void setup();
    void setupGui();
    void update();
    void draw();
    void drawDebugMsg();
    
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
    ofMaterial materialOcean;
    ofFbo fbo;
    ofShader shader;
    ofShader waterShader;
    ofShader buildingsShader;
    ofShader roadsShader;
    
    bool bShader;
    bool bColorInvert;
    bool bDebugMsg;
    bool bCove;
    ofVec3f camPosition;
    ofVec2f meshPosition;
    ofVec2f meshTarget;
    float mapX;
    float mapY;
    float camDistance;
    float posLerp;
    float camTilt;
    ofVec3f camLook;
    
    float distance(ofVec2f first, ofVec2f second) {
        return first.distance(second);
    }
    
    // system pieces
    void loadProject(int selection);
    void loadPoint(int point);
    void loadContent(int item);
    void worldTransform(float distance, float distEase, ofVec3f rotation, float rotEase);
    
    // colors
    void projectColors();
    void drawVignette();
    bool colorProject;
    ofColor colBackground;
    ofColor colDebug;
    ofFloatColor colEarth, colEarthDiff;
    ofFloatColor colRoads, colRoadsDiff;
    ofFloatColor colBuildings, colBuildingsDiff;
    ofFloatColor colBuildingsActive, colBuildingsActiveDiff;
    ofFloatColor colWater;
    float lightAngle;
    float lightAngleDest;
    ofColor colVignette;
    
    // automatic system
    void autoSysSetup();
    void autoSysUpdate();
    bool isSysSetup;
    bool systemActive;
    bool routeSelected;
    bool systemTimerPaused;
    bool drawRoute2d;
    bool dropCam;
    bool isCam;
    float elapsedTime;
    float maxTime;
    float elapsedTimeInterestPoints;
    float scrollPercent;
    float waveDistance;
    float camRotSinX;
    float camRotSinY;
    float camRotSinZ;
    int currentInterval;
    int maxInterval;
    int currentPoint;
    int currentInterestPoint;
    
    // routes
    Route route;
    vector<InterestPoints> intPoints;
    int pointJump;
    int routeSelection;
    
    // tiles
    TileLoader tileLoader;
    
    // scroller
    IFS::Scrollable scroller;
    
    // menu
    void menuSetup(int _w, int _h);
    void menuUpdates();
    InteractiveMenu menu;
    bool pointReached;
    bool isDraw;
    
    // content menu
    void contentSetup(int _w, int _h);
    void contentUpdate();
    ContentMenu content;
    
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
