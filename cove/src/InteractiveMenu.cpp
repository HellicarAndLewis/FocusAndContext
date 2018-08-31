//
//  InteractiveMenu.cpp
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 9/03/2016.
//  Last edited by James Bentley on 28/04/2016.
//  Updated by James Bentley on 13/08/2018
//

#include "InteractiveMenu.h"
#include "Globals.h"
#include "ofxNestedFileLoader.h"

//--------------------------------------------------------------
void InteractiveMenu::setup(int _w, int _h, float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut, vector<Location*> _lLocations, vector<Location*> _rLocations)
{
    // setup variables
    width = _w;
    height = _h;
    mainArea = _mainArea;
    subArea = _subArea;
    padding = _padding;
    easeIn = _easeIn;
    easeOut = _easeOut;
    length = BUTTON_AMT;
    leftOn = false;
    rightOn = false;
    buttonClicked = false;
    
    // content media setup
    c.setup();
    
    titleFont.setup("fonts/Plain-Regular.ttf", 1.5, 1024, true, 8, 2.0);

    // menu button sounds
    snd1.load("content/audio/Arup_buttonPress1.wav");
    snd1.setMultiPlay(false);
    snd1.setVolume(0.7);
    
    snd2.load("content/audio/Arup_buttonPress2.wav");
    snd2.setMultiPlay(false);
    snd2.setVolume(0.7);
    
    // project intro sounds
    hs1Intro.load("content/Google Drive/Arup/Research/Content/HS1/IntroductionVideo/HS1Intro.wav");
    hs1Intro.setMultiPlay(false);
    hs1Intro.setLoop(false);
    
    crossrailIntro.load("content/Google Drive/Arup/Research/Content/Crossrail/IntroductionVideo/CrossrailIntro.wav");
    crossrailIntro.setMultiPlay(false);
    crossrailIntro.setLoop(false);
    
    for(int i = 0; i < BUTTON_AMT; i++) {
        lLocations[i] = _lLocations[i];
        rLocations[i] = _rLocations[i];
    }
    
//    c.setCons(allCons);
    
    vector<InteractiveTile*> allTiles = initializeTiles();
    
    if(ofGetWidth() > ofGetHeight()) {
        setTilePositionsLandscape();
    } else {
        setTilePositionsPortrait();
    }
    
    setupTiles(allTiles);
    
    for(int  i = 0; i < BUTTON_AMT; i++) {
        ofAddListener(lLocations[i]->onLabelClicked, this, &InteractiveMenu::onLabelClicked);
        ofAddListener(rLocations[i]->onLabelClicked, this, &InteractiveMenu::onLabelClicked);
        ofAddListener(hs1MainTile->onClick, this, &InteractiveMenu::onMainButtonClicked);
        ofAddListener(crossrailMainTile->onClick, this, &InteractiveMenu::onMainButtonClicked);
    }
    
    setTileTitlesAndContent();
    
    leftWasOn = false;
}

vector<InteractiveTile*> InteractiveMenu::initializeTiles() {
    // Initialize all my tile pointers;
    // Main tiles
    vector<InteractiveTile*> allInteractiveTiles;

    hs1MainTile = new MainTile();
    crossrailMainTile = new MainTile();
    //Location tiles
    for(int i = 0; i < BUTTON_AMT; i++) {
        hs1LocationTiles.push_back(new LocationTile());
        crossrailLocationTiles.push_back(new LocationTile());
    }
    //Content tiles
    for(int i = 0; i < BUTTON_AMT; i++) {
        vector<ContentTile*> hs1Tiles;
        vector<ContentTile*> crossrailTiles;
        for(int j = 0; j < BUTTON_AMT; j++) {
            hs1Tiles.push_back(new ContentTile());
            crossrailTiles.push_back(new ContentTile());
        }
        hs1ContentTiles.push_back(hs1Tiles);
        crossrailContentTiles.push_back(crossrailTiles);
    }
    
    allInteractiveTiles.push_back(hs1MainTile);
    allInteractiveTiles.push_back(crossrailMainTile);
    
    for(int i = 0; i < BUTTON_AMT; i++) {
        allInteractiveTiles.push_back(hs1LocationTiles[i]);
        allInteractiveTiles.push_back(crossrailLocationTiles[i]);
        for(int j = 0; j < BUTTON_AMT; j++) {
            allInteractiveTiles.push_back(hs1ContentTiles[i][j]);
            allInteractiveTiles.push_back(crossrailContentTiles[i][j]);
        }
    }
    
    for(int i = 0; i < allInteractiveTiles.size(); i++) {
        allInteractiveTiles[i]->font = &titleFont;
        allInteractiveTiles[i]->c = &c;
    }
    
    return allInteractiveTiles;

}

