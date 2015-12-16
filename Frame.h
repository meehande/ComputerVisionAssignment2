#pragma once
#include "MedianBackground.h"

class Frame{
public:
	int id;
	Mat* original_frame;
	Mat* median_background;
	Mat* median_foreground;
	Mat* median_difference;

	Frame(){
		original_frame = new Mat();
		median_background = new Mat();
		median_difference = new Mat();
		median_foreground = new Mat();
	}

};