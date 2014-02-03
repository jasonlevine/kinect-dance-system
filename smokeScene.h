//
//  smokeScene.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-03.
//
//

#pragma once

#include "scene.h"

#include "MSAFluid.h"
#include "ParticleSystem.h"

class smokeScene : public scene {
public:
    void setup(openNIManager * _oni, flowManager * _flow );
    void update(int width, int height);
    void draw(int x, int y, int width, int height, bool drawToScreen);
    
    openNIManager * oni;
    flowManager * flow;
    
    ofxUICanvas *gui;
    void toggleGUI(){ gui->toggleVisible(); }
    
    //----------------------------
    
    void mouseMoved(int x, int y );
    void fadeToColor(float r, float g, float b, float speed);
	void addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce);
    float                   colorMult;
    float                   velocityMult;
	int                     fluidCellsX;
	bool                    resizeFluid;
	bool                    drawFluid;
	bool                    drawParticles;

    msa::fluid::Solver      fluidSolver;
	msa::fluid::DrawerGl	fluidDrawer;
	
	ParticleSystem          particleSystem;
	
	ofVec2f                 pMouse;

    
};
