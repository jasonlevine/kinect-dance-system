//
//  lineScene.h
//  openNiSample007
//
//  Created by Jason Levine on 2014-02-03.
//
//

#include "scene.h"

class lineScene : public scene {
public:
    void setup(openNIManager * _oni, flowManager * _flow );
    void update(int width, int height);
    void draw(int x, int y, int width, int height, bool drawToScreen);
    
    openNIManager * oni;
    flowManager * flow;
    
    ofxUICanvas *gui;
    void toggleGUI(){ gui->toggleVisible(); }
    
    //------------------------------------------------------------
    
    void drawLine(ofVec3f jointA, ofVec3f jointB);
    void drawLines(ofVec3f jointA, ofVec3f jointB, float spacing);
    void drawBodyLines();
    void drawMoire();
    
    float width, height;
    float lineWidth;
    float linesWidth;
    float distanceScale;
    int alpha;
    bool llArm, rlArm,
    luArm, ruArm,
    llLeg, rlLeg,
    luLeg, ruLeg;
    
    bool bDrawBody, bDrawMoire;
    float skeletonSmoothing;
    
    ofFloatColor bgColor;
    ofFloatColor lineColor;
    
};
