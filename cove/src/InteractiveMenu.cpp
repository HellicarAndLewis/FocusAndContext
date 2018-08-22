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
    areaDiff = mainArea - subArea;
    padding = _padding;
    paddingVertical = padding - 10;
    contentHeight = (height - padding - mainArea + (areaDiff / 2)) - mainArea - paddingVertical;
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

    for(int  i = 0; i < BUTTON_AMT; i++) {
        ofAddListener(lLocations[i]->onLabelClicked, this, &InteractiveMenu::onLabelClicked);
        ofAddListener(rLocations[i]->onLabelClicked, this, &InteractiveMenu::onLabelClicked);
    }
    
    // Set the base positions of the buttons.
    ofVec2f hs1Base = ofVec2f(padding, height - padding - mainArea);
    ofVec2f crossrailBase = ofVec2f((width - padding) - mainArea, height - padding - mainArea);
    
    // Initialize all my tile pointers;
    // Main tiles
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
    
    vector<InteractiveTile*> allInteractiveTiles;
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
    
    // Setup content Tiles
    for(int i = 0; i < hs1ContentTiles.size(); i++) {
        for(int j = 0; j < hs1ContentTiles[i].size(); j++) {
            hs1ContentTiles[i][j]->parentTile = hs1LocationTiles[i];
            hs1ContentTiles[i][j]->size = ofVec2f(mainArea - 10, mainArea - 10);
            hs1ContentTiles[i][j]->position = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            hs1ContentTiles[i][j]->intermediateTarget = ofVec2f((mainArea + padding), 0);
            hs1ContentTiles[i][j]->expandTarget = ofVec2f((mainArea + padding), (i - j) * (mainArea + padding));
            hs1ContentTiles[i][j]->isExpanded = false;
            hs1ContentTiles[i][j]->allTiles = allInteractiveTiles;
            hs1ContentTiles[i][j]->contentDisplayerToActivate = c.hs1Displayers["StPancras"][0];
            hs1ContentTiles[i][j]->setup();
        }
    }
    
    for(int i = 0; i < crossrailContentTiles.size(); i++) {
        for(int j = 0; j < crossrailContentTiles[i].size(); j++) {
            crossrailContentTiles[i][j]->parentTile = crossrailLocationTiles[i];
            crossrailContentTiles[i][j]->position = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->collapseTarget = ofVec2f(0, 0);
            crossrailContentTiles[i][j]->intermediateTarget = ofVec2f(-(mainArea + padding), 0);
            crossrailContentTiles[i][j]->expandTarget = ofVec2f(-(mainArea + padding), (i - j) * (mainArea + padding));
            crossrailContentTiles[i][j]->size = ofVec2f(mainArea - 10, mainArea - 10);
            crossrailContentTiles[i][j]->isExpanded = false;
            crossrailContentTiles[i][j]->allTiles = allInteractiveTiles;
            crossrailContentTiles[i][j]->contentDisplayerToActivate = c.crossrailDisplayers["Soho"][0];
            crossrailContentTiles[i][j]->setup();
        }
    }

    // Setup Location Tiles
    for(int i = 0; i < hs1LocationTiles.size(); i++) {
        hs1LocationTiles[i]->parentTile = hs1MainTile;
        hs1LocationTiles[i]->position = ofVec2f(0, 0);
        hs1LocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        hs1LocationTiles[i]->expandTarget = ofVec2f(0, - (i+1) * mainArea - (i+1) * padding);
        hs1LocationTiles[i]->size = ofVec2f(mainArea - 10, mainArea - 10);
        hs1LocationTiles[i]->contentTilesToExpand = hs1ContentTiles[i];
        for(int j = 0; j < hs1ContentTiles.size(); j++) {
            if(j != i) {
                for(int k = 0; k < BUTTON_AMT; k++) {
                    hs1LocationTiles[i]->contentTilesToCollapse.push_back(hs1ContentTiles[j][k]);
                }
            }
        }
        hs1LocationTiles[i]->allTiles = allInteractiveTiles;
        hs1LocationTiles[i]->setup();
    }
    
    for(int i = 0; i < crossrailLocationTiles.size(); i++) {
        crossrailLocationTiles[i]->parentTile = crossrailMainTile;
        crossrailLocationTiles[i]->position = ofVec2f(0, 0);
        crossrailLocationTiles[i]->collapseTarget = ofVec2f(0, 0);
        crossrailLocationTiles[i]->expandTarget = ofVec2f(0, - (i+1) * mainArea - (i+1) * padding);
        crossrailLocationTiles[i]->size = ofVec2f(mainArea - 10, mainArea - 10);
        crossrailLocationTiles[i]->contentTilesToExpand = crossrailContentTiles[i];
        for(int j = 0; j < crossrailContentTiles.size(); j++) {
            if(j != i) {
                for(int k = 0; k < BUTTON_AMT; k++) {
                    crossrailLocationTiles[i]->contentTilesToCollapse.push_back(crossrailContentTiles[j][k]);
                }
            }
        }
        crossrailLocationTiles[i]->allTiles = allInteractiveTiles;
        crossrailLocationTiles[i]->setup();
    }
    
    // Setup the Main tiles.
    hs1MainTile->position = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->target = ofVec2f(hs1Base.x, hs1Base.y);
    hs1MainTile->size = ofVec2f(mainArea, mainArea);
    hs1MainTile->locationTilesToExpand = hs1LocationTiles;
    hs1MainTile->locationTilesToCollapse = crossrailLocationTiles;
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

    crossrailMainTile->position = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->target = ofVec2f(crossrailBase.x, crossrailBase.y);
    crossrailMainTile->size = ofVec2f(mainArea, mainArea);
    crossrailMainTile->locationTilesToExpand = crossrailLocationTiles;
    crossrailMainTile->locationTilesToCollapse = hs1LocationTiles;
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

    // setup left menu line
    lLine.lineLength = 0;
    lLine.drawType = 1;
    lLine.isDraw = true;
    lLine.set(padding, height - padding - mainArea, mainArea, mainArea);
    
    // setup right menu line
    rLine.lineLength = 0;
    rLine.drawType = 2;
    rLine.isDraw = true;
    rLine.set(width - padding, height - padding - mainArea, mainArea, mainArea);
    
    //----------------------
    // content stuff
    //----------------------
    
    ofxNestedFileLoader loader;
    vector<string> paths = loader.load("content/Google Drive/Arup/Research/Content/HS1");
    int labelsIndex = 0;
