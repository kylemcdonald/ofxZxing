#pragma once

#include "ofMain.h"

namespace ofxZxing {

class Result {
public:
	Result();
	Result(string text, vector<ofVec2f> points);

	void draw();
	
	bool getFound() const;
	string getText() const;
	vector<ofVec2f>& getPoints();
	
	ofVec2f getScreenPosition() const;
	ofVec2f getScreenNormal() const;
	float getScreenSize() const;
	float getRotation(ofVec2f relativeTo = ofVec2f(0, -1)) const;
	
	/*
	// these would be nice:
	ofVec3f getRealPosition(float physicalSize) const;
	ofVec3f getRealNormal(float physicalSize) const;
	*/
	
protected:
	bool found;
	string text;
	vector<ofVec2f> points;
	ofVec2f center;
	ofVec2f screenNormal;
	float screenSize;
};

}