//
//  TileLoader.cpp
//  Cove
//
//  Created by Chris Mullany on 15/01/2016.
//  Edited by Jason Walters on 2/03/2016.
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
    
    if (tiles.size() > 0)
        tiles.clear();
    
    ofDirectory dir(path);
    dir.allowExt("json");
    dir.listDir();
    
    for(int i = 0; i < dir.size(); i++){
        string path = dir.getPath(i);
        string fileName = ofFilePath::getFileName(path);
        LocalTile localTile(fileName);
        
        cout << "new tile at " << path << " " << localTile.x << "," << localTile.y << " " << localTile.zoom;
                
        if (i == 0) {
            // This is important! Need to set the offset for the first tile manually!
            builder.setOffset(localTile.x, localTile.y, localTile.zoom);
        }
        if (localTile.isValid) {
            string dataPath = ofToDataPath(path, true);
            glmTile tempTile = builder.getFromFile(dataPath);
            localTile.tile.setVectorTile(tempTile);
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
            //localTile.meshOcean = localTile.tile.getMeshFor("ocean");
//            if(i%2 == 0) {
//                localTile.isActive = true;
//            } else {
//            }
            localTile.isActive = false;
            if (localTile.zoom < 16) {
                macroTiles.push_back(localTile);
            }
            else {
                localTile.isActive = true;
                microTiles.push_back(localTile);
            }
            tiles.push_back(localTile);
        }
    }
    
    cout << "macro tiles:" << macroTiles.size() << ", micro tiles: " << tiles.size();
}


void TileLoader::setActive(int x, int y) {
    for (auto & tile: tiles) {
//        if (tile.x == x && tile.y == y) {
//            tile.isActive = true;
//        }
//        else tile.isActive = false;
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
