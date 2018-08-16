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
void Content::setCons(vector<InteractiveObject*> cons) {
    for(auto location = hs1Displayers.begin(); location != hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setCons(cons);
        }
    }
    for(auto location = crossrailDisplayers.begin(); location != crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->setCons(cons);
        }
    }
}

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
    
    //Setup fonts (must be called before fileLocation() method
    titleFont.setup("fonts/Plain-Bold.ttf", 1.0, 1024, true, 8, 2.0);
    textFont.setup("fonts/Plain-Regular.ttf", 1.5, 1024, true, 8, 2.0);
    sourceFont.setup("fonts/Plain-Light.ttf", 1.0, 1024, true, 8, 2.0);
    
    // setup file paths
    fileLocation();
    
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
    
    //load background Images
    backgroundImage169.load("content/shared/backgroundTile169.png");
    
    backgroundImageAudio.load("content/shared/backgroundTileAudio.png");
    
    backgroundImage65.load("content/shared/backgroundTile65.png");
    
    backgroundImage43.load("content/shared/backgroundTile43.png");
    
    spinMeImage.load("content/shared/360Icon.png");
    
    playhead.setAlpha(255.0);
    
    item = 5;
    
    maxScale = 1.0;
}

//--------------------------------------------------------------
void Content::fileLocation() {
    //Initialize hs1 content
    hs1Displayers["StPancras"] = vector<ContentDisplayer*>();
    hs1Displayers["StratfordInternational"] = vector<ContentDisplayer*>();
    hs1Displayers["EbbsfleetInternational"] = vector<ContentDisplayer*>();
    hs1Displayers["MedwayViaduct"] = vector<ContentDisplayer*>();
    hs1Displayers["AshfordInternational"] = vector<ContentDisplayer*>();
    
    //initialize crossrail content
    crossrailDisplayers["Soho"] = vector<ContentDisplayer*>();
    crossrailDisplayers["TottenhamCourtRoad"] = vector<ContentDisplayer*>();
    crossrailDisplayers["Barbican"] = vector<ContentDisplayer*>();
    crossrailDisplayers["LiverpoolStreet"] = vector<ContentDisplayer*>();
    crossrailDisplayers["CanaryWharf"] = vector<ContentDisplayer*>();
    
    //Load HS1 Content w/ new displayers
    int locationNameIndex = 7;
    int storyIndex = 8; // This is the file with all the info about each content piece
    int contentComponentIndex = 9; // This is where the component is, ie backgorund, notes, title or content
    int contentFileIndex = 10; // This is the actual content file
    auto currentProjectDisplayers = &hs1Displayers;
    
    //Pre-load POI audio with placeholders
    for(int i = 0; i < 5; i++) {
        introSoundPaths[0][i] = "content/Google Drive/Arup/Research/Content/Placeholder/no_audio.wav";
        introSoundPaths[1][i] = "content/Google Drive/Arup/Research/Content/Placeholder/no_audio.wav";
    }
    
    ofxNestedFileLoader loader;
    vector<string> currentPaths = loader.load("content/Google Drive/Arup/Research/Content/HS1/Location");
    for(int i = 0; i < currentPaths.size(); i++) {
        vector<string> splitString = ofSplitString(currentPaths[i], "/");
        if(splitString[splitString.size()-1] == "Icon\r") {
            // Ignore all icon files
        } else if(splitString[storyIndex] == "IntroAudio" || splitString[storyIndex] == "MenuButton" || splitString[contentComponentIndex] == "Notes") {
            //Ignore our notes and folders that should be loaded elsewhere
            if(splitString[storyIndex] == "IntroAudio") {
                string locationName = splitString[locationNameIndex];
                int locationIndex = locationsDictionary[0].at(locationName);
                introSoundPaths[0][locationIndex] = currentPaths[i];
            }
        } else {
            string contentPath = splitString[contentFileIndex];
            string locationName = splitString[locationNameIndex];
            vector<string> contentPathSplit = ofSplitString(contentPath, ".");
            string fileType = contentPathSplit[1];
            if(splitString[contentComponentIndex] == "Content") {
                if(fileType == "png" || fileType == "jpg") {
                    //We've got an image!
                    ImageDisplayer* displayer = new ImageDisplayer();
                    displayer->setImage(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImage169);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "wav") {
                    //We've got an audio file!
                    AudioDisplayer* displayer = new AudioDisplayer();
                    displayer->setAudio(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImageAudio);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "mp4" || fileType == "mov") {
                    //We've got a video!
                    VideoDisplayer* displayer = new VideoDisplayer();
                    displayer->setVideo(currentPaths[i]);
                    if(displayer->getVideo()->getHeight() == 742) {
                        displayer->setBackgroundImage(&backgroundImage65);
                    } else if(displayer->getVideo()->getHeight() == 726) {
                        displayer->setBackgroundImage(&backgroundImage43);
                    } else {
                        displayer->setBackgroundImage(&backgroundImage169);
                    }
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);

                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "fbx") {
                    //We've got a model!
                    ModelDisplayer* displayer = new ModelDisplayer();
                    displayer->setScene(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImage169);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setCamera(&cam);
                    displayer->setLight(&light);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    displayer->setTextImage(&spinMeImage);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else {
                    //SOME USELESS FILE, IGNORE IT!
                }
            } else if(splitString[contentComponentIndex] == "Title") {
                ofxXmlSettings displayableText;
                displayableText.load(currentPaths[i]);
                string titleText = displayableText.getValue("Title", "Title");
                string infoText = displayableText.getValue("Text", "Info Text");
                string sourceText = displayableText.getValue("Source", "Source");
                float cutoffPercent = displayableText.getValue("Cutoff", 0.5);

//                ofImage* image = new ofImage();
//                image->load(currentPaths[i]);
                if((*currentProjectDisplayers)[locationName].size() > 0) {
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setTitle(titleText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setText(infoText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setSource("Source: " + sourceText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setTextCutoffPercent(cutoffPercent);
                }
            }
        }
    }

    currentProjectDisplayers = &crossrailDisplayers;
    currentPaths.clear();
    loader.clearPaths();

    //load Crossrail content w/ new displayers
    currentPaths = loader.load("content/Google Drive/Arup/Research/Content/Crossrail/Location");
    for(int i = 0; i < currentPaths.size(); i++) {
        vector<string> splitString = ofSplitString(currentPaths[i], "/");
        if(splitString[splitString.size()-1] == "Icon\r") {
            // Ignore all icon files
        } else if(splitString[storyIndex] == "IntroAudio" || splitString[storyIndex] == "MenuButton" || splitString[contentComponentIndex] == "Notes") {
            //Ignore our notes and folders that should be loaded elsewhere
            if(splitString[storyIndex] == "IntroAudio") {
                string locationName = splitString[locationNameIndex];
                int locationIndex = locationsDictionary[1].at(locationName);
                introSoundPaths[1][locationIndex] = currentPaths[i];
            }
        } else {
            string contentPath = splitString[contentFileIndex];
            string locationName = splitString[locationNameIndex];
            vector<string> contentPathSplit = ofSplitString(contentPath, ".");
            string fileType = contentPathSplit[1];
            if(splitString[contentComponentIndex] == "Content") {
                if(fileType == "png" || fileType == "jpg") {
                    //We've got an image!
                    ImageDisplayer* displayer = new ImageDisplayer();
                    displayer->setImage(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImage169);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "wav") {
                    //We've got an audio file!
                    AudioDisplayer* displayer = new AudioDisplayer();
                    displayer->setAudio(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImageAudio);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "mp4" || fileType == "mov") {
                    //We've got a video!
                    VideoDisplayer* displayer = new VideoDisplayer();
                    displayer->setVideo(currentPaths[i]);
                    if(displayer->getVideo()->getHeight() == 742) {
                        displayer->setBackgroundImage(&backgroundImage65);
                    } else if(displayer->getVideo()->getHeight() == 726) {
                        displayer->setBackgroundImage(&backgroundImage43);
                    } else {
                        displayer->setBackgroundImage(&backgroundImage169);
                    }
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else if(fileType == "fbx") {
                    //We've got a model!
                    ModelDisplayer* displayer = new ModelDisplayer();
                    displayer->setScene(currentPaths[i]);
                    displayer->setBackgroundImage(&backgroundImage169);
                    displayer->setContentLocation(currentPaths[i]);
                    displayer->setPlayhead(&playhead);
                    displayer->setCamera(&cam);
                    displayer->setLight(&light);
                    displayer->setTitleFont(&titleFont);
                    displayer->setTextFont(&textFont);
                    displayer->setSourceFont(&sourceFont);
                    displayer->setTextImage(&spinMeImage);
                    (*currentProjectDisplayers)[locationName].push_back(displayer);
                } else {
                    //SOMETHING'S GONE WRONG!
                }
            } else if(splitString[contentComponentIndex] == "Title") {
                ofxXmlSettings displayableText;
                displayableText.load(currentPaths[i]);
                string titleText = displayableText.getValue("Title", "Title");
                string infoText = displayableText.getValue("Text", "Info Text");
                string sourceText = displayableText.getValue("Source", "Source");
                float cutoffPercent = displayableText.getValue("Cutoff", 0.5);

                //                ofImage* image = new ofImage();
                //                image->load(currentPaths[i]);
                if((*currentProjectDisplayers)[locationName].size() > 0) {
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setTitle(titleText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setText(infoText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setSource("Source: " + sourceText);
                    (*currentProjectDisplayers)[locationName][(*currentProjectDisplayers)[locationName].size()-1]->setTextCutoffPercent(cutoffPercent);
                }
            }
        }
    }

    //pre-load all POI intro sounds
    bool loaded = introSounds[0][0].load(introSoundPaths[0][0]);
    introSounds[0][1].load(introSoundPaths[0][1]);
    introSounds[0][2].load(introSoundPaths[0][2]);
    introSounds[0][3].load(introSoundPaths[0][3]);
    introSounds[0][4].load(introSoundPaths[0][4]);
    introSounds[1][0].load(introSoundPaths[1][0]);
    introSounds[1][1].load(introSoundPaths[1][1]);
    introSounds[1][2].load(introSoundPaths[1][2]);
    introSounds[1][3].load(introSoundPaths[1][3]);
    introSounds[1][4].load(introSoundPaths[1][4]);
}

//--------------------------------------------------------------
void Content::update() {
    //update hs1 content
    for(auto location = hs1Displayers.begin(); location != hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->update();
        }
    }
    //update crossrail content
    for(auto location = crossrailDisplayers.begin(); location != crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            (*content)->update();
        }
    }
}

//--------------------------------------------------------------
void Content::draw() {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    float x = ofGetWidth()/2;
    float y = ofGetHeight()/2;
    //draw Inactive hs1 content
    for(auto location = hs1Displayers.begin(); location != hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            if(!(*content)->getIsActive()) (*content)->draw(x, y);
        }
    }
    //draw Inactive crossrail content
    for(auto location = crossrailDisplayers.begin(); location != crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            if(!(*content)->getIsActive()) (*content)->draw(x, y);
        }
    }
    //draw Active hs1 content
    for(auto location = hs1Displayers.begin(); location != hs1Displayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            if((*content)->getIsActive()) (*content)->draw(x, y);
        }
    }
    //draw Active crossrail content
    for(auto location = crossrailDisplayers.begin(); location != crossrailDisplayers.end(); location++) {
        for(auto content = location->second.begin(); content != location->second.end(); content++) {
            if((*content)->getIsActive()) (*content)->draw(x, y);
        }
    }
    ofSetRectMode(OF_RECTMODE_CORNER);
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
    for(int j = 0; j < 5; j++) {
        if(scale[j] >= maxScale - 0.01) {
            titleAndCaptionAlpha[j] = ofLerp(titleAndCaptionAlpha[j], 255, lerpIn);
            for(int i = 0; i < 5; i++) {
                if(i != j) {
                    titleAndCaptionAlpha[i] = ofLerp(titleAndCaptionAlpha[i], 0.0, 1.0);
                }
            }
        }
    }
}

//--------------------------------------------------------------
void Content::load(int _project, int _point, int _item)
{
    project = _project;
    point = _point;
    item = _item;
    
    stopAudio();
    
    if (project == 0) {
        
        if (item == 0)
        {
            // loads specific image
            //img[item].load(path[project][point][item][0]);
        }
        else if (item == 1)
        {
            // loads specific image
            //img[item].load(path[project][point][item][0]);
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
            string filename = "";// path[project][point][item][0];
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
            string filename = "";//path[project][point][item][0];
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
            //img[item].load(path[project][point][item][0]);
        }
        else if (item == 4)
        {
            // loads specific image
            //img[item].load(path[project][point][item][0]);
        }
    }
    
    //load title and caption text
    //titleTextImage[item].load(path[project][point][item][1]);
    //captionTextImage[item].load(path[project][point][item][2]);
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

//--------------------------------------------------------------
void Content::stopAudio() {
    // stop all project running sounds
    for (int i = 0; i < 5; i++)
    {
        if (sound[0][i].isPlaying()) sound[0][i].stop();
        if (sound[1][i].isPlaying()) sound[1][i].stop();
    }
}

//--------------------------------------------------------------
void Content::stopLocationAudio() {
    //stop all Location Intro Audio
    for(int i = 0; i < 5; i++) {
        if (introSounds[0][i].isPlaying()) introSounds[0][i].stop();
        if (introSounds[1][i].isPlaying()) introSounds[1][i].stop();
    }
}
