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
    vector<ContentTile*> ContentTilesToExpand;
    vector<ContentTile*> ContentTilesToCollapse;
    
    void onPress(int x, int y, int button) {
        
    }
    
    void ExpandContentTiles() {
        for(int i = 0; i < ContentTilesToExpand.size(); i++) {
            ContentTilesToExpand[i]->setAnimation(Anim::expand);
        }
    }
    
    void CollapseContentTiles() {
        for(int i = 0; i < ContentTilesToCollapse.size(); i++) {
            ContentTilesToCollapse[i]->setAnimation(Anim::collapse);
        }
    }
    
};

#endif /* LocationTile_h */
