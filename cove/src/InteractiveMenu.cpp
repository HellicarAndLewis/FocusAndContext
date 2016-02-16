#include "InteractiveMenu.h"

//--------------------------------------------------------------
void InteractiveMenu::setup(float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut)
{
    // setup variables
    mainArea = _mainArea;
    subArea = _subArea;
    areaDiff = mainArea - subArea;
    padding = _padding;
    easeIn = _easeIn;
    easeOut = _easeOut;
    length = BUTTON_AMT;
    leftOn = false;
    rightOn = false;
    buttonClicked = false;
    
    // setup left sub menu
    for (int i = 0; i < length; i++) {
        posLeft[i].set(padding, ofGetHeight() - padding - mainArea + (areaDiff / 2));
        sizeLeft[i] = subArea;
        
        objsLeft[i].drawType = 0;
        objsLeft[i].set(padding, ofGetHeight() - padding - mainArea + (areaDiff / 2),
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
                objsLeft[i].title = ofToString("Ashford International");
                break;
                
            case 4:
                objsLeft[i].title = ofToString("Warwick Gardens");
                break;
        }
    }
    
    // setup right sub menu
    for (int i = 0; i < length; i++) {
        
        posRight[i].set(ofGetWidth() - padding - subArea, ofGetHeight() - padding - mainArea + (areaDiff / 2));
        sizeRight[i] = subArea;
    
        objsRight[i].drawType = 0;
        objsRight[i].set(ofGetWidth() - padding - subArea,
                         ofGetHeight() - padding - mainArea + (areaDiff / 2),
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
    
    // setup left menu main
    objLeft.isMainTile = true;
    objLeft.title = "HS1";
    objLeft.lineLength = 0;
    objLeft.drawType = 0;
    objLeft.set(padding,
                ofGetHeight() - padding - mainArea,
                mainArea,
                mainArea);
    
    // setup right menu main
    objRight.isMainTile = true;
    objRight.title = "Crossrail";
    objRight.lineLength = 0;
    objRight.drawType = 0;
    objRight.set((ofGetWidth() - padding) - mainArea,
                 ofGetHeight() - padding - mainArea,
                 mainArea,
                 mainArea);
    
    // setup left menu line
    objLeftLine.lineLength = 0;
    objLeftLine.drawType = 1;
    objLeftLine.set(padding,
                    ofGetHeight() - padding - mainArea,
                    0,
                    mainArea);
    
    // setup right menu line
    objRightLine.lineLength = 0;
    objRightLine.drawType = 2;//2;
    objRightLine.set((ofGetWidth() - padding),
                     ofGetHeight() - padding - mainArea,
                     0,
                     mainArea);
}

//--------------------------------------------------------------
void InteractiveMenu::update()
{
    // draw menu lines
    drawLines();
    // button position and size
    transform();
    // check button presses
    pressed();
}

//--------------------------------------------------------------
void InteractiveMenu::transform()
{
    // left sub menu animations
    for (int i = 0; i < length; i++) {
        
        if (leftOn) {
            
            if (bLeftActive[i]) {
                
                float distance = i  * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance - areaDiff/2, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, ofGetHeight() - padding - mainArea, easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], mainArea, easeOut);
            } else {
                
                float distance = i  * (subArea + padding) + (padding * 2) + mainArea;
                posLeft[i].x = ofLerp(posLeft[i].x, distance, easeOut);
                posLeft[i].y = ofLerp(posLeft[i].y, ofGetHeight() - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeLeft[i] = ofLerp(sizeLeft[i], subArea, easeOut);
            }
            
        } else {
            
            posLeft[i].x = ofLerp(posLeft[i].x, padding, easeIn);
            posLeft[i].y = ofLerp(posLeft[i].y, ofGetHeight() - padding - mainArea + (areaDiff / 2), easeIn);
            
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
            
            float distance = ofGetWidth() - padding - subArea - (i  * (subArea + padding) + padding + mainArea);
            
            if (bRightActive[i]) {
                
                posRight[i].x = ofLerp(posRight[i].x, distance - areaDiff/2, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, ofGetHeight() - padding - mainArea, easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], mainArea, easeOut);
            } else {
                
                posRight[i].x = ofLerp(posRight[i].x, distance, easeOut);
                posRight[i].y = ofLerp(posRight[i].y, ofGetHeight() - padding - mainArea + (areaDiff / 2), easeOut);
                
                sizeRight[i] = ofLerp(sizeRight[i], subArea, easeOut);
            }
            
        } else {
            
            posRight[i].x = ofLerp(posRight[i].x, ofGetWidth() - padding - subArea, easeIn);
            posRight[i].y = ofLerp(posRight[i].y, ofGetHeight() - padding - mainArea + (areaDiff / 2), easeIn);
            
            sizeRight[i] = ofLerp(sizeRight[i], subArea, easeIn);
            
            bRightActive[i] = false;
        }
        
        // update objects position and size
        objsRight[i].set(posRight[i].x, posRight[i].y, sizeRight[i], sizeRight[i]);
        objsRight[i].isSelected = bRightActive[i];
    }
}

//--------------------------------------------------------------
void InteractiveMenu::drawLines()
{
    // left side lines
    if (leftOn) {
        float lineDist = (length-1) * (subArea + padding) + (padding + subArea + padding);
        objLeftLine.lineLength = ofLerp(objLeftLine.lineLength, lineDist, easeOut);
    } else {
        objLeftLine.lineLength = ofLerp(objLeftLine.lineLength, 0, easeIn * 2);
    }
    
    // right side lines
    if (rightOn) {
        float defaultPos = ofGetWidth() - padding - mainArea;
        float lineDist = defaultPos - ((length-1) * (subArea + padding) + padding + defaultPos + padding + subArea);
        objRightLine.lineLength = ofLerp(objRightLine.lineLength, lineDist, easeOut);
    } else {
        objRightLine.lineLength = ofLerp(objRightLine.lineLength, 0, easeIn * 2);
    }
}

//--------------------------------------------------------------
void InteractiveMenu::pressed()
{
    for (int i = 0; i < length; i++) {
        if (objsLeft[i].isMousePressed(0) == 1 && leftOn && !bLeftActive[i] && !buttonClicked) {
            cout << "button " << ofToString(i) << " released" << endl;
            
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
            cout << "button " << ofToString(i) << " released" << endl;
            
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
}