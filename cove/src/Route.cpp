//
//  Route.cpp
//  Cove
//
//  Created by Chris Mullany on 19/01/2016.
//
//

#include "Route.h"
#include "glmGeo.h"

Route::Route() {
    activeLocation = NULL;
}

void Route::setup() {
}

void Route::update(float percent) {
    
    // store overall route percent
    this->percent = percent;
    
    // update active location
    for (auto &location: locations) {
        location.update();
        location.isActive = false;
    }
    
    // get the nearest point on the route to current progress
    float totalLength = route.getLengthAtIndex(locations.size()-1);
    float indexInterp = route.getIndexAtLength(percent * totalLength);
    activeIndex = round(indexInterp);
    activeLocation = &locations[activeIndex];
    
    // get the percent distance (0 - 0.5) to the nearest point
    percentToActive = indexInterp - activeIndex;
    if (activeIndex > indexInterp) percentToActive = activeIndex - indexInterp;
    // using a threshold of 0.1, set the nearest point to active
    if (percentToActive < 0.1) activeLocation->isActive = true;
}

void Route::draw(ofCamera& cam) {
    ofDisableDepthTest();
    ofSetColor(200, 0, 0);
    ofPushMatrix();
    {
        ofTranslate(0, 0, -20);
        ofSetLineWidth(5);
        route.draw();
        ofSetLineWidth(1);
    }
    ofPopMatrix();
    ofSetColor(255);
    for (auto &location: locations) {
        location.draw(cam);
    }
    ofEnableDepthTest();
}

void Route::draw2d() {
    for (auto &location: locations) {
        location.draw2d();
    }
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////
void Route::load(string path, ofVec3f posOffset) {
    
    if(!xml.loadFile(path + "/route.xml") ){
        ofLogError() << "Can't load " << path << " in Route::load";
        return;
    }
    
    folderPath = path;
    titleFont.load("fonts/Helvetica.dfont", 40);
    populateLocations();
    
    int i = 0;
    for (auto &location: locations) {
        location.position.set((lon2x(location.getLon()) - posOffset.x), (lat2y(location.getLat()) - posOffset.y));
        route.addVertex(location.position);
        routeInverse.addVertex(location.position * -1);
        location.index = i;
        i++;
    }
    
    i = 0;
    float totalLength = route.getLengthAtIndex(locations.size()-1);
    for (auto &location: locations) {
        location.routePercent = route.getLengthAtIndex(i) / totalLength;
        i++;
    }
    
    activeLocation = &locations[0];
    activeLocation->isActive = true;
}


Location* Route::getLocation() {
    return activeLocation;
}


ofPoint Route::getPosition(bool doInvert) {
    if (doInvert) {
        return routeInverse.getPointAtPercent(percent);
    }
    else {
        return route.getPointAtPercent(percent);
    }
}

//////////////////////////////////////////////////////////////////////////////////
// protected
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// private
//////////////////////////////////////////////////////////////////////////////////
void Route::populateLocations() {
    xml.pushTag("route");
    int numLocationTags = xml.getNumTags("location");
    for (int i=0; i < numLocationTags; i++) {
        xml.pushTag("location", i);
        Location location;
        location.titleFont = &titleFont;
        location.setup(xml.getValue("title", ""));
        location.latlon.set(xml.getValue("lat", 0.0f), xml.getValue("lon", 0.0f));
        location.camDistance = xml.getValue("camera:distance", 400);
        location.camRotation.set(
                                 xml.getValue("camera:xrot", -15),
                                 xml.getValue("camera:yrot", 0),
                                 xml.getValue("camera:zrot", 15));
        // images / media
        string filename = xml.getValue("titleImg", "");
        if (filename != "") location.labelImage.load(folderPath + "/labels/" + filename);
        filename = xml.getValue("detailImg", "");
        if (filename != "") {
            location.contentImage.load(folderPath + "/detail/" + filename);
            location.contentImage.resize(800, 800);
        }
        locations.push_back(location);
        
        ofLogNotice() << "location " << location.title << " " << location.latlon.x << "," << location.latlon.y;
        
        xml.popTag();
    }
    xml.popTag();
    
}
//////////////////////////////////////////////////////////////////////////////////
// custom event handlers
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////