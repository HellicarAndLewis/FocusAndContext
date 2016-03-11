//
//  Content.cpp
//  Cove
//
//  Created by Jason Walters on 10/03/2016.
//  Last edited by Jason Walters on 10/03/2016.
//
//

#include "Content.h"
#include "Globals.h"

//--------------------------------------------------------------
void Content::setup()
{
    // setup file paths
    fileLocation();
}

//--------------------------------------------------------------
void Content::fileLocation()
{
    // HS1 - St Pancras
    path[0][0][0] = "content/media/HS1/Location/StPancras/Text/StPancras.png";
    path[0][0][1] = "content/media/HS1/Location/StPancras/Image/ModelSlabPressuresKingsCross.jpg";
    path[0][0][2] = "content/media/Placeholder/no_video.mp4";
    path[0][0][3] = "content/media/Placeholder/no_data.jpg";
    path[0][0][4] = "content/media/Placeholder/no_data.jpg";
    
    // HS1 - Stratford - StratfordInternational
    path[0][1][0] = "content/media/HS1/Location/StratfordInternational/Text/StratfordInternational.png";
    path[0][1][1] = "content/media/HS1/Location/StratfordInternational/Image/HighSpeedHS1HawkEditions.jpg";
    path[0][1][2] = "content/media/Placeholder/no_video.mp4";
    path[0][1][3] = "content/media/Placeholder/no_data.jpg";
    path[0][1][4] = "content/media/Placeholder/no_data.jpg";
    
    // HS1 - Ebbsfleet - EbbsfleetInternational
    path[0][2][0] = "content/media/HS1/Location/EbbsfleetInternational/Text/EbbsfleetInternational.png";
    path[0][2][1] = "content/media/HS1/Location/EbbsfleetInternational/Image/EbbsfleetElephant.jpg";
    path[0][2][2] = "content/media/HS1/Location/EbbsfleetInternational/Video/BridgePush.mpg";
    path[0][2][3] = "content/media/Placeholder/no_data.jpg";
    path[0][2][4] = "content/media/Placeholder/no_data.jpg";
    
    // HS1 - Medway Viaduct
    path[0][3][0] = "content/media/HS1/Location/MedwayViaduct/Text/MedwayViaduct.png";
    path[0][3][1] = "content/media/HS1/Location/MedwayViaduct/Image/MedwayViaduct01.jpg";
    path[0][3][2] = "content/media/HS1/Location/MedwayViaduct/Video/CTRL.mp4";
    path[0][3][3] = "content/media/Placeholder/no_data.jpg";
    path[0][3][4] = "content/media/Placeholder/no_data.jpg";
    
    // HS1 - Ashford
    path[0][4][0] = "content/media/HS1/Location/AshfordInternational/Text/PlanningTheRoute.png";
    path[0][4][1] = "content/media/HS1/Location/AshfordInternational/Image/HS1RouteIntersectingWithExistingRailLinks.jpg";
    path[0][4][2] = "content/media/HS1/Location/AshfordInternational/Video/Ctrl.mp4";
    path[0][4][3] = "content/media/Placeholder/no_data.jpg";
    path[0][4][4] = "content/media/Placeholder/no_data.jpg";
    
    // Crossrail - Woolwich
    path[1][0][4] = "content/media/Placeholder/no_data.jpg";
    path[1][0][3] = "content/media/Placeholder/no_data.jpg";
    path[1][0][2] = "content/media/Placeholder/no_video.mp4";
    path[1][0][1] = "content/media/Placeholder/no_data.jpg";
    path[1][0][0] = "content/media/Placeholder/no_data.jpg";
    
    // Crossrail - Canary Wharf
    path[1][1][4] = "content/media/Crossrail/Location/CanaryWharf/Text/PlanningForAShipImpact.png";
    path[1][1][3] = "content/media/Crossrail/Location/CanaryWharf/Image/CanaryWharfStation.jpg";
    path[1][1][2] = "content/media/Crossrail/Location/CanaryWharf/Video/CrossrailTimeLapseVideoDrainingOfNorthDock.mov";
    path[1][1][1] = "content/media/Placeholder/no_data.jpg";
    path[1][1][0] = "content/media/Placeholder/no_data.jpg";
    
    // Crossrail - Liverpool
    path[1][2][4] = "content/media/Crossrail/Location/LiverpoolStreet/Text/ArcheologicalDiscoveries.png";
    path[1][2][3] = "content/media/Crossrail/Location/LiverpoolStreet/Image/RomanCopperAlloyAndSilverCoins.jpg";
    path[1][2][2] = "content/media/Crossrail/Location/LiverpoolStreet/Video/CrossrailArchaeologyLiverpoolStreet.mp4";
    path[1][2][1] = "content/media/Placeholder/no_data.jpg";
    path[1][2][0] = "content/media/Placeholder/no_data.jpg";
    
    // Crossrail - Barbican
    path[1][3][4] = "content/media/Crossrail/Location/Barbican/Text/FloatingTracks.png";
    path[1][3][3] = "content/media/Crossrail/Location/Barbican/Image/Gantry3dModel.jpg";
    path[1][3][2] = "content/media/Crossrail/Location/Barbican/Video/CrossrailRailwaySystems.mp4";
    path[1][3][1] = "content/media/Placeholder/no_data.jpg";
    path[1][3][0] = "content/media/Placeholder/no_data.jpg";
    
    // Crossrail - Tottenham Court Road
    path[1][4][4] = "content/media/Crossrail/Location/TottenhamCourtRoad/Text/TheEyeOfTheNeedle.png";
    path[1][4][3] = "content/media/Crossrail/Location/TottenhamCourtRoad/Image/TottenhamCourtRoadStationArchitectsImpression01.jpg";
    path[1][4][2] = "content/media/Crossrail/Location/TottenhamCourtRoad/Video/BreakthroughCrossrailsTunnellingStory.mp4";
    path[1][4][1] = "content/media/Placeholder/no_data.jpg";
    path[1][4][0] = "content/media/Placeholder/no_data.jpg";
    
    // pre-load all videos
    vid[0][0].load(path[0][0][2]);
    vid[0][1].load(path[0][1][2]);
    vid[0][2].load(path[0][2][2]);
    vid[0][3].load(path[0][3][2]);
    vid[0][4].load(path[0][4][2]);
    vid[1][0].load(path[1][0][2]);
    vid[1][1].load(path[1][1][2]);
    vid[1][2].load(path[1][2][2]);
    vid[1][3].load(path[1][3][2]);
    vid[1][4].load(path[1][4][2]);
}