//    for(int i = 0; i < paths.size(); i++) {
//        vector<string> splitString = ofSplitString(paths[i], "/");
//        if(splitString.size() == 11) {
//            if(splitString[9] == "MenuButton" && splitString[10] != "Icon\r") {
//                string full = paths[i];
//                string file = splitString[splitString.size() - 1];
//                vector<string> splitFile = ofSplitString(file, ".");
//                string title = splitFile[0];
//                cout<<title<<endl;
////                string title = splitString[5] + "/" + splitString[6] + "/" + splitString[7] + "/" + splitString[8];
//                int locationIndex = c.locationsDictionary[0].at(splitString[7]);
////                hs1ContentTiles[locationIndex][labelsIndex]->title = title;
//                //contentLLabels[locationIndex][labelsIndex] = title;
//                labelsIndex++;
//                if(labelsIndex == 5) {
//                    labelsIndex = 0;
//                }
//            }
//        }
//    }
    
    loader.clearPaths();
    
//    content/Google Drive/Arup/Research/Content/HS1/Location/AshfordInternational/01_Media_ImgMap/Background/White Planel.png
    
//    paths = loader.load("content/Google Drive/Arup/Research/Content/Crossrail");
//    labelsIndex = 0;
//    for(int i = 0; i < paths.size(); i++) {
//        vector<string> splitString = ofSplitString(paths[i], "/");
//        if(splitString.size() == 11) {
//            if(splitString[9] == "MenuButton" && splitString[10] != "Icon\r") {
//                string full = paths[i];
//                string file = splitString[splitString.size() - 1];
//                vector<string> splitFile = ofSplitString(file, ".");
//                string title = splitFile[0];
////                string title = splitString[5] + "/" + splitString[6] + "/" + splitString[7] + "/" + splitString[8];
//                int locationIndex = c.locationsDictionary[1].at(splitString[7]);
////                contentRLabels[locationIndex][labelsIndex] = title;
//                cout<<title<<endl;
//                labelsIndex++;
//                if(labelsIndex == 5) {
//                    labelsIndex = 0;
//                }
//            }
//        }
//    }
    
    for(int i = 0; i < 5; i++) {
        lPoints[i].setup();
        rPoints[i].setup();
    }

    // setup content menu items
    setupLeftContent();
    setupRightContent();
    
    
    for(int i = 0; i < 5; i++) {
        for(int j = 4; j > -1; j--) {
            allCons.push_back(&rCon[j][i]);
        }
        for(int j = 4; j > -1; j--) {
            allCons.push_back(&lCon[j][i]);
        }
    }
    
    c.setCons(allCons);
    
    leftWasOn = false;
}

