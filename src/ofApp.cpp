#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackgroundGradient(ofColor(20), ofColor(0));

	dampen = .4;
	ofSetFrameRate(30);

	//gui
	gui.setup("Instellingen", "settings.xml");
	gui.add(color.set("Colour", ofColor::white, 0, 255));

	//SQL
	string databasePath = ofToDataPath("enmasse.sqlite", true);
	db = new SQLite::Database(databasePath);


}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	//draw gui
	gui.draw();

	//draw sphere
	//ofPushMatrix();
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 40);
	
	cam.begin();
	
	ofVec3f axis;
	float angle;
	curRot.getRotate(angle, axis);

	ofRotate(angle, axis.x, axis.y, axis.z);
	//ofSetColor(ofColor::darkBlue);
	/*ofNoFill();
	ofDrawSphere(0, 0, 0, 200);*/

	sphere.setRadius(200);
	sphere.setResolution(30);
	sphere.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	bol = sphere.getMesh();

	vector<ofVec3f> verts = bol.getVertices();

	for (int i = 0; i < verts.size(); i++) {
		verts[i].x += ofRandom(300);
		verts[i].y += ofRandom(300);
		verts[i].z += ofRandom(300);

		//bol.addColor(ofFloatColor(float(i) / bol.getVertices().size(), 0, 1.0 - (float(i) / bol.getVertices().size())));
	}

	ofSetColor(ofColor::darkBlue);
	glPointSize(10);
	bol.drawWireframe();
	bol.drawVertices();

	int n = bol.getNumVertices();
	float nearestDistance = 0;
	ofVec2f nearestVertex;
	int nearestIndex = 0;
	ofVec2f mouse(mouseX, mouseY);
	for (int i = 0; i < 6; i++) {
		ofVec3f cur = cam.worldToScreen(bol.getVertex(active[i]));
		float distance = cur.distance(mouse);
		if (i == 0 || distance < nearestDistance) {
			nearestDistance = distance;
			nearestVertex = cur;
			nearestIndex = i;

		}
	}

//	ofLog() << "vertex = " << nearestVertex << endl;

	ofNoFill();
	//ofSetLineWidth(2);
//	ofSetColor(ofColor::white);
	ofSetColor(ofColor::red);
	ofDrawCircle(nearestVertex, 20);

	ofVec2f offset(10, -10);
	ofDrawBitmapStringHighlight(ofToString(nearestIndex), nearestVertex + offset);
	
	//ofPopMatrix();
	cam.end();

//draw user circle
	/*ofFill();
	ofSetColor(color);
	ofDrawCircle(ofGetScreenWidth()/2, ofGetScreenHeight()/2, 20);*/

	//social pins
	//int sPin = sPins[selectedPin];
	//ofLog() << "pin = " << sPin << endl;

	socialQuery = new SQLite::Statement(*db, "SELECT * FROM posts WHERE code=?");
	//socialQuery->bind(1, active);
	socialQuery->reset(); // zet de query weer terug naar de beginstand (met ?)

	while (socialQuery->executeStep()) {

		//social pin1
	/*	ofSetColor(ofColor::white);
		ofDrawCircle(500, 500, 10);*/

	}


}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	//track mouse position
	ofVec2f mouse(x, y);
	ofQuaternion yRot((x - lastmouse.x)*dampen, ofVec3f(0, 1, 0));
	ofQuaternion xRot((y - lastmouse.y)*dampen, ofVec3f(-1, 0, 0));
	curRot *= yRot*xRot;
	lastmouse = mouse;

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

