//
//  InteractiveMenu.cpp
//  Cove
//
//  Created by Jason Walters on 13/02/2016.
//  Last edited by Jason Walters on 9/03/2016.
//
//

#include "InteractiveMenu.h"
#include "Globals.h"
#include "ofxNestedFileLoader.h"

//--------------------------------------------------------------
void InteractiveMenu::setup(int _w, int _h, float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut)
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
    hs1Intro.load("content/Dropbox/ArupContentForInstallation/Placeholder/no_audio.wav");
    hs1Intro.setMultiPlay(false);
    hs1Intro.setLoop(false);
    
    crossrailIntro.load("content/Dropbox/ArupContentForInstallation/Placeholder/no_audio.wav");
    crossrailIntro.setMultiPlay(false);
    crossrailIntro.setLoop(false);
    
    // setup left sub menu
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
    
    // setup right sub menu
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
    lLine.set(padding, height - padding - mainArea, 0, mainArea);
    
    // setup right menu line
    rLine.lineLength = 0;
    rLine.drawType = 2;
    rLine.isDraw = true;
    rLine.set(width - padding, height - padding - mainArea, 0, mainArea);
    
    
    //----------------------
    // content stuff
    //----------------------
    
    for(int i = 0; i < 5; i++) {
        // labels left
        contentLLabels[i][0] = lPoints[i].title + "/Text";
        contentLLabels[i][1] = lPoints[i].title + "/Image";
        contentLLabels[i][2] = lPoints[i].title + "/Video";
        contentLLabels[i][3] = lPoints[i].title + "/3dModel";
        contentLLabels[i][4] = lPoints[i].title + "/Audio";

        // labels right
        contentRLabels[i][4] = rPoints[i].title + "/Text";
        contentRLabels[i][3] = rPoints[i].title + "/Image";
        contentRLabels[i][2] = rPoints[i].title + "/Video";
        contentRLabels[i][1] = rPoints[i].title + "/3D Model";
        contentRLabels[i][0] = rPoints[i].title + "/Audio";
    }
    
