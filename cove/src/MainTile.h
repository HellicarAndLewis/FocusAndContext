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
#include "ContentTile.h"

class MainTile : public InteractiveTile {
public:
    vector<LocationTile*> locationTilesToExpand;
    vector<LocationTile*> locationTilesToCollapse;
    vector<ContentTile*> contentTilesToCollapse;
    
    bool animating = false;
    
    ofEvent<string> onClick;
    
    void setup() {
        InteractiveTile::setup();
        color = ofColor(255);
    }
    // Do something when pressed
    void onPress(int x, int y, int button) {
        bool someTilesAnimating = false;
        for(int i = 0; i < allTiles.size(); i++) {
            if(allTiles[i]->animationStep > -1) {
                someTilesAnimating = true;
            }
        }
        if(!someTilesAnimating) {
            ofNotifyEvent(onClick, title);
            deactivateAllContent();
            animationStep = 0;
            if(sound->getPosition() > 0.1 || !sound->isPlaying()) sound->play();
        }
    }
    
    void update(int easing) {
        InteractiveTile::update(easing);
        switch(animationStep) {
            case 0 :
                ensmallContentTiles();
                if(allContentTilesCorrectSize()) {
                    animationStep++;
                }
                break;
            case 1 :
                sendCollapseContentTilesToIntermediateTarget();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 2 :
                collapseContentTiles();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 3 :
                ensmallLocationTiles();
                if(allLocationTilesCorrectSize()) {
                    animationStep++;
                }
                break;
            case 4 :
                collapseLocationTiles();
                expandLocationTiles();
                if(allLocationTilesInPosition()) {
                    animationStep++;
                }
                break;
            default :
                animationStep = -1;
                break;
        }
    }
    
    bool allLocationTilesInPosition() {
        bool allTilesCollapsed = true;
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            if(!locationTilesToCollapse[i]->isNearTarget()) {
                return false;
            }
        }
        return true;
    }
    
    bool allContentTilesInPosition() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            if(!contentTilesToCollapse[i]->isNearTarget()) {
                return false;
            }
        }
        return true;
    }
    
    bool allLocationTilesCorrectSize() {
        for(int i = 0; i < locationTilesToExpand.size(); i++) {
            if(!locationTilesToExpand[i]->isNearSizeTarget()) {
                return false;
            }
        }
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            if(!locationTilesToCollapse[i]->isNearSizeTarget()) {
                return false;
            }
        }
        return true;
    }
    
    bool allContentTilesCorrectSize() {
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            if(!locationTilesToCollapse[i]->isNearSizeTarget()) {
                return false;
            }
        }
        return true;
    }
    
    void ensmallLocationTiles() {
        for(int i = 0; i < locationTilesToExpand.size(); i++) {
            locationTilesToExpand[i]->ensmall();
        }
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            locationTilesToCollapse[i]->ensmall();
        }
    }
    
    void ensmallContentTiles() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            contentTilesToCollapse[i]->ensmall();
        }
    }
    
    void collapseLocationTiles() {
        for(int i = 0; i < locationTilesToCollapse.size(); i++) {
            locationTilesToCollapse[i]->collapse();
        }
    }
    
    void expandLocationTiles() {
        for(int i = 0; i < locationTilesToExpand.size(); i++) {
            locationTilesToExpand[i]->expand();
        }
    }
    
    void sendCollapseContentTilesToIntermediateTarget() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            if(contentTilesToCollapse[i]->isExpanded) {
                contentTilesToCollapse[i]->goToIntermediateTarget();
            }
        }
    }
    
    void collapseContentTiles() {
        for(int i = 0; i < contentTilesToCollapse.size(); i++) {
            contentTilesToCollapse[i]->collapse();
        }
    }
};


#endif /* mainTile_h */