//--------------------------------------------------------------
void InteractiveMenu::onLabelClicked(string & title) {
    if(leftOn) {
        for(int i = 0; i < BUTTON_AMT; i++) {
            if(lLocations[i]->title == title) {
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
                // Deselect all crossrail and hs1 content
                for(int i = 0; i < allCons.size(); i++) {
                    allCons[i]->isSelected = false;
                }
                // Set globals
                buttonClicked = true;
                Globals::buttonPressed = true;
            }
        }
    } else if(rightOn) {
        for(int i = 0; i < BUTTON_AMT; i++) {
            if(rLocations[i]->title == title) {
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
                // Deselect all crossrail and hs1 content
                for(int i = 0; i < allCons.size(); i++) {
                    allCons[i]->isSelected = false;
                }
                // Set globals
                buttonClicked = true;
                Globals::buttonPressed = true;
            }
        }
    }
}

//--------------------------------------------------------------
void InteractiveMenu::setupLeftContent()
{
    // default x position
    float dX = (padding * 2);
    
    // ----------------------------------
    // content menu item 0
    // ----------------------------------
    // setup objects
    for(int j = 0; j < BUTTON_AMT; j++) {
        for (int i = 0; i < BUTTON_AMT; i++)
        {
            posLCon[j][i].set(padding, height - padding - mainArea + (areaDiff / 2));
            lCon[j][i].set(posLCon[j][i], subArea, subArea);
            lCon[j][i].drawType = 0;
            lCon[j][i].lineLength = 0;
            lCon[j][i].title = contentLLabels[j][i];
        }
        
        // setup vertical line
        lConVLines[j].lineLength = 0;
        lConVLines[j].drawType = 3;
        lConVLines[j].set(lCon[j][j].x, lCon[j][j].y, mainArea, mainArea);

        // setup horizonal line
        lConHLines[j].lineLength = 0;
        lConHLines[j].drawType = 1;
//        lConHLines[j].set(dX, height - padding - mainArea, mainArea, mainArea); //DANGER! Don't know why this doesn't need to be set
    }
}

