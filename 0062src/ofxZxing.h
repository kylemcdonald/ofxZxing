#pragma once

#include "Result.h"


namespace ofxZxing {
	
Result decode(unsigned char* pixels, int height, int width, bool adaptive = true);

}