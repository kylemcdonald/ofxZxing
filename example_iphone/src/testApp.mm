#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	// register touch events
	ofRegisterTouchEvents(this);
	
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//iPhoneAlerts will be sent to this.
	ofxiPhoneAlerts.addListener(this);
	
	ofBackground(127,127,127);

	//reader = new QRCodeReader();
	imagePicker = new ofxiPhoneImagePicker();
	
	alreadyShowing = false;
	
}

//--------------------------------------------------------------
void testApp::update(){

	
	if(imagePicker->imageUpdated){
		
		if (cameraPixels == NULL){
            cameraPixels = new unsigned char [imagePicker->width * imagePicker->height*4];
        }

        // invert the image
        for (int i = 0; i < imagePicker->height; i++){
            memcpy(cameraPixels+(imagePicker->height-i-1)*imagePicker->width*4, imagePicker->pixels+i*imagePicker->width*4, imagePicker->width*4);
        }
		
		//img.setFromPixels(imagePicker->pixels, imagePicker->width, imagePicker->height, OF_IMAGE_COLOR_ALPHA, true);
		img.setFromPixels(cameraPixels, imagePicker->width, imagePicker->height, OF_IMAGE_COLOR_ALPHA, true);
		img.setImageType(OF_IMAGE_COLOR);
		img.resize(320, 460); // just setting this to be actual screen height
		
		ofxZxing::Result curResult = ofxZxing::decode(img.getPixelsRef(), true);
		//float curTime = ofGetElapsedTimef();
		if(curResult.getFound()) { // only update if we found something, avoid flickering
			cout << " found one! " << endl;
			cout << curResult.getText() << endl;
			
			NSString *errorMessage = [NSString stringWithCString:curResult.getText().c_str()
														encoding:[NSString defaultCStringEncoding]];
			NSURL *url = [NSURL URLWithString:errorMessage];
			if (![[UIApplication sharedApplication] openURL:url]) // in the future we'll wanna check these
				NSLog(@"%@%@",@"Failed to open url:",[url description]);
			
		} else {
			cout << " nothing found " << endl;
		}
		
		alreadyShowing = false;
        imagePicker->imageUpdated = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(127,127,127);
	if (cameraPixels != NULL){
		img.draw(0, 0);
	}
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown(ofTouchEventArgs &touch)
{
	cout << " touchDown " << endl;
	if(!alreadyShowing)
	{
		imagePicker->openCamera();
		alreadyShowing = true;
	}
}

//--------------------------------------------------------------
void testApp::touchMoved(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchUp(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::touchDoubleTap(ofTouchEventArgs &touch){

}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

