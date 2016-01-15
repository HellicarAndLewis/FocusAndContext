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
            localTile.mesh = localTile.tile.getMesh();
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
