//
//  ContentTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef ContentTile_h
#define ContentTile_h

#include "InteractiveTile.h"
#include "Content.h"

class ContentTile : public InteractiveTile {
public:
    
    ofVec2f expandTarget;
    ofVec2f intermediateTarget;
    ofVec2f collapseTarget;
    
    ContentDisplayer* contentDisplayerToActivate;
    
    bool isExpanded;
    
    void setup() {
        InteractiveTile::setup();
        
        color = ofColor(240);
    }
    
    void update(float easing) {
        InteractiveTile::update(easing);
        if(isNearTarget() && target == expandTarget) {
            isExpanded = true;
        } else {
            isExpanded = false;
        }
    }
    
    void onPress(int x, int y, int button) {
        bool someTilesAnimating = false;
        for(int i = 0; i < allTiles.size(); i++) {
            if(allTiles[i]->animationStep > -1) {
                someTilesAnimating = true;
            }
        }
        if(!someTilesAnimating && target == expandTarget) {
            deactivateAllContent();
            contentDisplayerToActivate->setIsActive(true);
        }
    }
    
    void goToIntermediateTarget() {
        target = intermediateTarget;
    }
    
    void collapse() {
        target = collapseTarget;
    }
    
    void expand() {
        target = expandTarget;
    }
};


#endif /* ContentTile_h */
