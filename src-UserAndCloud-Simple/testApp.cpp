#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    ofSetFrameRate(30);
    oni.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    oni.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	oni.draw();
}

//--------------------------------------------------------------
void testApp::exit(){
    oni.exit();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    oni.keyPressed(key);
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