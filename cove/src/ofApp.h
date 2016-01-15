//
//  ofApp.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//

#pragma once

#include "ofMain.h"
#include "ofxVectorTile.h"
#include "ofxVectorLabels.h"
#include "ofxVectorBuilder.h"
#include "ofxDatGui.h"
#include "Scrollable.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void setupGui();
    void update();
    void draw();
    
    void startScene();
    void endScene();
    
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
    ofFbo fbo;
    ofShader shader;
    bool bShader;
    
    // tiles
    ofxVectorTile tile;
    ofxVectorTile tile2;
    ofxVectorBuilder builder;
    ofxVectorLabels labels;
    ofVboMesh tileMesh;
    ofVboMesh tileMesh2;
    
    // scroller
    IFS::Scrollable scroller;
    
    // GUI
    ofxDatGui* gui;
    ofxDatGuiSlider* guiTileAlpha;
    
};
