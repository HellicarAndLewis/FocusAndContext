#include "ofMain.h"
#include "ofApp.h"

int main( ){
//    ofAppGlutWindow window;
//    window.setGlutDisplayString("rgba double samples>=4");
//    ofSetupOpenGL(&window, 1080, 1920, OF_FULLSCREEN);
//    ofRunApp( new ofApp());
    
    ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
    ofRunApp(new ofApp());
}