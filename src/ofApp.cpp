#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofBackgroundGradient(ofColor(20), ofColor(0));

	font.load("CarroisGothic-Regular.ttf", 64);

	dampen = .4;
	ofSetFrameRate(30);

	//gui
	gui.setup("Instellingen", "settings.xml");
	gui.add(color.set("Colour", ofColor::white, 0, 255));

	//SQL
	string databasePath = ofToDataPath("enmasse.sqlite", true);
	db = new SQLite::Database(databasePath);

	//currentText = db->execAndGet"SELECT MIN(code) FROM posts").getInt();

	//userPins

	//Pin1(ofColor::blueSteel, 15);
	//Pin2(ofColor::darkBlue, 15);
	//Pin3(ofColor(100, 210, 100), 15);
	//Pin4(ofColor::magenta, 15);


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
	//curRot.getRotate(angle, axis);

//	ofRotate(angle, axis.x, axis.y, axis.z);

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
	glPointSize(1);
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


			ofVec2f offset(10, -10);
			ofDrawBitmapStringHighlight(ofToString(nearestIndex), bol.getVertex(active[i]));

			selectedPin = (active[i]);

			//social pins

			socialQuery = new SQLite::Statement(*db, "SELECT * FROM posts WHERE code=?");
			socialQuery->bind(1, selectedPin);

			while (socialQuery->executeStep()) {

				const string& currentText = socialQuery->getColumn("text");
				font.drawString(currentText, nearestVertex.x, nearestVertex.y);
			}

			socialQuery->reset(); // zet de query weer terug naar de beginstand (met ?)


		}

		//	ofLog() << "vertex = " << nearestVertex << endl;

		ofNoFill();
		//ofSetLineWidth(2);
		//	ofSetColor(ofColor::white);
		ofSetColor(ofColor::red);
		ofDrawSphere(nearestVertex, 10);






		//draw user circle
		ofFill();
		ofSetColor(color);
		ofDrawSphere(bol.getVertex(945), 20);

	}

	//draw other circles
	//circle1

	ofFill();
	ofSetColor(ofColor::darkViolet);
	Pin1.draw(bol.getVertex(820), 15);



	cam.end();
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

	//int n = bol.getNumVertices();
	//ofVec2f mouse(mouseX, mouseY);


	//for (int i = 0; i < 6; i++) {
	//	ofVec3f cur = cam.worldToScreen(bol.getVertex(820));
	//	float distance = cur.distance(mouse);
	//	if (i == 0 || distance < nearestDistance) {
	//		nearestDistance = distance;
	//		nearestVertex = cur;
	//		nearestIndex = i;
	//	}

	//	if (button = 1) {
	//		 
	//		if (mouse()
	//	}
	//}

	// maak van de muispositie een ofVec2f
	ofVec3f mouse(x, y);

	// bereken de afstand van de muis tot Pin1
	float distance = Pin1.PinPos.distance(mouse);

	// is de afstand van muispos tot Pin1 kleiner dan radius?


	if (distance < Pin1.radius) {
		clickedPin1 = true;
	}
	else {
		clickedPin1 = false;
	}

	ofLog() << "mouse clicked in Pin 1: " << clickedPin1 << endl;

	// hoera, we hebben op pin1 geklikt!




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

