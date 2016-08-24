#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ENVIRONMENT AND MAXIMILIAN
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofBackground(0,0,0);
    sampleRate 	= 44100; /* Audio sampling rate */
    bufferSize	= 512; /* Audio buffer size */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    //ZONE 1 SETUP
    //parameters: name, x, y, width, background color, foreground color, sound filename, sound buffer size
    zones[0].setup("buttonZone", 20, 40, 450, ofColor(100, 100, 100, 150), ofColor(0, 255, 255, 255), "synth.wav", bufferSize);
    //ZONE 1 UI
    zones[0].addUI(new ofxAVUIButton("Sample Trigger", ofxAVUIZone::TRIGGER_PLAY), 100);
    //toggle - caption, parameter name
    zones[0].addUI(new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING), 60);
    //add VisualCircles - the constructor argument is the number of circles
    zones[0].addVisual(new ofxAVUIVisualCircles(10), ofColor(0, 255, 0, 196));
    // Add pad element
    zones[0].addUI(new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME), 150);

    //ZONE 2 SETUP
    zones[1].setup("buttonZone", 20, 400, 450, ofColor(100, 100, 100, 150), ofColor(0, 255, 255, 255), "drumloop.wav", bufferSize);
    zones[1].addUI(new ofxAVUIButton("Sample Trigger", ofxAVUIZone::TRIGGER_PLAY), 100);
    zones[1].addUI(new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING), 60);
    zones[1].addVisual(new ofxAVUIVisualCircles(10), ofColor(255, 0, 0, 196));
    zones[1].addUI(new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME), 150);

    //ZONE 3 SETUP
    zones[2].setup("buttonZone", 550, 40, 450, ofColor(100, 100, 100, 150), ofColor(0, 255, 255, 255), "bass.wav", bufferSize);
    zones[2].addUI(new ofxAVUIButton("Sample Trigger", ofxAVUIZone::TRIGGER_PLAY), 100);
    zones[2].addUI(new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING), 60);
    zones[2].addVisual(new ofxAVUIVisualCircles(10), ofColor(255, 255, 0, 196));
    zones[2].addUI(new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME), 150);

    //ZONE 4 SETUP
    zones[3].setup("buttonZone", 550, 400, 450, ofColor(100, 100, 100, 150), ofColor(0, 255, 255, 255), "sound.wav", bufferSize);
    zones[3].addUI(new ofxAVUIButton("Sample Trigger", ofxAVUIZone::TRIGGER_PLAY), 100);
    zones[3].addUI(new ofxAVUIToggle("Looping", ofxAVUIZone::TOGGLE_LOOPING), 60);
    zones[3].addVisual(new ofxAVUIVisualCircles(10), ofColor(0, 0, 255, 196));
    zones[3].addUI(new ofxAVUIXYPad("Pad", ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::TRIGGER_PLAY, ofxAVUIZone::PITCH, ofxAVUIZone::VOLUME), 150);

    
    
    
    //START SOUND
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup*/
    
    //Set-up OSC receiver
    receiver.setup(PORT);
}


//--------------------------------------------------------------
void ofApp::update(){

    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/wek/outputs"){
            vx = m.getArgAsFloat(0);
            vy = m.getArgAsFloat(1);
        } else {
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            cout << msg_string << endl;
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i = 0; i < 4; i++) {
        zones[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    
    for (int i = 0; i < bufferSize; i++){
        
        output[i*nChannels    ] = 0;
        output[i*nChannels + 1] = 0;
        
        for (int k=0; k<4; k++) {
            zones[k].play(i);
            output[i*nChannels    ] += zones[k].getOutput(0);
            output[i*nChannels + 1] += zones[k].getOutput(1);
        }
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        /* you can also grab the data out of the arrays*/
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
