#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup() {
//    ofSetFrameRate(30);
    
    oni.setup();
    flow.setup();
    
    lasers = new laserScene;
    lasers->setup(&oni, &flow);
    
    smoke = new smokeScene;
    smoke->setup(&oni, &flow);
    
    bDebug = false;
    bCalibrate = true;
    
    ofBackground(25);
    ofEnableAntiAliasing();
    
}

//--------------------------------------------------------------
void testApp::update(){
    oni.update();
    
    if(oni.isNewFrame()) {
        if ((oni.isSkeleton() && oni.isFound()) || oni.bUseDepth) {
            flow.update(oni.maskPix);
        }
    }
    
    smoke->update(0,0);

}

//--------------------------------------------------------------
void testApp::draw(){
	if (bCalibrate) {
        oni.draw();
        ofSetColor(255);
        flow.draw(0,480,640,480);
    }
    else {
        smoke->draw(0, 0, ofGetWidth(), ofGetHeight(), true);
    }
    
}

//--------------------------------------------------------------
void testApp::exit(){
    oni.exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    oni.keyPressed(key);
    
    switch (key) {
        case 'd':
            bDebug = true;
            break;
            
        case 'c':
            bCalibrate = !bCalibrate;
            break;
            
        case 'g':
            lasers->toggleGUI();
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    smokeScene * mySmoke = static_cast<smokeScene*>(smoke);
    mySmoke->mouseMoved(x,y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}