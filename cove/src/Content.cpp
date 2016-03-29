//
//  Content.cpp
//  Cove
//
//  Created by Jason Walters on 10/03/2016.
//  Last edited by Jason Walters on 23/03/2016.
//
//

#include "Content.h"
#include "Globals.h"

//Initialize the dictionary of locations, content types and indices
const vector<map<string, int>> Content::locationsDictionary = createMaps();


//--------------------------------------------------------------
void Content::setup()
{
    // model camera view distance
    cam.lookAt(ofVec3f(0,0,0));
    cam.setFarClip(5000);
    cam.setNearClip(.5f);
    camMaxZoom = 6000;
    camMinZoom = 250;
    camZoom = camMaxZoom;
    
    // setup file paths
    fileLocation();
    
    // setup FBX scene
    ofxFBXSceneSettings settings;
    string filename =  "content/Dropbox/ArupContentForInstallation/Placeholder/no_model.fbx";//path[0][0][3][0];
    if( scene.load(filename, settings) ) {
        cout << "ofApp :: loaded the scene OK" << endl;
    } else {
        cout << "ofApp :: Error loading the scene" << endl;
    }
    model.setup( &scene );
    
    //past color
    ofColor col;
    col.setHex(0x4EB9E5/*0x0D0D0B*/);
    playhead.setPastColor(col);
    
    //future color
    col.setHex(0x95CEE2/*0x8FC3E8*/);
    playhead.setFutureColor(col);
    
    //bar color
    col.setHex(0xFFFFFF);
    playhead.setBarColor(col);
    
    
    playhead.setAlpha(255.0);
    
    item = 5;
    
    maxScale = 1.0;
}

