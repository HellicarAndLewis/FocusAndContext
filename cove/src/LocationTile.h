//
//  LocationTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef LocationTile_h
#define LocationTile_h

#include "InteractiveTile.h"
#include "ContentTile.h"

class LocationTile : public InteractiveTile {
public:
    vector<InteractiveTile*> tilesToExpand;
    vector<InteractiveTile*> tilesToCollapse;
    
    void setup() {
        InteractiveTile::setup();
        
        debugColor = ofColor(255, 0, 0);
    }
    
    void update() {
        InteractiveTile::update();
    }
    
    void onPress(int x, int y, int button) {
        cout<<"Location Tile Pressed"<<endl;
        collapseTiles();
        expandTiles();
    }
    
    void expandTiles() {
        for(int i = 0; i < tilesToExpand.size(); i++) {
            tilesToExpand[i]->setAnimation(Anim::expandFromLocation);
        }
    }
    
    void collapseTiles() {
        for(int i = 0; i < tilesToCollapse.size(); i++) {
            tilesToCollapse[i]->setAnimation(Anim::collapseToLocation);
        }
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
    
};

#endif /* LocationTile_h */
