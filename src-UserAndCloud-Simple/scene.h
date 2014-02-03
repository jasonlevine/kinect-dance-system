//
//  scene.h
//  just_you_AA_NI_GLSL
//
//  Created by Jason Levine on 2013-11-11.
//
//
#include "flowManager.h"
#include "openNIManager.h"
#include "ofxUI.h"


#pragma once

class scene {
public:
    virtual void setup(openNIManager * _oni, flowManager * _flow ){}
    virtual void update(int width, int height){}
    virtual void draw(int x, int y, int width, int height, bool drawToScreen){}
    virtual void toggleGUI(){}
    
    openNIManager * oni;
    flowManager * flow;
    
    ofxUICanvas *gui;
};
