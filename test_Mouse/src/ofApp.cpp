#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 0, 0);
    float x = ofGetMouseX();
    float y = ofGetMouseY();
    ofVec2f mt = mouse.transformMouseCoordinates(x, y);
    ofDrawCircle(mt.x, mt.y, 20);
    ofDrawLine(mt.x - 30, mt.y, mt.x+30, mt.y);
    ofDrawLine(mt.x, mt.y-30, mt.x, mt.y+30);
    
    ofSetColor(0, 255, 0);
    ofDrawCircle(ofGetMouseX(), ofGetMouseY(), 20);
    ofDrawLine(ofGetMouseX() - 30, ofGetMouseY(), ofGetMouseX()+30, ofGetMouseY());
    ofDrawLine(ofGetMouseX(), ofGetMouseY()-30, ofGetMouseX(), ofGetMouseY()+30);
    
    ofSetColor(255);
    ofDrawBitmapStringHighlight("Subscruber Flip Mouse: " + ofToString(mouse.flipMouse), 10, 10);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        mouse.flipMouse = !mouse.flipMouse;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    cout<<"Mouse Moved ofApp Native: "<<x<<","<<y<<endl;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    cout<<"Mouse Dragged ofApp Native: "<<x<<","<<y<<endl;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cout<<"Mouse Pressed ofApp Native: "<<x<<","<<y<<endl;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    cout<<"Mouse Released ofApp Native: "<<x<<","<<y<<": "<<button<<endl;

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    cout<<"Mouse Entered ofApp Native: "<<x<<","<<y<<endl;

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    cout<<"Mouse Exited ofApp Native: "<<x<<","<<y<<endl;
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
