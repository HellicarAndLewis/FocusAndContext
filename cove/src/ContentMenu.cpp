//
//  ContentMenu.cpp
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 3/03/2016.
//
//

#include "ContentMenu.h"
#include "Globals.h"

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
    
    destroyContent();
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
void ContentMenu::drawContent()
{
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    float lerpValue = 0.2;
    for (int j = 0; j < CONTENT_AMT; j++)
    {
        if (item[j])
        {
            if (display)
            {
                scale[j] = ofLerp(scale[j], 1.3, lerpValue);
                img[j].load(path[j]);
                
                if (scale[j] >= 1.2999)//0.999)
                {
                    display = false;
                }
            }
        }
        else
        {
            scale[j] = ofLerp(scale[j], 0.0, lerpValue);
        }
        
        // if allocated then draw
        if (img[j].isAllocated()) {
            ofSetColor(0, 0, 0, 20);
            ofDrawRectangle(width/2 + 6, height/2 + 6, img[j].getWidth() * scale[j], img[j].getHeight() * scale[j]);
            
            ofSetColor(255, 255, 255);
            img[j].draw(width/2, height/2, img[j].getWidth() * scale[j], img[j].getHeight() * scale[j]);
        }
        
        // if all scales near zero, can launch next content
        if (scale[0] <= 0.0001 && scale[1] <= 0.0001 && scale[2] <= 0.0001 && scale[3] <= 0.0001 && scale[4] <= 0.0001)
        {
            display = true;
        }
    }
    
    ofSetRectMode(OF_RECTMODE_CORNER);
}
//--------------------------------------------------------------
void ContentMenu::destroyContent()
{
    float lerpValue = 0.4;
    if (Globals::buttonPressed)
    {
        for (int j = 0; j < CONTENT_AMT; j++) {
            item[j] = false;
            scale[j] = ofLerp(scale[j], 0.0, lerpValue);
            
            if (scale[j] <= 0.0001)
                Globals::buttonPressed = false;
        }
    }
}

//--------------------------------------------------------------
void ContentMenu::transform()
{
    
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
                               //cout << "button0, content0 " << ofToString(i) << " " << ofToString(j) << endl;
                                
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button0, content1 " << ofToString(i) << " " << ofToString(j) << endl;
                                
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button0, content2 " << ofToString(i) << " " << ofToString(j) << endl;
                                
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                               //cout << "button0, content3 " << ofToString(i) << " " << ofToString(j) << endl;
                                
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                               //cout << "button0, content4 " << ofToString(i) << " " << ofToString(j) << endl;
                                
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
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
                               //cout << "button 1, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 1, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 1, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                               //cout << "button 1, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                               //cout << "button 1, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
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
                               //cout << "button 2, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 2, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 2, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                               //cout << "button 2, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                               //cout << "button 2, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
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
                               //cout << "button 3, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 3, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 3, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                               //cout << "button 3, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                               //cout << "button 3, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
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
                               //cout << "button 4, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 4, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                               //cout << "button 4, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                               //cout << "button 4, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                               //cout << "button 4, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
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
                               //cout << "button0, content0 " << ofToString(i) << " " << ofToString(j) << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button0, content1 " << ofToString(i) << " " << ofToString(j) << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button0, content2 " << ofToString(i) << " " << ofToString(j) << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                               //cout << "button0, content3 " << ofToString(i) << " " << ofToString(j) << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                               //cout << "button0, content4 " << ofToString(i) << " " << ofToString(j) << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
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
                               //cout << "button 1, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 1, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 1, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                               //cout << "button 1, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                               //cout << "button 1, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
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
                               //cout << "button 2, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 2, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 2, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                               //cout << "button 2, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                               //cout << "button 2, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
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
                               //cout << "button 3, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 3, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 3, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                               //cout << "button 3, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                               //cout << "button 3, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
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
                               //cout << "button 4, content 0" << endl;
                                display = false;
                                path[0] = "content/media/text.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 4, content 1" << endl;
                                display = false;
                                path[1] = "content/media/image.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                               //cout << "button 4, content 2" << endl;
                                display = false;
                                path[2] = "content/media/video.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                               //cout << "button 4, content 3" << endl;
                                display = false;
                                path[3] = "content/media/model.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                               //cout << "button 4, content 4" << endl;
                                display = false;
                                path[4] = "content/media/audio.png";
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                break;
                        }
                        break;
                }
                
                buttonClicked = true;
            }
        }
    }
}