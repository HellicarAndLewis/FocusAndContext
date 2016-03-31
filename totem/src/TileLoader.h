//
//  TileLoader.h
//  Cove
//
//  Created by Chris Mullany on 15/01/2016.
//
//

#pragma once
#include "ofMain.h"
#include "LocalTile.h"
#include "ofxVectorBuilder.h"

class TileLoader {
public:
    TileLoader();
    
	void setup();
	void update();
	void draw();
	void exit();
    
    void loadDir(string path);
    void setActive(int x, int y);
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
    // tiles
    vector<LocalTile> tiles;
    vector<LocalTile> macroTiles;
    vector<LocalTile> microTiles;
    ofxVectorBuilder builder;

protected:  
private:
    
};