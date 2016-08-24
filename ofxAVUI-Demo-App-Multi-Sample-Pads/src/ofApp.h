#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxAVUI.h"
#include "ofxOsc.h"

// listen on port 12000
#define PORT 12000
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    // Audio output and input methods
    
    void audioOut(float * output, int bufferSize, int nChannels);
    void audioIn(float * input, int bufferSize, int nChannels);
    
    int		bufferSize;
    int		sampleRate;
    
    //ofxAVUI
    ofxAVUIZone             zones[4];

    //OSC 
    ofxOscReceiver receiver;
    float vx, vy;
};
