#include "Result.h"

namespace ofxZxing {

Result::Result() :
	found(false) {
}

Result::Result(string text, vector<ofxVec2f> points) :
	found(true), text(text), points(points) {	
	if(points.size() > 1) {
		screenNormal = points[1] - points[0];
	}
	if(points.size() > 2) {
		center = (points[0] + points[2]) / 2;
	}
	screenSize = screenNormal.length();
}

	
#ifndef OF_IPHONE_62
	
void drawTextBox(string text, ofxVec2f position, ofColor fgColor = ofColor::white, ofColor bgColor = ofColor::black) {

	ofPushStyle();
	
	int border = 4;
	ofSetColor(bgColor);
	ofRect(
		(int) position.x - border,
		(int) position.y - 4 - border,
		text.length() * 8 + (border * 2),
		8 + (border * 2));
		
	ofSetColor(fgColor);
	ofDrawBitmapString(text, position);
	
	ofPopStyle();
}
	
#endif

void Result::draw() {

	ofSetColor(1, 0, 0);
	ofSetLineWidth(3);

#ifdef OF_IPHONE_62
	
	GLfloat triVertices[points.size()*2];
	
	for(int i = 0; i < points.size(); i++) {
		triVertices[i] = points[i].x;
		triVertices[i+1] = points[i].y;
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, triVertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	
#endif
	
#ifndef OF_IPHONE_62
	ofPushStyle();
	
	ofSetColor(ofColor::red);
	ofSetLineWidth(3);
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < points.size(); i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	
	
	for(int i = 0; i < points.size(); i++) {
		drawTextBox(ofToString(i), points[i]);
	}
	
	drawTextBox(text, center);
	
	ofPopStyle();
#endif
	
}
	
bool Result::getFound() const {
	return found;
}

string Result::getText() const {
	return text;
}

vector<ofxVec2f>& Result::getPoints() {
	return points;
}

ofxVec2f Result::getScreenPosition() const {
	return center;
}

ofxVec2f Result::getScreenNormal() const {
	return screenNormal;
}

float Result::getScreenSize() const {
	return screenSize;
}

float Result::getRotation(ofxVec2f relativeTo) const {
	return relativeTo.angle(screenNormal);
}

}