void InteractiveMenu::setTilePositionsPortrait() {
    
    string test = "Archaeological";
    int textSize = 40;
    int numLines;
    for(int i = textSize; i > 8; i--) {
        ofRectangle r = titleFont.drawMultiLineColumn(test, textSize, 0, 0, subArea - subArea * 0.1 *2
                                                      , numLines, true);
        textSize = i;
        if(numLines == 1) {
            break;
        }
    }
    
    cout<<"Text Size: "<<textSize<<endl;
    
    // Set the base positions of the buttons.
    ofVec2f hs1Base = ofVec2f(padding + mainArea/2, height - padding - mainArea/2);
    ofVec2f crossrailBase = ofVec2f((width - padding) - mainArea/2, height - padding - mainArea/2);

    // Setup the Main tiles.
    hs1MainTile->position = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->target = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->size = ofVec2f(mainArea, mainArea);
    hs1MainTile->sizeTarget = ofVec2f(mainArea, mainArea);
    hs1MainTile->textWidth = subArea;
    hs1MainTile->textBuffer = subArea * 0.1;
    hs1MainTile->textSize = textSize;
    
    crossrailMainTile->position = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->target = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->size = ofVec2f(mainArea, mainArea);
    crossrailMainTile->sizeTarget = ofVec2f(mainArea, mainArea);
    crossrailMainTile->textWidth = subArea;
    crossrailMainTile->textBuffer = subArea * 0.1;
    crossrailMainTile->textSize = textSize;

    // Setup Location Tiles
    for(int i = 0; i < hs1LocationTiles.size(); i++) {
        hs1LocationTiles[i]->parentTile = hs1MainTile;
        hs1LocationTiles[i]->position = ofVec2f(0, 0);
        hs1LocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        hs1LocationTiles[i]->expandTarget = ofVec2f((i+1) * subArea + (i+1) * padding, 0);
        hs1LocationTiles[i]->size = ofVec2f(subArea, subArea);
        hs1LocationTiles[i]->sizeTarget = ofVec2f(subArea, subArea);
        hs1LocationTiles[i]->enlargeTarget = ofVec2f(mainArea);
        hs1LocationTiles[i]->ensmallTarget = ofVec2f(subArea);
        hs1LocationTiles[i]->textWidth = subArea;
        hs1LocationTiles[i]->textBuffer = subArea * 0.1;
        hs1LocationTiles[i]->textSize = textSize;

    }
    
    for(int i = 0; i < crossrailLocationTiles.size(); i++) {
        crossrailLocationTiles[i]->parentTile = crossrailMainTile;
        crossrailLocationTiles[i]->position = ofVec2f(0, 0);
        crossrailLocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        crossrailLocationTiles[i]->expandTarget = ofVec2f(- (i+1) * subArea - (i+1) * padding, 0 );
        crossrailLocationTiles[i]->size = ofVec2f(subArea, subArea);
        crossrailLocationTiles[i]->sizeTarget = ofVec2f(subArea, subArea);
        crossrailLocationTiles[i]->enlargeTarget = ofVec2f(mainArea);
        crossrailLocationTiles[i]->ensmallTarget = ofVec2f(subArea);
        crossrailLocationTiles[i]->textWidth = subArea;
        crossrailLocationTiles[i]->textBuffer = subArea * 0.1;
        crossrailLocationTiles[i]->textSize = textSize;

    }
    
    // Setup content Tiles
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            hs1ContentTiles[i][j]->parentTile = hs1LocationTiles[i];
            hs1ContentTiles[i][j]->size = ofVec2f(subArea, subArea);
            hs1ContentTiles[i][j]->sizeTarget = ofVec2f(subArea, subArea);
            hs1ContentTiles[i][j]->enlargeTarget = ofVec2f(mainArea);
            hs1ContentTiles[i][j]->ensmallTarget = ofVec2f(subArea);
            hs1ContentTiles[i][j]->position = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->intermediateTarget = ofVec2f(0, -(subArea + padding));
            hs1ContentTiles[i][j]->expandTarget = ofVec2f(-(i - j) * (subArea + padding), -(subArea + padding));
            hs1ContentTiles[i][j]->textWidth = subArea;
            hs1ContentTiles[i][j]->textBuffer = subArea * 0.1;
            hs1ContentTiles[i][j]->textSize = textSize;

        }
    }

    
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            crossrailContentTiles[i][j]->parentTile = crossrailLocationTiles[i];
            crossrailContentTiles[i][j]->size = ofVec2f(subArea, subArea);
            crossrailContentTiles[i][j]->sizeTarget = ofVec2f(subArea, subArea);
            crossrailContentTiles[i][j]->enlargeTarget = ofVec2f(mainArea);
            crossrailContentTiles[i][j]->ensmallTarget = ofVec2f(subArea);
            crossrailContentTiles[i][j]->position = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->intermediateTarget = ofVec2f(0, -(subArea + padding));
            crossrailContentTiles[i][j]->expandTarget = ofVec2f((i - j) * (subArea + padding), -(subArea + padding));
            crossrailContentTiles[i][j]->textWidth = subArea;
            crossrailContentTiles[i][j]->textBuffer = subArea * 0.1;
            crossrailContentTiles[i][j]->textSize = textSize;

        }
    }
}