//--------------------------------------------------------------
void InteractiveMenu::setupRightContent()
{
    // default x position
    float dX = (padding * 2);
    
    // ----------------------------------
    // content menu item 0
    // ----------------------------------
    // setup objects
    for(int j = 0; j < BUTTON_AMT; j++) {
        for (int i = 0; i < BUTTON_AMT; i++)
        {
            posRCon[j][i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
            
            rCon[j][i].set(posRCon[j][i], subArea, subArea);
            rCon[j][i].drawType = 0;
            rCon[j][i].lineLength = 0;
            rCon[j][i].title = contentRLabels[j][i];
        }
        
        // setup vertical line
        rConVLines[j].lineLength = 0;
        rConVLines[j].drawType = 3;
        rConVLines[j].set(rCon[j][j].x, rCon[j][j].y, mainArea, mainArea);
        
        // setup horizonal line
        rConHLines[j].lineLength = 0;
        rConHLines[j].drawType = 2;
        rConHLines[j].set(dX, height - padding - mainArea, mainArea, 0); //DANGER! Don't know why this doesn't need to be set
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
    
    // check button presses
//    pressedLocation();
    
    // button position and size
//    transformPortrait();
    transformLandscape();

    // draw menu content objects and lines
    drawContentMenu();
    
    // content pressed
    pressedContent();
    
    // hs1 project content menu position and size
    for(int i = 0; i < BUTTON_AMT; i++) {
        transformLeftContent(i);
        transformRightContent(i);
    }
    
    // delayed project selection swtich
    if (leftSwitch && !bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
    {
        if (!leftOn) leftOn = true;
        if (rightOn) rightOn = false;
        
        leftSwitch = false;
    }
    else if (rightSwitch && !bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
    {
        if (leftOn) leftOn = false;
        if (!rightOn) rightOn = true;
        
        rightSwitch = false;
    }
    
    // update content
    c.update();
    
    if(leftOn && !leftWasOn) {
        crossrailIntro.stop();
        c.stopLocationAudio();
        hs1Intro.play();
        leftWasOn = true;
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
        for(int i = 0; i < allCons.size(); i++) {
            allCons[i]->isSelected = false;
        }
    } else if(rightOn && leftWasOn) {
        hs1Intro.stop();
        c.stopLocationAudio();
        crossrailIntro.play();
        leftWasOn = false;
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
        for(int i = 0; i < allCons.size(); i++) {
            allCons[i]->isSelected = false;
        }
    }
}

bool InteractiveMenu::otherLeftHLinesAreInactive(int index) {
    bool b = true;
    for(int i = 0; i < BUTTON_AMT; i++) {
        if(i != index) {
            b = b && !bLLineH[i];
        }
    }
    return b;
}

bool InteractiveMenu::otherRightHLinesAreInactive(int index) {
    bool b = true;
    for(int i = 0; i < BUTTON_AMT; i++) {
        if(i != index) {
            b = b && !bRLineH[i];
        }
    }
    return b;
}

void InteractiveMenu::transformLeftContent(int index) {
    if(leftOn) {
        if(bLeftActive[index] && otherLeftHLinesAreInactive(index)) {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon[index][i].y = ofLerp(posLCon[index][i].y, contentHeight, easeOut);
                
                if (posLCon[index][i].y <= contentHeight + easeOut)
                {
                    posLCon[index][i].x = ofLerp(posLCon[index][i].x, posLeft[i].x, easeOut);
                }
            }
            
            lConVLines[index].lineLength = ofLerp(lConVLines[index].lineLength, mainArea, easeOut);
            
            //Check magic numbers here!
            if (posLCon[index][0].y < posLeft[index].y)
            {
                if (!bLLineH[index]) bLLineH[index] = true;
            }
            
            if (posLCon[index][4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lConHLines[index].lineLength = ofLerp(lConHLines[index].lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = index * (subArea + padding) + (padding * 2) + mainArea;
            float dest;
            if(index != 4) {
                dest = distance + easeIn;
            } else {
                dest = distance - easeIn;
            }
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon[index][i].x = ofLerp(posLCon[index][i].x, distance, easeIn);
                
                if(index != 4) {
                    if (posLCon[index][0].x <= dest && posLCon[index][1].x <= dest && posLCon[index][2].x <= dest && posLCon[index][3].x <= dest && posLCon[index][4].x <= dest)
                    {
                        posLCon[index][i].y = ofLerp(posLCon[index][i].y, posLeft[i].y, easeIn);
                        lConVLines[index].lineLength = ofLerp(lConVLines[index].lineLength, 0, easeIn * 2);
                        
                        // Note magic numbers again
                        if (posLCon[index][4].y >= posLeft[index].y - easeIn)
                        {
                            if (bLLineH[index]) bLLineH[index] = false;
                        }
                    }
                } else {
                    if (posLCon[index][0].x >= dest && posLCon[index][1].x >= dest && posLCon[index][2].x >= dest && posLCon[index][3].x >= dest && posLCon[index][4].x >= dest)
                    {
                        posLCon[index][i].y = ofLerp(posLCon[index][i].y, posLeft[i].y, easeIn);
                        lConVLines[index].lineLength = ofLerp(lConVLines[index].lineLength, 0, easeIn * 2);
                        
                        // Note magic numbers again
                        if (posLCon[index][4].y >= posLeft[index].y - easeIn)
                        {
                            if (bLLineH[index]) bLLineH[index] = false;
                        }
                    }
                }

            }
            
            lConHLines[index].lineLength = ofLerp(lConHLines[index].lineLength, 0, easeIn);
        }
        
        // if objects are in place, then do something...
        if(index != 4) {
            if (bLeftActive[index] && posLCon[index][4].x > posLeft[4].x - easeOut)
            {
                bLPlace[index] = true;
            }
            else {
                bLPlace[index] = false;
            }
        } else {
            if (bLeftActive[index] && posLCon[index][0].x < posLeft[0].x + easeOut)
            {
                bLPlace[index] = true;
            }
            else {
                bLPlace[index] = false;
            }
        }

    }
    else
    {
        if (posLCon[index][4].y < posLeft[0].y - easeIn)
        {
            float distance = index * (subArea + padding) + (padding * 2) + mainArea;
;
            float dest;
            if(index != 4) {
                dest = distance + easeIn;
            } else {
                dest = distance - easeIn;
            }

            // if content item #index is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon[index][i].x = ofLerp(posLCon[index][i].x, distance, easeIn);
                
                if(index != 4) {
                    if (posLCon[index][0].x <= dest && posLCon[index][1].x <= dest && posLCon[index][2].x <= dest && posLCon[index][3].x <= dest && posLCon[index][4].x <= dest)
                    {
                        posLCon[index][i].y = ofLerp(posLCon[index][i].y, posLeft[i].y, easeIn);
                        lConVLines[index].lineLength = ofLerp(lConVLines[index].lineLength, 0, easeIn * 2);
                    }
                } else {
                    if (posLCon[index][0].x >= dest && posLCon[index][1].x >= dest && posLCon[index][2].x >= dest && posLCon[index][3].x >= dest && posLCon[index][4].x >= dest)
                    {
                        posLCon[index][i].y = ofLerp(posLCon[index][i].y, posLeft[i].y, easeIn);
                        lConVLines[index].lineLength = ofLerp(lConVLines[index].lineLength, 0, easeIn * 2);
                    }
                }
            }
            
            lConHLines[index].lineLength = ofLerp(lConHLines[index].lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #index pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon[index][i].x = ofLerp(posLCon[index][i].x, padding, easeIn);
            }
        }
    }
    
    // content item #index object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon[index][i].isSelected) {
            sizeLCon[index][i] = ofLerp(sizeLCon[index][i], mainArea, easeOut);
        }
        else {
            sizeLCon[index][i] = ofLerp(sizeLCon[index][i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon[index][i].setPosition(posLCon[index][i]);
        lCon[index][i].setFromCenter(posLCon[index][i].x+subArea/2, posLCon[index][i].y+subArea/2, sizeLCon[index][i], sizeLCon[index][i]);
    }
    
    // content item #index vertical line
    lConVLines[index].setPosition(posLCon[index][index].x + subArea/2, posLeft[index].y);
    
    // horizontal line
    lConHLines[index].setPosition(posLCon[index][index].x - lConHLines[index].lineLength * 0.25 * index, posLCon[index][index].y + subArea/2);
}

void InteractiveMenu::transformRightContent(int index) {
    // if left side menu is active
    if (rightOn)
    {
        // if content item #index is active
        if (bRightActive[index] && otherRightHLinesAreInactive(index))
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon[index][i].y = ofLerp(posRCon[index][i].y, contentHeight, easeOut);
                
                if (posRCon[index][i].y <= contentHeight + easeOut)
                {
                    posRCon[index][i].x = ofLerp(posRCon[index][i].x, posRight[i].x, easeOut);
                }
            }
            
            rConVLines[index].lineLength = ofLerp(rConVLines[index].lineLength, mainArea, easeOut);
            
            if (posRCon[index][0].y < posRight[index].y)
            {
                if (!bRLineH[index]) bRLineH[index] = true;
            }
            
            if (posRCon[index][4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rConHLines[index].lineLength = ofLerp(rConHLines[index].lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (index  * (subArea + padding) + padding + mainArea);
            float dest;
            if(index != 0) {
                dest = distance + easeIn;
            } else {
                dest = distance - easeIn;
            }
            
            // if content item #3 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon[index][i].x = ofLerp(posRCon[index][i].x, distance, easeIn);
                
                if(index != 0) {
                    if (posRCon[index][0].x <= dest && posRCon[index][1].x <= dest && posRCon[index][2].x <= dest && posRCon[index][3].x <= dest && posRCon[index][4].x <= dest)
                    {
                        posRCon[index][i].y = ofLerp(posRCon[index][i].y, posRight[i].y, easeIn);
                        rConVLines[index].lineLength = ofLerp(rConVLines[index].lineLength, 0, easeIn * 2);
                        
                        if (posRCon[index][4].y >= posRight[index].y - easeIn)
                        {
                            if (bRLineH[index]) bRLineH[index] = false;
                        }
                    }
                } else {
                    if (posRCon[index][0].x >= dest && posRCon[index][1].x >= dest && posRCon[index][2].x >= dest && posRCon[index][3].x >= dest && posRCon[index][4].x >= dest)
                    {
                        posRCon[index][i].y = ofLerp(posRCon[index][i].y, posRight[i].y, easeIn);
                        rConVLines[index].lineLength = ofLerp(rConVLines[index].lineLength, 0, easeIn * 2);
                        
                        if (posRCon[index][4].y >= posRight[index].y - easeIn)
                        {
                            if (bRLineH[index]) bRLineH[index] = false;
                        }
                    }
                }

            }
            
            rConHLines[index].lineLength = ofLerp(rConHLines[index].lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if(index != 0) {
            if (bRightActive[index] && posRCon[index][0].x > posRight[0].x - easeOut)
            {
                bRPlace[index] = true;
            }
            else {
                bRPlace[index] = false;
            }
        } else {
            if (bRightActive[index] && posRCon[index][4].x < posRight[4].x + easeOut)
            {
                bRPlace[index] = true;
            }
            else {
                bRPlace[index] = false;
            }
        }
    }
    else
    {
        if (posRCon[index][4].y < posRight[index].y - easeIn)
        {
            float distance = width - padding - subArea - (index  * (subArea + padding) + padding + mainArea);
            float dest;
            if(index != 0) {
                dest = distance + easeIn;
            } else {
                dest = distance - easeIn;
            }
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon[index][i].x = ofLerp(posRCon[index][i].x, distance, easeIn);
                
                if(index != 0) {
                    if (posRCon[index][0].x <= dest && posRCon[index][1].x <= dest && posRCon[index][2].x <= dest && posRCon[index][3].x <= dest && posRCon[index][4].x <= dest)
                    {
                        posRCon[index][i].y = ofLerp(posRCon[index][i].y, posRight[i].y, easeIn);
                        rConVLines[index].lineLength = ofLerp(rConVLines[index].lineLength, 0, easeIn * 2);
                    }
                } else {
                    if (posRCon[index][0].x >= dest && posRCon[index][1].x >= dest && posRCon[index][2].x >= dest && posRCon[index][3].x >= dest && posRCon[index][4].x >= dest)
                    {
                        posRCon[index][i].y = ofLerp(posRCon[index][i].y, posRight[i].y, easeIn);
                        rConVLines[index].lineLength = ofLerp(rConVLines[index].lineLength, 0, easeIn * 2);
                    }
                }

            }
            
            rConHLines[index].lineLength = ofLerp(rConHLines[index].lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #index pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon[index][i].x = ofLerp(posRCon[index][i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #index object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon[index][i].isSelected) {
            sizeRCon[index][i] = ofLerp(sizeRCon[index][i], mainArea, easeOut);
        }
        else {
            sizeRCon[index][i] = ofLerp(sizeRCon[index][i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon[index][i].setPosition(posRCon[index][i]);
        rCon[index][i].setFromCenter(posRCon[index][i].x+subArea/2, posRCon[index][i].y+subArea/2, sizeRCon[index][i], sizeRCon[index][i]);
    }
    
    // content item #1 vertical line
    rConVLines[index].setPosition(posRCon[index][index].x + subArea/2, posRight[index].y);
    
    // horizontal line
    if(index == 0) {
        rConHLines[index].setPosition(posRCon[index][index].x + rConHLines[index].lineLength * 0.25 * index, posRCon[index][0].y + subArea/2); // note this is ugly
    } else {
        rConHLines[index].setPosition(posRCon[index][index].x + rConHLines[index].lineLength * 0.25 * index, posRCon[index][1].y + subArea/2); // note this is ugly
    }

}

//--------------------------------------------------------------
void InteractiveMenu::transformLandscape()
{
    // left sub menu animations
    for (int i = 0; i < length; i++)
    {
        if (leftOn)
        {
            float distance = i * (subArea + padding) + (padding * 2) + mainArea;
            posLeft[i].x = ofLerp(posLeft[i].x, padding + (areaDiff/2), easeOut);
            posLeft[i].y = ofLerp(posLeft[i].y, distance, easeOut);
            if (bLeftActive[i])
            {
                sizeLeft[i] = ofLerp(sizeLeft[i], mainArea, easeOut);
            }
            else
            {
                sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeOut);
            }

        }
        else
        {
            posLeft[i].x = ofLerp(posLeft[i].x, padding, easeIn);
            posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);

            sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeIn);

            bLeftActive[i] = false;
        }

        // update objects position and size // Change sized here maybe JB
        lPoints[i].setPosition(posLeft[i]);
        lPoints[i].setFromCenter(posLeft[i].x+subArea/2, posLeft[i].y+subArea/2, sizeLeft[i], sizeLeft[i]);
        lPoints[i].isSelected = bLeftActive[i];
    }

    if (leftClose)
    {
        for (int i = 0; i < length; i++)
        {
            sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeIn);
            bLeftActive[i] = false;
        }

        leftClose = false;
    }

    // right sub menu animations
    for (int i = 0; i < length; i++)
    {
        if (rightOn)
        {
            float distance = (i  * (subArea + padding) + (padding * 1) + mainArea);
            posRight[i].x = ofLerp(posRight[i].x, width - padding - subArea - (areaDiff/2), easeOut);
            posRight[i].y = ofLerp(posRight[i].y, distance, easeOut);
            if (bLeftActive[i])
            {
                sizeRight[i] = ofLerp(sizeRight[i], mainArea, easeOut);
            }
            else
            {
                sizeRight[i] = ofLerp(sizeRight[i], subArea, easeOut);
            }
        }
        else
        {
            posRight[i].x = ofLerp(posRight[i].x, width - padding - subArea, easeIn);
            posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);

            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);

            bRightActive[i] = false;
        }

        // update objects position and size
        rPoints[i].setPosition(posRight[i]);
        rPoints[i].setFromCenter(posRight[i].x+subArea/2, posRight[i].y+subArea/2, sizeRight[i], sizeRight[i]);
        rPoints[i].isSelected = bRightActive[i];
    }

    if (rightClose)
    {
        for (int i = 0; i < length; i++)
        {
            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);
            bRightActive[i] = false;
        }

        rightClose = false;
    }

    // Line stuff....
    float lineDist = (length-1) * (subArea + padding) + (padding + subArea);

    // left side lines
    if (leftOn)
    {
        lLine.lineLength = ofLerp(lLine.lineLength, lineDist, easeOut);
    }
    else
    {
        lLine.lineLength = ofLerp(lLine.lineLength, 0, easeIn);// * 2);
    }

    // right side lines
    if (rightOn)
    {
        rLine.lineLength = ofLerp(rLine.lineLength, lineDist, easeOut);
    }
    else
    {
        rLine.lineLength = ofLerp(rLine.lineLength, 0, easeIn);// * 2);
    }
}

//--------------------------------------------------------------
void InteractiveMenu::transformPortrait()
{
    // left sub menu animations
    for (int i = 0; i < length; i++)
    {
        if (leftOn)
        {
            if (bLeftActive[i])
            {
                float distance = i * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], mainArea, easeOut);
            }
            else
            {
                float distance = i * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeOut);
            }
            
        }
        else
        {
            posLeft[i].x = ofLerp(posLeft[i].x, padding, easeIn);
            posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);
            
            sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeIn);
            
            bLeftActive[i] = false;
        }
        
        // update objects position and size // Change sized here maybe JB
        lPoints[i].setPosition(posLeft[i]);
        lPoints[i].setFromCenter(posLeft[i].x+subArea/2, posLeft[i].y+subArea/2, sizeLeft[i], sizeLeft[i]);
        lPoints[i].isSelected = bLeftActive[i];
    }
    
    if (leftClose)
    {
        for (int i = 0; i < length; i++)
        {
            sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeIn);
            bLeftActive[i] = false;
        }
        
        leftClose = false;
    }
    
    // right sub menu animations
    for (int i = 0; i < length; i++)
    {
        if (rightOn)
        {
            float distance = width - padding - subArea - (i  * (subArea + padding) + (padding * 1) + mainArea);
            
            if (bRightActive[i])
            {
                posRight[i].x = ofLerp(posRight[i].x, distance, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], mainArea, easeOut);
            }
            else
            {
                posRight[i].x = ofLerp(posRight[i].x, distance, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], subArea, easeOut);
            }
        }
        else
        {
            posRight[i].x = ofLerp(posRight[i].x, width - padding - subArea, easeIn);
            posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);
            
            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);
            
            bRightActive[i] = false;
        }
        
        // update objects position and size
        rPoints[i].setPosition(posRight[i]);
        rPoints[i].setFromCenter(posRight[i].x+subArea/2, posRight[i].y+subArea/2, sizeRight[i], sizeRight[i]);
        rPoints[i].isSelected = bRightActive[i];
    }
    
    if (rightClose)
    {
        for (int i = 0; i < length; i++)
        {
            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);
            bRightActive[i] = false;
        }
        
        rightClose = false;
    }
    
    // Line stuff....
    float lineDist = (length-1) * (subArea + padding) + (padding + subArea + padding);
    
    // left side lines
    if (leftOn)
    {
        lLine.lineLength = ofLerp(lLine.lineLength, lineDist, easeOut);
    }
    else
    {
        lLine.lineLength = ofLerp(lLine.lineLength, 0, easeIn);// * 2);
    }
    
    // right side lines
    if (rightOn)
    {
        rLine.lineLength = ofLerp(rLine.lineLength, lineDist, easeOut);
    }
    else
    {
        rLine.lineLength = ofLerp(rLine.lineLength, 0, easeIn);// * 2);
    }
}

