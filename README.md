# FocusAndContext
An series of interactions that place content in geographical space.

##Installation Instructions
 1. Download and install openFrameworks via the instructions found here, you'll want version 0.9.3: http://openframeworks.cc/download/
 2. Once you've installed openFrameworks you'll need to clone this repository into your apps folder.
 3. Once you've clone the rpo you'll need to isntall all the addons listed below in the addons folder.
 3. Once the folder has been cloned you'll need to acquire the data, You can get this from Google Drive.
 4. Once you have installed google drive ans synced with the appropriate folder you'll need to move your google drive root folder into FocusAndContext/cove/bin.data/content
 5. Next you need to edit a few addons, the first is ofxFBXScene and the second is ofxVectorTile. To edit these open the cove/data folder and take the files located in ofxFBXScene-Edit and ofxVectorTile-Edit folders and replace the files in the addons with the once provided in this repo.
 6. To run in Totem mode simply open the xcode project inside the totem folder and compile and run it in debug mode
 7. To run in Cove mode do the same but in the cove folder, you'll also need to rotate your screen by going to System Preferences > Displays and changing Rotation to 90 degrees.
 8. Everything should now be installed for a one-off play! 
 9. To get the system installation ready you'll need to change a few settings in the comuters preferences: follow the instructions found here: http://openframeworks.cc/ofBook/chapters/installation_up_4evr_macosx.html ignoring step 3 and 5.
 
##Intallation From Our System
 1. Connect computer to touch screen via HDMI and USB
 2. Power both computer and touch-screen, the 'cove' application will automatically launch.
 3. Ensure Computer is not covered so it will not over-heat.
 4. To Install Totem projection simply connect the media display device to a projector via HDMI or VGA and power both the projector and the playback device. The totem video loop will automatically start and run forever.
 5. If you want to change the idle time, ie the time the cove waits until it switches projects autonomously you'll need to quit the application by pressing escape. Navigate to the file found here: ~/Documents/openFrameworksNightly/apps/FocusAndContext/cove/bin/data/settings/idleTime.xml
 6. Double click on the xml file to open it in any text editor
 7. Change the time displayed from: <idleTime>150.</idleTime> to <idleTime>[NEW NUMBER]</idleTime> to whatever you want!

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
- ofxFontStash: https://github.com/armadillu/ofxFontStash

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
