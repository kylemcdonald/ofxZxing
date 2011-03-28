#include "testApp.h"

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	logo.loadImage("of-80s.png");
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		ofxZxing::Result curResult = ofxZxing::decode(cam.getPixelsRef());
		float curTime = ofGetElapsedTimef();
		if(curResult.getFound()) { // only update if we found something, avoid flickering
			result = curResult;
			lastFound = curTime;
		} else if(curTime - lastFound > 1) {  // if we haven't found anything after a second
			result = curResult; // then update anyway
		}
	}
}

void testApp::draw() {
	ofSetColor(255);
	if(result.getFound()) {
		cam.draw(0, 0);
		
		float rotation = result.getRotation();
		ofVec2f position = result.getScreenPosition();
		float size = result.getScreenSize() / logo.getWidth();
		
		ofPushMatrix();
		ofTranslate(position);
		ofRotate(rotation);
		ofScale(size, size, size);
		logo.draw(-logo.getWidth() / 2, -logo.getHeight() / 2);
		ofPopMatrix();
		
		result.draw();		
	} else {
		cam.draw(0, 0);
	}
}
