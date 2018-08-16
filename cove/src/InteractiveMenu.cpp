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
    
    // setup left location menu
    for (int i = 0; i < length; i++)
    {
        posLeft[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        sizeLeft[i] = subArea;
        
        lPoints[i].drawType = 0;
        lPoints[i].set(padding, height - padding - mainArea + (areaDiff / 2), subArea, subArea);
        lPoints[i].isMainTile = false;
        lPoints[i].fadeLabel = false;
        lPoints[i].isDraw = true;
    }
    
    // setup right location menu
    for (int i = 0; i < length; i++)
    {
        posRight[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        sizeRight[i] = subArea;
        
        rPoints[i].drawType = 0;
        rPoints[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2), subArea, subArea);
        rPoints[i].isMainTile = false;
        rPoints[i].fadeLabel = false;
        rPoints[i].isDraw = true;
    }
    
//    ofAddListener(Location.onLabelClicked, this, &InteractiveMenu::onLabelClicked);
    
    // left sub menu titles
    lPoints[0].title = "HS1/Location/StPancras";
    lPoints[1].title = "HS1/Location/StratfordInternational";
    lPoints[2].title = "HS1/Location/EbbsfleetInternational";
    lPoints[3].title = "HS1/Location/MedwayViaduct";
    lPoints[4].title = "HS1/Location/AshfordInternational";
    // right sub menu titles
    rPoints[4].title = "Crossrail/Location/Soho";
    rPoints[3].title = "Crossrail/Location/TottenhamCourtRoad";
    rPoints[2].title = "Crossrail/Location/Barbican";
    rPoints[1].title = "Crossrail/Location/LiverpoolStreet";
    rPoints[0].title = "Crossrail/Location/CanaryWharf";
    
    // setup left menu main
    leftMain.isMainTile = true;
    leftMain.fadeLabel = false;
    leftMain.title = "HS1";
    leftMain.lineLength = 0;
    leftMain.drawType = 0;
    leftMain.isDraw = true;
    leftMain.set(padding, height - padding - mainArea, mainArea, mainArea);
    leftMain.setup();
    
    // setup right menu main
    rightMain.isMainTile = true;
    rightMain.fadeLabel = false;
    rightMain.title = "Crossrail";
    rightMain.lineLength = 0;
    rightMain.drawType = 0;
    rightMain.isDraw = true;
    rightMain.set((width - padding) - mainArea, height - padding - mainArea, mainArea, mainArea);
    rightMain.setup();
    
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
    for(int i = 0; i < paths.size(); i++) {
        vector<string> splitString = ofSplitString(paths[i], "/");
        if(splitString.size() == 11) {
            if(splitString[9] == "MenuButton" && splitString[10] != "Icon\r") {
                string full = paths[i];
                string title = splitString[5] + "/" + splitString[6] + "/" + splitString[7] + "/" + splitString[8];
                int locationIndex = c.locationsDictionary[0].at(splitString[7]);
                contentLLabels[locationIndex][labelsIndex] = title;
                labelsIndex++;
                if(labelsIndex == 5) {
                    labelsIndex = 0;
                }
            }
        }
    }
    
    loader.clearPaths();
    
//    content/Google Drive/Arup/Research/Content/HS1/Location/AshfordInternational/01_Media_ImgMap/Background/White Planel.png
    
    paths = loader.load("content/Google Drive/Arup/Research/Content/Crossrail");
    labelsIndex = 0;
    for(int i = 0; i < paths.size(); i++) {
        vector<string> splitString = ofSplitString(paths[i], "/");
        if(splitString.size() == 11) {
            if(splitString[9] == "MenuButton" && splitString[10] != "Icon\r") {
                string full = paths[i];
                string title = splitString[5] + "/" + splitString[6] + "/" + splitString[7] + "/" + splitString[8];
                int locationIndex = c.locationsDictionary[1].at(splitString[7]);
                contentRLabels[locationIndex][labelsIndex] = title;
                labelsIndex++;
                if(labelsIndex == 5) {
                    labelsIndex = 0;
                }
            }
        }
    }
    
    for(int i = 0; i < 5; i++) {
        lPoints[i].setup();
        rPoints[i].setup();
    }

    // setup content menu items
    setupLeftContent();
    setupRightContent();
    
    // content media setup
    c.setup();
    
    
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
            cout<<"X: "<<width - padding - subArea<<endl;
            cout<<"Y: "<<height - padding - mainArea + (areaDiff / 2)<<endl;
            
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
    // check button presses
    pressedLocation();
    
    // button position and size
//    transformPortrait();
    transformLandscape();

    // draw menu content objects and lines
    drawContentMenu();
    
    // content pressed
    pressedContent();
    
    // draw menu objects and lines
    drawMenu();
    
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
