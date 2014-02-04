#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup() {
//    ofSetFrameRate(30);
    
    oni.setup();
    flow.setup();
    
    laserScene * lasers = new laserScene;
    lasers->setup(&oni, &flow);
    scenes.push_back(lasers);
    
    smokeScene * smoke = new smokeScene;
    smoke->setup(&oni, &flow);
    scenes.push_back(smoke);
    
    particleScene * particles = new particleScene;
    particles->setup(&oni, &flow);
    scenes.push_back(particles);
    
    lineScene * lines = new lineScene;
    lines->setup(&oni, &flow);
    scenes.push_back(lines);
    
    currentScene = 2;
    numScenes = 4;
    
    bDebug = false;
    bCalibrate = true;
    
    ofBackground(25);
    ofEnableAntiAliasing();
    
    scale = 1.0;
    xOffset = yOffset = 0.0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    oni.update();
    
    if(oni.isNewFrame()) {
        if ((oni.isSkeleton() && oni.isFound()) || oni.bUseDepth) {
            flow.update(oni.maskPix);
        }
    }
    
    scenes[currentScene]->update(ofGetWidth(),ofGetHeight());

}

//--------------------------------------------------------------
void testApp::draw(){
	if (bCalibrate) {
        ofSetColor(255);
        oni.draw(xOffset, yOffset, scale);
//        ofSetColor(255);
//        flow.draw(0,480,640,480);
    }
    else {
        scenes[currentScene]->draw(xOffset, yOffset, scale);
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
        {
            particleScene * myParticles = static_cast<particleScene*>(scenes[2]);
            myParticles->bDebug = true;
            break;
        }
            
        case 'c':
            bCalibrate = !bCalibrate;
            break;
            
        case 'g':
            scenes[currentScene]->toggleGUI();
            break;
            
        case 's':
            currentScene++;
            currentScene%=numScenes;
            if (currentScene == 3) oni.bUseDepth = false;
            cout << "currentScene = " << currentScene << endl;
            break;
            
        case OF_KEY_LEFT:
            xOffset-=5;
            break;
            
        case OF_KEY_RIGHT:
            xOffset+=5;
            break;
            
        case OF_KEY_UP:
            yOffset-=5;
            break;
            
        case OF_KEY_DOWN:
            yOffset+=5;
            break;
            
        case '-':
            scale-=0.1;
            break;
            
        case '=':
            scale+=0.1;
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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