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
    
    ofVec2f enlargeTarget;
    ofVec2f ensmallTarget;
    
    vector<ContentTile*> contentTilesToEnsmall;
    
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
            sound->play();
            contentDisplayerToActivate->setIsActive(true);
            enlarge();
            ensmallContentTilesToEnsmall();
        }
    }
    
    void ensmallContentTilesToEnsmall() {
        for(int i = 0; i < contentTilesToEnsmall.size(); i++) {
            contentTilesToEnsmall[i]->ensmall();
        }
    }
    
    void enlarge() {
        sizeTarget = enlargeTarget;
    }
    
    void ensmall() {
        sizeTarget = ensmallTarget;
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
