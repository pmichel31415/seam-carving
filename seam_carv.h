
#ifndef seam_carv_Header_h
#define seam_carv_Header_h

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

struct Pixel{
	int x;
	int y;
	float value;
};

struct Path{
	Vector<Pixel> path;
	double energy;
};

Mat get_energy(const Mat& I);

Mat carve_x(const Mat& src, Path seam, int nb_tries);
Mat e_carve_x(const Mat& src, Path seam, int nb_tries);
Mat carve_y(const Mat& src, Path seam, int nb_tries);
Mat e_carve_y(const Mat& src, Path seam, int nb_tries);

#endif
