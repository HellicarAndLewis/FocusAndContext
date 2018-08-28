//
//  LocationTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef LocationTile_h
#define LocationTile_h

#include "Location.h"
#include "InteractiveTile.h"
#include "ContentTile.h"

class LocationTile : public InteractiveTile {
public:
    
    ofVec2f collapseTarget;
    ofVec2f expandTarget;
    
    ofVec2f enlargeTarget;
    ofVec2f ensmallTarget;
    
    vector<ContentTile*> contentTilesToEnsmall;
    vector<LocationTile*> locationTilesToEnsmall;

    vector<ContentTile*> contentTilesToCollapse;
    vector<ContentTile*> contentTilesToExpand;
    
    // This is kind of a janky way to get zooming in to work. I'm going to notify the location points "onClick" event so I can zoom in with the buttons too.
    Location* location;
    
    void setup() {
        InteractiveTile::setup();
        
        color = ofColor(240);
    }
    
    void update(float easing) {
        InteractiveTile::update(easing);
        switch(animationStep) {
            case 0 :
                ensmallContentTilesToEnsmall();
                if(allContentTilesAreEnsmalled()) {
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
                ensmallLocationTilesToEnsmall();
                enlarge();
                if(allLocationTilesAreEnsmalled() && isNearSizeTarget()) {
                    animationStep++;
                }
                break;
            case 4 :
                sendExpandContentTilesToIntermediateTarget();
                if(allContentTilesInPosition()) {
                    animationStep++;
                }
                break;
            case 5 :
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
    
    void activate() {
        deactivateAllContent();
        ensmallContentTilesToEnsmall();
        bool expanded = true;
        for(int i = 0; i < contentTilesToExpand.size(); i++) {
            if(!(contentTilesToExpand[i]->isExpanded)) {
                expanded = false;
            }
        }
        if(!expanded) {
            animationStep = 0;
        }
        sound->play();
    }
    
    void onPress(int x, int y, int button) {
        bool someTilesAnimating = false;
        for(int i = 0; i < allTiles.size(); i++) {
            if(allTiles[i]->animationStep > -1) {
                someTilesAnimating = true;
            }
        }
        if(!someTilesAnimating && target == expandTarget) {
            string locationTitle = location->title;
            ofNotifyEvent(location->onLabelClicked, locationTitle);
            activate();
        }
    }
                   
   bool allContentTilesAreEnsmalled() {
       for(int i = 0; i < contentTilesToEnsmall.size(); i++) {
           if(!contentTilesToEnsmall[i]->isNearSizeTarget()) {
               return false;
           }
       }
       return true;
   }
    
    bool allLocationTilesAreEnsmalled() {
        for(int i = 0; i < locationTilesToEnsmall.size(); i++) {
            if(!locationTilesToEnsmall[i]->isNearSizeTarget()) {
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
    
    void ensmallContentTilesToEnsmall() {
        for(int i = 0; i < contentTilesToEnsmall.size(); i++) {
            contentTilesToEnsmall[i]->ensmall();
        }
    }
    
    void ensmallLocationTilesToEnsmall() {
        for(int i = 0; i < locationTilesToEnsmall.size(); i++) {
            locationTilesToEnsmall[i]->ensmall();
        }
    }
    
    void enlarge() {
        sizeTarget = enlargeTarget;
    }
    
    void ensmall() {
        sizeTarget = ensmallTarget;
    }
    
};

#endif /* LocationTile_h */