void InteractiveMenu::setTilePositionsLandscape() {
    
    string test = "International";
    int textSize = 40;
    int numLines;
    for(int i = textSize; i > 8; i--) {
        ofRectangle r = titleFont.drawMultiLineColumn(test, textSize, 0, 0, subArea - subArea * 0.1 *2
                                                  , numLines, true);
        if(numLines == 1) {
            textSize = i;
            break;
        }
    }
    
    cout<<"Text Size: "<<textSize<<endl;
    
    // Set the base positions of the buttons.
    ofVec2f hs1Base = ofVec2f(padding + mainArea/2, height - padding - mainArea/2);
    ofVec2f crossrailBase = ofVec2f((width - padding) - mainArea/2, height - padding - mainArea/2);
    
    // Setup the Main tiles.
    hs1MainTile->position = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->target = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->size = ofVec2f(mainArea, mainArea);
    hs1MainTile->sizeTarget = ofVec2f(mainArea, mainArea);
    hs1MainTile->textWidth = mainArea;
    hs1MainTile->textBuffer = mainArea * 0.1;
    hs1MainTile->textSize = textSize;

    crossrailMainTile->position = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->target = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->size = ofVec2f(mainArea, mainArea);
    crossrailMainTile->sizeTarget = ofVec2f(mainArea, mainArea);
    crossrailMainTile->textWidth = mainArea;
    crossrailMainTile->textBuffer = mainArea * 0.1;
    crossrailMainTile->textSize = textSize;

    // Setup Location Tiles
    for(int i = 0; i < hs1LocationTiles.size(); i++) {
        hs1LocationTiles[i]->parentTile = hs1MainTile;
        hs1LocationTiles[i]->position = ofVec2f(0, 0);
        hs1LocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        hs1LocationTiles[i]->expandTarget = ofVec2f(0, - (i+1) * subArea - (i+1) * padding);
        hs1LocationTiles[i]->size = ofVec2f(subArea, subArea);
        hs1LocationTiles[i]->sizeTarget = ofVec2f(subArea, subArea);
        hs1LocationTiles[i]->enlargeTarget = ofVec2f(mainArea);
        hs1LocationTiles[i]->ensmallTarget = ofVec2f(subArea);
        hs1LocationTiles[i]->textWidth = subArea;
        hs1LocationTiles[i]->textBuffer = subArea * 0.1;
        hs1LocationTiles[i]->textSize = textSize;

    }
    
    for(int i = 0; i < crossrailLocationTiles.size(); i++) {
        crossrailLocationTiles[i]->parentTile = crossrailMainTile;
        crossrailLocationTiles[i]->position = ofVec2f(0, 0);
        crossrailLocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        crossrailLocationTiles[i]->expandTarget = ofVec2f(0, - (i+1) * subArea - (i+1) * padding);
        crossrailLocationTiles[i]->size = ofVec2f(subArea, subArea);
        crossrailLocationTiles[i]->sizeTarget = ofVec2f(subArea, subArea);
        crossrailLocationTiles[i]->enlargeTarget = ofVec2f(mainArea);
        crossrailLocationTiles[i]->ensmallTarget = ofVec2f(subArea);
        crossrailLocationTiles[i]->textWidth = subArea;
        crossrailLocationTiles[i]->textBuffer = subArea * 0.1;
        crossrailLocationTiles[i]->textSize = textSize;
    }
    
    // Setup content Tiles
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            hs1ContentTiles[i][j]->parentTile = hs1LocationTiles[i];
            hs1ContentTiles[i][j]->size = ofVec2f(subArea, subArea);
            hs1ContentTiles[i][j]->sizeTarget = ofVec2f(subArea, subArea);
            hs1ContentTiles[i][j]->enlargeTarget = ofVec2f(mainArea);
            hs1ContentTiles[i][j]->ensmallTarget = ofVec2f(subArea);
            hs1ContentTiles[i][j]->position = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->intermediateTarget = ofVec2f((subArea + padding), 0);
            hs1ContentTiles[i][j]->expandTarget = ofVec2f((subArea + padding), (i - j) * (subArea + padding));
            hs1ContentTiles[i][j]->textWidth = subArea;
            hs1ContentTiles[i][j]->textBuffer = subArea * 0.1;
            hs1ContentTiles[i][j]->textSize = textSize;

        }
    }
    
    
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            crossrailContentTiles[i][j]->parentTile = crossrailLocationTiles[i];
            crossrailContentTiles[i][j]->size = ofVec2f(subArea, subArea);
            crossrailContentTiles[i][j]->sizeTarget = ofVec2f(subArea, subArea);
            crossrailContentTiles[i][j]->enlargeTarget = ofVec2f(mainArea);
            crossrailContentTiles[i][j]->ensmallTarget = ofVec2f(subArea);
            crossrailContentTiles[i][j]->position = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->intermediateTarget = ofVec2f(-(subArea + padding), 0);
            crossrailContentTiles[i][j]->expandTarget = ofVec2f(-(subArea + padding), (i - j) * (subArea + padding));
            crossrailContentTiles[i][j]->textWidth = subArea;
            crossrailContentTiles[i][j]->textBuffer = subArea * 0.1;
            crossrailContentTiles[i][j]->textSize = textSize;
        }
    }
}
        
