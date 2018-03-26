#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	image.load("background.jpg");
	font.load("CarroisGothic-Regular.ttf", 64);
	//externe font laden

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
//draw background
	image.draw(0, 0);

//draw gui
	gui.draw();

	cam.begin();

	ofVec3f axis;
	float angle;

//main sphere
	sphere.setRadius(200);
	sphere.setResolution(30);
	sphere.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	bol = sphere.getMesh();

	//vertices aanmaken
	vector<ofVec3f> verts = bol.getVertices(); // vector aanmaken voor vertices

	for (int i = 0; i < verts.size(); i++) { //verteces aanmaken/plaatsen
		verts[i].x += ofRandom(300);
		verts[i].y += ofRandom(300);
		verts[i].z += ofRandom(300);
	}

	//draw sphere
	ofSetColor(ofColor::navy);
	glPointSize(1);
	bol.drawWireframe();
	bol.drawVertices();

	//afstand uitrekenen tussen muis en dichtsbijzijnde vertex
	int n = bol.getNumVertices();
	float nearestDistance = 0;
	ofVec2f nearestVertex;
	int nearestIndex = 0;
	ofVec2f mouse(mouseX, mouseY);

	//loop: langs de 6 punten lopen (waar de "social pins" staan) en kijken of de muis in de buurt zit
	for (int i = 0; i < 6; i++) {
		ofVec3f cur = cam.worldToScreen(bol.getVertex(active[i]));
		float distance = cur.distance(mouse);
		if (i == 0 || distance < nearestDistance) {
			nearestDistance = distance;
			nearestVertex = cur;
			nearestIndex = i;

			// wanneer de muis in de buurt van een punt zit, de index van de "dichtsbijzinde" punt (van de 6) printen naast die punt
			ofVec2f offset(10, -10);
			ofDrawBitmapStringHighlight(ofToString(nearestIndex), bol.getVertex(active[i]));

			selectedPin = (active[i]);

//social pins
			//met query alle informatie uit database ophalen. Elke text binden aan een van de 6 punten
			socialQuery = new SQLite::Statement(*db, "SELECT * FROM posts WHERE code=?");
			socialQuery->bind(1, selectedPin);

			//text gebonden aan pin printen, als de muis in de buurt zit
			while (socialQuery->executeStep()) {

				const string& currentText = socialQuery->getColumn("text");
				font.drawString(currentText, nearestVertex.x, nearestVertex.y);
				
			}

			socialQuery->reset(); // zet de query weer terug naar de beginstand (met ?)


		}

	
		// rondje tekenen om dichtsbijzijnde punt (Van de 6) als muis in de buurt zit. 
		ofNoFill();
		//ofSetLineWidth(2);
		//	ofSetColor(ofColor::white);
		ofSetColor(ofColor::red);
		ofDrawSphere(nearestVertex, 10);






//draw user circle
		//bol aanmaken op sphere, kleur wordt gekozen door GUI
		ofFill();
		ofSetColor(color);
		ofDrawSphere(bol.getVertex(945), 20);

	}

//draw other circles
	// rondjes van "andere gebruikers" aanmaken

	//Pin1
	ofFill();
	ofSetColor(ofColor::darkViolet);
	Pin1.draw(bol.getVertex(820), 15);

	//Pin2
	ofFill();
	ofSetColor(ofColor::darkMagenta);
	Pin2.draw(bol.getVertex(2100), 15);

	//Pin3
	ofFill();
	ofSetColor(ofColor::teal);
	Pin2.draw(bol.getVertex(12), 15);

	//Pin4
	ofFill();
	ofSetColor(ofColor::orangeRed);
	Pin2.draw(bol.getVertex(1300), 15);



	cam.end();
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
	// NIET WAAR




}



