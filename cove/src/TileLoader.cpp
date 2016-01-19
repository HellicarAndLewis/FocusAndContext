//
//  TileLoader.cpp
//  Cove
//
//  Created by Chris Mullany on 15/01/2016.
//
//

#include "TileLoader.h"

TileLoader::TileLoader() {
}

void TileLoader::setup() {
    labels.loadFont("ofxdatgui_assets/font-verdana.ttf", 10);
    labels.setFontColor(ofColor::black, ofColor::white);
    builder.setLabelManager(&labels);
}

void TileLoader::update() {
}

void TileLoader::draw() {
}

void TileLoader::exit() {
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////
void TileLoader::loadDir(string path) {
    
    if (tiles.size() > 0) {
        tiles.clear();
    }
    
    ofDirectory dir(path);
    dir.allowExt("json");
    dir.listDir();
    
    for(int i = 0; i < dir.size(); i++){
        string path = dir.getPath(i);
        ofLogVerbose("new tile at " + path);
        string fileName = ofFilePath::getFileName(path);
        LocalTile localTile(fileName);
        if (i == 0) {
            // This is important! Need to set the offset for the first tile manually!
            builder.setOffset(localTile.x, localTile.y, localTile.zoom);
        }
        if (localTile.isValid) {
            localTile.tile = builder.getFromFile(ofToDataPath(path, true));
            //    "earth", _tile, 0.0);
            //    "landuse", _tile, .1);
            //    "water", _tile, .2);
            //    "buildings", _tile, .3);
            //    "places", _tile, .4);
            //    "roads", _tile, .5);
            //    "pois"
            vector<string> layerNames = {"earth"};
            localTile.meshEarth = localTile.tile.getMeshFor(layerNames);
            localTile.meshBuildings = localTile.tile.getMeshFor("buildings");
            localTile.meshRoads = localTile.tile.getMeshFor("roads");
            localTile.meshWater = localTile.tile.getMeshFor("water");
            tiles.push_back(localTile);
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////
// protected
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// custom event handlers
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////

void TileLoader::keyPressed (int key) {}

void TileLoader::keyReleased (int key) {}

void TileLoader::mouseMoved(int x, int y) {}

void TileLoader::mouseDragged(int x, int y, int button) {}

void TileLoader::mousePressed(int x, int y, int button) {}

void TileLoader::mouseReleased(int x, int y, int button) {}

void TileLoader::windowResized(int w, int h) {}

void TileLoader::dragEvent(ofDragInfo dragInfo) {}

void TileLoader::gotMessage(ofMessage msg) {}
