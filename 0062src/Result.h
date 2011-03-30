#pragma once

#include "ofMain.h"

#define OF_IPHONE_62

#ifdef OF_IPHONE_62

#include "ofxVec2f.h" //007 has ofVec2f

#endif

namespace ofxZxing {

class Result {
public:
	Result();
	Result(string text, vector<ofxVec2f> points);

	void draw();
	
	bool getFound() const;
	string getText() const;
	vector<ofxVec2f>& getPoints();
	
	ofxVec2f getScreenPosition() const;
	ofxVec2f getScreenNormal() const;
	float getScreenSize() const;
	float getRotation(ofxVec2f relativeTo = ofxVec2f(0, -1)) const;
	
	/*
	// these would be nice:
	ofVec3f getRealPosition(float physicalSize) const;
	ofVec3f getRealNormal(float physicalSize) const;
	*/
	
protected:
	bool found;
	string text;
	vector<ofxVec2f> points;
	ofxVec2f center;
	ofxVec2f screenNormal;
	float screenSize;
};

}