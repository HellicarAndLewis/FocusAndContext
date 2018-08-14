#include "ofMain.h"
#include "ofApp.h"

int main( ){
//    ofAppGlutWindow window;
//    window.setGlutDisplayString("rgba double samples>=4");
//    ofSetupOpenGL(&window, 1080, 1920, OF_FULLSCREEN);
//    ofRunApp( new ofApp());
    
    ofGLFWWindowSettings settings;
    settings.monitor = 1;
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    
//    ofSetupOpenGL(1080, 1920, OF_WINDOW);
    
    ofRunApp(new ofApp());
}
