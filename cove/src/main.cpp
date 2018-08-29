#include "ofMain.h"
#include "ofApp.h"

int main(int argc, char *argv[] ){

    ofGLFWWindowSettings settings;
    settings.windowMode = OF_FULLSCREEN;
    ofCreateWindow(settings);
    
    ofApp *app = new ofApp();
    
    app->arguments = vector<string>(argv, argv + argc);
    
    ofRunApp(app);
}
