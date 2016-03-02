//
//  ContentMenu.cpp
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 21/02/2016.
//
//

#include "ContentMenu.h"

//--------------------------------------------------------------
void ContentMenu::setup(int _w, int _h, float _area, float _padding)
{
    // setup variables
    width = _w;
    height = _h;
    area = _area;
    padding = _padding;
    leftOn = false;
    rightOn = false;
    buttonClicked = false;
    
    // setup content menu for both projects (left/right menu)
    for (int i = 0; i < POINTS; i++) {
        for (int j = 0; j < CONTENT_AMT; j++) {
            float x = i * (area + padding);
            contentLeft[i][j].set(padding + x, height - padding - (area * 2 + padding), area, area);
            contentRight[i][j].set(padding + x, height - padding - (area * 2 + padding), area, area);
            
            contentLeft[i][j].title = "LT Content " + ofToString(i);
            contentRight[i][j].title = "RT Content " + ofToString(i);
        }
    }
    
    /*
    // setup left sub menu
    for (int i = 0; i < length; i++) {
        posLeft[i].set(padding, height - padding - mainArea + (areaDiff / 2));
        sizeLeft[i] = subArea;
        
        objsLeft[i].drawType = 0;
        objsLeft[i].set(padding, height - padding - mainArea + (areaDiff / 2),
                        subArea,
                        subArea);
        objsLeft[i].isMainTile = false;
        
        switch (i) {
            case 0:
                objsLeft[i].title = ofToString("St Pancras");
                break;
                
            case 1:
                objsLeft[i].title = ofToString("Stratford");
                break;
                
            case 2:
                objsLeft[i].title = ofToString("Ebbsfleet");
                break;
                
            case 3:
                objsLeft[i].title = ofToString("Ashford");
                break;
                
            case 4:
                objsLeft[i].title = ofToString("Warwick Gardens");
                break;
        }
    }
     */
    
    /*
    // setup right sub menu
    for (int i = 0; i < length; i++) {
        
        posRight[i].set(width - padding - subArea, height - padding - mainArea + (areaDiff / 2));
        sizeRight[i] = subArea;
    
        objsRight[i].drawType = 0;
        objsRight[i].set(width - padding - subArea,
                         height - padding - mainArea + (areaDiff / 2),
                         subArea,
                         subArea);
        objsRight[i].isMainTile = false;

        switch (i) {
            case 4:
                objsRight[i].title = ofToString("Tottenham Ct Rd");
                break;
                
            case 3:
                objsRight[i].title = ofToString("Barbican");
                break;
                
            case 2:
                objsRight[i].title = ofToString("Canary Wharf");
                break;
                
            case 1:
                objsRight[i].title = ofToString("Custom House");
                break;
                
            case 0:
                objsRight[i].title = ofToString("Woolwich");
                break;
        }
    }
     */
    
    /*
    // setup left menu main
    objLeft.isMainTile = true;
    objLeft.title = "HS1";
    objLeft.lineLength = 0;
    objLeft.drawType = 0;
    objLeft.set(padding,
                height - padding - mainArea,
                mainArea,
                mainArea);
    
    // setup right menu main
    objRight.isMainTile = true;
    objRight.title = "Crossrail";
    objRight.lineLength = 0;
    objRight.drawType = 0;
    objRight.set((width - padding) - mainArea,
                 height - padding - mainArea,
                 mainArea,
                 mainArea);
    
    // setup left menu line
    objLeftLine.lineLength = 0;
    objLeftLine.drawType = 1;
    objLeftLine.set(padding,
                    height - padding - mainArea,
                    0,
                    mainArea);
    
    // setup right menu line
    objRightLine.lineLength = 0;
    objRightLine.drawType = 2;//2;
    objRightLine.set((width - padding),
                     height - padding - mainArea,
                     0,
                     mainArea);
     */
}

//--------------------------------------------------------------
void ContentMenu::update()
{
    // button position and size
    transform();
    // check button presses
    pressed();
}