void InteractiveMenu::setupTiles(vector<InteractiveTile*> allInteractiveTiles) {
    
    for(int i = 0; i < allInteractiveTiles.size(); i++) {
        allInteractiveTiles[i]->font = &titleFont;
        allInteractiveTiles[i]->c = &c;
    }
    
    // Setup the Main tiles.
    hs1MainTile->locationTilesToExpand = hs1LocationTiles;
    hs1MainTile->locationTilesToCollapse = crossrailLocationTiles;
    hs1MainTile->sound = &hs1Intro;
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            hs1MainTile->contentTilesToCollapse.push_back(hs1ContentTiles[i][j]);
        }
    }
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            hs1MainTile->contentTilesToCollapse.push_back(crossrailContentTiles[i][j]);
        }
    }
    hs1MainTile->allTiles = allInteractiveTiles;
    hs1MainTile->setup();
    
    crossrailMainTile->locationTilesToExpand = crossrailLocationTiles;
    crossrailMainTile->locationTilesToCollapse = hs1LocationTiles;
    crossrailMainTile->sound = &crossrailIntro;
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            crossrailMainTile->contentTilesToCollapse.push_back(hs1ContentTiles[i][j]);
        }
    }
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            crossrailMainTile->contentTilesToCollapse.push_back(crossrailContentTiles[i][j]);
        }
    }
    crossrailMainTile->allTiles = allInteractiveTiles;
    crossrailMainTile->setup();
    
    // Setup Location Tiles
    for(int i = 0; i < hs1LocationTiles.size(); i++) {
        hs1LocationTiles[i]->contentTilesToExpand = hs1ContentTiles[i];
        hs1LocationTiles[i]->location = lLocations[i];
        hs1LocationTiles[i]->tilesToDrawLinesTo.push_back(hs1ContentTiles[i][i]);
        hs1LocationTiles[i]->sound = &snd1;
        for(int j = 0; j < hs1LocationTiles.size(); j++) {
            if(j != i) {
                hs1LocationTiles[i]->locationTilesToEnsmall.push_back(hs1LocationTiles[j]);
            }
        }
        for(int j = 0; j < hs1ContentTiles.size(); j++) {
            for(int k = 0; k < BUTTON_AMT; k++) {
                if(j != i) {
                    hs1LocationTiles[i]->contentTilesToCollapse.push_back(hs1ContentTiles[j][k]);
                }
                hs1LocationTiles[i]->contentTilesToEnsmall.push_back(hs1ContentTiles[j][k]);
                hs1LocationTiles[i]->contentTilesToEnsmall.push_back(crossrailContentTiles[j][k]);
            }
        }
        hs1LocationTiles[i]->allTiles = allInteractiveTiles;
        hs1LocationTiles[i]->setup();
    }
    hs1LocationTiles[4]->tilesToDrawLinesTo.push_back(hs1MainTile);
    
    for(int i = 0; i < crossrailLocationTiles.size(); i++) {
        crossrailLocationTiles[i]->contentTilesToExpand = crossrailContentTiles[i];
        crossrailLocationTiles[i]->location = rLocations[BUTTON_AMT - 1- i];
        crossrailLocationTiles[i]->tilesToDrawLinesTo.push_back(crossrailContentTiles[i][i]);
        crossrailLocationTiles[i]->sound = &snd2;
        for(int j = 0; j < crossrailLocationTiles.size(); j++) {
            if(j != i) {
                crossrailLocationTiles[i]->locationTilesToEnsmall.push_back(crossrailLocationTiles[j]);
            }
        }
        for(int j = 0; j < crossrailContentTiles.size(); j++) {
            for(int k = 0; k < BUTTON_AMT; k++) {
                if(j != i) {
                    crossrailLocationTiles[i]->contentTilesToCollapse.push_back(crossrailContentTiles[j][k]);
                }
                crossrailLocationTiles[i]->contentTilesToEnsmall.push_back(hs1ContentTiles[j][k]);
                crossrailLocationTiles[i]->contentTilesToEnsmall.push_back(crossrailContentTiles[j][k]);
            }
        }
        crossrailLocationTiles[i]->allTiles = allInteractiveTiles;
        crossrailLocationTiles[i]->setup();
    }
    crossrailLocationTiles[4]->tilesToDrawLinesTo.push_back(crossrailMainTile);
    
    
    // Setup content Tiles
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            hs1ContentTiles[i][j]->isExpanded = false;
            hs1ContentTiles[i][j]->allTiles = allInteractiveTiles;
            for(int k = 0; k < hs1ContentTiles[i].size(); k++) {
                if(k != j) {
                    hs1ContentTiles[i][j]->contentTilesToEnsmall.push_back(hs1ContentTiles[i][k]);
                }
            }
            hs1ContentTiles[i][j]->setup();
            hs1ContentTiles[i][j]->sound = &snd1;
        }
        hs1ContentTiles[i][0]->tilesToDrawLinesTo.push_back(hs1ContentTiles[i][4]);
    }
    
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            crossrailContentTiles[i][j]->isExpanded = false;
            crossrailContentTiles[i][j]->allTiles = allInteractiveTiles;
            for(int k = 0; k < hs1ContentTiles[i].size(); k++) {
                if(k != j) {
                    crossrailContentTiles[i][j]->contentTilesToEnsmall.push_back(crossrailContentTiles[i][k]);
                }
            }
            crossrailContentTiles[i][j]->setup();
            crossrailContentTiles[i][j]->sound = &snd2;
        }
        crossrailContentTiles[i][0]->tilesToDrawLinesTo.push_back(crossrailContentTiles[i][4]);
    }

}

