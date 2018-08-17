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
    vector<LocationTile*> locationTilesToExpand;
    vector<LocationTile*> locationTilesToCollapse;

    // Do something when pressed
    void onPress(int x, int y, int button) {
        ExpandLocationTiles();
        CollapseLocationTiles();
    }
    
    void draw() {
        ofSetColor(255, 255, 0);
        ofDrawRectangle(x, y, width, height);
    }
    
    void ExpandLocationTiles() {
        for(int i = 0; i < locationTilesToExpand.size(); i++) {
            locationTilesToExpand[i]->setAnimation(Anim::expand);
        }
    }
    
    void CollapseLocationTiles() {
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            locationTilesToCollapse[i]->setAnimation(Anim::collapse);
        }
    }
};


#endif /* mainTile_h */
