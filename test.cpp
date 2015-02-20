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
double nwidth;

/// Matrices to store images
Mat src;
Mat dst;

/**
* @function on_trackbar
* @brief Callback for trackbar
*/

void on_trackbar(int, void*)
{
	alpha = (double)alpha_slider / alpha_slider_max;
	int nwidth = alpha*src.cols;
	resize(src, dst, Size(0,0),alpha,1);

	imshow("Seam carving", src);
}

int main()
{
	cout << "test" << endl;
	src = imread("Broadway_tower_edit.jpg");

	/// Create Windows
	namedWindow("Seam carving");

	alpha_slider = 0;

	
	

	/// Create Trackbars
	char TrackbarName[50];
	sprintf(TrackbarName, "Alpha x %d", alpha_slider_max);

	createTrackbar(TrackbarName, "Seam carving", &alpha_slider, alpha_slider_max, on_trackbar);

	/// Show some stuff
	on_trackbar(alpha_slider, 0);

	waitKey(0);
}
