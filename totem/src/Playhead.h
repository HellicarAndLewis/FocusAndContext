//
//  Playhead.h
//  PlayheadTest
//
//  Created by James Bentley on 3/27/16.
//
//

#ifndef Playhead_h
#define Playhead_h

#include "ofMain.h"

class Playhead {
public:
    Playhead();
    void draw(float x, float y, float width, float height, float percentage);
    
    void setPastColor(ofColor _col) {pastColor = _col;};
    void setFutureColor(ofColor _col) {futureColor = _col;};
    void setBarColor(ofColor _col) {barColor = _col;};
    void setAlpha(float _alpha) {alpha = _alpha;};
    
private:
    ofColor pastColor, futureColor, barColor;
    float alpha;
};

#endif /* Playhead_hpp */
