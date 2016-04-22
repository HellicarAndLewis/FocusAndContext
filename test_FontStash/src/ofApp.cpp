#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fontBold.setup("fonts/Plain-Bold.ttf", 1.03333, 1024, true, 8, 2.0);
    fontMedium.setup("fonts/Plain-Medium.ttf", 1.03333, 1024, true, 8, 2.0);
    fontRegular.setup("fonts/Plain-Regular.ttf", 1.03333, 1024, true, 8, 2.0);

    currentLabel.load("images/Text.png");
    
    content.load("images/content.png");
        
    //Content header size: 36
    //Content header space width: 24
    //Content description size: 15
    //POI description size:
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofSetColor(255);
    ofDrawRectRounded(0, 0, 972, 874, 20);
    ofDrawRectRounded(972 + 10, 0, 972, 874, 20);
    currentLabel.draw(972 + 10, 0);
    
    string s;
    int numLines;
    
    int x;
    int y;
    
    ofSetColor(0);
    s = "Linking Overpass";
    x = 33;
    y = 55;
    fontBold.drawMultiLineColumn(s, 36, x, y, 874, numLines);

    s = "A stray (currently) unconnected bridge near Ebbsfleet station to become a main street at Ebbsfleet development plan linking both sides of the high speed railway.";
    x = 33;
    y = 757;
    fontRegular.setLineHeight(1.5);
    fontRegular.drawMultiLineColumn(s, 18, x, y, 909 * 2/3, numLines);
    
    ofSetColor(255);
    ofSetRectMode(OF_RECTMODE_CENTER);
    content.draw(972/2, 874/2);
    content.draw(972 + 10 + 972/2, 874/2);
    
//    font.setLineHeight(1.5);
//    font.drawMultiLineColumn(s, 15, 31, 50, 280, numLines);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
