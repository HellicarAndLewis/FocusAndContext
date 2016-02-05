//
//  Interactive.h
//  Cove
//
//  Created by Chris Mullany on 14/01/2016.
//
//
#pragma once
#include "ofMain.h"

namespace IFS {
    
    class Interactive {
    public:
        
        Interactive(){
            enabled = false;
            visible = true;
            autoUpdate = autoDraw = true;
        }
        
        bool enabled;
        bool visible;
        bool autoUpdate, autoDraw;
        
        bool isEnabled(){
            return enabled;
        }
        
        void enable()
        {
            if(!isEnabled())
            {
                enabled = true;
                visible = true;
                enableAppDrawCallback();
                enableAppUpdateCallback();
                enableAppExitCallback();
#ifdef TARGET_OPENGLES
                enableTouchEventCallbacks();
#else
                enableMouseEventCallbacks();
                enableWindowEventCallbacks();
#endif
                enableKeyEventCallbacks();
            }
        }
        
        void disable()
        {
            if(isEnabled())
            {
                enabled = false;
                visible = false;
                disableAppDrawCallback();
                disableAppUpdateCallback();
                disableAppExitCallback();
#ifdef TARGET_OPENGLES
                disableTouchEventCallbacks();
#else
                disableMouseEventCallbacks();
                disableWindowEventCallbacks();
#endif
                disableKeyEventCallbacks();
            }
        }
        
        //App Callbacks
        void enableAppEventCallbacks()
        {
            ofAddListener(ofEvents().update, this, &Interactive::onUpdate);
            ofAddListener(ofEvents().draw, this, &Interactive::onDraw);
            ofAddListener(ofEvents().exit, this, &Interactive::onExit);
        }
        
        //App Callbacks
        void disableAppEventCallbacks()
        {
            ofRemoveListener(ofEvents().update, this, &Interactive::onUpdate);
            ofRemoveListener(ofEvents().draw, this, &Interactive::onDraw);
            ofRemoveListener(ofEvents().exit, this, &Interactive::onExit);
        }
        
        void enableAppDrawCallback()
        {
            ofAddListener(ofEvents().draw, this, &Interactive::onDraw);
        }
        
        void enableAppUpdateCallback()
        {
            ofAddListener(ofEvents().update, this, &Interactive::onUpdate);
        }
        
        void enableAppExitCallback()
        {
            ofAddListener(ofEvents().exit, this, &Interactive::onExit);
        }
        
        void disableAppDrawCallback()
        {
            ofRemoveListener(ofEvents().draw, this, &Interactive::onDraw);
        }
        
        void disableAppUpdateCallback()
        {
            ofRemoveListener(ofEvents().update, this, &Interactive::onUpdate);
        }
        
        void disableAppExitCallback()
        {
            ofRemoveListener(ofEvents().exit, this, &Interactive::onExit);
        }
        
#ifdef TARGET_OPENGLES
        
        //Touch Callbacks
        void enableTouchEventCallbacks()
        {
            
            ofAddListener(ofEvents().touchUp, this, &Interactive::onTouchUp);
            ofAddListener(ofEvents().touchDown, this, &Interactive::onTouchDown);
            ofAddListener(ofEvents().touchMoved, this, &Interactive::onTouchMoved);
            ofAddListener(ofEvents().touchCancelled, this, &Interactive::onTouchCancelled);
            ofAddListener(ofEvents().touchDoubleTap, this, &Interactive::onTouchDoubleTap);
        }
        
        void disableTouchEventCallbacks()
        {
            ofRemoveListener(ofEvents().touchUp, this, &Interactive::onTouchUp);
            ofRemoveListener(ofEvents().touchDown, this, &Interactive::onTouchDown);
            ofRemoveListener(ofEvents().touchMoved, this, &Interactive::onTouchMoved);
            ofRemoveListener(ofEvents().touchCancelled, this, &Interactive::onTouchCancelled);
            ofRemoveListener(ofEvents().touchDoubleTap, this, &Interactive::onTouchDoubleTap);
        }
        
#else
        
        //Mouse Callbacks
        void enableMouseEventCallbacks()
        {
            ofAddListener(ofEvents().mouseReleased, this, &Interactive::onMouseReleased);
            ofAddListener(ofEvents().mousePressed, this, &Interactive::onMousePressed);
            ofAddListener(ofEvents().mouseMoved, this, &Interactive::onMouseMoved);
            ofAddListener(ofEvents().mouseDragged, this, &Interactive::onMouseDragged);
        }
        