//--------------------------------------------------------------
void Content::fileLocation()
{
    int projectIndex = 0;

    //Load all the placeholder content, we'll overwrite it later
    //Load placeholder for HS1
    for(int i = 0; i < 5; i++) {
        path[projectIndex][i][0][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_data.jpg";
        path[projectIndex][i][1][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_data.jpg";
        path[projectIndex][i][2][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_video.mp4";
        path[projectIndex][i][3][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_model.fbx";
        path[projectIndex][i][4][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_audio.wav";
        for(int j = 0; j < 5; j++) {
            path[projectIndex][i][j][1] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_title.png";
            path[projectIndex][i][j][2] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_caption.png";
        }
    }
    
    //Load all real the content for HS1
    //Note: this will have the side-effect of loading the last file if there are multiple files in a folder
    ofxNestedFileLoader loader;
    vector<string> HS1 = loader.load("content/Dropbox/ArupContentForInstallation/HS1/Location");
    
    int locationNameIndex = 5;
    int contentTypeIndex = 6;
    int contentPieceIndex = 7;
    for(int i = 0; i < HS1.size(); i++) {
        vector<string> splitString = ofSplitString(HS1[i], "/");
        string locationName = splitString[locationNameIndex];
        string contentType = splitString[contentTypeIndex];
        string contentPieceName = splitString[contentPieceIndex];
        if(contentPieceName != "Notes") {
            int locationIndex = locationsDictionary[projectIndex].at(locationName);
            int contentIndex = locationsDictionary[projectIndex].at(contentType);
            int contentPieceIndex = locationsDictionary[projectIndex].at(contentPieceName);
            path[projectIndex][locationIndex][contentIndex][contentPieceIndex] = HS1[i];
        }
    }
    
    //clear the loader
    loader.clearPaths();
    
    projectIndex = 1;
    
    //Load placeholders for Crossrail
    for(int i = 0; i < 5; i++) {
        path[projectIndex][i][4][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_data.jpg";
        path[projectIndex][i][3][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_data.jpg";
        path[projectIndex][i][2][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_video.mp4";
        path[projectIndex][i][1][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_model.fbx";
        path[projectIndex][i][0][0] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_audio.wav";
        for(int j = 0; j < 5; j++) {
            path[projectIndex][i][j][1] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_title.png";
            path[projectIndex][i][j][2] = "content/Dropbox/ArupContentForInstallation/Placeholder/no_caption.png";
        }
    }
    
    //Load all the content for Crossrail
        //Note: this will have the side-effect of loading the last file if there are multiple files in a folder
    vector<string> Crossrail = loader.load("content/Dropbox/ArupContentForInstallation/Crossrail/Location");
    
    for(int i = 0; i < Crossrail.size(); i++) {
        vector<string> splitString = ofSplitString(Crossrail[i], "/");
        string locationName = splitString[locationNameIndex];
        string contentType = splitString[contentTypeIndex];
        string contentPieceName = splitString[contentPieceIndex];
        if(contentPieceName != "Notes") {
            int locationIndex = locationsDictionary[projectIndex].at(locationName);
            int contentIndex = locationsDictionary[projectIndex].at(contentType);
            int contentPieceIndex = locationsDictionary[projectIndex].at(contentPieceName);
            path[projectIndex][locationIndex][contentIndex][contentPieceIndex] = Crossrail[i];
        }
    }
    
    // pre-load all videos
    vid[0][0].load(path[0][0][2][0]);
    vid[0][1].load(path[0][1][2][0]);
    vid[0][2].load(path[0][2][2][0]);
    vid[0][3].load(path[0][3][2][0]);
    vid[0][4].load(path[0][4][2][0]);
    vid[1][0].load(path[1][0][2][0]);
    vid[1][1].load(path[1][1][2][0]);
    vid[1][2].load(path[1][2][2][0]);
    vid[1][3].load(path[1][3][2][0]);
    vid[1][4].load(path[1][4][2][0]);
    
    // pre-load all sound files
    sound[0][0].load(path[0][0][4][0]);
    sound[0][1].load(path[0][1][4][0]);
    sound[0][2].load(path[0][2][4][0]);
    sound[0][3].load(path[0][3][4][0]);
    sound[0][4].load(path[0][4][4][0]);
    sound[1][0].load(path[1][0][0][0]);
    sound[1][1].load(path[1][1][0][0]);
    sound[1][2].load(path[1][2][0][0]);
    sound[1][3].load(path[1][3][0][0]);
    sound[1][4].load(path[1][4][0][0]);
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 4; j++) {
            sound[i][j].setVolume(1.0);
            sound[i][j].setLoop(true);
        }
    }
    
    backgroundImage.load("content/shared/backgroundTile.png");
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
    
    // fbx model updates
    if (project == 0 && item == 3)
    {
        // update model
        model.update();
        
        // perform any bone manipulation here
        model.lateUpdate();
    }
    else if (project == 1 && item == 1)
    {
        // update model
        model.update();
        
        // perform any bone manipulation here
        model.lateUpdate();
    }
    
    // update light position
    light.setPosition(cam.getPosition());
    light.setOrientation(cam.getOrientationEuler());
    
    // camera reset x axis
    float val = ofLerp(0, cam.getLookAtDir().y, 0.2);
    // cam.setOrientation(ofVec3f(val, cam.getOrientationEuler().y, cam.getOrientationEuler().z));
    
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
                scale[0] = ofLerp(scale[0], maxScale, lerpOut);
                
                // stop any videos running
                stopVideos();
//                stopAudio();
            }
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            camZoom = ofLerp(camZoom, camMaxZoom, lerpIn);
            break;
            
        case 1:
            if (scale[0] <= dest && scale[2] <= dest && scale[3] <= dest && scale[4] <= dest)
            {
                scale[1] = ofLerp(scale[1], maxScale, lerpOut);
                
                if (project == 1) camZoom = ofLerp(camZoom, camMinZoom, lerpOut);
                
                // stop any videos running
                stopVideos();
                stopAudio();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            if (project == 0)  camZoom = ofLerp(camZoom, camMaxZoom, lerpIn);
            break;
            
        case 2:
            if (scale[0] <= dest && scale[1] <= dest && scale[3] <= dest && scale[4] <= dest)
            {
                scale[2] = ofLerp(scale[2], maxScale, lerpOut);
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            camZoom = ofLerp(camZoom, 20000, lerpIn);
            break;
            
        case 3:
            if (scale[0] <= dest && scale[1] <= dest && scale[2] <= dest && scale[4] <= dest)
            {
                scale[3] = ofLerp(scale[3], maxScale, lerpOut);
                
                if (project == 0) camZoom = ofLerp(camZoom, camMinZoom, lerpOut);
                
                // stop any videos running
                stopVideos();
                stopAudio();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            
            if (project == 1) camZoom = ofLerp(camZoom, camMaxZoom, lerpIn);
            break;
            
        case 4:
            if (scale[0] <= dest && scale[1] <= dest && scale[2] <= dest && scale[3] <= dest)
            {
                scale[4] = ofLerp(scale[4], maxScale, lerpOut);
                
                // stop any videos running
                stopVideos();
            }
            
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            camZoom = ofLerp(camZoom, camMaxZoom, lerpIn);
            break;
            
        case 5:
            scale[0] = ofLerp(scale[0], 0.0, lerpIn);
            scale[1] = ofLerp(scale[1], 0.0, lerpIn);
            scale[2] = ofLerp(scale[2], 0.0, lerpIn);
            scale[3] = ofLerp(scale[3], 0.0, lerpIn);
            scale[4] = ofLerp(scale[4], 0.0, lerpIn);
            camZoom = ofLerp(camZoom, camMaxZoom, lerpIn);
            
            if (scale[2] <= dest) {
                stopVideos();
                stopAudio();
            }
            break;
    }
    //Scale the Title and caption alpha
    if(scale[0] >= maxScale - 0.01) {
        titleAndCaptionAlpha[0] = ofLerp(titleAndCaptionAlpha[0], 255, lerpIn);
        for(int i = 0; i < 5; i++) {
            if(i != 0) {
                titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
            }
        }
    } else if(scale[1] >= maxScale - 0.01) {
        titleAndCaptionAlpha[1] = ofLerp(titleAndCaptionAlpha[1], 255, lerpIn);
        for(int i = 0; i < 5; i++) {
            if(i != 1) {
                titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
            }
        }
    }else if(scale[2] >= maxScale - 0.01) {
        titleAndCaptionAlpha[2] = ofLerp(titleAndCaptionAlpha[2], 255, lerpIn);
        for(int i = 0; i < 5; i++) {
            if(i != 2) {
                titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
            }
        }
    }else if(scale[3] >= maxScale - 0.01) {
        titleAndCaptionAlpha[3] = ofLerp(titleAndCaptionAlpha[3], 255, lerpIn);
        for(int i = 0; i < 5; i++) {
            if(i != 3) {
                titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
            }
        }
    }else if(scale[4] >= maxScale - 0.01) {
        titleAndCaptionAlpha[4] = ofLerp(titleAndCaptionAlpha[4], 255, lerpIn);
        for(int i = 0; i < 5; i++) {
            if(i != 4) {
                titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
            }
        }
    } else {
        for(int i = 0; i < 5; i++) {
            titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
        }
    }
}

//--------------------------------------------------------------
void Content::draw()
{
    if (Globals::programType) screenWidth = 1080;
    else screenWidth = 1600;
    
    float percentage = 0.75;
    float backgroundPercentage = 0.9;
    float alpha = 224.4;
    float camPam = 0.5;
    float titleBufferTop = 10;
    float captionBufferTop = 10;
    int sOffset = 6;
    
    //get the difference between screen width and draw the background pane
    float backgroundDiff = screenWidth / backgroundImage.getWidth();
    float backgroundWidth = (backgroundImage.getWidth() * backgroundDiff) * backgroundPercentage;
    float backgroundHeight = (backgroundImage.getHeight() * backgroundDiff) * backgroundPercentage;
    
    ofPushStyle();
    ofSetRectMode(OF_RECTMODE_CENTER);
//    for(int i = 0; i < 5; i++) {
//
//    }
    ofPopStyle();
    
    if (project == 0) {
        // draws text content (text is currently an image)
        ofSetRectMode(OF_RECTMODE_CENTER);
        if (img[0].isAllocated())
        {
            ofSetColor(255);
            captionTextImage[0].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[0].getWidth() * scale[0], captionTextImage[0].getHeight() * scale[0]);
            img[0].draw(ofGetWidth()/2, ofGetHeight()/2, img[0].getWidth() * scale[0], img[0].getHeight() * scale[0]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[0]);
            titleTextImage[0].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[0].getWidth() * scale[0], titleTextImage[0].getHeight() * scale[0]);
        }
        
        // draws image contentw
        if (img[1].isAllocated())
        {
            ofSetColor(255);
            captionTextImage[1].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[1].getWidth() * scale[1], captionTextImage[1].getHeight() * scale[1]);
            img[1].draw(ofGetWidth()/2, ofGetHeight()/2, img[1].getWidth() * scale[1], img[1].getHeight() * scale[1]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[1]);
            titleTextImage[1].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[1].getWidth() * scale[1], titleTextImage[1].getHeight() * scale[1]);

        }
    
        // draws video content
            for (int i = 0; i < 5; i++)
            {
                // hs1 project video content
                if (vid[0][i].isPlaying())
                {
                    ofSetColor(255);
                    captionTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[2].getWidth() * scale[2], captionTextImage[2].getHeight() * scale[2]);
                    vid[0][i].draw(ofGetWidth()/2, ofGetHeight()/2, vid[0][i].getWidth() * scale[2], vid[0][i].getHeight() * scale[2]);
                    ofSetColor(255, 255, 255, titleAndCaptionAlpha[2]);
                    titleTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[2].getWidth() * scale[2], titleTextImage[2].getHeight() * scale[2]);
                    float percentDone = vid[0][i].getPosition();
                    playhead.draw(ofGetWidth()/2, ofGetHeight()/2 + vid[0][i].getHeight()/2 + 5, vid[0][i].getWidth() * scale[2], 10 * scale[2], percentDone);
                    
                }
                
                // crossrail project video content
                if (vid[1][i].isPlaying())
                {
                    ofSetColor(255);
                    captionTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[2].getWidth() * scale[2], captionTextImage[2].getHeight() * scale[2]);
                    vid[1][i].draw(ofGetWidth()/2, ofGetHeight()/2, vid[1][i].getWidth() * scale[2], vid[1][i].getHeight() * scale[2]);
                    ofSetColor(255, 255, 255, titleAndCaptionAlpha[2]);
                    titleTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[2].getWidth() * scale[2], titleTextImage[2].getHeight() * scale[2]);
                    float percentDone = vid[1][i].getPosition();
                    playhead.draw(ofGetWidth()/2, ofGetHeight()/2 + vid[1][i].getHeight()/2 + 5, vid[1][i].getWidth() * scale[2], 10 * scale[2], percentDone);
                }
            }
        
            ofPushStyle();
            ofSetColor(255);
            captionTextImage[3].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[3].getWidth() * scale[3], captionTextImage[3].getHeight() * scale[3]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[3]);
            titleTextImage[3].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[3].getWidth() * scale[3], titleTextImage[3].getHeight() * scale[3]);
            ofPopStyle();
        
            // model drawing
            // rotate on y axis
            cam.pan(camPam);
            cam.setDistance(camZoom);
            ofEnableDepthTest();
            //Draw the backgroundTile
            cam.begin();
            ofEnableLighting();
            light.enable();
            ofSetColor(255, 255, 255);
            model.draw();
            light.disable();
            ofDisableLighting();
            cam.end();
            ofDisableDepthTest();
    
        //Plays audio content with play-head
        for(int i = 0; i < 5; i++) {
            if(sound[0][i].isPlaying()) {
                ofSetColor(255);
                captionTextImage[4].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[4].getWidth() * scale[4], captionTextImage[4].getHeight() * scale[4]);
                ofSetColor(255, 255, 255, titleAndCaptionAlpha[4]);
                titleTextImage[4].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[4].getWidth() * scale[4], titleTextImage[4].getHeight() * scale[4]);
                //draw the playhead
                float percentageDone = sound[0][i].getPosition();
                playhead.draw(ofGetWidth()/2, ofGetHeight()/2 - 19, 909 * scale[4], 30 * scale[4], percentageDone);
            }
        }
        ofSetRectMode(OF_RECTMODE_CORNER);
    } else {
        // draws text content (text is currently an image)
        ofSetRectMode(OF_RECTMODE_CENTER);
        if (img[4].isAllocated())
        {
            ofSetColor(255);
            captionTextImage[4].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[4].getWidth() * scale[4], captionTextImage[4].getHeight() * scale[4]);
            img[4].draw(ofGetWidth()/2, ofGetHeight()/2, img[4].getWidth() * scale[4], img[4].getHeight() * scale[4]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[4]);
            titleTextImage[4].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[4].getWidth() * scale[4], titleTextImage[4].getHeight() * scale[4]);
        }
        
        // draws image content
        if (img[3].isAllocated())
        {
            ofSetColor(255);
            captionTextImage[3].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[3].getWidth() * scale[3], captionTextImage[3].getHeight() * scale[3]);
            img[3].draw(ofGetWidth()/2, ofGetHeight()/2, img[3].getWidth() * scale[3], img[3].getHeight() * scale[3]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[3]);
            titleTextImage[3].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[3].getWidth() * scale[3], titleTextImage[3].getHeight() * scale[3]);
        }
        
            // draws video content
            for (int i = 0; i < 5; i++)
            {
                // crossrail project video content
                if (vid[1][i].isPlaying())
                {
                    ofSetColor(255);
                    captionTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[2].getWidth() * scale[2], captionTextImage[2].getHeight() * scale[2]);
                    vid[1][i].draw(ofGetWidth()/2, ofGetHeight()/2, vid[1][i].getWidth() * scale[2], vid[1][i].getHeight() * scale[2]);
                    ofSetColor(255, 255, 255, titleAndCaptionAlpha[2]);
                    titleTextImage[2].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[2].getWidth() * scale[2], titleTextImage[2].getHeight() * scale[2]);
                    ofSetColor(255);
                    float percentDone = vid[1][i].getPosition();
                    playhead.draw(ofGetWidth()/2, ofGetHeight()/2 + vid[1][i].getHeight()/2 + 5, vid[1][i].getWidth() + scale[2], 10 * scale[2], percentDone);
                }
            }
        
            ofPushStyle();
            ofSetColor(255);
            captionTextImage[1].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[1].getWidth() * scale[1], captionTextImage[1].getHeight() * scale[1]);
            ofSetColor(255, 255, 255, titleAndCaptionAlpha[1]);
            titleTextImage[1].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[1].getWidth() * scale[1], titleTextImage[1].getHeight() * scale[1]);
            ofPopStyle();
        
            //Draw the backgroundTile
            ofSetColor(255);
            cam.pan(camPam);
            cam.setDistance(camZoom);
            ofEnableDepthTest();
            cam.begin();
            ofEnableLighting();
            light.enable();
            ofSetColor(255, 255, 255);
            model.draw();
            light.disable();
            ofDisableLighting();
            cam.end();
            ofDisableDepthTest();
        
        //Plays audio content with play-head
        for(int i = 0; i < 5; i++) {
            if(sound[1][i].isPlaying()) {
                ofSetColor(255);
                captionTextImage[0].draw(ofGetWidth()/2, ofGetHeight()/2, captionTextImage[0].getWidth() * scale[0], captionTextImage[0].getHeight() * scale[0]);
                ofSetColor(255, 255, 255, titleAndCaptionAlpha[0]);
                titleTextImage[0].draw(ofGetWidth()/2, ofGetHeight()/2, titleTextImage[0].getWidth() * scale[0], titleTextImage[0].getHeight() * scale[0]);
                //draw the playhead
                float percentageDone = sound[1][i].getPosition();
                playhead.draw(ofGetWidth()/2, ofGetHeight()/2 - 19, 909 * scale[0], 30 * scale[0], percentageDone);
            }
        }
        ofSetRectMode(OF_RECTMODE_CORNER);
    }
}

