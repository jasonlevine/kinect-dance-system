//
//  particleScene.cpp
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-03.
//
//

#include "particleScene.h"

void particleScene::setup(openNIManager * _oni, flowManager * _flow ){
    oni = _oni;
    flow = _flow;
    
    particles.setup(200, ofGetWidth(), ofGetHeight(), true, false);
    
    velMult = 0.375;
    threshold = 1;
    bReverse = false;
    bGenerate = true;
    fadeAmt = 255;
    brightness = 1.0;
	contrast = 1.0;
    
    
    
    //init gui dims
    float dim = 16;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
    
    //gui!
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    //gui!
    gui = new ofxUICanvas(0, 0, length+xInit, ofGetHeight());
    
    gui->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 60);
    
    gui->addSpacer(length-xInit, 1);
    gui->addLabelToggle("generate/control", &bGenerate);
    gui->addIntSlider("totalParticles", 1, 2000, 200, length-xInit, dim);
    gui->addIntSlider("maxParticles", 2, 5000, &particles.maxParticles, length-xInit, dim);
    gui->addSlider("threshold", 0.0, 100.0, &threshold, length-xInit, dim);
    gui->addSlider("velMult", 0.01, 2.0, &velMult, length-xInit, dim);
    gui->addLabelToggle("reverse", &bReverse);
    gui->addLabelToggle("bounce", &particles.bounce);
    gui->addLabelToggle("wrap", &particles.wrap);
    gui->addIntSlider("attractionRadius", 1, 1000, &particles.attractionRadius, length-xInit, dim);
    gui->addSlider("attractionForce", 0.0, 5.0, &particles.attractionForce, length-xInit, dim);
    gui->addIntSlider("repulsionRadius", 1, 100, &particles.repulsionRadius, length-xInit, dim);
    gui->addSlider("repulsionForce", 0.0, 5.0, &particles.repulsionForce, length-xInit, dim);
    
    gui->addSpacer(length-xInit, 1);
    gui->addSlider("baseSize", 1, 10, &particles.baseSize, length-xInit, dim);
    gui->addSlider("sizeMod", 0.0001, 0.1, &particles.sizeMod, length-xInit, dim);
    gui->addIntSlider("tailLength", 1, 25, &particles.tailLength, length-xInit, dim);
    gui->addIntSlider("fadeAmt", 0, 255, &fadeAmt, length-xInit, dim);
    gui->addIntSlider("alpha", 0, 255, &particles.alpha, length-xInit, dim);
    gui->addLabelToggle("circles", &particles.drawCircles);
    gui->addLabelToggle("lines", &particles.drawLines);
    gui->addSpacer(length-xInit, 1);
    
    gui->addLabelToggle("flip?", false);
    gui->addLabelToggle("bloom", false);
    gui->addLabelToggle("rims", false);
    gui->addLabelToggle("bloom2", false);
    gui->addLabelToggle("dof", false);
    gui->addSpacer(length-xInit, 1);
    gui->addSlider("brightness", 0.0, 10.0, &brightness, length-xInit, dim);
    gui->addSlider("contrast", 0.0, 5.0, &contrast, length-xInit, dim);
    gui->addLabelButton("reset bri/con", false);
    
//    ofAddListener(gui->newGUIEvent,this,&particleScene::guiEvent);
    gui->setVisible(false);
}

void particleScene::update(int width, int height){
    if (bGenerate) {
        for (int i = 0; i < flow->features.size(); i++) {
            if (flow->motion[i + flow->motion.size()/2].lengthSquared() > threshold) {
                ofVec2f featMotion = flow->motion[i + flow->motion.size()/2];
                
                particles.add(flow->features[i], featMotion * velMult);
                
            }
        }

    }
    else {
        if (flow->motion.size() > 0) {
            for (int i = 0; i < particles.particles.size(); i++) {
                ofVec2f featMotion = flow->motion[i % flow->motion.size()/2 + flow->motion.size()/2];
                if (bReverse) featMotion *= -1;
                particles.particles[i]->vel+= featMotion * velMult;
            }
        }
    }
    
    ofVec2f centroid(0,0);
    for (int i = 0; i < flow->features.size(); i++) {
        centroid+=flow->features[i];
    }
    centroid/=flow->features.size();
    
    particles.update(centroid.x, centroid.y);
}

void particleScene::draw(float x, float y, float scale){
    ofBackground(0);
    
    ofPushMatrix();
    ofTranslate(x, y);
    ofTranslate(160, 120);
    ofScale(scale, scale);
    ofTranslate(-160, -120);
    particles.draw();
    ofPopMatrix();

//    if (bDebug) {
//        for (int i = 0; i < particles.particles.size(); i++) {
//            cout << "particle[" << i << "].pos = " << particles.particles[i]->pos << endl;
//        }
//        bDebug = false;
//    }
//    bDebug = false;
}