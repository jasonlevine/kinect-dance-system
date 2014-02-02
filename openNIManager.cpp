//
//  openNIManager.cpp
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#include "openNIManager.h"

//--------------------------------------------------------------
void openNIManager::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();
    
    
    openNIDevice.setUseMaskPixelsAllUsers(true);
    openNIDevice.setUsePointCloudsAllUsers(false);
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
    
}

//--------------------------------------------------------------
void openNIManager::update(){
    openNIDevice.update();
}

//--------------------------------------------------------------
void openNIManager::draw(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    ofPushMatrix();
    // use a blend mode so we can see 'through' the mask(s)
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    // get number of current users
    int numUsers = openNIDevice.getNumTrackedUsers();
    
    // iterate through users
    for (int i = 0; i < numUsers; i++){
        
        // get a reference to this user
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(i);
        
        // draw the mask texture for this user
        //        user.drawMask();
        
        // PIXEL REFERENCE
        maskPix = user.getMaskPixels();
        // do something with the pixels...
        
        if (maskPix.isAllocated()) {
            ofImage maskImg = maskPix;
            maskImg.draw(0, 480);
        }
        maskPix.clear();
        
    }
    
    ofDisableBlendMode();
    ofPopMatrix();
    
    // draw some info regarding frame counts etc
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);
}

//--------------------------------------------------------------
void openNIManager::userEvent(ofxOpenNIUserEvent & event){
    // show user event messages in the console
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void openNIManager::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void openNIManager::keyPressed(int key){
    
}
