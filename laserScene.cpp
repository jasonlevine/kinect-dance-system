//
//  laserScene.cpp
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#include "laserScene.h"

void laserScene::setup(openNIManager * _oni, flowManager * _flow ){
    oni = _oni;
    flow = _flow;
    
    threshold = 1;
    lineScale = 50;
    lineWidth = 1;
    
    //init gui dims
     float dim = 16;
     float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
     float length = 255-xInit;
     
     //gui!
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());

    gui->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 60);

    gui->addSpacer(length-xInit, 1);
    gui->addSlider("threshold", 0.0, 10.0, &threshold, length-xInit, dim);
    gui->addSlider("line scale", 1.0, 100.0, &lineScale, length-xInit, dim);
    gui->addSlider("line width", 1.0, 100.0, &lineWidth, length-xInit, dim);
    
    
    
}

void laserScene::update(int width, int height){

}

void laserScene::draw(int x, int y, int width, int height, bool drawToScreen){
    ofSetLineWidth(lineWidth);
    
    for (int i = 0; i < flow->current.size(); i++) {
        if (flow->motion[i + flow->motion.size()/2].lengthSquared() > threshold) {
            
            ofVec2f featMotion = flow->motion[i + flow->motion.size()/2];
            
            float x1 = (flow->features[i].x) / 240 * height;
            float y1 = (flow->features[i].y) / 240 * height;
            float x2 = (flow->features[i].x + featMotion.x) / 240 * ofGetHeight();
            float y2 = (flow->features[i].y + featMotion.y) / 240 * ofGetHeight();
            
            //                ofLine(x1,y1,x2,y2);
            ofLine((flow->features[i] - featMotion * lineScale) / 240 * ofGetHeight(),
                   (flow->features[i] + featMotion * lineScale) / 240 * ofGetHeight());
        }
    }
}

void laserScene::toggleGUI(){

}