//
//  MainTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef MainTile_h
#define MainTile_h

#include "InteractiveTile.h"
#include "LocationTile.h"

class MainTile : public InteractiveTile {
public:
    vector<InteractiveTile*> tilesToCollapse;
    vector<InteractiveTile*> tilesToExpand;
    
    void setup() {
        InteractiveTile::setup();
        debugColor = ofColor(0, 255, 0);
    }
    // Do something when pressed
    void onPress(int x, int y, int button) {
        cout<<"Main Tile Pressed!"<<endl;
        collapseTiles();
        expandTiles();
    }
    
    void addTilesToExpand(vector<InteractiveTile*> _tiles) {
        if(tilesToExpand.size() == 0) {
            tilesToExpand = _tiles;
        } else {
            tilesToExpand.insert(tilesToExpand.end(), _tiles.begin(), _tiles.end());
        }
    }
    
    void addTilesToCollapse(vector<InteractiveTile*> _tiles) {
        if(tilesToCollapse.size() == 0) {
            tilesToCollapse = _tiles;
        } else {
            tilesToCollapse.insert(tilesToCollapse.end(), _tiles.begin(), _tiles.end());
        }
    }
    
    void collapseTiles() {
        for(int i = 0; i < tilesToCollapse.size(); i++) {
            tilesToCollapse[i]->setAnimation(Anim::collapseToMain);
        }
    }
    
    void expandTiles() {
        for(int i = 0; i < tilesToExpand.size(); i++) {
            tilesToExpand[i]->setAnimation(Anim::expandFromMain);
        }
    }
};


#endif /* mainTile_h */
