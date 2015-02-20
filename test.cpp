#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;

/// Matrices to store images
Mat src1;
Mat src2;
Mat dst;

/**
* @function on_trackbar
* @brief Callback for trackbar
*/
void on_trackbar(int, void*)
{
	alpha = (double)alpha_slider / alpha_slider_max;
	beta = (1.0 - alpha);

	addWeighted(src1, alpha, src2, beta, 0.0, dst);

	imshow("Linear Blend", dst);
}

int main()
{
	cout << "test" << endl;
	Mat A = imread("Broadway_tower_edit.jpg");
	namedWindow("images");
	imshow("images", A);	waitKey();
	Mat I;
	cvtColor(A, I, CV_RGB2GRAY);
	namedWindow("images");
	imshow("images", I);	waitKey();
}
