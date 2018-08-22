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
    
    ofVec2f collapseTarget;
    ofVec2f expandTarget;
    
    vector<ContentTile*> contentTilesToCollapse;
    vector<ContentTile*> contentTilesToExpand;
        
    void setup() {
        InteractiveTile::setup();
        
        color = ofColor(240);
    }
    
    void update(float easing) {
        InteractiveTile::update(easing);
        switch(animationStep) {
            case 0 :
                sendCollapseContentTilesToIntermediateTarget();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 1 :
                collapseContentTiles();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 2 :
                sendExpandContentTilesToIntermediateTarget();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 3:
                expandContentTiles();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            default :
                animationStep = -1;
                break;
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
            bool expanded = true;
            for(int i = 0; i < contentTilesToExpand.size(); i++) {
                if(!(contentTilesToExpand[i]->isExpanded)) {
                    expanded = false;
                }
            }
            if(!expanded) {
                animationStep = 0;
            }
        }
    }
    
    bool allContentTilesInPosition() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            if(!contentTilesToCollapse[i]->isNearTarget()) {
                return false;
            }
        }
        for(int i = 0; i < contentTilesToExpand.size(); i++) {
            if(!contentTilesToExpand[i]->isNearTarget()) {
                return false;
            }
        }
        return true;
    }
    
    void sendCollapseContentTilesToIntermediateTarget() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            if(contentTilesToCollapse[i]->isExpanded) {
                contentTilesToCollapse[i]->goToIntermediateTarget();
            }
        }
    }
    
    void sendExpandContentTilesToIntermediateTarget() {
        for(int i = 0; i < contentTilesToExpand.size(); i++) {
            contentTilesToExpand[i]->goToIntermediateTarget();
        }
    }
    
    void collapseContentTiles() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            contentTilesToCollapse[i]->collapse();
        }
    }
    
    void expandContentTiles() {
        for(int i = 0; i < contentTilesToExpand.size(); i++) {
            contentTilesToExpand[i]->expand();
        }
    }
    void collapse() {
        target = collapseTarget;
    }
    
    void expand() {
        target = expandTarget;
    }
    
};

#endif /* LocationTile_h */
