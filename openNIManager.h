//
//  openNIManager.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-02.
//
//

#include "ofxOpenNI.h"
#include "ofxCvGrayscaleImage.h"
#include "ofMain.h"

class openNIManager {
public:
    void setup();
	void update();
	void draw();
    void exit();
    
    bool isNewFrame();
    bool isFound();
    bool isSkeleton();
    
    void setDepthThresh();

    
	void keyPressed  (int key);

    void userEvent(ofxOpenNIUserEvent & event);
    
	ofxOpenNI openNIDevice;
    
    ofTrueTypeFont verdana;
    
    ofPixels maskPix;
    
    bool bUseDepth;
    
    int nearThresh, farThresh;
    
    ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    
};
