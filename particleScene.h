//
//  particleScene.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-03.
//
//

#pragma once

#include "scene.h"
#include "particleSystem.h"

class particleScene : public scene {
public:
    void setup(openNIManager * _oni, flowManager * _flow );
    void update(int width, int height);
    void draw(int x, int y, int width, int height, bool drawToScreen);
    
    openNIManager * oni;
    flowManager * flow;
    
    ofxUICanvas * gui;
    void toggleGUI(){ gui->toggleVisible(); }
    
    particleSystem particles;
    
    bool bDebug, bGenerate, bReverse;
    
    float threshold, scale;
    
    int fadeAmt;
    int alpha;
    float brightness;
	float contrast;
    
};
