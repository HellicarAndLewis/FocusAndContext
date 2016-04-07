//
//  Route.cpp
//  Cove
//
//  Created by Chris Mullany on 19/01/2016.
//  Edited by Jason Walters on 22/03/2016.
//
//

#include "Route.h"
#include "glmGeo.h"

Route::Route() {
    activeLocation = NULL;
    locationThreshold = 0.05;
    zoomLevel = 16;
}

void Route::setup() {

}

void Route::flushData() {
    
    // flush data depending on which project/route
    if (activeProject == 0) {
        if (routeLeft.size() > 0) routeLeft.clear();
        if (routeRenderLeft.size() > 0) routeRenderLeft.clear();
        if (routeInverseLeft.size() > 0) routeInverseLeft.clear();
        
        if (locationsLeft.size() > 0) locationsLeft.clear();
    } else {
        if (routeRight.size() > 0) routeRight.clear();
        if (routeRenderRight.size() > 0) routeRenderRight.clear();
        if (routeInverseRight.size() > 0) routeInverseRight.clear();
        if (locationsRight.size() > 0) locationsRight.clear();
    }
}

void Route::update(float percent) {
    
    // store overall route percent
    this->percent = percent;
    
    // update active location per project/route
    if (activeProject == 0) {
        for (auto &location: locationsLeft) {
            location.update();
           // location.isActive = false;
        }
        
        // get the nearest point on the route to current progress
        float totalLength = routeLeft.getLengthAtIndex(locationsLeft.size()-1);
        float indexInterp = routeLeft.getIndexAtLength(percent * totalLength);
        activeIndex = round(indexInterp);
        activeLocation = &locationsLeft[activeIndex];
        
        // get the percent distance (0 - 0.5) to the nearest point
        percentToActive = indexInterp - activeIndex;
        if (activeIndex > indexInterp) percentToActive = activeIndex - indexInterp;
        // set the nearest point to active if it's nearer than a certain threshold
        if (percentToActive < locationThreshold) activeLocation->isActive = true;
    } else {
        for (auto &location: locationsRight) {
            location.update();
          //  location.isActive = false;
        }
        
        // get the nearest point on the route to current progress
        float totalLength = routeRight.getLengthAtIndex(locationsRight.size()-1);
        float indexInterp = routeRight.getIndexAtLength(percent * totalLength);
        activeIndex = round(indexInterp);
        activeLocation = &locationsRight[activeIndex];
        
        // get the percent distance (0 - 0.5) to the nearest point
        percentToActive = indexInterp - activeIndex;
        if (activeIndex > indexInterp) percentToActive = activeIndex - indexInterp;
        // set the nearest point to active if it's nearer than a certain threshold
        if (percentToActive < locationThreshold) activeLocation->isActive = true;
    }
}

void Route::draw(ofCamera& cam) {
    
    // lerp alpha values
    if (activeProject == 0) {
        alphaLeft = ofLerp(alphaLeft, 255, 0.2);
        alphaRight = ofLerp(alphaRight, 0, 0.2);
        
    } else {
        alphaLeft = ofLerp(alphaLeft, 0, 0.2);
        alphaRight = ofLerp(alphaRight, 255, 0.2);
    }
    
    // draw hs1/left project route
    ofDisableDepthTest();
    ofSetColor(255, 130, 0, alphaLeft);
    ofPushMatrix();
    {
        ofTranslate(0, 0, 0);
        float rad = 4.;
        ofSetLineWidth(rad);
        routeRenderLeft.draw();
        ofSetLineWidth(1);
    }
    ofPopMatrix();
    
    ofSetColor(255);
    for (auto &location: locationsLeft) {
        location.draw(cam, alphaLeft, -1150);
    }
    ofEnableDepthTest();
    
    ofDisableDepthTest();
    ofSetColor(255, 130, 0, alphaRight);
    ofPushMatrix();
    {
        ofTranslate(0, 0, 0);
        float rad = 4.;
        ofSetLineWidth(rad);
        routeRenderRight.draw();
        ofSetLineWidth(1);
    }
    ofPopMatrix();
    
    ofSetColor(255);
    for (auto &location: locationsRight) {
        location.draw(cam, alphaRight, -1600);
    }
    ofEnableDepthTest();
}

