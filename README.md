# FocusAndContext
An series of interactions that place content in geographical space.

### Addons
- ofxDatGui
- ofxFBX
- ofxGlmTools
- ofxGui
- ofxJSON
- ofxMSAInteractiveObject
- ofxPostProcessing
- ofxVectorTile
- ofxXMLSettings

### Areas
##### ofApp.h/.cpp
This is the main area of the application.

####### Colors
- void ofApp::projectColors() - Materials, Lighting, etc.

####### Menu
- void ofApp::menuSetup(int _w, int _h) - Configures menu space.  Do ALL menu button size and padding here!
- void ofApp::menuUpdates() - Menu system updates; also where the main menu is triggered.
- void ofApp::mouseReleased(int x, int y, int button) - This is where the main menu project buttons are triggered.

####### Totem Auto System
- void ofApp::autoSysSetup() - Configures automated system.
- void ofApp::autoSysUpdate() - This is the automated system.

##### Globals.h/.cpp
Global variables can be defined here and accessed anywhere.

##### Route Group
These files control the routes for each project, interest points, and tiles for locations.

####### Route.cpp
- void Route::draw(ofCamera& cam) - Draws the route path for each project.

####### Location.cpp
- void Location::draw(ofCamera& cam, float _alpha, float _height) - Draws the point of interest labels for each project.

##### Tiles Group
These files parse the JSON data to create tile layers.

##### Menu Group
These files handle the interactive menu system.

####### InteractiveMenu.cpp
* For sizing, it's dynamic here so make sure to adjust in ofApp.cpp function "menuSetup()".
- void InteractiveMenu::setup(int _w, int _h, float _mainArea, float _subArea, float _padding, float _easeIn, float _easeOut) - This function sets up the main menu, button sounds, button title names, etc.

##### Content Group
Handles all content media loading, drawing, setup, etc.
