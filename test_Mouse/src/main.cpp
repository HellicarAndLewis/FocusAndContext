#include "ofMain.h"
#include "ofApp.h"

int main(int argc, char *argv[] ){
    
    ofGLFWWindowSettings settings;
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    
    ofApp *app = new ofApp();
        
    ofRunApp(app);
}
