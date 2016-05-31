#include "ofMain.h"
#include "ofApp.h"
#include "ofxWatchdog.h"

int main( ){
//    ofAppGlutWindow window;
//    window.setGlutDisplayString("rgba double samples>=4");
//    ofSetupOpenGL(&window, 1080, 1920, OF_FULLSCREEN);
//    ofRunApp( new ofApp());
    
    ofSetupOpenGL(1080, 1920, OF_FULLSCREEN);
    
    ofxWatchdog::watch(3000, true, true, true);
    
    ofRunApp(new ofApp());
}