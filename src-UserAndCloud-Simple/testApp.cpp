#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup() {
//    ofSetFrameRate(30);
    
    oni.setup();
    flow.setup();
    ppm.setup();
    
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
    
    bgColor.set(1.0,0.0,0.0);
    ofBackground(bgColor);
    bgColorChanged = false;
    
    ofEnableAntiAliasing();
    
    scale = 1.0;
    offset.set(0,0);
    
    setupGUI();
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
	ofSetColor(255);
    
    if (bCalibrate) {
        oni.draw(offset.x, offset.y, scale);
//        ofSetColor(255);
//        flow.draw(0,480,640,480);
    }
    else {
        ofEnableAlphaBlending();
        ppm.begin(bgColor, bgColorChanged);
        scenes[currentScene]->draw(offset.x, offset.y, scale);
        ppm.end();
        
//        ofSetColor(255);
//        ppm.fbo.draw(0,0);
        
        ppm.draw();
        
        bgColorChanged = false;
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
            
        case 'G':
            gui->toggleVisible();
            gui2->toggleVisible();
            break;

            
        case 's':
            scenes[currentScene]->hideGUI();
            currentScene++;
            currentScene%=numScenes;
            if (currentScene == 3) oni.bUseDepth = false;
            cout << "currentScene = " << currentScene << endl;
            break;
            
        case OF_KEY_LEFT:
            offset.x-=5;
            break;
            
        case OF_KEY_RIGHT:
            offset.x+=5;
            break;
            
        case OF_KEY_UP:
            offset.y-=5;
            break;
            
        case OF_KEY_DOWN:
            offset.y+=5;
            break;
            
        case '-':
            scale-=0.1;
            break;
            
        case '=':
            scale+=0.1;
            break;
            
        case 'p':
        {
            string filename = "presets/" + ofGetTimestampString() + ".xml";
            gui->saveSettings(filename);
            break;
        }
            
        case 'f':
            ofToggleFullscreen();
            break;

    }
}

void testApp::setupGUI(){
    //init gui dims
    float dim = 16;
    float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
    
    //gui!
    gui = new ofxUICanvas(length+xInit, 0, length+xInit, ofGetHeight());
    
    gui->addFPSSlider("FPS SLIDER", length-xInit, dim*.25, 60);
    gui->addSpacer(length-xInit, 1);
    gui->addLabel("MAPPING");
    gui->add2DPad("position", ofPoint(0,1920), ofPoint(0, 1080), &offset);
    gui->addSlider("scale", 0.0, 5.0, &scale, length-xInit, dim);
    gui->addSpacer(length-xInit, 1);
    gui->addIntSlider("scene", 0, numScenes-1, &currentScene);
    gui->addLabel("BACKGROUND");
    gui->addSlider("bgred", 0.0, 1.0, &bgColor.r, length-xInit, dim);
    gui->addSlider("bggreen", 0.0, 1.0, &bgColor.g, length-xInit, dim);
    gui->addSlider("bgblue", 0.0, 1.0, &bgColor.b, length-xInit, dim);
    gui->addSpacer(length-xInit, 1);
    gui->addLabel("POST");
    gui->addSlider("fadeAmt", 0.0, 1.0, &ppm.fadeAmt, length-xInit, dim);
    gui->addLabelToggle("flip?", false);
    gui->addLabelToggle("bloom", false);
    gui->addLabelToggle("rims", false);
    gui->addLabelToggle("bloom2", false);
    gui->addLabelToggle("dof", false);
    gui->addSpacer(length-xInit, 1);
    gui->addSlider("brightness", 0.0, 10.0, &brightness, length-xInit, dim);
    gui->addSlider("contrast", 0.0, 5.0, &contrast, length-xInit, dim);
    gui->addLabelButton("reset bri/con", false);
    
    gui->setDrawBack(false);
    
    gui2 = new ofxUICanvas(length * 2 + xInit + 2, 0, length+xInit, ofGetHeight());
    
    gui2->addLabelButton("save preset", false);
    gui2->setDrawBack(false);
    
    string path = "presets/";
    ofDirectory dir(path);
    dir.allowExt("xml");
    dir.listDir();
    
    vector<string> presets;
    for(int i = 0; i < dir.numFiles(); i++){
        presets.push_back(dir.getPath(i));
        cout << dir.getPath(i) << endl;
    }
    
    ddl = gui2->addDropDownList("presets", presets);
    ddl->setAllowMultiple(false);
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
}


void testApp::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(name == "bgred" || name == "bggreen" || name == "bgblue" ) {
        bgColorChanged = true;
    }
    else if(name == "flip?")
	{
		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
        ppm.post.setFlip(toggle->getValue());
	}
    else if(name == "bloom")
	{
		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
		ppm.post[0]->setEnabled(toggle->getValue());
	}
    else if(name == "rims")
	{
		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
		ppm.post[1]->setEnabled(toggle->getValue());
	}
    else if(name == "bloom2")
	{
		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
		ppm.post[2]->setEnabled(toggle->getValue());
	}
    else if(name == "dof")
	{
		ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget;
		ppm.post[3]->setEnabled(toggle->getValue());
	}
    else if(name == "brightness")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		shared_ptr<ContrastPass> contrastPass = static_pointer_cast<ContrastPass>(ppm.renderPasses[4]);
		contrastPass->setBrightness( slider->getScaledValue() );
	}
	else if(name == "contrast")
	{
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		shared_ptr<ContrastPass> contrastPass = static_pointer_cast<ContrastPass>(ppm.renderPasses[4]);
		contrastPass->setContrast( contrast );
	}
	else if(name == "reset bri/con")
	{
		shared_ptr<ContrastPass> contrastPass = static_pointer_cast<ContrastPass>(ppm.renderPasses[4]);
		contrastPass->setContrast( 1.0 );
		contrastPass->setBrightness( 1.0 );
		contrast = 1.0;
		brightness = 1.0;
	}
    else if (name == "save preset") {
        ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
        if (button->getValue()) {
            string timeStamp = ofGetTimestampString();
            string filename = "presets/" + timeStamp + ".xml";
            gui->saveSettings(filename);
            
            string sceneFilename = filename + ".scene";
            scenes[currentScene]->saveGUI(sceneFilename);
            
            ddl->addToggle(filename);
        }
    }
    else if(name == "presets")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
            string presetName = selected[0]->getName();
            gui->loadSettings(presetName);
            scenes[currentScene]->loadGUI(presetName + ".scene");
            //reset bri/con
            shared_ptr<ContrastPass> contrastPass = static_pointer_cast<ContrastPass>(ppm.renderPasses[4]);
            contrastPass->setContrast( 1.0 );
            contrastPass->setBrightness( 1.0 );
            contrast = 1.0;
            brightness = 1.0;
        }
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