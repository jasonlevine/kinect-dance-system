//
//  smokeScene.cpp
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-03.
//
//

#include "smokeScene.h"


//--------------------------------------------------------------
void smokeScene::setup(openNIManager * _oni, flowManager * _flow ) {
    oni = _oni;
    flow = _flow;
	
	// setup fluid stuff
	fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
	
	fluidCellsX			= 150;
	
	drawFluid			= true;
	drawParticles		= true;
    
    colorMult           = 50;
    velocityMult        = 34;
	
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);

	
    
    //init gui dims
    float dim = 16;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
    
    //gui!
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    gui->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 60);
    
    gui->addSpacer(length-xInit, 1);
	gui->addIntSlider("fluidCellsX", 20, 400, &fluidCellsX);
	gui->addButton("resizeFluid", &resizeFluid);
    gui->addSlider("colorMult", 0, 100, &colorMult);
    gui->addSlider("velocityMult", 0, 100, &velocityMult);
	gui->addSlider("fs.viscocity", 0.0, 0.01, &fluidSolver.viscocity);
	gui->addSlider("fs.colorDiffusion", 0.0, 0.0003, &fluidSolver.colorDiffusion);
	gui->addSlider("fs.fadeSpeed", 0.0, 0.1, &fluidSolver.fadeSpeed);
	gui->addIntSlider("fs.solverIterations", 1, 50, &fluidSolver.solverIterations);
	gui->addSlider("fs.deltaT", 0.1, 5, &fluidSolver.deltaT);
//	gui->addComboBox("fd.drawMode", (int&)fluidDrawer.drawMode, msa::fluid::getDrawModeTitles());
	gui->addToggle("fs.doRGB", &fluidSolver.doRGB);
	gui->addToggle("fs.doVorticityConfinement", &fluidSolver.doVorticityConfinement);
	gui->addToggle("drawFluid", &drawFluid);
	gui->addToggle("drawParticles", &drawParticles);
	gui->addToggle("fs.wrapX", &fluidSolver.wrap_x);
	gui->addToggle("fs.wrapY", &fluidSolver.wrap_y);

    gui->setVisible(false);
//	gui->currentPage().setXMLName("ofxMSAFluidSettings.xml");
//    gui->loadFromXML();
//	gui->setDefaultKeys(true);
//	gui->setAutoSave(true);
//    gui->show();

	
//	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	pMouse = msa::getWindowCenter();
	resizeFluid			= true;
	
	ofSetBackgroundAuto(false);
}


void smokeScene::fadeToColor(float r, float g, float b, float speed) {
    glColor4f(r, g, b, speed);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}


// add force and dye to fluid, and create particles
void smokeScene::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce) {
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0) {
		pos.x = ofClamp(pos.x, 0.0f, 1.0f);
		pos.y = ofClamp(pos.y, 0.0f, 1.0f);
		
        int index = fluidSolver.getIndexForPos(pos);
		
		if(addColor) {
            //			Color drawColor(CM_HSV, (getElapsedFrames() % 360) / 360.0f, 1, 1);
			ofColor drawColor;
			drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
			
			fluidSolver.addColorAtIndex(index, drawColor * colorMult);
			
			if(drawParticles)
				particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
		}
		
		if(addForce)
			fluidSolver.addForceAtIndex(index, vel * velocityMult);
		
    }
}


void smokeScene::update(int width, int height){
	if(resizeFluid) 	{
		fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
		fluidDrawer.setup(&fluidSolver);
		resizeFluid = false;
	}
    
	fluidSolver.update();
}

void smokeScene::draw(int x, int y, int width, int height, bool drawToScreen){
	if(drawFluid) {
        ofClear(0);
		glColor3f(1, 1, 1);
		fluidDrawer.draw(0, 0, ofGetWidth(), ofGetHeight());
	} else {
        //		if(ofGetFrameNum()%5==0)
        fadeToColor(0, 0, 0, 0.01);
	}
	if(drawParticles)
		particleSystem.updateAndDraw(fluidSolver, ofGetWindowSize(), drawFluid);
	
    //	ofDrawBitmapString(sz, 50, 50);
    
}
//--------------------------------------------------------------
void smokeScene::mouseMoved(int x, int y){
	ofVec2f eventPos = ofVec2f(x, y);
	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
	addToFluid(mouseNorm, mouseVel, true, true);
	pMouse = eventPos;
}

