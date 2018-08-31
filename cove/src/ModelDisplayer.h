//
//  ModelDisplayer.h
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#pragma once

#include "ofMain.h"
#include "ContentDisplayer.h"
#include "ofxFBX.h"
#include "ModelContentCam.h"

class ModelDisplayer : public ContentDisplayer {
public:
    //Constructor
    ModelDisplayer();
    
    // Setters
    void setManager(ofxFBXManager* _manager) { manager = _manager; };
    void setScene(ofxFBXScene* _scene) { scene = _scene; };
    bool setScene(string sceneLocation) {
        scene = new ofxFBXScene();
        ofxFBXSceneSettings settings;
        bool loaded = scene->load(sceneLocation, settings);
        if(loaded) {
            manager->setup( scene );
        }
        return loaded;
    }
    void setCamera(ModelContentCam* _camera) { cam = _camera; };
    void setLight(ofLight* _light) { light = _light; };
    
    // Getters
    ofxFBXManager* getManager() { return manager; };
    ofxFBXScene* getScene() { return scene; };
    ModelContentCam* getCamera() { return cam; };
    ofLight* getLight() { return light; };
    
    // Functionality
    virtual void draw(float x, float y);
    virtual void update();
    
private:
    ofxFBXManager* manager;
    ofxFBXScene* scene;
    ModelContentCam* cam;
    ofLight* light;
    float camMaxZoom;
    float camMinZoom;
    float camZoom;
};