//    //setup specific content labels
//    //St Pancras
//    contentLLabels[0][0] = "HOT SPOT KING'S CROSS LONDON - The gravy train will arrive here shortly";
//    contentLLabels[0][1] = "Diagram and artistÕs impression (1997)";
//    contentLLabels[0][2] = "Film (2013)";
//    contentLLabels[0][3] = "3D Model of St Pancras International";
//    contentLLabels[0][4] = "Acoustic Testing at St Pancras International";
//    
//    //Stratford
//    contentLLabels[1][0] = "Aerial Image (2003)";
//    contentLLabels[1][1] = "Diagram and artistÕs impression (1997)";
//    contentLLabels[1][2] = "Film";
//    contentLLabels[1][3] = "3D Model of Stratford International";
//    contentLLabels[1][4] = "London's Big Push East";
//    
//    //Ebbsfleet
//    contentLLabels[2][0] = "Drawing of a new Ebbsfleet Town";
//    contentLLabels[2][1] = "Photo (2009)";
//    contentLLabels[2][2] = "Bridge Push";
//    contentLLabels[2][3] = "The Ebbsfleet Elephant";
//    contentLLabels[2][4] = "Garden of England-or urban sprawl?";
//    
//    //Medway Viaduct
//    contentLLabels[3][0] = "Plan and Elevations of Viaduct (1998)";
//    contentLLabels[3][1] = "The Medway Viaduct Under Construction (2001)";
//    contentLLabels[3][2] = "A most iconic bridge";
//    contentLLabels[3][3] = "The Medway Viaduct";
//    contentLLabels[3][4] = "Speed record foreshadows opening of UK's first high speed line";
//    
//    //Ashford International
//    contentLLabels[4][0] = "The Arup Alignment";
//    contentLLabels[4][1] = "Ashford International Station";
//    contentLLabels[4][2] = "Bridge House Slide";
//    contentLLabels[4][3] = "The Medway Viaduct";
//    contentLLabels[4][4] = "AshfordÊboosted by London link";
    
    for(int i = 0; i < 5; i++) {
        lPoints[i].setup();
        rPoints[i].setup();
    }

    
    // setup content menu items
    setupLeftContent();
    setupRightContent();
    
    // content media setup
    c.setup();
    
    leftWasOn = false;
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
    for (int i = 0; i < length; i++)
    {
        posLCon0[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        
        lCon0[i].set(posLCon0[i], subArea, subArea);
        lCon0[i].drawType = 0;
        lCon0[i].lineLength = 0;
        lCon0[i].title = contentLLabels[0][i];
    }
    
    // setup vertical line
    lCon0VLine.lineLength = 0;
    lCon0VLine.drawType = 3;
    lCon0VLine.set(lCon0[0].x, lCon0[0].y, mainArea, 0);
    
    // setup horizonal line
    lCon0HLine.lineLength = 0;
    lCon0HLine.drawType = 1;
    lCon0HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 1
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posLCon1[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        
        lCon1[i].set(posLCon1[i], subArea, subArea);
        lCon1[i].drawType = 0;
        lCon1[i].lineLength = 0;
        lCon1[i].title = contentLLabels[1][i];
    }
    
    // setup vertical line
    lCon1VLine.lineLength = 0;
    lCon1VLine.drawType = 3;
    lCon1VLine.set(lCon1[1].x, lCon1[1].y, mainArea, 0);
    
    // setup horizonal line
    lCon1HLine.lineLength = 0;
    lCon1HLine.drawType = 1;
    lCon1HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 2
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posLCon2[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        
        lCon2[i].set(posLCon2[i], subArea, subArea);
        lCon2[i].drawType = 0;
        lCon2[i].lineLength = 0;
        lCon2[i].title = contentLLabels[2][i];
    }
    
    // setup vertical line
    lCon2VLine.lineLength = 0;
    lCon2VLine.drawType = 3;
    lCon2VLine.set(lCon2[2].x, lCon2[2].y, mainArea, 0);
    
    // setup horizonal line
    lCon2HLine.lineLength = 0;
    lCon2HLine.drawType = 1;
    lCon2HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 3
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posLCon3[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        
        lCon3[i].set(posLCon3[i], subArea, subArea);
        lCon3[i].drawType = 0;
        lCon3[i].lineLength = 0;
        lCon3[i].title = contentLLabels[3][i];
    }
    
    // setup vertical line
    lCon3VLine.lineLength = 0;
    lCon3VLine.drawType = 3;
    lCon3VLine.set(lCon3[3].x, lCon3[3].y, mainArea, 0);
    
    // setup horizonal line
    lCon3HLine.lineLength = 0;
    lCon3HLine.drawType = 1;
    lCon3HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 4
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posLCon4[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        
        lCon4[i].set(posLCon4[i], subArea, subArea);
        lCon4[i].drawType = 0;
        lCon4[i].lineLength = 0;
        lCon4[i].title = contentLLabels[4][i];
    }
    
    // setup vertical line
    lCon4VLine.lineLength = 0;
    lCon4VLine.drawType = 3;
    lCon4VLine.set(lCon4[4].x, lCon4[4].y, mainArea, 0);
    
    // setup horizonal line
    lCon4HLine.lineLength = 0;
    lCon4HLine.drawType = 1;
    lCon4HLine.set(dX, height - padding - mainArea, mainArea, 0);
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
    for (int i = 0; i < length; i++)
    {
        posRCon0[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        
        rCon0[i].set(posRCon0[i], subArea, subArea);
        rCon0[i].drawType = 0;
        rCon0[i].lineLength = 0;
        rCon0[i].title = contentRLabels[0][i];
    }
    
    // setup vertical line
    rCon0VLine.lineLength = 0;
    rCon0VLine.drawType = 3;
    rCon0VLine.set(rCon0[0].x, rCon0[0].y, mainArea, 0);
    
    // setup horizonal line
    rCon0HLine.lineLength = 0;
    rCon0HLine.drawType = 2;
    rCon0HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 1
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posRCon1[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        
        rCon1[i].set(posRCon1[i], subArea, subArea);
        rCon1[i].drawType = 0;
        rCon1[i].lineLength = 0;
        rCon1[i].title = contentRLabels[1][i];
    }
    
    // setup vertical line
    rCon1VLine.lineLength = 0;
    rCon1VLine.drawType = 3;
    rCon1VLine.set(rCon1[1].x, rCon1[1].y, mainArea, 0);
    
    // setup horizonal line
    rCon1HLine.lineLength = 0;
    rCon1HLine.drawType = 2;
    rCon1HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 2
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posRCon2[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        
        rCon2[i].set(posRCon2[i], subArea, subArea);
        rCon2[i].drawType = 0;
        rCon2[i].lineLength = 0;
        rCon2[i].title = contentRLabels[2][i];
    }
    
    // setup vertical line
    rCon2VLine.lineLength = 0;
    rCon2VLine.drawType = 3;
    rCon2VLine.set(rCon2[2].x, rCon2[2].y, mainArea, 0);
    
    // setup horizonal line
    rCon2HLine.lineLength = 0;
    rCon2HLine.drawType = 2;
    rCon2HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 3
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posRCon3[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        
        rCon3[i].set(posRCon3[i], subArea, subArea);
        rCon3[i].drawType = 0;
        rCon3[i].lineLength = 0;
        rCon3[i].title = contentRLabels[3][i];
    }
    
    // setup vertical line
    rCon3VLine.lineLength = 0;
    rCon3VLine.drawType = 3;
    rCon3VLine.set(rCon3[3].x, rCon3[3].y, mainArea, 0);
    
    // setup horizonal line
    rCon3HLine.lineLength = 0;
    rCon3HLine.drawType = 2;
    rCon3HLine.set(dX, height - padding - mainArea, mainArea, 0);
    
    
    // ----------------------------------
    // content menu item 4
    // ----------------------------------
    // setup objects
    for (int i = 0; i < length; i++)
    {
        posRCon4[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        
        rCon4[i].set(posRCon4[i], subArea, subArea);
        rCon4[i].drawType = 0;
        rCon4[i].lineLength = 0;
        rCon4[i].title = contentRLabels[4][i];
    }
    
    // setup vertical line
    rCon4VLine.lineLength = 0;
    rCon4VLine.drawType = 3;
    rCon4VLine.set(rCon4[4].x, rCon4[4].y, mainArea, 0);
    
    // setup horizonal line
    rCon4HLine.lineLength = 0;
    rCon4HLine.drawType = 2;
    rCon4HLine.set(dX, height - padding - mainArea, mainArea, 0);
}

//--------------------------------------------------------------
void InteractiveMenu::update()
{
    // draw menu objects and lines
    drawMenu();
    
    // check button presses
    pressed();
    
    // button position and size
    transform();
    
    // draw menu content objects and lines
    drawContentMenu();
    
    // content pressed
    pressedContent();
    
    // hs1 project content menu position and size
    transformLeftContent0();
    transformLeftContent1();
    transformLeftContent2();
    transformLeftContent3();
    transformLeftContent4();
    
    // crossrail project content menu position and size
    transformRightContent0();
    transformRightContent1();
    transformRightContent2();
    transformRightContent3();
    transformRightContent4();
    
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
    } else if(rightOn && leftWasOn) {
        hs1Intro.stop();
        c.stopLocationAudio();
        crossrailIntro.play();
        leftWasOn = false;
    }
}

//--------------------------------------------------------------
void InteractiveMenu::transformLeftContent0()
{
    // if left side menu is active
    if (leftOn)
    {
        // if content item #0 is active
        if (bLeftActive[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon0[i].y = ofLerp(posLCon0[i].y, contentHeight, easeOut);
                
                if (posLCon0[i].y <= contentHeight + easeOut)
                {
                    posLCon0[i].x = ofLerp(posLCon0[i].x, posLeft[i].x, easeOut);
                }
            }
            
            lCon0VLine.lineLength = ofLerp(lCon0VLine.lineLength, mainArea, easeOut);
            
            if (posLCon0[0].y < posLeft[0].y)
            {
                if (!bLLineH[0]) bLLineH[0] = true;
            }
            
            if (posLCon0[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lCon0HLine.lineLength = ofLerp(lCon0HLine.lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = 0  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon0[i].x = ofLerp(posLCon0[i].x, distance, easeIn);
                
                if (posLCon0[0].x <= dest && posLCon0[1].x <= dest && posLCon0[2].x <= dest && posLCon0[3].x <= dest && posLCon0[4].x <= dest)
                {
                    posLCon0[i].y = ofLerp(posLCon0[i].y, posLeft[i].y, easeIn);
                    lCon0VLine.lineLength = ofLerp(lCon0VLine.lineLength, 0, easeIn * 2);
                    
                    if (posLCon0[4].y >= posLeft[0].y - easeIn)
                    {
                        if (bLLineH[0]) bLLineH[0] = false;
                    }
                }
            }
            
            lCon0HLine.lineLength = ofLerp(lCon0HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bLeftActive[0] && posLCon0[4].x > posLeft[4].x - easeOut)
        {
            bLPlace[0] = true;
        }
        else {
            bLPlace[0] = false;
        }
    }
    else
    {
        if (posLCon0[4].y < posLeft[0].y - easeIn)
        {
            float distance = 0  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon0[i].x = ofLerp(posLCon0[i].x, distance, easeIn);
                
                if (posLCon0[0].x <= dest && posLCon0[1].x <= dest && posLCon0[2].x <= dest && posLCon0[3].x <= dest && posLCon0[4].x <= dest)
                {
                    posLCon0[i].y = ofLerp(posLCon0[i].y, posLeft[i].y, easeIn);
                    lCon0VLine.lineLength = ofLerp(lCon0VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            lCon0HLine.lineLength = ofLerp(lCon0HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon0[i].x = ofLerp(posLCon0[i].x, padding, easeIn);
            }
        }
    }
    
    // content item #0 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon0[i].isSelected) {
            sizeLCon0[i] = ofLerp(sizeLCon0[i], mainArea, easeOut);
        }
        else {
            sizeLCon0[i] = ofLerp(sizeLCon0[i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon0[i].setPosition(posLCon0[i]);
        lCon0[i].setFromCenter(posLCon0[i].x+subArea/2, posLCon0[i].y+subArea/2, sizeLCon0[i], sizeLCon0[i]);
    }
    
    // content item #0 vertical line
    lCon0VLine.setPosition(posLCon0[0].x + subArea/2, posLeft[0].y);
    
    // horizontal line
    lCon0HLine.setPosition(posLCon0[0].x, posLCon0[0].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformLeftContent1()
{
    // if left side menu is active
    if (leftOn)
    {
        // if content item #0 is active
        if (bLeftActive[1] && !bLLineH[0] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon1[i].y = ofLerp(posLCon1[i].y, contentHeight, easeOut);
                
                if (posLCon1[i].y <= contentHeight + easeOut)
                {
                    posLCon1[i].x = ofLerp(posLCon1[i].x, posLeft[i].x, easeOut);
                }
            }
            
            lCon1VLine.lineLength = ofLerp(lCon1VLine.lineLength, mainArea, easeOut);
            
            if (posLCon1[0].y < posLeft[1].y)
            {
                if (!bLLineH[1]) bLLineH[1] = true;
            }
            
            if (posLCon1[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lCon1HLine.lineLength = ofLerp(lCon1HLine.lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = 1  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #1 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon1[i].x = ofLerp(posLCon1[i].x, distance, easeIn);
                
                if (posLCon1[0].x <= dest && posLCon1[1].x <= dest && posLCon1[2].x <= dest && posLCon1[3].x <= dest && posLCon1[4].x <= dest)
                {
                    posLCon1[i].y = ofLerp(posLCon1[i].y, posLeft[i].y, easeIn);
                    lCon1VLine.lineLength = ofLerp(lCon1VLine.lineLength, 0, easeIn * 2);
                    
                    if (posLCon1[4].y >= posLeft[1].y - easeIn)
                    {
                        if (bLLineH[1]) bLLineH[1] = false;
                    }
                }
            }
            
            lCon1HLine.lineLength = ofLerp(lCon1HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bLeftActive[1] && posLCon1[4].x > posLeft[4].x - easeOut)
        {
            bLPlace[1] = true;
        }
        else {
            bLPlace[1] = false;
        }
    }
    else
    {
        if (posLCon1[4].y < posLeft[0].y - easeIn)
        {
            float distance = 1  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon1[i].x = ofLerp(posLCon1[i].x, distance, easeIn);
                
                if (posLCon1[0].x <= dest && posLCon1[1].x <= dest && posLCon1[2].x <= dest && posLCon1[3].x <= dest && posLCon1[4].x <= dest)
                {
                    posLCon1[i].y = ofLerp(posLCon1[i].y, posLeft[i].y, easeIn);
                    lCon1VLine.lineLength = ofLerp(lCon1VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            lCon1HLine.lineLength = ofLerp(lCon1HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon1[i].x = ofLerp(posLCon1[i].x, padding, easeIn);
            }
        }
    }
    
    // content item #1 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon1[i].isSelected) {
            sizeLCon1[i] = ofLerp(sizeLCon1[i], mainArea, easeOut);
        }
        else {
            sizeLCon1[i] = ofLerp(sizeLCon1[i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon1[i].setPosition(posLCon1[i]);
        lCon1[i].setFromCenter(posLCon1[i].x+subArea/2, posLCon1[i].y+subArea/2, sizeLCon1[i], sizeLCon1[i]);
    }
    
    // content item #1 vertical line
    lCon1VLine.setPosition(posLCon1[1].x + subArea/2, posLeft[1].y);
    
    // horizontal line
    lCon1HLine.setPosition(posLCon1[1].x - lCon1HLine.lineLength * 0.25, posLCon1[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformLeftContent2()
{
    // if left side menu is active
    if (leftOn)
    {
        // if content item #2 is active
        if (bLeftActive[2] && !bLLineH[0] && !bLLineH[1] && !bLLineH[3] && !bLLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon2[i].y = ofLerp(posLCon2[i].y, contentHeight, easeOut);
                
                if (posLCon2[i].y <= contentHeight + easeOut)
                {
                    posLCon2[i].x = ofLerp(posLCon2[i].x, posLeft[i].x, easeOut);
                }
            }
            
            lCon2VLine.lineLength = ofLerp(lCon2VLine.lineLength, mainArea, easeOut);
            
            if (posLCon2[0].y < posLeft[2].y)
            {
                if (!bLLineH[2]) bLLineH[2] = true;
            }
            
            if (posLCon2[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lCon2HLine.lineLength = ofLerp(lCon2HLine.lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = 2  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeOut;
            
            // if content item #2 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon2[i].x = ofLerp(posLCon2[i].x, distance, easeIn);
                
                if (posLCon2[0].x <= dest && posLCon2[1].x <= dest && posLCon2[2].x <= dest && posLCon2[3].x <= dest && posLCon2[4].x <= dest)
                {
                    posLCon2[i].y = ofLerp(posLCon2[i].y, posLeft[i].y, easeIn);
                    lCon2VLine.lineLength = ofLerp(lCon2VLine.lineLength, 0, easeIn * 2);
                    
                    if (posLCon2[4].y >= posLeft[2].y - easeIn)
                    {
                        if (bLLineH[2]) bLLineH[2] = false;
                    }
                }
            }
            
            lCon2HLine.lineLength = ofLerp(lCon2HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bLeftActive[2] && posLCon2[4].x > posLeft[4].x - easeOut)
        {
            bLPlace[2] = true;
        }
        else {
            bLPlace[2] = false;
        }
    }
    else
    {
        if (posLCon2[4].y < posLeft[0].y - easeIn)
        {
            float distance = 2  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon2[i].x = ofLerp(posLCon2[i].x, distance, easeIn);
                
                if (posLCon2[0].x <= dest && posLCon2[1].x <= dest && posLCon2[2].x <= dest && posLCon2[3].x <= dest && posLCon2[4].x <= dest)
                {
                    posLCon2[i].y = ofLerp(posLCon2[i].y, posLeft[i].y, easeIn);
                    lCon2VLine.lineLength = ofLerp(lCon2VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            lCon2HLine.lineLength = ofLerp(lCon2HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon2[i].x = ofLerp(posLCon2[i].x, padding, easeIn);
            }
        }
    }
    
    // content item #2 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon2[i].isSelected) {
            sizeLCon2[i] = ofLerp(sizeLCon2[i], mainArea, easeOut);
        }
        else {
            sizeLCon2[i] = ofLerp(sizeLCon2[i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon2[i].setPosition(posLCon2[i]);
        lCon2[i].setFromCenter(posLCon2[i].x+subArea/2, posLCon2[i].y+subArea/2, sizeLCon2[i], sizeLCon2[i]);
    }
    
    // content item #2 vertical line
    lCon2VLine.setPosition(posLCon2[2].x + subArea/2, posLeft[2].y);
    
    // horizontal line
    lCon2HLine.setPosition(posLCon2[2].x - lCon2HLine.lineLength * 0.5, posLCon2[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformLeftContent3()
{
    // if left side menu is active
    if (leftOn)
    {
        // if content item #3 is active
        if (bLeftActive[3] && !bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon3[i].y = ofLerp(posLCon3[i].y, contentHeight, easeOut);
                
                if (posLCon3[i].y <= contentHeight + easeOut)
                {
                    posLCon3[i].x = ofLerp(posLCon3[i].x, posLeft[i].x, easeOut);
                }
            }
            
            lCon3VLine.lineLength = ofLerp(lCon3VLine.lineLength, mainArea, easeOut);
            
            if (posLCon3[0].y < posLeft[3].y)
            {
                if (!bLLineH[3]) bLLineH[3] = true;
            }
            
            if (posLCon3[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lCon3HLine.lineLength = ofLerp(lCon3HLine.lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = 3 * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #3 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon3[i].x = ofLerp(posLCon3[i].x, distance, easeIn);
                
                if (posLCon3[0].x <= dest && posLCon3[1].x <= dest && posLCon3[2].x <= dest && posLCon3[3].x <= dest && posLCon3[4].x <= dest)
                {
                    posLCon3[i].y = ofLerp(posLCon3[i].y, posLeft[i].y, easeIn);
                    lCon3VLine.lineLength = ofLerp(lCon3VLine.lineLength, 0, easeIn * 2);
                    
                    if (posLCon3[4].y >= posLeft[3].y - easeIn)
                    {
                        if (bLLineH[3]) bLLineH[3] = false;
                    }
                }
            }
            
            lCon3HLine.lineLength = ofLerp(lCon3HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bLeftActive[3] && posLCon3[0].x < posLeft[0].x + easeOut)
        {
            bLPlace[3] = true;
        }
        else {
            bLPlace[3] = false;
        }
    }
    else
    {
        if (posLCon3[4].y < posLeft[0].y - easeIn)
        {
            float distance = 3  * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon3[i].x = ofLerp(posLCon3[i].x, distance, easeIn);
                
                if (posLCon3[0].x <= dest && posLCon3[1].x <= dest && posLCon3[2].x <= dest && posLCon3[3].x <= dest && posLCon3[4].x <= dest)
                {
                    posLCon3[i].y = ofLerp(posLCon3[i].y, posLeft[i].y, easeIn);
                    lCon3VLine.lineLength = ofLerp(lCon3VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            lCon3HLine.lineLength = ofLerp(lCon3HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon3[i].x = ofLerp(posLCon3[i].x, padding, easeIn);
            }
        }
    }
    
    // content item #3 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon3[i].isSelected) {
            sizeLCon3[i] = ofLerp(sizeLCon3[i], mainArea, easeOut);
        }
        else {
            sizeLCon3[i] = ofLerp(sizeLCon3[i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon3[i].setPosition(posLCon3[i]);
        lCon3[i].setFromCenter(posLCon3[i].x+subArea/2, posLCon3[i].y+subArea/2, sizeLCon3[i], sizeLCon3[i]);
    }
    
    // content item #1 vertical line
    lCon3VLine.setPosition(posLCon3[3].x + subArea/2, posLeft[3].y);
    
    // horizontal line
    lCon3HLine.setPosition(posLCon3[3].x - lCon3HLine.lineLength * 0.75, posLCon3[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformLeftContent4()
{
    // if left side menu is active
    if (leftOn)
    {
        // if content item #4 is active
        if (bLeftActive[4] && !bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon4[i].y = ofLerp(posLCon4[i].y, contentHeight, easeOut);
                
                if (posLCon4[i].y <= contentHeight + easeOut)
                {
                    posLCon4[i].x = ofLerp(posLCon4[i].x, posLeft[i].x, easeOut);
                }
            }
            
            lCon4VLine.lineLength = ofLerp(lCon4VLine.lineLength, mainArea, easeOut);
            
            if (posLCon4[0].y < posLeft[4].y)
            {
                if (!bLLineH[4]) bLLineH[4] = true;
            }
            
            if (posLCon4[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                lCon4HLine.lineLength = ofLerp(lCon4HLine.lineLength, l, easeOut);
            }
        }
        else if (!bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            float distance = 4 * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance - easeIn;
            
            // if content item #4 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon4[i].x = ofLerp(posLCon4[i].x, distance, easeIn);
                
                if (posLCon4[0].x >= dest && posLCon4[1].x >= dest && posLCon4[2].x >= dest && posLCon4[3].x >= dest && posLCon4[4].x >= dest)
                {
                    posLCon4[i].y = ofLerp(posLCon4[i].y, posLeft[i].y, easeIn);
                    lCon4VLine.lineLength = ofLerp(lCon4VLine.lineLength, 0, easeIn * 2);
                    
                    if (posLCon4[4].y >= posLeft[4].y - easeIn)
                    {
                        if (bLLineH[4]) bLLineH[4] = false;
                    }
                }
            }
            
            lCon4HLine.lineLength = ofLerp(lCon4HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bLeftActive[4] && posLCon4[0].x < posLeft[0].x + easeOut)
        {
            bLPlace[4] = true;
        }
        else {
            bLPlace[4] = false;
        }
    }
    else
    {
        if (posLCon4[4].y < posLeft[0].y - easeIn)
        {
            float distance = 4 * (subArea + padding) + (padding * 2) + mainArea;
            float dest = distance - easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon4[i].x = ofLerp(posLCon4[i].x, distance, easeIn);
                
                if (posLCon4[0].x >= dest && posLCon4[1].x >= dest && posLCon4[2].x >= dest && posLCon4[3].x >= dest && posLCon4[4].x >= dest)
                {
                    posLCon4[i].y = ofLerp(posLCon4[i].y, posLeft[i].y, easeIn);
                    lCon4VLine.lineLength = ofLerp(lCon4VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            lCon4HLine.lineLength = ofLerp(lCon4HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posLCon4[i].x = ofLerp(posLCon4[i].x, padding, easeIn);
            }
        }
    }
    
    // content item #4 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (lCon4[i].isSelected) {
            sizeLCon4[i] = ofLerp(sizeLCon4[i], mainArea, easeOut);
        }
        else {
            sizeLCon4[i] = ofLerp(sizeLCon4[i], subArea, easeIn);
        }
        
        // update objects position and size
        lCon4[i].setPosition(posLCon4[i]);
        lCon4[i].setFromCenter(posLCon4[i].x+subArea/2, posLCon4[i].y+subArea/2, sizeLCon4[i], sizeLCon4[i]);
    }
    
    // content item #1 vertical line
    lCon4VLine.setPosition(posLCon4[4].x + subArea/2, posLeft[4].y);
    
    // horizontal line
    lCon4HLine.setPosition(posLCon4[4].x - lCon4HLine.lineLength, posLCon4[4].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformRightContent0()
{
    // if left side menu is active
    if (rightOn)
    {
        // if content item #0 is active
        if (bRightActive[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon0[i].y = ofLerp(posRCon0[i].y, contentHeight, easeOut);
                
                if (posRCon0[i].y <= contentHeight + easeOut)
                {
                    posRCon0[i].x = ofLerp(posRCon0[i].x, posRight[i].x, easeOut);
                }
            }
            
            rCon0VLine.lineLength = ofLerp(rCon0VLine.lineLength, mainArea, easeOut);
            
            if (posRCon0[0].y < posRight[0].y)
            {
                if (!bRLineH[0]) bRLineH[0] = true;
            }
            
            if (posRCon0[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rCon0HLine.lineLength = ofLerp(rCon0HLine.lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (0  * (subArea + padding) + padding + mainArea);
            float dest = distance - easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon0[i].x = ofLerp(posRCon0[i].x, distance, easeIn);
                
                if (posRCon0[0].x >= dest && posRCon0[1].x >= dest && posRCon0[2].x >= dest && posRCon0[3].x >= dest && posRCon0[4].x >= dest)
                {
                    posRCon0[i].y = ofLerp(posRCon0[i].y, posRight[i].y, easeIn);
                    rCon0VLine.lineLength = ofLerp(rCon0VLine.lineLength, 0, easeIn * 2);
                    
                    if (posRCon0[4].y >= posRight[0].y - easeIn)
                    {
                        if (bRLineH[0]) bRLineH[0] = false;
                    }
                }
            }
            
            rCon0HLine.lineLength = ofLerp(rCon0HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bRightActive[0] && posRCon0[4].x < posRight[4].x + easeOut)
        {
            bRPlace[0] = true;
        }
        else {
            bRPlace[0] = false;
        }
    }
    else
    {
        if (posRCon0[4].y < posRight[0].y - easeIn)
        {
            float distance = width - padding - subArea - (0  * (subArea + padding) + padding + mainArea);
            float dest = distance - easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon0[i].x = ofLerp(posRCon0[i].x, distance, easeIn);
                
                if (posRCon0[0].x >= dest && posRCon0[1].x >= dest && posRCon0[2].x >= dest && posRCon0[3].x >= dest && posRCon0[4].x >= dest)
                {
                    posRCon0[i].y = ofLerp(posRCon0[i].y, posRight[i].y, easeIn);
                    rCon0VLine.lineLength = ofLerp(rCon0VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            rCon0HLine.lineLength = ofLerp(rCon0HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon0[i].x = ofLerp(posRCon0[i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #0 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon0[i].isSelected) {
            sizeRCon0[i] = ofLerp(sizeRCon0[i], mainArea, easeOut);
        }
        else {
            sizeRCon0[i] = ofLerp(sizeRCon0[i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon0[i].setPosition(posRCon0[i]);
        rCon0[i].setFromCenter(posRCon0[i].x+subArea/2, posRCon0[i].y+subArea/2, sizeRCon0[i], sizeRCon0[i]);
    }
    
    // content item #0 vertical line
    rCon0VLine.setPosition(posRCon0[0].x + subArea/2, posRight[0].y);
    
    // horizontal line
    rCon0HLine.setPosition(posRCon0[0].x, posRCon0[0].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformRightContent1()
{
    // if left side menu is active
    if (rightOn)
    {
        // if content item #0 is active
        if (bRightActive[1] && !bRLineH[0] && !bRLineH[2] && !bRLineH[3] && !bRLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon1[i].y = ofLerp(posRCon1[i].y, contentHeight, easeOut);
                
                if (posRCon1[i].y <= contentHeight + easeOut)
                {
                    posRCon1[i].x = ofLerp(posRCon1[i].x, posRight[i].x, easeOut);
                }
            }
            
            rCon1VLine.lineLength = ofLerp(rCon1VLine.lineLength, mainArea, easeOut);
            
            if (posRCon1[0].y < posRight[1].y)
            {
                if (!bRLineH[1]) bRLineH[1] = true;
            }
            
            if (posRCon1[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rCon1HLine.lineLength = ofLerp(rCon1HLine.lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (1  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #1 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon1[i].x = ofLerp(posRCon1[i].x, distance, easeIn);
                
                if (posRCon1[0].x <= dest && posRCon1[1].x <= dest && posRCon1[2].x <= dest && posRCon1[3].x <= dest && posRCon1[4].x <= dest)
                {
                    posRCon1[i].y = ofLerp(posRCon1[i].y, posRight[i].y, easeIn);
                    rCon1VLine.lineLength = ofLerp(rCon1VLine.lineLength, 0, easeIn * 2);
                    
                    if (posRCon1[4].y >= posRight[1].y - easeIn)
                    {
                        if (bRLineH[1]) bRLineH[1] = false;
                    }
                }
            }
            
            rCon1HLine.lineLength = ofLerp(rCon1HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bRightActive[1] && posRCon1[4].x < posRight[4].x + easeOut)
        {
            bRPlace[1] = true;
        }
        else {
            bRPlace[1] = false;
        }
    }
    else
    {
        if (posRCon1[4].y < posRight[1].y - easeIn)
        {
            float distance = width - padding - subArea - (1  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon1[i].x = ofLerp(posRCon1[i].x, distance, easeIn);
                
                if (posRCon1[0].x <= dest && posRCon1[1].x <= dest && posRCon1[2].x <= dest && posRCon1[3].x <= dest && posRCon1[4].x <= dest)
                {
                    posRCon1[i].y = ofLerp(posRCon1[i].y, posRight[i].y, easeIn);
                    rCon1VLine.lineLength = ofLerp(rCon1VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            rCon1HLine.lineLength = ofLerp(rCon1HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon1[i].x = ofLerp(posRCon1[i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #1 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon1[i].isSelected) {
            sizeRCon1[i] = ofLerp(sizeRCon1[i], mainArea, easeOut);
        }
        else {
            sizeRCon1[i] = ofLerp(sizeRCon1[i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon1[i].setPosition(posRCon1[i]);
        rCon1[i].setFromCenter(posRCon1[i].x+subArea/2, posRCon1[i].y+subArea/2, sizeRCon1[i], sizeRCon1[i]);
    }
    
    // content item #1 vertical line
    rCon1VLine.setPosition(posRCon1[1].x + subArea/2, posRight[1].y);
    
    // horizontal line
    rCon1HLine.setPosition(posRCon1[1].x + rCon1HLine.lineLength * 0.25, posRCon1[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformRightContent2()
{
    // if left side menu is active
    if (rightOn)
    {
        // if content item #2 is active
        if (bRightActive[2] && !bRLineH[0] && !bRLineH[1] && !bRLineH[3] && !bRLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon2[i].y = ofLerp(posRCon2[i].y, contentHeight, easeOut);
                
                if (posRCon2[i].y <= contentHeight + easeOut)
                {
                    posRCon2[i].x = ofLerp(posRCon2[i].x, posRight[i].x, easeOut);
                }
            }
            
            rCon2VLine.lineLength = ofLerp(rCon2VLine.lineLength, mainArea, easeOut);
            
            if (posRCon2[0].y < posRight[2].y)
            {
                if (!bRLineH[2]) bRLineH[2] = true;
            }
            
            if (posRCon2[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rCon2HLine.lineLength = ofLerp(rCon2HLine.lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (2  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #2 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon2[i].x = ofLerp(posRCon2[i].x, distance, easeIn);
                
                if (posRCon2[0].x <= dest && posRCon2[1].x <= dest && posRCon2[2].x <= dest && posRCon2[3].x <= dest && posRCon2[4].x <= dest)
                {
                    posRCon2[i].y = ofLerp(posRCon2[i].y, posRight[i].y, easeIn);
                    rCon2VLine.lineLength = ofLerp(rCon2VLine.lineLength, 0, easeIn * 2);
                    
                    if (posRCon2[4].y >= posRight[2].y - easeIn)
                    {
                        if (bRLineH[2]) bRLineH[2] = false;
                    }
                }
            }
            
            rCon2HLine.lineLength = ofLerp(rCon2HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bRightActive[2] && posRCon2[4].x < posRight[4].x + easeOut)
        {
            bRPlace[2] = true;
        }
        else {
            bRPlace[2] = false;
        }
    }
    else
    {
        if (posRCon2[4].y < posRight[2].y - easeIn)
        {
            float distance = width - padding - subArea - (2  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon2[i].x = ofLerp(posRCon2[i].x, distance, easeIn);
                
                if (posRCon2[0].x <= dest && posRCon2[1].x <= dest && posRCon2[2].x <= dest && posRCon2[3].x <= dest && posRCon2[4].x <= dest)
                {
                    posRCon2[i].y = ofLerp(posRCon2[i].y, posRight[i].y, easeIn);
                    rCon2VLine.lineLength = ofLerp(rCon2VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            rCon2HLine.lineLength = ofLerp(rCon2HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon2[i].x = ofLerp(posRCon2[i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #2 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon2[i].isSelected) {
            sizeRCon2[i] = ofLerp(sizeRCon2[i], mainArea, easeOut);
        }
        else {
            sizeRCon2[i] = ofLerp(sizeRCon2[i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon2[i].setPosition(posRCon2[i]);
        rCon2[i].setFromCenter(posRCon2[i].x+subArea/2, posRCon2[i].y+subArea/2, sizeRCon2[i], sizeRCon2[i]);
    }
    
    // content item #2 vertical line
    rCon2VLine.setPosition(posRCon2[2].x + subArea/2, posRight[2].y);
    
    // horizontal line
    rCon2HLine.setPosition(posRCon2[2].x + rCon2HLine.lineLength * 0.5, posRCon2[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformRightContent3()
{
    // if left side menu is active
    if (rightOn)
    {
        // if content item #3 is active
        if (bRightActive[3] && !bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[4])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon3[i].y = ofLerp(posRCon3[i].y, contentHeight, easeOut);
                
                if (posRCon3[i].y <= contentHeight + easeOut)
                {
                    posRCon3[i].x = ofLerp(posRCon3[i].x, posRight[i].x, easeOut);
                }
            }
            
            rCon3VLine.lineLength = ofLerp(rCon3VLine.lineLength, mainArea, easeOut);
            
            if (posRCon3[0].y < posRight[3].y)
            {
                if (!bRLineH[3]) bRLineH[3] = true;
            }
            
            if (posRCon3[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rCon3HLine.lineLength = ofLerp(rCon3HLine.lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (3  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #3 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon3[i].x = ofLerp(posRCon3[i].x, distance, easeIn);
                
                if (posRCon3[0].x <= dest && posRCon3[1].x <= dest && posRCon3[2].x <= dest && posRCon3[3].x <= dest && posRCon3[4].x <= dest)
                {
                    posRCon3[i].y = ofLerp(posRCon3[i].y, posRight[i].y, easeIn);
                    rCon3VLine.lineLength = ofLerp(rCon3VLine.lineLength, 0, easeIn * 2);
                    
                    if (posRCon3[4].y >= posRight[3].y - easeIn)
                    {
                        if (bRLineH[3]) bRLineH[3] = false;
                    }
                }
            }
            
            rCon3HLine.lineLength = ofLerp(rCon3HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bRightActive[3] && posRCon3[0].x > posRight[0].x - easeOut)
        {
            bRPlace[3] = true;
        }
        else {
            bRPlace[3] = false;
        }
    }
    else
    {
        if (posRCon3[4].y < posRight[3].y - easeIn)
        {
            float distance = width - padding - subArea - (3  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon3[i].x = ofLerp(posRCon3[i].x, distance, easeIn);
                
                if (posRCon3[0].x <= dest && posRCon3[1].x <= dest && posRCon3[2].x <= dest && posRCon3[3].x <= dest && posRCon3[4].x <= dest)
                {
                    posRCon3[i].y = ofLerp(posRCon3[i].y, posRight[i].y, easeIn);
                    rCon3VLine.lineLength = ofLerp(rCon3VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            rCon3HLine.lineLength = ofLerp(rCon3HLine.lineLength, 0, easeIn);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon3[i].x = ofLerp(posRCon3[i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #3 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon3[i].isSelected) {
            sizeRCon3[i] = ofLerp(sizeRCon3[i], mainArea, easeOut);
        }
        else {
            sizeRCon3[i] = ofLerp(sizeRCon3[i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon3[i].setPosition(posRCon3[i]);
        rCon3[i].setFromCenter(posRCon3[i].x+subArea/2, posRCon3[i].y+subArea/2, sizeRCon3[i], sizeRCon3[i]);
    }
    
    // content item #1 vertical line
    rCon3VLine.setPosition(posRCon3[3].x + subArea/2, posRight[3].y);
    
    // horizontal line
    rCon3HLine.setPosition(posRCon3[3].x + rCon3HLine.lineLength * 0.75, posRCon3[1].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transformRightContent4()
{
    // if left side menu is active
    if (rightOn)
    {
        // if content item #4 is active
        if (bRightActive[4] && !bRLineH[0] && !bRLineH[1] && !bRLineH[2] && !bRLineH[3])
        {
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon4[i].y = ofLerp(posRCon4[i].y, contentHeight, easeOut);
                
                if (posRCon4[i].y <= contentHeight + easeOut)
                {
                    posRCon4[i].x = ofLerp(posRCon4[i].x, posRight[i].x, easeOut);
                }
            }
            
            rCon4VLine.lineLength = ofLerp(rCon4VLine.lineLength, mainArea, easeOut);
            
            if (posRCon4[0].y < posRight[4].y)
            {
                if (!bRLineH[4]) bRLineH[4] = true;
            }
            
            if (posRCon4[4].y <= contentHeight + easeOut)
            {
                float l = (length-1) * (padding + subArea);
                rCon4HLine.lineLength = ofLerp(rCon4HLine.lineLength, l, easeOut);
            }
        }
        else if (!bLLineH[0] && !bLLineH[1] && !bLLineH[2] && !bLLineH[3] && !bLLineH[4])
        {
            float distance = width - padding - subArea - (4  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #4 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon4[i].x = ofLerp(posRCon4[i].x, distance, easeIn);
                
                if (posRCon4[0].x <= dest && posRCon4[1].x <= dest && posRCon4[2].x <= dest && posRCon4[3].x <= dest && posRCon4[4].x <= dest)
                {
                    posRCon4[i].y = ofLerp(posRCon4[i].y, posRight[i].y, easeIn);
                    rCon4VLine.lineLength = ofLerp(rCon4VLine.lineLength, 0, easeIn * 2);
                    
                    if (posRCon4[4].y >= posRight[4].y - easeIn)
                    {
                        if (bRLineH[4]) bRLineH[4] = false;
                    }
                }
            }
            
            rCon4HLine.lineLength = ofLerp(rCon4HLine.lineLength, 0, easeIn);
        }
        
        // if objects are in place, the do something...
        if (bRightActive[4] && posRCon4[0].x > posRight[0].x - easeOut)
        {
            bRPlace[4] = true;
        }
        else {
            bRPlace[4] = false;
        }
    }
    else
    {
        if (posRCon4[4].y < posRight[3].y - easeIn)
        {
            float distance = width - padding - subArea - (4  * (subArea + padding) + padding + mainArea);
            float dest = distance + easeIn;
            
            // if content item #0 is not active
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon4[i].x = ofLerp(posRCon4[i].x, distance, easeIn);
                
                if (posRCon4[0].x <= dest && posRCon4[1].x <= dest && posRCon4[2].x <= dest && posRCon4[3].x <= dest && posRCon4[4].x <= dest)
                {
                    posRCon4[i].y = ofLerp(posRCon4[i].y, posRight[i].y, easeIn);
                    rCon4VLine.lineLength = ofLerp(rCon4VLine.lineLength, 0, easeIn * 2);
                }
            }
            
            rCon4HLine.lineLength = ofLerp(rCon4HLine.lineLength, 0, easeOut);
        }
        else
        {
            // returns content item #0 pos to default
            for (int i = 0; i < BUTTON_AMT; i++)
            {
                posRCon4[i].x = ofLerp(posRCon4[i].x, width - padding - subArea, easeIn);
            }
        }
    }
    
    // content item #4 object
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on selection, change size
        if (rCon4[i].isSelected) {
            sizeRCon4[i] = ofLerp(sizeRCon4[i], mainArea, easeOut);
        }
        else {
            sizeRCon4[i] = ofLerp(sizeRCon4[i], subArea, easeIn);
        }
        
        // update objects position and size
        rCon4[i].setPosition(posRCon4[i]);
        rCon4[i].setFromCenter(posRCon4[i].x+subArea/2, posRCon4[i].y+subArea/2, sizeRCon4[i], sizeRCon4[i]);
    }
    
    // content item #1 vertical line
    rCon4VLine.setPosition(posRCon4[4].x + subArea/2, posRight[4].y);
    
    // horizontal line
    rCon4HLine.setPosition(posRCon4[4].x + rCon4HLine.lineLength, posRCon4[4].y + subArea/2);
}

//--------------------------------------------------------------
void InteractiveMenu::transform()
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
    // left content menu item 0 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        lCon0[i].isDraw = bLLineH[0];
        // fade in labels
        lCon0[i].fadeLabel = !bLPlace[0];
    }
    // lines
    lCon0VLine.isDraw = bLLineH[0];
    lCon0HLine.isDraw = bLLineH[0];
    
    
    // ----------------------------------
    // left content menu item 1 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        lCon1[i].isDraw = bLLineH[1];
        // fade in labels
        lCon1[i].fadeLabel = !bLPlace[1];
    }
    // lines
    lCon1VLine.isDraw = bLLineH[1];
    lCon1HLine.isDraw = bLLineH[1];
    
    
    // ----------------------------------
    // left content menu item 2 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        lCon2[i].isDraw = bLLineH[2];
        // fade in labels
        lCon2[i].fadeLabel = !bLPlace[2];
    }
    // lines
    lCon2VLine.isDraw = bLLineH[2];
    lCon2HLine.isDraw = bLLineH[2];
    
    
    // ----------------------------------
    // left content menu item 3 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        lCon3[i].isDraw = bLLineH[3];
        // fade in labels
        lCon3[i].fadeLabel = !bLPlace[3];
    }
    // lines
    lCon3VLine.isDraw = bLLineH[3];
    lCon3HLine.isDraw = bLLineH[3];
    
    
    // ----------------------------------
    // left content menu item 4 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        lCon4[i].isDraw = bLLineH[4];
        // fade in labels
        lCon4[i].fadeLabel = !bLPlace[4];
    }
    // lines
    lCon4VLine.isDraw = bLLineH[4];
    lCon4HLine.isDraw = bLLineH[4];
    
    
    // ----------------------------------
    // right content menu item 0 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        rCon0[i].isDraw = bRLineH[0];
        // fade in labels
        rCon0[i].fadeLabel = !bRPlace[0];
    }
    // lines
    rCon0VLine.isDraw = bRLineH[0];
    rCon0HLine.isDraw = bRLineH[0];
    
    
    // ----------------------------------
    // right content menu item 1 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        rCon1[i].isDraw = bRLineH[1];
        // fade in labels
        rCon1[i].fadeLabel = !bRPlace[1];
    }
    // lines
    rCon1VLine.isDraw = bRLineH[1];
    rCon1HLine.isDraw = bRLineH[1];
    
    
    // ----------------------------------
    // right content menu item 2 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        rCon2[i].isDraw = bRLineH[2];
        // fade in labels
        rCon2[i].fadeLabel = !bRPlace[2];
    }
    // lines
    rCon2VLine.isDraw = bRLineH[2];
    rCon2HLine.isDraw = bRLineH[2];
    
    
    // ----------------------------------
    // right content menu item 3 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        rCon3[i].isDraw = bRLineH[3];
        // fade in labels
        rCon3[i].fadeLabel = !bRPlace[3];
    }
    // lines
    rCon3VLine.isDraw = bRLineH[3];
    rCon3HLine.isDraw = bRLineH[3];
    
    
    // ----------------------------------
    // right content menu item 4 drawing
    // ----------------------------------
    // objects
    for (int i = 0; i < BUTTON_AMT; i++) {
        rCon4[i].isDraw = bRLineH[4];
        // fade in labels
        rCon4[i].fadeLabel = !bRPlace[4];
    }
    // lines
    rCon4VLine.isDraw = bRLineH[4];
    rCon4HLine.isDraw = bRLineH[4];
}

//--------------------------------------------------------------
void InteractiveMenu::drawMenu()
{
    
}

//--------------------------------------------------------------
void InteractiveMenu::pressed()
{
    /*
    // menu button check
    for (int i = 0; i < BUTTON_AMT; i++)
    {
        // based on left button, load point
        if (bLeftActive[i] && buttonClicked)
        {
            buttonClicked = false;
        }
        
        // based on right button, load point
        if (bRightActive[i] && buttonClicked)
        {
            buttonClicked = false;
        }
    }
     */
    
    for (int i = 0; i < length; i++)
    {
        if (lPoints[i].isMousePressed(0) == 1 && leftOn && !bLeftActive[i] && !buttonClicked)
        {
            switch (i) {
                case 0:
                    bLeftActive[0] = true;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                           if(c.introSounds[0][j].isPlaying()) c.introSounds[0][j].stop();
                        } else {
                            c.introSounds[0][j].play();
                        }
                    }
                    break;
                case 1:
                    bLeftActive[0] = false;
                    bLeftActive[1] = true;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[0][j].isPlaying()) c.introSounds[0][j].stop();
                        } else {
                            c.introSounds[0][j].play();
                        }
                    }
                    break;
                case 2:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = true;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[0][j].isPlaying()) c.introSounds[0][j].stop();
                        } else {
                            c.introSounds[0][j].play();
                        }
                    }
                    break;
                case 3:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = true;
                    bLeftActive[4] = false;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[0][j].isPlaying()) c.introSounds[0][j].stop();
                        } else {
                            c.introSounds[0][j].play();
                        }
                    }
                    break;
                case 4:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = true;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[0][j].isPlaying()) c.introSounds[0][j].stop();
                        } else {
                            c.introSounds[0][j].play();
                        }
                    }
                    break;
            }
            
            if(i < 5) {

            }
            
            // play menu button sound
            snd1.play();
            
            buttonClicked = true;
            Globals::buttonPressed = true;
        }
        
        // check for right button clicks
        if (rPoints[i].isMousePressed(0) == 1 && rightOn && !bRightActive[i] && !buttonClicked)
        {
            switch (i) {
                case 0:
                    bRightActive[0] = true;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    c.stopAudio();
                    hs1Intro.stop();
                    crossrailIntro.stop();
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[1][j].isPlaying()) c.introSounds[1][j].stop();
                        } else {
                            c.introSounds[1][j].play();
                        }
                    }
                    break;
                case 1:
                    bRightActive[0] = false;
                    bRightActive[1] = true;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[1][j].isPlaying()) c.introSounds[1][j].stop();
                        } else {
                            c.introSounds[1][j].play();
                        }
                    }
                    break;
                case 2:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = true;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[1][j].isPlaying()) c.introSounds[1][j].stop();
                        } else {
                            c.introSounds[1][j].play();
                        }
                    }
                    break;
                case 3:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = true;
                    bRightActive[4] = false;
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[1][j].isPlaying()) c.introSounds[1][j].stop();
                        } else {
                            c.introSounds[1][j].play();
                        }
                    }
                    break;
                case 4:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = true;
                    for(int j = 0; j < 5; j++) {
                        if(j != i) {
                            if(c.introSounds[1][j].isPlaying()) c.introSounds[1][j].stop();
                        } else {
                            c.introSounds[1][j].play();
                        }
                    }
                    break;
            }
            
            // play menu button sound
            snd1.play();
            
            buttonClicked = true;
            Globals::buttonPressed = true;
        }
    }
}

//--------------------------------------------------------------
void InteractiveMenu::pressedContent()
{
    // ------------------------------------
    // left content menu item 0 selection
    // ------------------------------------
    if (lCon0[0].isMousePressed() && bLPlace[0] && !lCon0[0].isSelected)
    {
        lCon0[0].isSelected = true;
        lCon0[1].isSelected = false;
        lCon0[2].isSelected = false;
        lCon0[3].isSelected = false;
        lCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 0, 0);
        if (!Globals::vignetteOn)
            Globals::vignetteOn = true;
    }
    else if (lCon0[1].isMousePressed() && bLPlace[0] && !lCon0[1].isSelected)
    {
        lCon0[0].isSelected = false;
        lCon0[1].isSelected = true;
        lCon0[2].isSelected = false;
        lCon0[3].isSelected = false;
        lCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 0, 1);
        if (!Globals::vignetteOn)
            Globals::vignetteOn = true;
    }
    else if (lCon0[2].isMousePressed() && bLPlace[0] && !lCon0[2].isSelected)
    {
        lCon0[0].isSelected = false;
        lCon0[1].isSelected = false;
        lCon0[2].isSelected = true;
        lCon0[3].isSelected = false;
        lCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 0, 2);
        if (!Globals::vignetteOn)
            Globals::vignetteOn = true;
    }
    else if (lCon0[3].isMousePressed() && bLPlace[0] && !lCon0[3].isSelected)
    {
        lCon0[0].isSelected = false;
        lCon0[1].isSelected = false;
        lCon0[2].isSelected = false;
        lCon0[3].isSelected = true;
        lCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 0, 3);
        if (!Globals::vignetteOn)
            Globals::vignetteOn = true;
    }
    else if (lCon0[4].isMousePressed() && bLPlace[0] && !lCon0[4].isSelected)
    {
        lCon0[0].isSelected = false;
        lCon0[1].isSelected = false;
        lCon0[2].isSelected = false;
        lCon0[3].isSelected = false;
        lCon0[4].isSelected = true;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 0, 4);
        if (!Globals::vignetteOn)
            Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        lCon0[0].isSelected = false;
        lCon0[1].isSelected = false;
        lCon0[2].isSelected = false;
        lCon0[3].isSelected = false;
        lCon0[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        // c.stopLocationAudio();
        if (Globals::vignetteOn)
            Globals::vignetteOn = false;
    }
    
    // ------------------------------------
    // left content menu item 1 selection
    // ------------------------------------
    if (lCon1[0].isMousePressed() && bLPlace[1] && !lCon1[0].isSelected)
    {
        lCon1[0].isSelected = true;
        lCon1[1].isSelected = false;
        lCon1[2].isSelected = false;
        lCon1[3].isSelected = false;
        lCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 1, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon1[1].isMousePressed() && bLPlace[1] && !lCon1[1].isSelected)
    {
        lCon1[0].isSelected = false;
        lCon1[1].isSelected = true;
        lCon1[2].isSelected = false;
        lCon1[3].isSelected = false;
        lCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 1, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon1[2].isMousePressed() && bLPlace[1] && !lCon1[2].isSelected)
    {
        lCon1[0].isSelected = false;
        lCon1[1].isSelected = false;
        lCon1[2].isSelected = true;
        lCon1[3].isSelected = false;
        lCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        
        // load current content, enable vignette
        c.load(0, 1, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon1[3].isMousePressed() && bLPlace[1] && !lCon1[3].isSelected)
    {
        lCon1[0].isSelected = false;
        lCon1[1].isSelected = false;
        lCon1[2].isSelected = false;
        lCon1[3].isSelected = true;
        lCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 1, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon1[4].isMousePressed() && bLPlace[1] && !lCon1[4].isSelected)
    {
        lCon1[0].isSelected = false;
        lCon1[1].isSelected = false;
        lCon1[2].isSelected = false;
        lCon1[3].isSelected = false;
        lCon1[4].isSelected = true;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 1, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        lCon1[0].isSelected = false;
        lCon1[1].isSelected = false;
        lCon1[2].isSelected = false;
        lCon1[3].isSelected = false;
        lCon1[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    // ------------------------------------
    // left content menu item 2 selection
    // ------------------------------------
    if (lCon2[0].isMousePressed() && bLPlace[2] && !lCon2[0].isSelected)
    {
        lCon2[0].isSelected = true;
        lCon2[1].isSelected = false;
        lCon2[2].isSelected = false;
        lCon2[3].isSelected = false;
        lCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 2, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon2[1].isMousePressed() && bLPlace[2] && !lCon2[1].isSelected)
    {
        lCon2[0].isSelected = false;
        lCon2[1].isSelected = true;
        lCon2[2].isSelected = false;
        lCon2[3].isSelected = false;
        lCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 2, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon2[2].isMousePressed() && bLPlace[2] && !lCon2[2].isSelected)
    {
        lCon2[0].isSelected = false;
        lCon2[1].isSelected = false;
        lCon2[2].isSelected = true;
        lCon2[3].isSelected = false;
        lCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 2, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon2[3].isMousePressed() && bLPlace[2] && !lCon2[3].isSelected)
    {
        lCon2[0].isSelected = false;
        lCon2[1].isSelected = false;
        lCon2[2].isSelected = false;
        lCon2[3].isSelected = true;
        lCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 2, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon2[4].isMousePressed() && bLPlace[2] && !lCon2[4].isSelected)
    {
        lCon2[0].isSelected = false;
        lCon2[1].isSelected = false;
        lCon2[2].isSelected = false;
        lCon2[3].isSelected = false;
        lCon2[4].isSelected = true;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 2, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        lCon2[0].isSelected = false;
        lCon2[1].isSelected = false;
        lCon2[2].isSelected = false;
        lCon2[3].isSelected = false;
        lCon2[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    // ------------------------------------
    // left content menu item 3 selection
    // ------------------------------------
    if (lCon3[0].isMousePressed() && bLPlace[3] && !lCon3[0].isSelected)
    {
        lCon3[0].isSelected = true;
        lCon3[1].isSelected = false;
        lCon3[2].isSelected = false;
        lCon3[3].isSelected = false;
        lCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 3, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon3[1].isMousePressed() && bLPlace[3] && !lCon3[1].isSelected)
    {
        lCon3[0].isSelected = false;
        lCon3[1].isSelected = true;
        lCon3[2].isSelected = false;
        lCon3[3].isSelected = false;
        lCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 3, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon3[2].isMousePressed() && bLPlace[3] && !lCon3[2].isSelected)
    {
        lCon3[0].isSelected = false;
        lCon3[1].isSelected = false;
        lCon3[2].isSelected = true;
        lCon3[3].isSelected = false;
        lCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 3, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon3[3].isMousePressed() && bLPlace[3] && !lCon3[3].isSelected)
    {
        lCon3[0].isSelected = false;
        lCon3[1].isSelected = false;
        lCon3[2].isSelected = false;
        lCon3[3].isSelected = true;
        lCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 3, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon3[4].isMousePressed() && bLPlace[3] && !lCon3[4].isSelected)
    {
        lCon3[0].isSelected = false;
        lCon3[1].isSelected = false;
        lCon3[2].isSelected = false;
        lCon3[3].isSelected = false;
        lCon3[4].isSelected = true;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 3, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        lCon3[0].isSelected = false;
        lCon3[1].isSelected = false;
        lCon3[2].isSelected = false;
        lCon3[3].isSelected = false;
        lCon3[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    // ------------------------------------
    // left content menu item 4 selection
    // ------------------------------------
    if (lCon4[0].isMousePressed() && bLPlace[4] && !lCon4[0].isSelected)
    {
        lCon4[0].isSelected = true;
        lCon4[1].isSelected = false;
        lCon4[2].isSelected = false;
        lCon4[3].isSelected = false;
        lCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 4, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon4[1].isMousePressed() && bLPlace[4] && !lCon4[1].isSelected)
    {
        lCon4[0].isSelected = false;
        lCon4[1].isSelected = true;
        lCon4[2].isSelected = false;
        lCon4[3].isSelected = false;
        lCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 4, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon4[2].isMousePressed() && bLPlace[4] && !lCon4[2].isSelected)
    {
        lCon4[0].isSelected = false;
        lCon4[1].isSelected = false;
        lCon4[2].isSelected = true;
        lCon4[3].isSelected = false;
        lCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 4, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon4[3].isMousePressed() && bLPlace[4] && !lCon4[3].isSelected)
    {
        lCon4[0].isSelected = false;
        lCon4[1].isSelected = false;
        lCon4[2].isSelected = false;
        lCon4[3].isSelected = true;
        lCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(0, 4, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (lCon4[4].isMousePressed() && bLPlace[4] && !lCon4[4].isSelected)
    {
        lCon4[0].isSelected = false;
        lCon4[1].isSelected = false;
        lCon4[2].isSelected = false;
        lCon4[3].isSelected = false;
        lCon4[4].isSelected = true;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(0, 4, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        lCon4[0].isSelected = false;
        lCon4[1].isSelected = false;
        lCon4[2].isSelected = false;
        lCon4[3].isSelected = false;
        lCon4[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    
    // ------------------------------------
    // right content menu item 0 selection
    // ------------------------------------
    if (rCon0[0].isMousePressed() && bRPlace[0] && !rCon0[0].isSelected)
    {
        rCon0[0].isSelected = true;
        rCon0[1].isSelected = false;
        rCon0[2].isSelected = false;
        rCon0[3].isSelected = false;
        rCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 0, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon0[1].isMousePressed() && bRPlace[0] && !rCon0[1].isSelected)
    {
        rCon0[0].isSelected = false;
        rCon0[1].isSelected = true;
        rCon0[2].isSelected = false;
        rCon0[3].isSelected = false;
        rCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 0, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon0[2].isMousePressed() && bRPlace[0] && !rCon0[2].isSelected)
    {
        rCon0[0].isSelected = false;
        rCon0[1].isSelected = false;
        rCon0[2].isSelected = true;
        rCon0[3].isSelected = false;
        rCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 0, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon0[3].isMousePressed() && bRPlace[0] && !rCon0[3].isSelected)
    {
        rCon0[0].isSelected = false;
        rCon0[1].isSelected = false;
        rCon0[2].isSelected = false;
        rCon0[3].isSelected = true;
        rCon0[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 0, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon0[4].isMousePressed() && bRPlace[0] && !rCon0[4].isSelected)
    {
        rCon0[0].isSelected = false;
        rCon0[1].isSelected = false;
        rCon0[2].isSelected = false;
        rCon0[3].isSelected = false;
        rCon0[4].isSelected = true;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 0, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        rCon0[0].isSelected = false;
        rCon0[1].isSelected = false;
        rCon0[2].isSelected = false;
        rCon0[3].isSelected = false;
        rCon0[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    
    // ------------------------------------
    // right content menu item 1 selection
    // ------------------------------------
    if (rCon1[0].isMousePressed() && bRPlace[1] && !rCon1[0].isSelected)
    {
        rCon1[0].isSelected = true;
        rCon1[1].isSelected = false;
        rCon1[2].isSelected = false;
        rCon1[3].isSelected = false;
        rCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 1, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon1[1].isMousePressed() && bRPlace[1] && !rCon1[1].isSelected)
    {
        rCon1[0].isSelected = false;
        rCon1[1].isSelected = true;
        rCon1[2].isSelected = false;
        rCon1[3].isSelected = false;
        rCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 1, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon1[2].isMousePressed() && bRPlace[1] && !rCon1[2].isSelected)
    {
        rCon1[0].isSelected = false;
        rCon1[1].isSelected = false;
        rCon1[2].isSelected = true;
        rCon1[3].isSelected = false;
        rCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 1, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon1[3].isMousePressed() && bRPlace[1] && !rCon1[3].isSelected)
    {
        rCon1[0].isSelected = false;
        rCon1[1].isSelected = false;
        rCon1[2].isSelected = false;
        rCon1[3].isSelected = true;
        rCon1[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 1, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon1[4].isMousePressed() && bRPlace[1] && !rCon1[4].isSelected)
    {
        rCon1[0].isSelected = false;
        rCon1[1].isSelected = false;
        rCon1[2].isSelected = false;
        rCon1[3].isSelected = false;
        rCon1[4].isSelected = true;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 1, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        rCon1[0].isSelected = false;
        rCon1[1].isSelected = false;
        rCon1[2].isSelected = false;
        rCon1[3].isSelected = false;
        rCon1[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    
    // ------------------------------------
    // right content menu item 2 selection
    // ------------------------------------
    if (rCon2[0].isMousePressed() && bRPlace[2] && !rCon2[0].isSelected)
    {
        rCon2[0].isSelected = true;
        rCon2[1].isSelected = false;
        rCon2[2].isSelected = false;
        rCon2[3].isSelected = false;
        rCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 2, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon2[1].isMousePressed() && bRPlace[2] && !rCon2[1].isSelected)
    {
        rCon2[0].isSelected = false;
        rCon2[1].isSelected = true;
        rCon2[2].isSelected = false;
        rCon2[3].isSelected = false;
        rCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 2, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon2[2].isMousePressed() && bRPlace[2] && !rCon2[2].isSelected)
    {
        rCon2[0].isSelected = false;
        rCon2[1].isSelected = false;
        rCon2[2].isSelected = true;
        rCon2[3].isSelected = false;
        rCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 2, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon2[3].isMousePressed() && bRPlace[2] && !rCon2[3].isSelected)
    {
        rCon2[0].isSelected = false;
        rCon2[1].isSelected = false;
        rCon2[2].isSelected = false;
        rCon2[3].isSelected = true;
        rCon2[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 2, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon2[4].isMousePressed() && bRPlace[2] && !rCon2[4].isSelected)
    {
        rCon2[0].isSelected = false;
        rCon2[1].isSelected = false;
        rCon2[2].isSelected = false;
        rCon2[3].isSelected = false;
        rCon2[4].isSelected = true;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 2, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        rCon2[0].isSelected = false;
        rCon2[1].isSelected = false;
        rCon2[2].isSelected = false;
        rCon2[3].isSelected = false;
        rCon2[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    
    // ------------------------------------
    // right content menu item 3 selection
    // ------------------------------------
    if (rCon3[0].isMousePressed() && bRPlace[3] && !rCon3[0].isSelected)
    {
        rCon3[0].isSelected = true;
        rCon3[1].isSelected = false;
        rCon3[2].isSelected = false;
        rCon3[3].isSelected = false;
        rCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 3, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon3[1].isMousePressed() && bRPlace[3] && !rCon3[1].isSelected)
    {
        rCon3[0].isSelected = false;
        rCon3[1].isSelected = true;
        rCon3[2].isSelected = false;
        rCon3[3].isSelected = false;
        rCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 3, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon3[2].isMousePressed() && bRPlace[3] && !rCon3[2].isSelected)
    {
        rCon3[0].isSelected = false;
        rCon3[1].isSelected = false;
        rCon3[2].isSelected = true;
        rCon3[3].isSelected = false;
        rCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 3, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon3[3].isMousePressed() && bRPlace[3] && !rCon3[3].isSelected)
    {
        rCon3[0].isSelected = false;
        rCon3[1].isSelected = false;
        rCon3[2].isSelected = false;
        rCon3[3].isSelected = true;
        rCon3[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 3, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon3[4].isMousePressed() && bRPlace[3] && !rCon3[4].isSelected)
    {
        rCon3[0].isSelected = false;
        rCon3[1].isSelected = false;
        rCon3[2].isSelected = false;
        rCon3[3].isSelected = false;
        rCon3[4].isSelected = true;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 3, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        rCon3[0].isSelected = false;
        rCon3[1].isSelected = false;
        rCon3[2].isSelected = false;
        rCon3[3].isSelected = false;
        rCon3[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
    
    
    // ------------------------------------
    // right content menu item 4 selection
    // ------------------------------------
    if (rCon4[0].isMousePressed() && bRPlace[4] && !rCon4[0].isSelected)
    {
        rCon4[0].isSelected = true;
        rCon4[1].isSelected = false;
        rCon4[2].isSelected = false;
        rCon4[3].isSelected = false;
        rCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 4, 0);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon4[1].isMousePressed() && bRPlace[4] && !rCon4[1].isSelected)
    {
        rCon4[0].isSelected = false;
        rCon4[1].isSelected = true;
        rCon4[2].isSelected = false;
        rCon4[3].isSelected = false;
        rCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 4, 1);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon4[2].isMousePressed() && bRPlace[4] && !rCon4[2].isSelected)
    {
        rCon4[0].isSelected = false;
        rCon4[1].isSelected = false;
        rCon4[2].isSelected = true;
        rCon4[3].isSelected = false;
        rCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        hs1Intro.stop();
        crossrailIntro.stop();
        // c.stopLocationAudio();
        
        // load current content, enable vignette
        c.load(1, 4, 2);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon4[3].isMousePressed() && bRPlace[4] && !rCon4[3].isSelected)
    {
        rCon4[0].isSelected = false;
        rCon4[1].isSelected = false;
        rCon4[2].isSelected = false;
        rCon4[3].isSelected = true;
        rCon4[4].isSelected = false;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 4, 3);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (rCon4[4].isMousePressed() && bRPlace[4] && !rCon4[4].isSelected)
    {
        rCon4[0].isSelected = false;
        rCon4[1].isSelected = false;
        rCon4[2].isSelected = false;
        rCon4[3].isSelected = false;
        rCon4[4].isSelected = true;
        
        // play button sound
        snd2.play();
        
        // load current content, enable vignette
        c.load(1, 4, 4);
        if (!Globals::vignetteOn) Globals::vignetteOn = true;
    }
    else if (!bLPlace[0] && !bLPlace[1] && !bLPlace[2] && !bLPlace[3] && !bLPlace[4] && !bRPlace[0] && !bRPlace[1] && !bRPlace[2] && !bRPlace[3] && !bRPlace[4])
    {
        rCon4[0].isSelected = false;
        rCon4[1].isSelected = false;
        rCon4[2].isSelected = false;
        rCon4[3].isSelected = false;
        rCon4[4].isSelected = false;
        
        // close content, stop video, and disable vignette
        c.item = 5;
        c.stopVideos();
        c.stopAudio();
        if (Globals::vignetteOn) Globals::vignetteOn = false;
    }
}

//--------------------------------------------------------------
void InteractiveMenu::drawContent()
{
    // content class draw function
    c.draw();
}