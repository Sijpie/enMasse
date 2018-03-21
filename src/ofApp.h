#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "SQLiteCpp.h"

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

		ofxPanel gui;
		ofParameter<ofColor> color;
		
	private:

		SQLite::Database* db;
		SQLite::Statement* socialQuery;

		ofSpherePrimitive sphere;
		ofMesh bol;
		ofEasyCam cam;

//sphere
		ofQuaternion curRot;
		float dampen;
		ofVec2f lastmouse;

//social pins
		int active[6] = { 350, 450, 512, 580, 680, 720 };
		int selectedPin = 0;


};
