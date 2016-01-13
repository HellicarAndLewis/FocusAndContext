
#include "ofApp.h"
#include "OpenStreetMapProvider.h"
#include "GeoUtils.h"

void ofApp::setup() {
    ofSetVerticalSync(true);
    
    map.setup(std::shared_ptr<OpenStreetMapProvider>(new OpenStreetMapProvider()),
              ofGetWidth(),
              ofGetHeight());
    
    map.setGeoLocationCenter(GeoLocation(41.878247, -87.629767));
    map.setZoom(12);
    
}


void ofApp::update() {
}


void ofApp::draw() {
    ofBackground(0);
    
    map.draw();
    
    ofSetColor(255, 127, 255);
    
    cout << map.getGeoLocationCenter() << endl;
    
    ofDrawBitmapStringHighlight(ofToString(map.getGeoLocationCenter()),
                                ofGetWidth() / 2,
                                ofGetHeight() / 2);
    
    ofVec2d mousePosition(mouseX, mouseY);
    
    ofDrawBitmapStringHighlight(ofToString(map.pointToTileCoordinate(mousePosition)),
                                mouseX + 16,
                                mouseY);
    
    ofDrawBitmapStringHighlight(ofToString(map.pointToGeolocation(mousePosition)),
                                mouseX + 16,
                                mouseY + 14);
    
    
}


void ofApp::keyPressed(int key) {
    if (key == 'f' || key == 'F')
    {
        ofToggleFullscreen();
    }
}
