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
    if (percentToActive < 0.02) activeLocation->isActive = true;
}

void Route::draw(ofCamera& cam) {
    ofDisableDepthTest();
    ofSetColor(180, 0, 0);
    ofPushMatrix();
    {
        ofTranslate(0, 0, 0);
        ofSetLineWidth(5);
        routeRender.draw();
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

//
// loads route locations
// path is the directory that holds a route.xml file
// posOffset is the position offset of the first tile from ofxVectorBuilder.h
//
void Route::load(string path, ofVec3f posOffset) {
    
    if(!xml.loadFile(path + "/route.xml") ){
        ofLogError() << "Can't load " << path << " in Route::load";
        return;
    }
    
    folderPath = path;
    titleFont.load("fonts/Helvetica.dfont", 40);
    
    contentImages[0].load(path + "/detail/Content_Text.png");
    contentImages[1].load(path + "/detail/Content_3D.png");
    contentImages[2].load(path + "/detail/Content_Video.png");
    contentImages[3].load(path + "/detail/Content_Newsclips.png");
    contentImages[4].load(path + "/detail/Content_Sound.png");
    
    populateLocations();
    
    latRange.set("lat range", 0, 999, -999);
    lonRange.set("lon range", 0, 999, -999);
    
    int i = 0;
    for (auto &location: locations) {
        // use glmGeo.h helpers to convert lon and lat into oF friendly points
        // these will match up with the dimensions/coordinates used in the tile meshes
        // the offset accounts for the starting position of the first tile
        location.position.set((lon2x(location.getLon()) - posOffset.x), (lat2y(location.getLat()) - posOffset.y));
        // add the oF position of the location to the route polylines
        // route render is just for drawing, don't add the black ones as they're just zoomed out overviews
        if (location.title != "") routeRender.addVertex(location.position);
        // route is the actual route
        route.addVertex(location.position);
        // route inverse is used to shift the whole mesh along an inverted path so that the camera can stay fixed.
        routeInverse.addVertex(location.position * -1);
        location.index = i;
        
        // store the tile x/y so that we can reference it later in order to higlight it
        location.tilePos.set(long2tilex(location.getLon(), 16), lat2tiley(location.getLat(), 16));
        
        lonRange.setMin(MIN(location.latlon.x, lonRange.getMin()));
        lonRange.setMax(MAX(location.latlon.x, lonRange.getMax()));
        latRange.setMin(MIN(location.latlon.y, latRange.getMin()));
        latRange.setMax(MAX(location.latlon.y, latRange.getMax()));
        
        for (auto & image: contentImages) {
            location.contentImages.push_back(&image);
        }
        
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


//
// returns the current/active location
//
Location* Route::getLocation() {
    return activeLocation;
}

//
// returns the current position along the route
// based on the current percent along the route
//
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

//
// creates Location objects from the specified xml file
// adds them to the locations vector
//
void Route::populateLocations() {
    xml.pushTag("route");
    int numLocationTags = xml.getNumTags("location");
    for (int i=0; i < numLocationTags; i++) {
        xml.pushTag("location", i);
        Location location;
        location.titleFont = &titleFont;
        location.setup(xml.getValue("title", ""));
        location.latlon.set(xml.getValue("lat", 0.0f), xml.getValue("lon", 0.0f));
        location.camDistance = xml.getValue("camera:distance", 500);
        location.camRotation.set(
                                 xml.getValue("camera:xrot", -45),
                                 xml.getValue("camera:yrot", 0),
                                 xml.getValue("camera:zrot", 30));
        // images / media
        string filename = xml.getValue("titleImg", "");
        if (filename != "") location.labelImage.load(folderPath + "/labels/" + filename);
        /*
        filename = xml.getValue("detailImg", "");
        if (filename != "") {
            location.contentImage.load(folderPath + "/detail/" + filename);
            location.contentImage.resize(800, 800);
        }
         */
        locations.push_back(location);
        
        ofLogVerbose() << "location " << location.title << " " << location.latlon.x << "," << location.latlon.y;
        
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