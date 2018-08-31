#pragma once

#include "ofMain.h"

class MouseSubscriber {
public:
    bool flipMouse;
    MouseSubscriber() {
        setup();
        flipMouse = false;
    }
    void setup() {
        ofAddListener(ofEvents().mousePressed, this, &MouseSubscriber::mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &MouseSubscriber::mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &MouseSubscriber::mouseReleased);
        ofAddListener(ofEvents().mouseMoved, this, &MouseSubscriber::mouseMoved);
    }
    
    ofVec2f transformMouseCoordinates(float x, float y) {
        if(flipMouse) {
            float xPercentage = (float)(x) / (float)(1080);
            float yPercentage = (float)(y) / (float)1920;
            x = 1080 - 1080 * yPercentage;
            y = 1920 * xPercentage;
            return ofVec2f(x, y);
        }
        return ofVec2f(x, y);
    }
    
    void mouseMoved(ofMouseEventArgs &e) {
        float x = e.x;
        float y = e.y;
        ofVec2f mousePos = transformMouseCoordinates(x, y);
        cout<<"Mouse Moved Mouse Subscriber Untransformed: "<<x<<","<<y<<endl;
        cout<<"Mouse Moved Mouse Subscriber Transformed: "<<mousePos.x<<","<<mousePos.y<<endl;
    }
    
    void mouseDragged(ofMouseEventArgs &e) {
        float x = e.x;
        float y = e.y;
        ofVec2f mousePos = transformMouseCoordinates(x, y);
        cout<<"Mouse Dragged Mouse Subscriber Untransformed: "<<x<<","<<y<<endl;
        cout<<"Mouse Dragged Mouse Subscriber Transformed: "<<mousePos.x<<","<<mousePos.y<<endl;
    }
    
    void mousePressed(ofMouseEventArgs &e) {
        float x = e.x;
        float y = e.y;
        ofVec2f mousePos = transformMouseCoordinates(x, y);
        cout<<"Mouse Pressed Mouse Subscriber Untransformed: "<<x<<","<<y<<endl;
        cout<<"Mouse Pressed Mouse Subscriber Transformed: "<<mousePos.x<<","<<mousePos.y<<endl;
    }
    
    void mouseReleased(ofMouseEventArgs &e) {
        float x = e.x;
        float y = e.y;
        ofVec2f mousePos = transformMouseCoordinates(x, y);
        cout<<"Mouse Released Mouse Subscriber Untransformed: "<<x<<","<<y<<endl;
        cout<<"Mouse Released Mouse Subscriber Transformed: "<<mousePos.x<<","<<mousePos.y<<endl;
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        MouseSubscriber mouse;
};
