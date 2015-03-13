
#ifndef seam_carv_random_Header_h
#define seam_carv_random_Header_h

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <time.h> 
#include "seam_carv.h"

using namespace cv;
using namespace std;

#define LEFT -1
#define MID 0
#define RIGHT 1




int get_random_int_in_range(int inf, int sup);
int get_next_weighted(double weight_1, double weight_2, double weight_3);
double safe_get(const Mat& E, int y, int x);
int which_min_paul(int x, int y, int z);

Path random_walk_x(const Mat& I);
Path random_walk_y(const Mat& I);

Path min_energy_path(const Vector<Path>& V);

Path random_carv_x(const Mat& E, int nb_tries);
Path random_carv_y(const Mat& E, int nb_tries);

Mat show_path(const Mat& src, Path p);
Mat show_all_path(const Mat& src);


void carve(Mat& src, int d_rows, int d_cols, int nb_tries){

void resize_seam_carv_random(Mat& src, double ratio_x, double ratio_y, int nb_tries){

#endif
