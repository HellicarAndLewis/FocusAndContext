# FocusAndContext
An series of interactions that place content in geographical space.

## Addons
- ofxDatGui: https://github.com/braitsch/ofxDatGui
- ofxFBX: https://github.com/NickHardeman/ofxFBX/tree/develop
- ofxGlmTools: https://github.com/patriciogonzalezvivo/ofxGlmTools
- ofxGui: included w/ openFrameworks
- ofxJSON: https://github.com/jefftimesten/ofxJSON
- ofxMSAInteractiveObject: https://github.com/memo/ofxMSAInteractiveObject
- ofxPostProcessing: https://github.com/neilmendoza/ofxPostProcessing
- ofxVectorTile: https://github.com/tangrams/ofxVectorTile
- ofxXMLSettings: included w/ openFrameworks
- ofxNestedFileLoader: https://github.com/Bentleyj/ofxNestedFileLoader

## Areas
#### ofApp.h/.cpp
This is the main area of the application.

###### Color Function
- void ofApp::projectColors() - Materials, Lighting, etc.

###### Menu Functions
- void ofApp::menuSetup(int _w, int _h) - Configures menu space.  Do ALL menu button size and padding here!
- void ofApp::menuUpdates() - Menu system updates; also where the main menu is triggered.
- void ofApp::mouseReleased(int x, int y, int button) - This is where the main menu project buttons are triggered.

###### Totem/Auto System Functions
- void ofApp::autoSysSetup() - Configures automated system.
- void ofApp::autoSysUpdate() - This is the automated system.

#### Globals.h/.cpp
Global variables can be defined here and accessed anywhere.

#### Route XML Data
Route points are hardcoded in an XML called route.xml for each project located in '/data/content/{project name}/route.xml'.

#### Route Xcode Files Group
These files control the routes for each project, interest points, and tiles for locations.
- Location.h/.cpp
- Route.h/.cpp
- InterestPoints.h

###### Route.cpp
- void Route::draw(ofCamera& cam) - Draws the route path for each project.

###### Location.cpp
- void Location::draw(ofCamera& cam, float _alpha, float _height) - Draws the point of interest labels for each project.

#### Tiles Xcode Files Group
These files parse the JSON data to create tile layers.
- LocalTile.h
- TileLoader.h/.cpp

#### Menu Xcode Files Group
These files handle the interactive menu system.
- InteractiveObject.h - This file defines the buttons or objects...
- InteractiveMenu.h/.cpp - The entire menu system.

###### InteractiveMenu.cpp
* For sizing, it's dynamic here so make sure to adjust in ofApp.cpp function "menuSetup()".
- void InteractiveMenu::setup(int _w, int _h, float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut) - This function sets up the main menu, button sounds, button title names, etc.

#### Content Xcode Files Group
Handles all content media loading, drawing, setup, etc.  ALL videos are preloaded on launch because they are too demanding in loading.  Alternative is to use 'threading' but as we only 10 videos, it's best to avoid as once the system is running it's running.
- Content.h/.cpp

###### Content.cpp
- void Content::fileLocation() - ALL content paths are defined here.  Thing to note, Crossrail content goes backwards in the array vs HS1.
- HS1 Buttons {0,1,2,3,4} = {Text Image, Image, Video, Model, ??? (Currently an Image)}
- Crossrail Buttons {4,3,2,1,0} = {??? (Currently an Image), Model, Video, Image, Text Image}

If any content type is changed, you'll need to make sure it's corrected in all functions.  i.e. if you change an image to a video, now all the update/load/draw functions need to reflect this...

## ofxVectorTile
I made a modification to the file 'glmGeometryBuilder.cpp'.  Hacked the last function so that buildings with zero height could have some varying/random height.  Make sure to replace the file here with the one in your addon folder, as addon's do not sync to github.

File is located here - 'https://github.com/HellicarAndLewis/FocusAndContext/tree/master/cove/bin/data/ofxVectorTile-Edit'
