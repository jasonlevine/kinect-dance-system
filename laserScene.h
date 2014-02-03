//
//  laserScene.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#pragma once

#include "scene.h"

class laserScene : public scene {
public:
    void setup(openNIManager * _oni, flowManager * _flow );
    void update(int width, int height);
    void draw(int x, int y, int width, int height, bool drawToScreen);

    
    openNIManager * oni;
    flowManager * flow;
    
    ofxUICanvas *gui;
    void toggleGUI(){ gui->toggleVisible(); }
    
    float threshold;
    float lineScale;
    float lineWidth;
    float lineWidthMult;
    
    ofFloatColor bgColor, lineColor;
    
    
};