//--------------------------------------------------------------
void Content::update()
{
    // update any running videos
    for (int i = 0; i < 5; i++)
    {
        if (vid[0][i].isPlaying()) vid[0][i].update();
        if (vid[1][i].isPlaying()) vid[1][i].update();
    }
    
    // content scaling
    scaling();
}

//--------------------------------------------------------------
void Content::scaling()
{
    float dest = 0.001;
    float lerpOut = 0.1;
    float lerpIn = 0.4;
    
    switch (item) {
        case 0:
            if (scale[1] <= dest && scale[2] <= dest && scale[3] <= dest && scale[4] <= dest)
            {
                scale[0] = ofLerp(scale[0], 1.0, lerpOut);
                
                // stop any videos running
                stop();
            }
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            break;
            
        case 1:
            if (scale[0] <= dest && scale[2] <= dest && scale[3] <= dest && scale[4] <= dest)
            {
                scale[1] = ofLerp(scale[1], 1.0, lerpOut);
                
                // stop any videos running
                stop();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            break;
            
        case 2:
            if (scale[0] <= dest && scale[1] <= dest && scale[3] <= dest && scale[4] <= dest)
            {
                scale[2] = ofLerp(scale[2], 1.0, lerpOut);
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            break;
            
        case 3:
            if (scale[0] <= dest && scale[1] <= dest && scale[2] <= dest && scale[4] <= dest)
            {
                scale[3] = ofLerp(scale[3], 1.0, lerpOut);
                
                // stop any videos running
                stop();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            break;
            
        case 4:
            if (scale[0] <= dest && scale[1] <= dest && scale[2] <= dest && scale[3] <= dest)
            {
                scale[4] = ofLerp(scale[4], 1.0, lerpOut);
                
                // stop any videos running
                stop();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            break;
            
        case 5:
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            
            if (scale[2] <= dest)
                stop();
            break;
    }
}

//--------------------------------------------------------------
void Content::draw()
{
    float screenWidth = 1080;
    float percentage = 0.75;
    float alpha = 75;
    int sOffset = 6;
    
    // draws text content (text is currently an image)
    ofSetRectMode(OF_RECTMODE_CENTER);
    if (img[0].isAllocated())
    {
        // gets the difference between screen width and adjusts
        float diff = screenWidth / img[0].getWidth();
        float w = (img[0].getWidth() * diff) * percentage;
        float h = (img[0].getHeight() * diff) * percentage;
        
        // content shadow
        ofSetColor(0, alpha);
        ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[0], h * scale[0]);
        
        // content item
        ofSetColor(255);
        img[0].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[0], h * scale[0]);
    }
    
    // draws image content
    if (img[1].isAllocated())
    {
        // gets the difference between screen width and adjusts
        float diff = screenWidth / img[1].getWidth();
        float w = (img[1].getWidth() * diff) * percentage;
        float h = (img[1].getHeight() * diff) * percentage;
        
        // content shadow
        ofSetColor(0, alpha);
        ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[1], h * scale[1]);
        
        // content item
        ofSetColor(255);
        img[1].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[1], h * scale[1]);
    }
    
    // draws video content
    for (int i = 0; i < 5; i++)
    {
        // hs1 project video content
        if (vid[0][i].isPlaying())
        {
            // gets the difference between screen width and adjusts
            float diff = screenWidth / vid[0][i].getWidth();
            float w = (vid[0][i].getWidth() * diff) * percentage;
            float h = (vid[0][i].getHeight() * diff) * percentage;
            
            // content shadow
            ofSetColor(0, alpha);
            ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[2], h * scale[2]);
            
            // content item
            ofSetColor(255);
            vid[0][i].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[2], h * scale[2]);
        }
        
        // crossrail project video content
        if (vid[1][i].isPlaying())
        {
            // gets the difference between screen width and adjusts
            float diff = screenWidth / vid[1][i].getWidth();
            float w = (vid[1][i].getWidth() * diff) * percentage;
            float h = (vid[1][i].getHeight() * diff) * percentage;
            
            // content shadow
            ofSetColor(0, alpha);
            ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[2], h * scale[2]);
            
            // content item
            ofSetColor(255);
            vid[1][i].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[2], h * scale[2]);
        }
    }
    
    // image 3 is placeholder for model content
    if (img[3].isAllocated())
    {
        // gets the difference between screen width and adjusts
        float diff = screenWidth / img[3].getWidth();
        float w = (img[3].getWidth() * diff) * percentage;
        float h = (img[3].getHeight() * diff) * percentage;
        
        // content shadow
        ofSetColor(0, alpha);
        ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[3], h * scale[3]);
        
        // content item
        ofSetColor(255);
        img[3].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[3], h * scale[3]);
    }
    
    // image 4 is placeholder for audio content
    if (img[4].isAllocated())
    {
        // gets the difference between screen width and adjusts
        float diff = screenWidth / img[4].getWidth();
        float w = (img[4].getWidth() * diff) * percentage;
        float h = (img[4].getHeight() * diff) * percentage;
        
        // content shadow
        ofSetColor(0, alpha);
        ofDrawRectangle(ofGetWidth()/2 + sOffset, ofGetHeight()/2 + sOffset, w * scale[4], h * scale[4]);
        
        // content item
        ofSetColor(255);
        img[4].draw(ofGetWidth()/2, ofGetHeight()/2, w * scale[4], h * scale[4]);
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
}

//--------------------------------------------------------------
void Content::load(int _project, int _point, int _item)
{
    project = _project;
    point = _point;
    item = _item;
    
    if (item != 2)
    {
        // loads specific image
        img[item].load(path[project][point][item]);
    }
    else
    {
        // videos are pre-loaded, play video selection
        if (!vid[project][point].isPlaying()) vid[project][point].play();
    }
}

//--------------------------------------------------------------
void Content::stop()
{
    // stop all project running videos
    for (int i = 0; i < 5; i++)
    {
        if (vid[0][i].isPlaying()) vid[0][i].stop();
        if (vid[1][i].isPlaying()) vid[1][i].stop();
    }
}