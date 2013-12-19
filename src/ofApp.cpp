#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(54, 54, 54);
	
	// 0 output channels,
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.listDevices();
	
	//if you want to set a different device id
	//soundStream.setDeviceID(5); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
	
	int bufferSize = 1024;
	
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
    
    Audio1.assign(bufferSize, 0.0);
	Audio2.assign(bufferSize, 0.0);
    Audio3.assign(bufferSize, 0.0);
	Audio4.assign(bufferSize, 0.0);
    Audio5.assign(bufferSize, 0.0);
	Audio6.assign(bufferSize, 0.0);
   
    volume				= 20.0f;
    
	soundStream.setup(this,6, 2, 44100, bufferSize, 4);
    
    pos1 = ofPoint(160,480);
    pos2 = ofPoint(480,480);
    pos3 = ofPoint(800,480);
    pos4 = ofPoint(160,160);
    pos5 = ofPoint(480,160);
    pos6 = ofPoint(800,160);
    
    ofSetCircleResolution(120);
    
    radius = 320;

    
  }

//--------------------------------------------------------------
void ofApp::update(){
    
    dist1 = ofDist(pos1.x,pos1.y,mouseX,mouseY);
    dist2 = ofDist(pos2.x,pos2.y,mouseX,mouseY);
    dist3 = ofDist(pos3.x,pos3.y,mouseX,mouseY);
    dist4 = ofDist(pos4.x,pos4.y,mouseX,mouseY);
    dist5 = ofDist(pos5.x,pos5.y,mouseX,mouseY);
    dist6 = ofDist(pos6.x,pos6.y,mouseX,mouseY);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(125,125,255);
    ofCircle(mouseX,mouseY,10);
	
    ofSetColor(0);
    
    if (dist1 < radius*2) {
        ofCircle(pos1.x, pos1.y, (radius-dist1/2)*left[0]/2);
    }else ofCircle(pos1.x, pos1.y,1);
    
    if (dist2 < radius*2) {
        ofCircle(pos2.x, pos2.y, (radius-dist2/2)*left[0]/2);
    }else ofCircle(pos2.x, pos2.y, 1);
    
    if (dist3 < radius*2) {
        ofCircle(pos3.x, pos3.y, (radius-dist3/2)*left[0]/2);
    }else ofCircle(pos3.x, pos3.y, 1);
    
    if (dist4 < radius*2) {
        ofCircle(pos4.x, pos4.y, (radius-dist4/2)*left[0]/2);
    }else ofCircle(pos4.x, pos4.y, 1);
    
    if (dist5 < radius*2) {
        ofCircle(pos5.x, pos5.y, (radius-dist5/2)*left[0]/2);
    }else ofCircle(pos5.x, pos5.y, 1);
    
    if (dist6 < radius*2) {
        ofCircle(pos6.x, pos6.y, (radius-dist6/2)*left[0]/2);
    }else ofCircle(pos6.x, pos6.y, 1);
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(dist1),10,10);
    ofDrawBitmapString(ofToString(dist2),10,20);
    ofDrawBitmapString(ofToString(dist3),10,30);
    ofDrawBitmapString(ofToString(dist4),10,40);
    ofDrawBitmapString(ofToString(dist5),10,50);
    ofDrawBitmapString(ofToString(dist6),10,60);
    ofDrawBitmapString(ofToString(left[0]), 10,80);
}
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;
        
		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}
    
    if (key == '-' || key == '_' ){
		volume -= 0.5;
		volume = MAX(volume, 0);
	} else if (key == '+' || key == '=' ){
		volume += 0.5;
		volume = MIN(volume, 10);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
    PositionX = x;
    PositionY = y;
    
    
}
//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
        
        channel1 = ofMap(dist1, 0, radius, 1.0, 0.0);
        channel2 = ofMap(dist2, 0, radius, 1.0, 0.0);
        channel3 = ofMap(dist3, 0, radius, 1.0, 0.0);
        channel4 = ofMap(dist4, 0, radius, 1.0, 0.0);
        channel5 = ofMap(dist5, 0, radius, 1.0, 0.0);
        channel6 = ofMap(dist6, 0, radius, 1.0, 0.0);
    
        if (channel1 < 0) channel1 =0;
        if (channel2 < 0) channel2 =0;
        if (channel3 < 0) channel3 =0;
        if (channel4 < 0) channel4 =0;
        if (channel5 < 0) channel5 =0;
        if (channel6 < 0) channel6 =0;
    
		for (int i = 0; i < bufferSize; i++){
			Audio1[i] =      output[i*nChannels ] = left[i]  * volume * channel1;
			Audio1[i] =      output[i*nChannels ] = right[i] * volume * channel1;
            
            Audio2[i] =      output[i*nChannels + 1] = left[i]  * volume * channel2;
			Audio2[i] =      output[i*nChannels + 1] = right[i] * volume * channel2;
            
            Audio3[i] =      output[i*nChannels + 2] = left[i]  * volume * channel3;
			Audio3[i] =      output[i*nChannels + 2] = right[i] * volume * channel3;
            
            Audio4[i] =      output[i*nChannels + 3] = left[i]  * volume * channel4;
			Audio4[i] =      output[i*nChannels + 3] = right[i] * volume * channel4;
            
            Audio5[i] =      output[i*nChannels + 4] = left[i]  * volume * channel5;
			Audio5[i] =      output[i*nChannels + 4] = right[i] * volume * channel5;
            
            Audio6[i] =      output[i*nChannels + 5] = left[i]  * volume * channel6;
			Audio6[i] =      output[i*nChannels + 5] = right[i] * volume * channel6;
		}
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}