void Route::draw2d() {
    // draw tiles based on which project/route
    if (activeProject == 0) {
        for (auto &location: locationsLeft) {
            location.draw2d();
        }
    } else {
        for (auto &location: locationsRight) {
            location.draw2d();
        }
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
void Route::loadLeft(string path, ofVec3f posOffset) {
    
    activeProject = 0;
    
    if(!xml.loadFile(path + "/route.xml") ){
        ofLogError() << "Can't load " << path << " in Route::load";
        return;
    }
    
    folderPath = path;
    titleFont.load("fonts/Plain-Medium.ttf", 40);
    
    contentImages[0].load(path + "/detail/Content_Text.png");
    contentImages[1].load(path + "/detail/Content_3D.png");
    contentImages[2].load(path + "/detail/Content_Video.png");
    contentImages[3].load(path + "/detail/Content_Newsclips.png");
    contentImages[4].load(path + "/detail/Content_Sound.png");
    
    flushData();
    populateLocationsLeft();
    
    latRange.set("lat range", 0, 999, -999);
    lonRange.set("lon range", 0, 999, -999);
    
    int i = 0;
    for (auto &location: locationsLeft) {
        
        if (location.contentImages.size() > 0) location.contentImages.clear();
        
        // use glmGeo.h helpers to convert lon and lat into oF friendly points
        // these will match up with the dimensions/coordinates used in the tile meshes
        // the offset accounts for the starting position of the first tile
        location.position.set((lon2x(location.getLon()) - posOffset.x), (lat2y(location.getLat()) - posOffset.y));
        // add the oF position of the location to the route polylines
        // route render is just for drawing, don't add the black ones as they're just zoomed out overviews
        if (location.title == "") {
            routeRenderLeft.addVertex(location.position);
//            if(i+1 < locationsLeft.size()) {
//                ofVec2f first = location.position;
//                ofVec2f second = locationsLeft[i+1].position;
//                ofVec2f diff = first - second;
//                diff.rotate(90);
//                diff.normalize();
//                diff *= 50000;
//                routeRenderLeft.addVertex(first + diff);
//            }
        }
        // route is the actual route
        routeLeft.addVertex(location.position);
        // route inverse is used to shift the whole mesh along an inverted path so that the camera can stay fixed.
        routeInverseLeft.addVertex(location.position * -1);
        location.index = i;
        
        // store the tile x/y so that we can reference it later in order to higlight it
        location.tilePos.set(long2tilex(location.getLon(), zoomLevel), lat2tiley(location.getLat(), zoomLevel));
        
        lonRange.setMin(MIN(location.latlon.x, lonRange.getMin()));
        lonRange.setMax(MAX(location.latlon.x, lonRange.getMax()));
        latRange.setMin(MIN(location.latlon.y, latRange.getMin()));
        latRange.setMax(MAX(location.latlon.y, latRange.getMax()));
        
        for (auto & image: contentImages) {
            location.contentImages.push_back(&image);
        }
        
        i++;
    }
    
    routeRenderLeft = routeRenderLeft.getSmoothed(2);
    
    i = 0;
    float totalLength = routeLeft.getLengthAtIndex(locationsLeft.size()-1);
    for (auto &location: locationsLeft) {
        location.routePercent = routeLeft.getLengthAtIndex(i) / totalLength;
        i++;
    }
    
    activeLocation = &locationsLeft[0];
    activeLocation->isActive = true;
}

void Route::loadRight(string path, ofVec3f posOffset) {
    
    activeProject = 1;
    
    if(!xml.loadFile(path + "/route.xml") ){
        ofLogError() << "Can't load " << path << " in Route::load";
        return;
    }
    
    folderPath = path;
    titleFont.load("fonts/Plain-Medium.ttf", 40);
    
    contentImages[0].load(path + "/detail/Content_Text.png");
    contentImages[1].load(path + "/detail/Content_3D.png");
    contentImages[2].load(path + "/detail/Content_Video.png");
    contentImages[3].load(path + "/detail/Content_Newsclips.png");
    contentImages[4].load(path + "/detail/Content_Sound.png");
    
    flushData();
    populateLocationsRight();
    
    latRange.set("lat range", 0, 999, -999);
    lonRange.set("lon range", 0, 999, -999);
    
    int i = 0;
    for (auto &location: locationsRight) {
        
        if (location.contentImages.size() > 0) location.contentImages.clear();
        
        // use glmGeo.h helpers to convert lon and lat into oF friendly points
        // these will match up with the dimensions/coordinates used in the tile meshes
        // the offset accounts for the starting position of the first tile
        location.position.set((lon2x(location.getLon()) - posOffset.x), (lat2y(location.getLat()) - posOffset.y));
        // add the oF position of the location to the route polylines
        // route render is just for drawing, don't add the black ones as they're just zoomed out overviews
        //if (location.title != "") routeRender.addVertex(location.position);
        if (location.title == "") routeRenderRight.addVertex(location.position);
        // route is the actual route
        routeRight.addVertex(location.position);
        // route inverse is used to shift the whole mesh along an inverted path so that the camera can stay fixed.
        routeInverseRight.addVertex(location.position * -1);
        location.index = i;
        
        // store the tile x/y so that we can reference it later in order to higlight it
        location.tilePos.set(long2tilex(location.getLon(), zoomLevel), lat2tiley(location.getLat(), zoomLevel));
        
        lonRange.setMin(MIN(location.latlon.x, lonRange.getMin()));
        lonRange.setMax(MAX(location.latlon.x, lonRange.getMax()));
        latRange.setMin(MIN(location.latlon.y, latRange.getMin()));
        latRange.setMax(MAX(location.latlon.y, latRange.getMax()));
        
        for (auto & image: contentImages) {
            location.contentImages.push_back(&image);
        }
        
        i++;
    }
    
    routeRenderRight = routeRenderRight.getSmoothed(2);

    
    i = 0;
    float totalLength = routeRight.getLengthAtIndex(locationsRight.size()-1);
    for (auto &location: locationsRight) {
        location.routePercent = routeRight.getLengthAtIndex(i) / totalLength;
        i++;
    }
    
    activeLocation = &locationsRight[0];
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
    if (activeProject == 0) {
        if (doInvert)
            return routeInverseLeft.getPointAtPercent(percent);
        else
            return routeLeft.getPointAtPercent(percent);
    }
    else {
        if (doInvert)
            return routeInverseLeft.getPointAtPercent(percent);
        else
            return routeLeft.getPointAtPercent(percent);
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
void Route::populateLocationsLeft() {
    xml.pushTag("route");
    int numLocationTags = xml.getNumTags("location");
    int numNamedLocations = 0;
    for (int i=0; i < numLocationTags; i++) {
        xml.pushTag("location", i);
        Location location;
        location.titleFont = &titleFont;
        location.setup(xml.getValue("title", ""));
        location.latlon.set(xml.getValue("lat", 0.0f), xml.getValue("lon", 0.0f));
        location.camDistance = xml.getValue("camera:distance", 8000);
        location.camRotation.set(
                                 xml.getValue("camera:xrot", -45),
                                 xml.getValue("camera:yrot", 0),
                                 xml.getValue("camera:zrot", 30));
        
        // images / media
        string filename = xml.getValue("titleImg", "");
        if (filename != "") {
            location.labelImage.load(folderPath + "/labels/" + filename);
            location.verticalOffset = (numNamedLocations%2 == 0) ? 30000 : -30000;
            location.verticalOffsetSaved = (numNamedLocations%2 == 0) ? 30000 : -30000;
            numNamedLocations++;
        }
        
        /*
         filename = xml.getValue("detailImg", "");
         if (filename != "") {
         location.contentImage.load(folderPath + "/detail/" + filename);
         location.contentImage.resize(800, 800);
         }
         */
        
        locationsLeft.push_back(location);
        
        ofLogVerbose() << "location " << location.title << " " << location.latlon.x << "," << location.latlon.y;
        
        xml.popTag();
    }
    xml.popTag();
}

void Route::populateLocationsRight() {
    xml.pushTag("route");
    int numLocationTags = xml.getNumTags("location");
    int numNamedLocations = 0;
    for (int i=0; i < numLocationTags; i++) {
        xml.pushTag("location", i);
        Location location;
        location.titleFont = &titleFont;
        location.setup(xml.getValue("title", ""));
        location.latlon.set(xml.getValue("lat", 0.0f), xml.getValue("lon", 0.0f));
        location.camDistance = xml.getValue("camera:distance", 8000);
        location.camRotation.set(
                                 xml.getValue("camera:xrot", -45),
                                 xml.getValue("camera:yrot", 0),
                                 xml.getValue("camera:zrot", 30));
        
        // images / media
        string filename = xml.getValue("titleImg", "");
        if (filename != "") {
            location.labelImage.load(folderPath + "/labels/" + filename);
            switch(numNamedLocations) {
                case 0:
                    location.verticalOffset = 15000;
                    location.verticalOffsetSaved = 15000;
                    break;
                case 1:
                    location.verticalOffset = -5000;
                    location.verticalOffsetSaved = -5000;
                    break;
                case 2:
                    location.verticalOffset = 10000;
                    location.verticalOffsetSaved = 10000;
                    break;
                case 3:
                    location.verticalOffset = -10000;
                    location.verticalOffsetSaved = -10000;
                    break;
                case 4:
                    location.verticalOffset = 10000;
                    location.verticalOffsetSaved = 10000;
                    break;
                default :
                    break;
            }
            numNamedLocations++;
        }
        /*
        filename = xml.getValue("detailImg", "");
        if (filename != "") {
            location.contentImage.load(folderPath + "/detail/" + filename);
            location.contentImage.resize(800, 800);
        }
         */
        
        locationsRight.push_back(location);
        
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