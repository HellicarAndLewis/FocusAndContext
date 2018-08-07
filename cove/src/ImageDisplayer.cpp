//
//  ImageDisplayer.cpp
//  Cove
//
//  Created by James Bentley on 4/4/16.
//
//

#include "ImageDisplayer.h"

ImageDisplayer::ImageDisplayer() {
    ContentDisplayer();
    type = ContentTypes::IMAGE;
}

void ImageDisplayer::draw(float x, float y) {
    if(scale > 0.01) {
        ofPushStyle();
        ContentDisplayer::draw(x, y);
        ofSetColor(255);
        float width = image->getWidth();
        float height = image->getHeight();
        image->draw(x, y, width * scale, height * scale);
        int numLines;
        ofSetColor(0, 0, 0, alpha);
        textFont->drawMultiLineColumn(text, 18, x - width/2 + 5, y + height/2 + 30, width * textCutoffPercent, numLines);
        ofPopStyle();
    }
}