
#ifndef seam_carv_dynamic_Header_h
#define seam_carv_dynamic_Header_h

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

# include "seam_carv.h"

using namespace cv;
using namespace std;

#define UP -1
#define MID 0
#define DWN 1

int which_min(long x, long y);
int which_min(long x, long y, long z);
void dsc(const Mat& I);






#endif