void InteractiveMenu::setFlipMouseInput(bool _flip) {
    hs1MainTile->flipMouseInput = _flip;
    crossrailMainTile->flipMouseInput = _flip;
    for(int i = 0; i < hs1LocationTiles.size(); i++) {
        hs1LocationTiles[i]->flipMouseInput = _flip;
        crossrailLocationTiles[i]->flipMouseInput = _flip;
        for(int j = 0; j < hs1ContentTiles.size(); j++) {
            hs1ContentTiles[i][j]->flipMouseInput = _flip;
            crossrailContentTiles[i][j]->flipMouseInput = _flip;
        }
    }
}

void InteractiveMenu::setTileTitlesAndContent() {
    
    hs1LocationTiles[0]->title = "St Pancras International";
    hs1LocationTiles[1]->title = "Stratford International";
    hs1LocationTiles[2]->title = "Ebbsfleet International";
    hs1LocationTiles[3]->title = "Medway Viaduct";
    hs1LocationTiles[4]->title = "Ashford International";
    
    //St Pancras
    hs1ContentTiles[0][0]->title = "Designing the Undercroft";
    hs1ContentTiles[0][1]->title = "Station Renovation";
    hs1ContentTiles[0][2]->title = "Acoustic Testing";
    hs1ContentTiles[0][3]->title = "Land Use Plan";
    hs1ContentTiles[0][4]->title = "Station Model";
    hs1ContentTiles[0][0]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][0];
    hs1ContentTiles[0][1]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][1];
    hs1ContentTiles[0][2]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][2];
    hs1ContentTiles[0][3]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][3];
    hs1ContentTiles[0][4]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][4];
    
    // Stratford
    hs1ContentTiles[1][0]->title = "Tunnel Boring into London";
    hs1ContentTiles[1][1]->title = "Site Diagram";
    hs1ContentTiles[1][2]->title = "Under Construction";
    hs1ContentTiles[1][3]->title = "Stratford Today";
    hs1ContentTiles[1][4]->title = "Station Model";
    hs1ContentTiles[1][0]->contentDisplayerToActivate = c.hs1Displayers["StratfordInternational"][0];
    hs1ContentTiles[1][1]->contentDisplayerToActivate = c.hs1Displayers["StratfordInternational"][1];
    hs1ContentTiles[1][2]->contentDisplayerToActivate = c.hs1Displayers["StratfordInternational"][2];
    hs1ContentTiles[1][3]->contentDisplayerToActivate = c.hs1Displayers["StratfordInternational"][3];
    hs1ContentTiles[1][4]->contentDisplayerToActivate = c.hs1Displayers["StratfordInternational"][4];
    
    //Ebbsfleet
    hs1ContentTiles[2][0]->title = "Town Development";
    hs1ContentTiles[2][1]->title = "Bridge Push";
    hs1ContentTiles[2][2]->title = "Linking Overpass";
    hs1ContentTiles[2][3]->title = "Station Design";
    hs1ContentTiles[2][4]->title = "Ebbsfleet Elephant";
    hs1ContentTiles[2][0]->contentDisplayerToActivate = c.hs1Displayers["EbbsfleetInternational"][0];
    hs1ContentTiles[2][1]->contentDisplayerToActivate = c.hs1Displayers["EbbsfleetInternational"][1];
    hs1ContentTiles[2][2]->contentDisplayerToActivate = c.hs1Displayers["EbbsfleetInternational"][2];
    hs1ContentTiles[2][3]->contentDisplayerToActivate = c.hs1Displayers["EbbsfleetInternational"][3];
    hs1ContentTiles[2][4]->contentDisplayerToActivate = c.hs1Displayers["EbbsfleetInternational"][4];
    
    // Medway Viaduct
    hs1ContentTiles[3][0]->title = "Mapping Urban Regeneration";
    hs1ContentTiles[3][1]->title = "Under Construction";
    hs1ContentTiles[3][2]->title = "Aerial Footage";
    hs1ContentTiles[3][3]->title = "Completed Medway Viaduct";
    hs1ContentTiles[3][4]->title = "Bridge Model";
    hs1ContentTiles[3][0]->contentDisplayerToActivate = c.hs1Displayers["MedwayViaduct"][0];
    hs1ContentTiles[3][1]->contentDisplayerToActivate = c.hs1Displayers["MedwayViaduct"][1];
    hs1ContentTiles[3][2]->contentDisplayerToActivate = c.hs1Displayers["MedwayViaduct"][2];
    hs1ContentTiles[3][3]->contentDisplayerToActivate = c.hs1Displayers["MedwayViaduct"][3];
    hs1ContentTiles[3][4]->contentDisplayerToActivate = c.hs1Displayers["MedwayViaduct"][4];
    
    // Ashford
    hs1ContentTiles[4][0]->title = "The Campaign for HS1";
    hs1ContentTiles[4][1]->title = "The Arup Alignment";
    hs1ContentTiles[4][2]->title = "Relocating Houses";
    hs1ContentTiles[4][3]->title = "Ashford International Station";
    hs1ContentTiles[4][4]->title = "Ashford Today";
    hs1ContentTiles[4][0]->contentDisplayerToActivate = c.hs1Displayers["AshfordInternational"][0];
    hs1ContentTiles[4][1]->contentDisplayerToActivate = c.hs1Displayers["AshfordInternational"][1];
    hs1ContentTiles[4][2]->contentDisplayerToActivate = c.hs1Displayers["AshfordInternational"][2];
    hs1ContentTiles[4][3]->contentDisplayerToActivate = c.hs1Displayers["AshfordInternational"][3];
    hs1ContentTiles[4][4]->contentDisplayerToActivate = c.hs1Displayers["AshfordInternational"][4];
    
    // Crossrail
    crossrailLocationTiles[4]->title = "Soho";
    crossrailLocationTiles[3]->title = "Tottenham Court Road";
    crossrailLocationTiles[2]->title = "Barbican";
    crossrailLocationTiles[1]->title = "Liverpool Street";
    crossrailLocationTiles[0]->title = "Canary Wharf";
    
    // Canary Wharf
    crossrailContentTiles[0][0]->title = "Station Model";
    crossrailContentTiles[0][1]->title = "Crossrail Place";
    crossrailContentTiles[0][2]->title = "Elevated Walkway";
    crossrailContentTiles[0][3]->title = "Section View of Crossrail Place";
    crossrailContentTiles[0][4]->title = "Cofferdam Construction";
    crossrailContentTiles[0][0]->contentDisplayerToActivate = c.crossrailDisplayers["CanaryWharf"][0];
    crossrailContentTiles[0][1]->contentDisplayerToActivate = c.crossrailDisplayers["CanaryWharf"][1];
    crossrailContentTiles[0][2]->contentDisplayerToActivate = c.crossrailDisplayers["CanaryWharf"][2];
    crossrailContentTiles[0][3]->contentDisplayerToActivate = c.crossrailDisplayers["CanaryWharf"][3];
    crossrailContentTiles[0][4]->contentDisplayerToActivate = c.crossrailDisplayers["CanaryWharf"][4];
    
    // Liverpool Street
    crossrailContentTiles[1][0]->title = "Station Model";
    crossrailContentTiles[1][1]->title = "Historical Layers";
    crossrailContentTiles[1][2]->title = "Excavation Site";
    crossrailContentTiles[1][3]->title = "Plague Pit";
    crossrailContentTiles[1][4]->title = "The Archaeological Dig";
    crossrailContentTiles[1][0]->contentDisplayerToActivate = c.crossrailDisplayers["LiverpoolStreet"][0];
    crossrailContentTiles[1][1]->contentDisplayerToActivate = c.crossrailDisplayers["LiverpoolStreet"][1];
    crossrailContentTiles[1][2]->contentDisplayerToActivate = c.crossrailDisplayers["LiverpoolStreet"][2];
    crossrailContentTiles[1][3]->contentDisplayerToActivate = c.crossrailDisplayers["LiverpoolStreet"][3];
    crossrailContentTiles[1][4]->contentDisplayerToActivate = c.crossrailDisplayers["LiverpoolStreet"][4];
    
    // Barbican
    crossrailContentTiles[2][0]->title = "Floating Track Slab Model";
    crossrailContentTiles[2][1]->title = "Railway Gantry";
    crossrailContentTiles[2][2]->title = "Tracks Under the Barbican";
    crossrailContentTiles[2][3]->title = "Installing Floating Track";
    crossrailContentTiles[2][4]->title = "Silent Tracks";
    crossrailContentTiles[2][0]->contentDisplayerToActivate = c.crossrailDisplayers["Barbican"][0];
    crossrailContentTiles[2][1]->contentDisplayerToActivate = c.crossrailDisplayers["Barbican"][1];
    crossrailContentTiles[2][2]->contentDisplayerToActivate = c.crossrailDisplayers["Barbican"][2];
    crossrailContentTiles[2][3]->contentDisplayerToActivate = c.crossrailDisplayers["Barbican"][3];
    crossrailContentTiles[2][4]->contentDisplayerToActivate = c.crossrailDisplayers["Barbican"][4];
    
    // Tottenham Court Road
    crossrailContentTiles[3][0]->title = "Station Model";
    crossrailContentTiles[3][1]->title = "Platform Tunnel";
    crossrailContentTiles[3][2]->title = "Tunnel Boring Machines";
    crossrailContentTiles[3][3]->title = "Concrete Ring Construction";
    crossrailContentTiles[3][4]->title = "Station Design";
    crossrailContentTiles[3][0]->contentDisplayerToActivate = c.crossrailDisplayers["TottenhamCourtRoad"][0];
    crossrailContentTiles[3][1]->contentDisplayerToActivate = c.crossrailDisplayers["TottenhamCourtRoad"][1];
    crossrailContentTiles[3][2]->contentDisplayerToActivate = c.crossrailDisplayers["TottenhamCourtRoad"][2];
    crossrailContentTiles[3][3]->contentDisplayerToActivate = c.crossrailDisplayers["TottenhamCourtRoad"][3];
    crossrailContentTiles[3][4]->contentDisplayerToActivate = c.crossrailDisplayers["TottenhamCourtRoad"][4];
    
    // Soho
    crossrailContentTiles[4][0]->title = "Wallasea Island";
    crossrailContentTiles[4][1]->title = "Grout Shaft";
    crossrailContentTiles[4][2]->title = "Sinking Ground";
    crossrailContentTiles[4][3]->title = "Monitoring Spots";
    crossrailContentTiles[4][4]->title = "Tunnelling Under Historic Buildings";
    crossrailContentTiles[4][0]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][0];
    crossrailContentTiles[4][1]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][1];
    crossrailContentTiles[4][2]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][2];
    crossrailContentTiles[4][3]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][3];
    crossrailContentTiles[4][4]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][4];
    
    hs1MainTile->title = "HS1";
    crossrailMainTile->title = "Crossrail";
}

