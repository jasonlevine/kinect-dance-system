#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "openNIManager.h"
#include "flowManager.h"
#include "postProcManager.h"

#include "laserScene.h"
#include "smokeScene.h"
#include "particleScene.h"
#include "lineScene.h"

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

    openNIManager oni;
    flowManager flow;
    postProcManager ppm;
    
    
    ofxUICanvas * gui;
    
    
    bool bDebug;
    bool bCalibrate;
    
    int currentScene;
    int numScenes;
    vector<scene*> scenes;
    
    //mapping
    float scale;
//    float xOffset, yOffset;
    ofPoint offset;
    
};

#endif
