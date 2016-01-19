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

void Route::draw() {
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
        location.draw();
    }
    ofEnableDepthTest();
}

//////////////////////////////////////////////////////////////////////////////////
// public
//////////////////////////////////////////////////////////////////////////////////
void Route::load(string path, ofVec3f posOffset) {
    
    titleFont.load("fonts/Helvetica.dfont", 40);
    
    Location location0;
    location0.titleFont = &titleFont;
    location0.setup("");
    location0.latlon.set(-0.0934, 51.5135);
    location0.camDistance = 2500;
    location0.camRotation.set(0, 0, 0);
    locations.push_back(location0);
    Location location1;
    location1.titleFont = &titleFont;
    location1.setup("St Pauls");
    location1.latlon.set(-0.09781, 51.51356);
    locations.push_back(location1);
    Location location2;
    location2.titleFont = &titleFont;
    location2.setup("Bank");
    location2.latlon.set(-0.08907, 51.51331);
    locations.push_back(location2);
    Location location3;
    location3.titleFont = &titleFont;
    location3.setup("Liverpool St");
    location3.latlon.set(-0.08122, 51.51877);
    locations.push_back(location3);
    Location location4;
    location4.titleFont = &titleFont;
    location4.setup("Aldgate");
    location4.latlon.set(-0.07577, 51.51421);
    locations.push_back(location4);
    
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
        //scroller.ticks.push_back(location.routePercent);
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

//////////////////////////////////////////////////////////////////////////////////
// custom event handlers
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// oF event handlers
//////////////////////////////////////////////////////////////////////////////////