//--------------------------------------------------------------
void InteractiveMenu::drawContentMenu()
{
    // ----------------------------------
    // left content menu items drawing
    // ----------------------------------
    // objects
    for(int j = 0; j < BUTTON_AMT; j++) {
        for (int i = 0; i < BUTTON_AMT; i++) {
            lCon[j][i].isDraw = bLLineH[j];
            // fade in labels
            lCon[j][i].fadeLabel = !bLPlace[j];
        }
        // lines
        lConVLines[j].isDraw = bLLineH[j];
        lConHLines[j].isDraw = bLLineH[j];
    }
    
    // ----------------------------------
    // right content menu items drawing
    // ----------------------------------
    
    for(int j = 0; j < BUTTON_AMT; j++) {
        for (int i = 0; i < BUTTON_AMT; i++) {
            rCon[j][i].isDraw = bRLineH[j];
            // fade in labels
            rCon[j][i].fadeLabel = !bRPlace[j];
        }
        // lines
        rConVLines[j].isDraw = bRLineH[j];
        rConHLines[j].isDraw = bRLineH[j];
    }
}

//--------------------------------------------------------------
void InteractiveMenu::drawMenu() {
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
void InteractiveMenu::activateLeftLocation(int index) {
    if(!bLeftActive[index]) {
        snd1.play();
    }// play menu button sound
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
void InteractiveMenu::pressedLocation()
{
    for (int i = 0; i < length; i++)
    {
        // if left menu is active:
        if (lPoints[i].isMousePressed(0) == 1 && leftOn /*&& !bLeftActive[i]*/ && !buttonClicked)
        {
            // Activate location that was clicked on
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
            // Deselect all crossrail and hs1 content
            for(int i = 0; i < allCons.size(); i++) {
                allCons[i]->isSelected = false;
            }
            // Set globals
            buttonClicked = true;
            Globals::buttonPressed = true;
        }
        
        // check for right button clicks
        if (rPoints[i].isMousePressed(0) == 1 && rightOn /*&& !bRightActive[i]*/ && !buttonClicked)
        {
            // Activate location that was clicked on
            activateRightLocation(i);
            
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
            
            // Deselect all crossrail and hs1 content
            for(int i = 0; i < allCons.size(); i++) {
                allCons[i]->isSelected = false;
            }
            
            // Set globals
            buttonClicked = true;
            Globals::buttonPressed = true;
        }
    }
}

void InteractiveMenu::activateLeftContent(int locationIndex, int contentIndex) {
    string locationNames[5];
    locationNames[0] = "StPancras";
    locationNames[1] = "StratfordInternational";
    locationNames[2] = "EbbsfleetInternational";
    locationNames[3] = "MedwayViaduct";
    locationNames[4] = "AshfordInternational";

    if(!lCon[locationIndex][contentIndex].isSelected) {
        snd2.play();
    }
    for(int i = 0; i < BUTTON_AMT; i++) {
        lCon[locationIndex][i].isSelected = false;
    }
    lCon[locationIndex][contentIndex].isSelected = true;
    
    // load current content, enable vignette
    //c.load(0, 0, 0);
    for(auto location = c.hs1Displayers.begin(); location != c.hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setIsActive(false);
        }
    }
    c.hs1Displayers[locationNames[locationIndex]][contentIndex]->setIsActive(true);
    if (!Globals::vignetteOn)
        Globals::vignetteOn = true;
}

void InteractiveMenu::activateRightContent(int locationIndex, int contentIndex) {
    string locationNames[5];
    locationNames[0] = "CanaryWharf";
    locationNames[1] = "LiverpoolStreet";
    locationNames[2] = "Barbican";
    locationNames[3] = "TottenhamCourtRoad";
    locationNames[4] = "Soho";
    
    if(!rCon[locationIndex][contentIndex].isSelected) {
        snd2.play();
    }
    for(int i = 0; i < BUTTON_AMT; i++) {
        rCon[locationIndex][i].isSelected = false;
    }
    rCon[locationIndex][contentIndex].isSelected = true;
    
    // load current content, enable vignette
    //c.load(0, 0, 0);
    for(auto location = c.crossrailDisplayers.begin(); location != c.crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setIsActive(false);
        }
    }
    c.crossrailDisplayers[locationNames[locationIndex]][contentIndex]->setIsActive(true);
    if (!Globals::vignetteOn)
        Globals::vignetteOn = true;
}