//--------------------------------------------------------------
void InteractiveMenu::onMainButtonClicked(string & title) {
    if(title == hs1MainTile->title) {
        loadHs1 = true;
        loadCrossrail = false;
        leftOn = true;
        rightOn = false;
    }
    else if (title == crossrailMainTile->title)
    {
        loadHs1 = false;
        loadCrossrail = true;
        rightOn = true;
        leftOn = false;
    }
    for(int i = 0; i < BUTTON_AMT; i++) {
        bLeftActive[i] = false;
        bRightActive[i] = false;
    }
}

//--------------------------------------------------------------
void InteractiveMenu::onLabelClicked(string & title) {
    if(leftOn) {
        for(int i = 0; i < BUTTON_AMT; i++) {
            if(lLocations[i]->title == title) {
                if(hs1LocationTiles[i]->activate()) {
                    activateLeftLocation(i);
                    // Deactivate all crossrail and hs1 content displayers
                    for(auto location = c.hs1Displayers.begin(); location != c.hs1Displayers.end(); location++) {
                        for(auto content = location->second.begin(); content != location->second.end(); content++) {
                            (*content)->setIsActive(false);
                        }
                    }
                    for(auto location = c.crossrailDisplayers.begin(); location != c.crossrailDisplayers.end(); location++) {
                        for(auto content = location->second.begin(); content != location->second.end(); content++) {
                            (*content)->setIsActive(false);
                        }
                    }
                    // Set globals
                    buttonClicked = true;
                    Globals::buttonPressed = true;
                }
            }
        }
    } else if(rightOn) {
        for(int i = 0; i < BUTTON_AMT; i++) {
            if(rLocations[i]->title == title) {
                if(crossrailLocationTiles[BUTTON_AMT - 1 - i]->activate()) {
                    activateRightLocation(BUTTON_AMT - 1 - i);
                    // Deactivate all crossrail and hs1 content displayers
                    for(auto location = c.hs1Displayers.begin(); location != c.hs1Displayers.end(); location++) {
                        for(auto content = location->second.begin(); content != location->second.end(); content++) {
                            (*content)->setIsActive(false);
                        }
                    }
                    for(auto location = c.crossrailDisplayers.begin(); location != c.crossrailDisplayers.end(); location++) {
                        for(auto content = location->second.begin(); content != location->second.end(); content++) {
                            (*content)->setIsActive(false);
                        }
                    }
                    // Set globals
                    buttonClicked = true;
                    Globals::buttonPressed = true;
                }
            }
        }
    }
}

