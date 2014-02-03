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
    lineWidthMult = 1;
    
    bgColor.set(0.,0.,0.,1.0);
    lineColor.set(1.,1.,1.,0.5);
    

    
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
    gui->addSlider("line width", 1.0, 20.0, &lineWidth, length-xInit, dim);
    gui->addSlider("line width mult", 0.0, 2.0, &lineWidthMult, length-xInit, dim);
    gui->addSpacer(length-xInit, 1);
    gui->addLabel("BACKGROUND");
    gui->addSlider("red", 0.0, 1.0, &bgColor.r, length-xInit, dim);
    gui->addSlider("green", 0.0, 1.0, &bgColor.g, length-xInit, dim);
    gui->addSlider("blue", 0.0, 1.0, &bgColor.b, length-xInit, dim);
    gui->addSlider("alpha", 0.0, 1.0, &bgColor.a, length-xInit, dim);
    gui->addLabel("LASERS");
    gui->addSlider("red", 0.0, 1.0, &lineColor.r, length-xInit, dim);
    gui->addSlider("green", 0.0, 1.0, &lineColor.g, length-xInit, dim);
    gui->addSlider("blue", 0.0, 1.0, &lineColor.b, length-xInit, dim);
    gui->addSlider("alpha", 0.0, 1.0, &lineColor.a, length-xInit, dim);
    
    gui->setVisible(false);
}

void laserScene::update(int width, int height){

}

void laserScene::draw(int x, int y, int width, int height, bool drawToScreen){
    ofPushStyle();
    ofBackground(bgColor);
    ofSetColor(lineColor);
    ofEnableAlphaBlending();
    
    ofPushMatrix();
    ofTranslate((ofGetWidth() - ofGetHeight()) / 2, 0);
    for (int i = 0; i < flow->current.size(); i++) {
        if (flow->motion[i + flow->motion.size()/2].lengthSquared() > threshold) {
            
            ofVec2f featMotion = flow->motion[i + flow->motion.size()/2];
            ofSetLineWidth(lineWidth + featMotion.lengthSquared() * lineWidthMult);
//            float x1 = (flow->features[i].x) / 240 * height;
//            float y1 = (flow->features[i].y) / 240 * height;
//            float x2 = (flow->features[i].x + featMotion.x) / 240 * ofGetHeight();
//            float y2 = (flow->features[i].y + featMotion.y) / 240 * ofGetHeight();
            
            //                ofLine(x1,y1,x2,y2);
            ofLine((flow->features[i] - featMotion * lineScale) / 240 * height,
                   (flow->features[i] + featMotion * lineScale) / 240 * height);
        }
    }
    ofPopMatrix();
    ofDisableAlphaBlending();
    ofPopStyle();
}