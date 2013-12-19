#pragma once

#include "ofMain.h"
//#include "ofxKinect.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    void audioOut(float * input, int bufferSize, int nChannels);
	
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofSoundStream soundStream;
    
    float 	pan,pan2;
    int		sampleRate;
    bool 	bNoise;
    float 	volume;
    
    vector <float> Audio1;
    vector <float> Audio2;
    vector <float> Audio3;
    vector <float> Audio4;
    vector <float> Audio5;
    vector <float> Audio6;
    vector <float> Audio7;
    vector <float> Audio8;
    
    
  //  ofxKinect kinect;
   	
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
	
	int nearThreshold;
	int farThreshold;
	
	int angle,PositionX,PositionY;
    
    float channel1,channel2,channel3,channel4,channel5,channel6,channel7,channel8;
    
    ofVec2f c1,c2,c3,c4,c5,c6,c7,c8;
    
    ofPoint pos1,pos2,pos3,pos4,pos5,pos6;
    int dist1,dist2,dist3,dist4,dist5,dist6;
    
    int radius;


};
