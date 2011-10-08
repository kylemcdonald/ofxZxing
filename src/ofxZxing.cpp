#include "ofxZxing.h"

#include "ofPixelsBitmapSource.h"

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/Exception.h>

namespace ofxZxing {

using namespace std;
using namespace zxing;
using namespace zxing::qrcode;

Result decode(ofPixels& pixels, bool adaptive = true) {
  try {
    Ref<ofPixelsBitmapSource> source(new ofPixelsBitmapSource(pixels));
    
    Ref<Binarizer> binarizer(NULL);
    if(adaptive) {
      binarizer = new HybridBinarizer(source);
    } else {
      binarizer = new GlobalHistogramBinarizer(source);
    }
		
    Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));
	QRCodeReader reader;
		DecodeHints hints;
		hints.addFormat(BarcodeFormat_QR_CODE);
		hints.setTryHarder(true);
		Ref<zxing::Result> result(reader.decode(image, hints));
		
		string text = result->getText()->getText();
		vector<ofVec2f> points;
		vector< Ref<ResultPoint> > resultPoints = result->getResultPoints();
		for(int i = 0; i < resultPoints.size(); i++) {
			Ref<ResultPoint> cur = resultPoints[i];
			points.push_back(ofVec2f(cur->getX(), cur->getY()));
		}
		return Result(text, points);
  } catch (zxing::Exception& e) {
    //cerr << "Error: " << e.what() << endl;
		return Result();
  }
}

}