//--------------------------------------------------------------
void InteractiveMenu::update()
{
    hs1MainTile->update(easeIn);
    for(int i = 0; i < BUTTON_AMT; i++) {
        hs1LocationTiles[i]->update(easeIn);
        for(int j = 0; j < BUTTON_AMT; j++) {
            hs1ContentTiles[i][j]->update(easeIn);
        }
    }
    crossrailMainTile->update(easeOut);
    for(int i = 0; i < BUTTON_AMT; i++) {
       crossrailLocationTiles[i]->update(easeIn);
        for(int j = 0; j < BUTTON_AMT; j++) {
            crossrailContentTiles[i][j]->update(easeIn);
        }
    }
    
    // update content
    c.update();
}

//--------------------------------------------------------------
void InteractiveMenu::drawMenu() {
    for(int i = 0; i < BUTTON_AMT; i++) {
        for(int j = 0; j < BUTTON_AMT; j++) {
            hs1ContentTiles[i][j]->drawLines();
            crossrailContentTiles[i][j]->drawLines();

        }
        hs1LocationTiles[i]->drawLines();
        crossrailLocationTiles[i]->drawLines();
    }
    
    for(int i = 0; i < BUTTON_AMT; i++) {
        for(int j = 0; j < BUTTON_AMT; j++) {
            hs1ContentTiles[i][j]->draw();
        }
        hs1LocationTiles[i]->draw();
    }
    hs1MainTile->draw();
    
    for(int i = 0; i < BUTTON_AMT; i++) {
        for(int j = 0; j < BUTTON_AMT; j++) {
            crossrailContentTiles[i][j]->draw();
        }
        crossrailLocationTiles[i]->draw();
    }
    crossrailMainTile->draw();
}

