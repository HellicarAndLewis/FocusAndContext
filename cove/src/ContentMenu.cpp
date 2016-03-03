//
//  ContentMenu.cpp
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 3/03/2016.
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
    for (int i = 0; i < POI; i++)
    {
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            float x = j * (area + padding);
            float y = area * 2 + padding/2;
            contentLeft[i][j].set(padding + x, height - padding/2 - y, area, area);
            contentRight[i][j].set(padding + x, height - padding/2 - y, area, area);
            
            contentLeft[i][j].title = "L " + ofToString(i) + " " + ofToString(j);
            contentRight[i][j].title = "R " + ofToString(i) + " " + ofToString(j);
        }
    }
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
void ContentMenu::draw(int _project, int _point, bool _draw)
{
    if (_project == 0)
    {
        int i = _point;
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            float x = j * (area + padding);
            float y = area * 2 + padding/2;
            
            if (_draw) {
                contentLeft[i][j].isDraw = true;
                contentLeft[i][j].set(padding + x, height - padding/2 - y, area, area);
            } else {
                contentLeft[i][j].isDraw = false;
                contentLeft[i][j].set(padding + x, height + height/2, area, area);
            }
        }
    }
    else
    {
        int i = _point;
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            float x = j * (area + padding);
            float y = area * 2 + padding/2;
            
            if (_draw) {
                contentRight[i][j].isDraw = true;
                contentRight[i][j].set(padding + x, height - padding/2 - y, area, area);
            } else {
                contentRight[i][j].isDraw = false;
                contentRight[i][j].set(padding + x, height + height/2, area, area);
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
    
    for (int i = 0; i < POI; i++)
    {
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            if (contentLeft[i][j].isMousePressed(0) == 1 && leftOn && !bLeftActive[i][j] && !buttonClicked)
            {
                //cout << "hs1 " << ofToString(i) << " " << ofToString(j) << endl;
                
                switch (i) {
                    case 0:
                        
                        switch (j) {
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button0, content0 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button0, content1 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button0, content2 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                cout << "button0, content3 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                cout << "button0, content4 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                        }
                        break;
                    
                    case 1:
                        switch (j) {
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 1, content 0" << endl;
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 1, content 1" << endl;
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 1, content 2" << endl;
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                cout << "button 1, content 3" << endl;
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                cout << "button 1, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 2:
                        switch (j) {
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 2, content 0" << endl;
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 2, content 1" << endl;
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 2, content 2" << endl;
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                cout << "button 2, content 3" << endl;
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                cout << "button 2, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 3:
                        switch (j) {
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 3, content 0" << endl;
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 3, content 1" << endl;
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 3, content 2" << endl;
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                cout << "button 3, content 3" << endl;
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                cout << "button 3, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 4:
                        switch (j) {
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 4, content 0" << endl;
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 4, content 1" << endl;
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                cout << "button 4, content 2" << endl;
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                cout << "button 4, content 3" << endl;
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                cout << "button 4, content 4" << endl;
                                break;
                        }
                        break;
                }
                
                buttonClicked = true;
            }
        }
    }
    
    for (int i = 0; i < POI; i++)
    {
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            
            if (contentRight[i][j].isMousePressed(0) == 1 && rightOn && !bRightActive[i][j] && !buttonClicked)
            {
                //cout << "crossrail " << ofToString(i) << " " << ofToString(j) << endl;
                
                switch (i) {
                    case 0:
                        
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button0, content0 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button0, content1 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button0, content2 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                cout << "button0, content3 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                cout << "button0, content4 " << ofToString(i) << " " << ofToString(j) << endl;
                                break;
                        }
                        break;
                        
                    case 1:
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 1, content 0" << endl;
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 1, content 1" << endl;
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 1, content 2" << endl;
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                cout << "button 1, content 3" << endl;
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                cout << "button 1, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 2:
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 2, content 0" << endl;
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 2, content 1" << endl;
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 2, content 2" << endl;
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                cout << "button 2, content 3" << endl;
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                cout << "button 2, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 3:
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 3, content 0" << endl;
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 3, content 1" << endl;
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 3, content 2" << endl;
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                cout << "button 3, content 3" << endl;
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                cout << "button 3, content 4" << endl;
                                break;
                        }
                        break;
                        
                    case 4:
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 4, content 0" << endl;
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 4, content 1" << endl;
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                cout << "button 4, content 2" << endl;
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                cout << "button 4, content 3" << endl;
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                cout << "button 4, content 4" << endl;
                                break;
                        }
                        break;
                }
                
                buttonClicked = true;
            }
        }
    }
}