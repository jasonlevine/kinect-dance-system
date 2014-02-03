//
//  flowManager.cpp
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#include "flowManager.h"

//--------------------------------------------------------------
void flowManager::setup() {

    pyrLk.setMaxFeatures( 300 );
    pyrLk.setQualityLevel( 0.01 );
    pyrLk.setMinDistance( 4 );
    pyrLk.setWindowSize( 32 );
    pyrLk.setMaxLevel( 3 );
    
    ofPixels firstFrame;
    firstFrame.allocate(320, 240, 1);
    
    pyrLk.calcOpticalFlow(firstFrame, firstFrame);
    
    features.clear();
    motion.clear();
}

//--------------------------------------------------------------
void flowManager::update(ofPixels &maskPix){
    
    if (ofGetFrameNum() % 60 == 0) pyrLk.resetFeaturesToTrack();
    
    features = pyrLk.getFeatures();
    motion = pyrLk.getMotion();
    
    pyrLk.calcOpticalFlow(maskPix);
    
}

//--------------------------------------------------------------
void flowManager::draw(int x, int y, int w, int h){

    pyrLk.draw(x,y,w,h);
    
}
