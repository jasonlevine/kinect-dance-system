//
//  openNIManager.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#include "ofxOpenNI.h"
#include "ofMain.h"

class openNIManager {
public:
    void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);

    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    
    ofTrueTypeFont verdana;
    
    ofPixels maskPix;
    
};
