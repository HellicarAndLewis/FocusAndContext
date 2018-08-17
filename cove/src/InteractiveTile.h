//
//  InteractiveTile.h
//  Cove
//
//  Created by cafe on 17/08/2018.
//

#ifndef InteractiveTile_h
#define InteractiveTile_h

#include "InteractiveObject.h"

class InteractiveTile : public InteractiveObject {
public:
    enum Anim {expand = 0, collapse = 1};
    
    struct animationSequence {
        vector<ofVec2f> positions;
        float easing;
        int posIndex;
    };
    
    ofTrueTypeFont fontMain;
    ofTrueTypeFont fontSub;
    string title;
    string subText;
    float color;
    float alpha;
    bool isSelected;
    bool isDraw;
    bool fadeLabel;
    ofImage image;
    
    int animIndex;
    vector< animationSequence > animations;
    ofVec2f size;
    vector<InteractiveTile*> objectsToCheck;
    
    void setup() {
        // Enable MSAInteractiveObject events
        enableMouseEvents();
        enableKeyEvents();
        
        // set default color to darkened white
        color = 240;
        
        // Load the title of this content as an image.
        ofxNestedFileLoader loader;
        string location = "content/Google Drive/Arup/Research/Content/" + title + "/MenuButton";
        vector<string> path = loader.load(location);
        
        if(path.size() > 0) {
            for(int i = 0; i < path.size(); i++) {
                vector<string> stringSplit = ofSplitString(path[i], "/");
                if( !(stringSplit[stringSplit.size()-1] == "Icon\r") ) {
                    image.load(path[i]);
                    break;
                }
            }
        } else {
            image.load("content/Google Drive/Arup/Research/Content/Placeholder/no_data.png");
        }
//        objectsToCheck.push_back(this);
    }
    
    // Return true if the interactive object is near where it should be;
    bool isNearPosition() {
        vector<ofVec2f> positions = animations[animIndex].positions;
        if(positions.size() > 0) {
            float f = ofDist(x, y, positions[animations[animIndex].posIndex].x, positions[animations[animIndex].posIndex].y);
            return (f < 0.5);
        } else {
            return true;
        }
    }
    
    // Set a list of objects whose animations should be checked. Don't move on to the next part of your animation until all these objects are in the correct position.
    void setObjectsToCheck(vector<InteractiveTile*> _objectsToCheck) {
        for(int i = 0; i < _objectsToCheck.size(); i++) {
            bool objectFound = false;
            for(int j = 0; j < objectsToCheck.size(); j++) {
                if(objectsToCheck[j] == objectsToCheck[i]) {
                    objectFound = true;
                    break;
                }
            }
            if(!objectFound) {
                objectsToCheck.push_back(_objectsToCheck[i]);
            }
        }
    }
    
    // Add an Animation Sequence to the list of animations.
    void addAnimation(vector<ofVec2f> positions, float easing) {
        animationSequence anim;
        anim.positions = positions;
        anim.easing = easing;
        anim.posIndex = 0;
        animations.push_back(anim);
    }
    
    // Draw this tile
    void draw() {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(x, y, width, height);
//        // when selected, lerp to white
//        if (isSelected) color = ofLerp(color, 255, 0.2);
//        else color = ofLerp(color, 240, 0.2);
//
//        ofSetColor(color);
//        ofDrawRectRounded(x, y, width, height, 10);
//
//        // fades content titles
//        if (fadeLabel) alpha = ofLerp(alpha, 0, 0.1);
//        else alpha = ofLerp(alpha, 255, 0.2);
//
//        ofSetColor(255, alpha);
//        // draws menu tiles
//        image.draw(x, y, width, height);
    }
    
    void exit() {
        
    }
    
    // Set the animation state and reset all animation positions to 0
    void setAnimation(int i) {
        animIndex = i;
        for(int i = 0; i < animations.size(); i++) {
            animations[i].posIndex = 0;
        }
    }
    
    // Update performs the transforms of the animations and steps through positions withint the current animation state.
    void update() {
        if(animations.size() > 0) {
            bool allObjectsInPosition = true;
            for(int i = 0; i < objectsToCheck.size(); i++) {
                if(!objectsToCheck[i]->isNearPosition()) {
                    allObjectsInPosition = false;
                    break;
                }
            }
            
            if(allObjectsInPosition) {
                if(animations[animIndex].posIndex < animations[animIndex].positions.size()-1) {
                    animations[animIndex].posIndex++;
                }
            }
            
            float newX = ofLerp(x, animations[animIndex].positions[animations[animIndex].posIndex].x, animations[animIndex].easing);
            float newY = ofLerp(y, animations[animIndex].positions[animations[animIndex].posIndex].y, animations[animIndex].easing);
            //ofVec2f p = ofLerp(ofVec2f(x, y), currentAnim.positions[currentAnim.posIndex], currentAnim.easing);
            setPosition(ofVec2f(newX,newY));
        }

    }
    
    // Do something when pressed
    virtual void onPress(int x, int y, int button) {
//        cout<<"Tile Pressed!"<<endl;
//        animIndex++;
//        animIndex %= animations.size();
//        setAnimation(animIndex);
    }
    
};

#endif
