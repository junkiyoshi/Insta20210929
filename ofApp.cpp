#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableDepthTest();
	ofSetLineWidth(2);
	ofSetCircleResolution(60);

	ofColor color;
	for (int i = 0; i < 6; i++) {

		vector<unique_ptr<Particle>> flock;
		color.setHsb(ofMap(i, 0, 6, 0, 255), 192, 255);
		for (int k = 0; k < 50 + i * 50; k++) {

			auto particle = make_unique<Particle>(color);
			flock.push_back(move(particle));
		}

		this->flock_list.push_back(move(flock));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& flock : this->flock_list) {

		for (auto& particle : flock) {

			particle->update(flock);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	this->cam.begin();
	ofRotateY(ofGetFrameNum() * -0.5);
	ofTranslate(ofGetWidth() * -0.5, ofGetHeight() * -0.5, 700);
	
	int i = 0;
	for (auto& flock : this->flock_list) {

		ofTranslate(0, 0, -200);

		ofColor color;
		color.setHsb(ofMap(i++, 0, 6, 0, 255), 192, 255);
		ofNoFill();
		ofSetColor(color);
		ofDrawCircle(glm::vec2(ofGetWidth() * 0.5, ofGetHeight() * 0.5), 300);

		for (auto& particle : flock) {

			particle->draw();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}