//--------------------------------------------------------------
void ContentMenu::draw(int _project, bool _draw)
{
    if (_project == 0) {
        for (int i = 0; i < POINTS; i++) {
            for (int j = 0; j < CONTENT_AMT; j++) {
                float x = i * (area + padding);
                contentLeft[i][j].isDraw = _draw;
            }
        }
    }
    else {
        for (int i = 0; i < POINTS; i++) {
            for (int j = 0; j < CONTENT_AMT; j++) {
                float x = i * (area + padding);
                contentRight[i][j].isDraw = _draw;
            }
        }
    }
}

//--------------------------------------------------------------
void ContentMenu::transform()
{
    /*
    // left sub menu animations
    for (int i = 0; i < length; i++) {
        
        if (leftOn) {
            
            if (bLeftActive[i]) {
                
                float distance = i  * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance - areaDiff/2, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea, easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], mainArea, easeOut);
            } else {
                
                float distance = i  * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeOut);
            }
            
        } else {
            
            posLeft[i].x = ofLerp(posLeft[i].x, padding, easeIn);
            posLeft[i].y = ofLerp(posLeft[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);
            
            sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeIn);
            
            bLeftActive[i] = false;
        }
        
        // update objects position and size
        objsLeft[i].set(posLeft[i].x, posLeft[i].y, sizeLeft[i], sizeLeft[i]);
        objsLeft[i].isSelected = bLeftActive[i];
    }
    
    // right sub menu animations
    for (int i = 0; i < length; i++) {
        
        if (rightOn) {
            
            float distance = width - padding - subArea - (i  * (subArea + padding) + padding + mainArea);
            
            if (bRightActive[i]) {
                
                posRight[i].x = ofLerp(posRight[i].x, distance - areaDiff/2, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea, easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], mainArea, easeOut);
            } else {
                
                posRight[i].x = ofLerp(posRight[i].x, distance, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], subArea, easeOut);
            }
            
        } else {
            
            posRight[i].x = ofLerp(posRight[i].x, width - padding - subArea, easeIn);
            posRight[i].y = ofLerp(posRight[i].y, height - padding - mainArea + (areaDiff / 2), easeIn);
            
            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);
            
            bRightActive[i] = false;
        }
        
        // update objects position and size
        objsRight[i].set(posRight[i].x, posRight[i].y, sizeRight[i], sizeRight[i]);
        objsRight[i].isSelected = bRightActive[i];
    }
     */
}

//--------------------------------------------------------------
void ContentMenu::pressed()
{
//    for (int i = 0; i < POINTS; i++) {
//        for (int j = 0; j < CONTENT_AMT; j++) {
//            //
//            contentLeft[i][j]
//        }
//    }
    
    /*
    for (int i = 0; i < length; i++) {
        if (objsLeft[i].isMousePressed(0) == 1 && leftOn && !bLeftActive[i] && !buttonClicked) {
            switch (i) {
                case 0:
                    bLeftActive[0] = true;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    break;
                case 1:
                    bLeftActive[0] = false;
                    bLeftActive[1] = true;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    break;
                case 2:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = true;
                    bLeftActive[3] = false;
                    bLeftActive[4] = false;
                    break;
                case 3:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = true;
                    bLeftActive[4] = false;
                    break;
                case 4:
                    bLeftActive[0] = false;
                    bLeftActive[1] = false;
                    bLeftActive[2] = false;
                    bLeftActive[3] = false;
                    bLeftActive[4] = true;
                    break;
            }
            
            buttonClicked = true;
        }
    
        // check for right button clicks
        if (objsRight[i].isMousePressed(0) == 1 && rightOn && !bRightActive[i] && !buttonClicked) {
            switch (i) {
                case 0:
                    bRightActive[0] = true;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    break;
                case 1:
                    bRightActive[0] = false;
                    bRightActive[1] = true;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    break;
                case 2:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = true;
                    bRightActive[3] = false;
                    bRightActive[4] = false;
                    break;
                case 3:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = true;
                    bRightActive[4] = false;
                    break;
                case 4:
                    bRightActive[0] = false;
                    bRightActive[1] = false;
                    bRightActive[2] = false;
                    bRightActive[3] = false;
                    bRightActive[4] = true;
                    break;
            }
            
            buttonClicked = true;
        }
    }
     */
}