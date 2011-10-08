#pragma once

#include "Result.h"
#include "ofPixels.h"

namespace ofxZxing {

	Result decode(ofPixels& pixels, bool adaptive);

}