//
//  ContentTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef ContentTile_h
#define ContentTile_h

#include "InteractiveTile.h"

class ContentTile : public InteractiveTile {
public:
    
    void setup() {
        InteractiveTile::setup();
        
        debugColor = ofColor(0, 0, 255);
    }
    
    void update() {
        InteractiveTile::update();
    }
    
    void onPress(int x, int y, int button) {
        cout<<"Content Tile Pressed!"<<endl;
//        width = width * 1.1;
//        height = height * 1.1;
    }
};


#endif /* ContentTile_h */
