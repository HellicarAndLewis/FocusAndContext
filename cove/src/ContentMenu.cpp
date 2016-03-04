//
//  ContentMenu.cpp
//  Cove
//
//  Created by Jason Walters on 21/02/2016.
//  Last edited by Jason Walters on 4/03/2016.
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
            
            if (j == 0)
            {
                contentLeft[i][j].title = "Text";
                contentRight[i][j].title = "Text";
            }
            else if (j == 1)
            {
                contentLeft[i][j].title = "Image";
                contentRight[i][j].title = "Image";
            }
            else if (j == 2)
            {
                contentLeft[i][j].title = "Video";
                contentRight[i][j].title = "Video";
            }
            else if (j == 3)
            {
                contentLeft[i][j].title = "Model";
                contentRight[i][j].title = "Model";
            }
            else if (j == 4)
            {
                contentLeft[i][j].title = "Audio";
                contentRight[i][j].title = "Audio";
            }
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
    
    //vid.update();
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
void ContentMenu::drawContentTotem(int _project, int _point, int _item, bool _itemActive)
{
    int i = _point;
    int j = _item;
    float lerpValue = 0.2;
    item[j] = _itemActive;
    
    switch (j) {
        case 0:
            path[0] = "content/media/text.png";
            break;
        case 1:
            path[1] = "content/media/image.png";
            break;
        case 2:
            path[2] = "content/media/video.png";
            break;
        case 3:
            path[3] = "content/media/model.png";
            break;
        case 4:
            path[4] = "content/media/audio.png";
            break;
    }
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    if (item[j])
    {
        if (display)
        {
            scale[j] = ofLerp(scale[j], 1.3, lerpValue);
            
            //if (j != 2)
            img[j].load(path[j]);
            //else {
            //  vid.load(path[j]);
            //  vid.play();
            //}
            
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
        
        //if (vid.isPlaying()) vid.stop();
    }
    
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    if (item[0]) {
        item[1] = false;
        item[2] = false;
        item[3] = false;
        item[4] = false;
    }
    else if (item[1]) {
        item[0] = false;
        item[2] = false;
        item[3] = false;
        item[4] = false;
    }
    else if (item[2]) {
        item[1] = false;
        item[0] = false;
        item[3] = false;
        item[4] = false;
    }
    else if (item[3]) {
        item[1] = false;
        item[2] = false;
        item[0] = false;
        item[4] = false;
    }
    else if (item[4]) {
        item[1] = false;
        item[2] = false;
        item[3] = false;
        item[0] = false;
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
                
                /*
                if (j != 2)
                    img[j].load(path[j]);
                else {
                    //vid.load(path[j]);
                    vid.loadAsync(path[j]);
                    vid.play();
                }
                 */
                
                if (scale[j] >= 1.2999) display = false;
            }
        }
        else
        {
            scale[j] = ofLerp(scale[j], 0.0, lerpValue);
        }
        
        /*
        if (j != 2)
        {
            // if allocated then draw
            if (img[j].isAllocated()) {
                ofSetColor(0, 0, 0, 20);
                ofDrawRectangle(width/2 + 6, height/2 + 6, img[j].getWidth() * scale[j], img[j].getHeight() * scale[j]);
                
                ofSetColor(255, 255, 255);
                img[j].draw(width/2, height/2, img[j].getWidth() * scale[j], img[j].getHeight() * scale[j]);
            }
        }
        else {
                if (vid.isInitialized()) vid.draw(width/2, height/2, vid.getWidth() * scale[j], vid.getHeight() * scale[j]);
        }
         */
        
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

            //if (vid.isPlaying()) vid.stop();
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
        //if (vid.isPlaying()) vid.stop();
        
        // disable vignette
        Globals::vignetteOn = false;
        
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
                switch (i) {
                    case 0:
                        
                        switch (j) {
                                
                            case 0:
                                bLeftActive[i][0] = true;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;

                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = true;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = true;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = true;
                                bLeftActive[i][4] = false;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bLeftActive[i][0] = false;
                                bLeftActive[i][1] = false;
                                bLeftActive[i][2] = false;
                                bLeftActive[i][3] = false;
                                bLeftActive[i][4] = true;
                                
                                item[0] = bLeftActive[i][0];
                                item[1] = bLeftActive[i][1];
                                item[2] = bLeftActive[i][2];
                                item[3] = bLeftActive[i][3];
                                item[4] = bLeftActive[i][4];
                                
                                path[4] = "content/media/audio.png";
                                break;
                        }
                        break;
                }
                
                display = false;
                buttonClicked = true;
                Globals::vignetteOn = true;
            }
        }
    }
    
    for (int i = 0; i < POI; i++)
    {
        for (int j = 0; j < CONTENT_AMT; j++)
        {
            
            if (contentRight[i][j].isMousePressed(0) == 1 && rightOn && !bRightActive[i][j] && !buttonClicked)
            {
                switch (i) {
                    case 0:
                        
                        switch (j) {
                            case 0:
                                bRightActive[i][0] = true;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[4] = "content/media/audio.png";
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
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[0] = "content/media/text.png";
                                break;
                                
                            case 1:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = true;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[1] = "content/media/image.png";
                                break;
                                
                            case 2:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = true;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[2] = "content/media/video.png";
                                break;
                                
                            case 3:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = true;
                                bRightActive[i][4] = false;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[3] = "content/media/model.png";
                                break;
                                
                            case 4:
                                bRightActive[i][0] = false;
                                bRightActive[i][1] = false;
                                bRightActive[i][2] = false;
                                bRightActive[i][3] = false;
                                bRightActive[i][4] = true;
                                
                                item[0] = bRightActive[i][0];
                                item[1] = bRightActive[i][1];
                                item[2] = bRightActive[i][2];
                                item[3] = bRightActive[i][3];
                                item[4] = bRightActive[i][4];
                                
                                path[4] = "content/media/audio.png";
                                break;
                        }
                        break;
                }
                
                buttonClicked = true;
                Globals::vignetteOn = true;
                display = false;
            }
        }
    }
}