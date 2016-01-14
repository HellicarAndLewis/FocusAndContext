//
//  ofxVectorTile
//
//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxVectorTile.h"
#include "ofxVectorLabels.h"
#include "ofxVectorBuilder.h"
#include "ofxDatGui.h"

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
    
    ofEasyCam   cam;
    ofLight     light;
    ofFbo       fbo;
    ofShader    shader;
    
    ofxVectorTile      tile;
    ofxVectorBuilder   builder;
    ofxVectorLabels    labels;
    ofVboMesh           tileMesh;
    
    bool    bShader;
    
    ofxDatGui* gui;
    ofxDatGuiSlider* guiTileAlpha;
    
};