//--------------------------------------------------------------
void InteractiveMenu::pressedContent()
{
    // ------------------------------------
    // left content menu item selection
    // ------------------------------------
    for(int i = 0; i < BUTTON_AMT; i++) {
        bool contentActivated = false;
        for(int j = 0; j < BUTTON_AMT; j++) {

//            cout<<i<<","<<j<<": "<<"enabled: "<<lCon[i][j].enabled<<endl;
//            lCon[i][j].isMousePressed()
            if(lCon[i][j].isMousePressed() && bLPlace[i] && !lCon[i][j].isSelected) {
                activateLeftContent(i, j);
                contentActivated = true;
                break;
            }
        }
        if(!contentActivated) {
            if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
            {
                for(int j = 0; j < BUTTON_AMT; j++) {
                    lCon[i][j].isSelected = false;
                }
                // close content, stop video, and disable vignette
                c.item = 5;
                c.stopVideos();
                c.stopAudio();
                // c.stopLocationAudio();
                if (Globals::vignetteOn)
                    Globals::vignetteOn = false;
            }
        }
    }
    
    // ------------------------------------
    // right content menu item selection
    // ------------------------------------
    for(int i = 0; i < BUTTON_AMT; i++) {
        bool contentActivated = false;
        for(int j = 0; j < BUTTON_AMT; j++) {
            if(rCon[i][j].isMousePressed() && bRPlace[i] && !rCon[i][j].isSelected) {
                activateRightContent(i, j);
                contentActivated = true;
                break;
            }
        }
        if(!contentActivated) {
            if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
            {
                for(int j = 0; j < BUTTON_AMT; j++) {
                    rCon[i][j].isSelected = false;
                }
                // close content, stop video, and disable vignette
                c.item = 5;
                c.stopVideos();
                c.stopAudio();
                // c.stopLocationAudio();
                if (Globals::vignetteOn)
                    Globals::vignetteOn = false;
            }
        }
    }
}

//--------------------------------------------------------------
void InteractiveMenu::drawContent()
{
    // content class draw function
    c.draw();
}