//--------------------------------------------------------------
void InteractiveMenu::drawContent()
{
    // content class draw function
    c.draw();
}

//--------------------------------------------------------------
void InteractiveMenu::activateLeftLocation(int index) {
    if(!bLeftActive[index]) {
        snd1.play();
    }
    for(int i = 0; i < BUTTON_AMT; i++) {
        if(i == index) {
            bLeftActive[i] = true;
            if(!c.introSounds[0][i].isPlaying()) c.introSounds[0][i].play();
        }
        else {
            bLeftActive[i] = false;
            if(c.introSounds[0][i].isPlaying()) c.introSounds[0][i].stop();
        }
    }
    c.stopAudio();
    hs1Intro.stop();
    crossrailIntro.stop();
}

//--------------------------------------------------------------
void InteractiveMenu::activateRightLocation(int index) {
    if(!bRightActive[index]) {
        snd1.play();
    }// play menu button sound
    for(int i = 0; i < BUTTON_AMT; i++) {
        if(i == index) {
            bRightActive[i] = true;
            if(!c.introSounds[1][i].isPlaying()) c.introSounds[1][i].play();
        }
        else {
            bRightActive[i] = false;
            if(c.introSounds[1][i].isPlaying()) c.introSounds[1][i].stop();
        }
    }
    c.stopAudio();
    hs1Intro.stop();
    crossrailIntro.stop();
}

//--------------------------------------------------------------
void InteractiveMenu::activateLeftContent(int locationIndex, int contentIndex) {
    string locationNames[5];
    locationNames[0] = "StPancras";
    locationNames[1] = "StratfordInternational";
    locationNames[2] = "EbbsfleetInternational";
    locationNames[3] = "MedwayViaduct";
    locationNames[4] = "AshfordInternational";

    // Might need to play a sound here:
    //if(!lCon[locationIndex][contentIndex].isSelected) {
    snd2.play();
    //}
    
    for(auto location = c.hs1Displayers.begin(); location != c.hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setIsActive(false);
        }
    }
    c.hs1Displayers[locationNames[locationIndex]][contentIndex]->setIsActive(true);
    if (!Globals::vignetteOn)
        Globals::vignetteOn = true;
}

//--------------------------------------------------------------
void InteractiveMenu::activateRightContent(int locationIndex, int contentIndex) {
    string locationNames[5];
    locationNames[0] = "CanaryWharf";
    locationNames[1] = "LiverpoolStreet";
    locationNames[2] = "Barbican";
    locationNames[3] = "TottenhamCourtRoad";
    locationNames[4] = "Soho";
    // Maybe need to play sound here
    
//    if(!rCon[locationIndex][contentIndex].isSelected) {
        snd2.play();
//    }
    
    for(auto location = c.crossrailDisplayers.begin(); location != c.crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setIsActive(false);
        }
    }
    c.crossrailDisplayers[locationNames[locationIndex]][contentIndex]->setIsActive(true);
    if (!Globals::vignetteOn)
        Globals::vignetteOn = true;
}
