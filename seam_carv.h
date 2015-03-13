
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

void carve_x(Mat& src, Path seam, int nb_tries);
void e_carve_x(Mat& src, Path seam, int nb_tries);
void carve_y(Mat& src, Path seam, int nb_tries);
void e_carve_y(Mat& src, Path seam, int nb_tries);

#endif
