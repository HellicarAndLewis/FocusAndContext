//
//  ImageDisplayer.h
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#pragma once

#include "ofMain.h"
#include "ContentDisplayer.h"

class ImageDisplayer : public ContentDisplayer {
public:
    //Constructor
    ImageDisplayer();
    
    // Setters
    void setImage(ofImage* _image) { image = _image; };
    bool setImage(string _imageLocation) {
        image = new ofImage();
        return image->load(_imageLocation);
    }
    
    // Getters
    ofImage* getImage() { return image; };
    
    // Functionality
    virtual void draw(float x, float y);
    
private:
    ofImage* image;
};