        //Mouse Callbacks
        void disableMouseEventCallbacks()
        {
            ofRemoveListener(ofEvents().mouseReleased, this, &Interactive::onMouseReleased);
            ofRemoveListener(ofEvents().mousePressed, this, &Interactive::onMousePressed);
            ofRemoveListener(ofEvents().mouseMoved, this, &Interactive::onMouseMoved);
            ofRemoveListener(ofEvents().mouseDragged, this, &Interactive::onMouseDragged);
        }
        
        //Window Resize Callback
        void enableWindowEventCallbacks()
        {
            ofAddListener(ofEvents().windowResized, this, &Interactive::onWindowResized);
        }
        
        //Window Resize Callback
        void disableWindowEventCallbacks()
        {
            ofRemoveListener(ofEvents().windowResized, this, &Interactive::onWindowResized);
        }
        
        
#endif
        
        //KeyBoard Callbacks
        void enableKeyEventCallbacks()
        {
            ofAddListener(ofEvents().keyPressed, this, &Interactive::onKeyPressed);
            ofAddListener(ofEvents().keyReleased, this, &Interactive::onKeyReleased);
        }
        
        //KeyBoard Callbacks
        void disableKeyEventCallbacks()
        {
            ofRemoveListener(ofEvents().keyPressed, this, &Interactive::onKeyPressed);
            ofRemoveListener(ofEvents().keyReleased, this, &Interactive::onKeyReleased);
        }
        
        void onUpdate(ofEventArgs &data) { if(autoUpdate) update(); }
        void onDraw(ofEventArgs &data) { if(autoDraw) draw(); }
        void onExit(ofEventArgs &data) { exit(); }
        
        
        virtual void update()
        {
            ofLogNotice() << "update() not implemente in IFS::Interactive";
        }
        
        virtual void draw()
        {
            ofLogNotice() << "draw() not implemente in IFS::Interactive";
        }
        
        virtual void exit()
        {
            
        }
        
#ifdef TARGET_OPENGLES
        
        void onTouchDown(ofTouchEventArgs &data)
        {
            touchDown(data);
        }
        
        void onTouchMoved(ofTouchEventArgs &data)
        {
            touchMoved(data);
        }
        
        void onTouchUp(ofTouchEventArgs &data)
        {
            touchUp(data);
        }
        
        void onTouchDoubleTap(ofTouchEventArgs &data)
        {
            touchDoubleTap(data);
        }
        
        void onTouchCancelled(ofTouchEventArgs &data)
        {
            touchCancelled(data);
        }
        
        virtual void touchDown(ofTouchEventArgs& touch)
        {
        }
        
        virtual void touchMoved(ofTouchEventArgs& touch)
        {
        }
        
        virtual void touchUp(ofTouchEventArgs& touch)
        {
        }
        
        virtual void touchDoubleTap(ofTouchEventArgs& touch)
        {
        }
        
        virtual void touchCancelled(ofTouchEventArgs& touch)
        {
        }
        
#else
        
        void onMouseReleased(ofMouseEventArgs& data)
        {
            mouseReleased(data.x, data.y, data.button);
        }
        
        void onMousePressed(ofMouseEventArgs& data)
        {
            mousePressed(data.x, data.y, data.button);
        }
        
        void onMouseMoved(ofMouseEventArgs& data)
        {
            mouseMoved(data.x, data.y);
        }
        
        void onMouseDragged(ofMouseEventArgs& data)
        {
            mouseDragged(data.x, data.y, data.button);
        }
        
        virtual void mouseMoved(int x, int y )
        {
        }
        
        virtual void mouseDragged(int x, int y, int button)
        {
        }
        
        virtual void mousePressed(int x, int y, int button)
        {
        }
        
        virtual void mouseReleased(int x, int y, int button)
        {
        }
        
        void onWindowResized(ofResizeEventArgs& data)
        {
            windowResized(data.width, data.height);
        }
        
        virtual void windowResized(int w, int h)
        {
        }
        
#endif
        
        void onKeyPressed(ofKeyEventArgs& data)
        {
            keyPressed(data.key);
        }
        
        void onKeyReleased(ofKeyEventArgs& data)
        {
            keyReleased(data.key);
        }
        
        virtual void keyPressed(int key)
        {
        }
        
        virtual void keyReleased(int key)
        {
        }
        
    protected:
        
    private:
        
    };
}