
#ifndef seam_carv_random_Header_h
#define seam_carv_random_Header_h

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

#define LEFT -1
#define MID 0
#define RIGHT 1

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

int get_random_int_in_range(int inf, int sup);

Path random_walk_x(const Mat& I);
Path random_walk_y(const Mat& I);

Path min_energy_path(const Vector<Path>& V);

Path random_carv_x(const Mat& I, unsigned int nb_tries);
Path random_carv_y(const Mat& I, unsigned int nb_tries);

void carve(const Mat& src, Mat& dst);

void seam_carv_random_resize(const Mat& src, Mat& dst, double fx, double fy);

#endif