//--------------------------------------------------------------
void Content::load(int _project, int _point, int _item)
{
    project = _project;
    point = _point;
    item = _item;
    if(project == 1) {
        ofColor col;
        col.setHex(0x0D0D0B);
        playhead.setPastColor(col);
        
        col.setHex(0x8FC3E8);
        playhead.setFutureColor(col);
    } else {
        ofColor col;
        col.setHex(0x4EB9E5);
        playhead.setPastColor(col);
        
        col.setHex(0x95CEE2/*0x8FC3E8*/);
        playhead.setFutureColor(col);
    }

    
    stopAudio();
    
    if (project == 0) {
        
        if (item == 0)
        {
            // loads specific image
            img[item].load(path[project][point][item][0]);
        }
        else if (item == 1)
        {
            // loads specific image
            img[item].load(path[project][point][item][0]);
        }
        else if (item == 2)
        {
            // videos are pre-loaded, play video selection
            if (!vid[project][point].isPlaying()) vid[project][point].play();
        }
        else if (item == 3)
        {
            // setup FBX scene
            ofxFBXSceneSettings settings;
            scene.unloadModels();
            string filename = path[project][point][item][0];
            if( scene.load(filename, settings) ) {
                cout << "ofApp :: loaded the scene OK" << endl;
            } else {
                cout << "ofApp :: Error loading the scene" << endl;
            }
            model.setup( &scene );
        }
        else if (item == 4)
        {
            // loads specific image
            //img[item].load(path[project][point][item]);
            if(!sound[project][point].isPlaying()) {
                sound[project][point].play();
            }
            
        }
    }
    else {
        
        if (item == 0)
        {
            // loads specific image
            if(!sound[project][point].isPlaying()) {
                sound[project][point].play();
            }
        }
        else if (item == 1)
        {
            // setup FBX scene
            ofxFBXSceneSettings settings;
            scene.unloadModels();
            string filename = path[project][point][item][0];
            if( scene.load(filename, settings) ) {
                cout << "ofApp :: loaded the scene OK" << endl;
            } else {
                cout << "ofApp :: Error loading the scene" << endl;
            }
            model.setup( &scene );
        }
        else if (item == 2)
        {
            // videos are pre-loaded, play video selection
            if (!vid[project][point].isPlaying()) vid[project][point].play();
        }
        else if (item == 3)
        {
            // loads specific image
            img[item].load(path[project][point][item][0]);
        }
        else if (item == 4)
        {
            // loads specific image
            img[item].load(path[project][point][item][0]);
        }
    }
    
    //load title and caption text
    titleTextImage[item].load(path[project][point][item][1]);
    captionTextImage[item].load(path[project][point][item][2]);
}

//--------------------------------------------------------------
void Content::stopVideos()
{
    // stop all project running videos
    for (int i = 0; i < 5; i++)
    {
        if (vid[0][i].isPlaying()) vid[0][i].stop();
        if (vid[1][i].isPlaying()) vid[1][i].stop();
    }
}

void Content::stopAudio() {
    // stop all project running sounds
    for (int i = 0; i < 5; i++)
    {
        if (sound[0][i].isPlaying()) sound[0][i].stop();
        if (sound[1][i].isPlaying()) sound[1][i].stop();
    }
}