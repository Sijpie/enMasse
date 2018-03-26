#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SQLiteCpp.h"
#include "userPins.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
	

		ofxPanel gui;
		ofParameter<ofColor> color;
		
	private:

		SQLite::Database* db;
		SQLite::Statement* socialQuery;

		ofSpherePrimitive sphere;
		ofMesh bol;
		ofEasyCam cam;

		ofImage image;
		ofTrueTypeFont font;

//sphere
		ofQuaternion curRot;
		float dampen;
		ofVec2f lastmouse;

//social pins
		int active[6] = { 800, 450, 1000, 750, 680, 900 };
		int selectedPin = 0;
		int currentText = 0;

//user pins
		userPins Pin1;
		userPins Pin2;
		userPins Pin3;
		userPins Pin4;


//mouse clicks
		bool clickedPin1;
		bool clickedPin2;

		


};
