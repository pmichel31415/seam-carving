#include "gui.h"

const int width_slider_max = 100;
int width_slider;
double width_ratio;

const int height_slider_max = 100;
int height_slider;
double height_ratio;

/// Matrices to store images
Mat src;
Mat dst;

void on_trackbar_width(int, void*)
{
	if (width_slider == 0){
		width_slider = 1;
	}

	width_ratio = (double)(width_slider) / width_slider_max;

	

	resize_seam_carv_random(src, width_ratio, height_ratio,20);

	imshow("Seam carving", src);
}

void on_trackbar_height(int, void*)
{
	if (height_slider == 0){
		height_slider = 1;
	}
	height_ratio = (double)(height_slider) / height_slider_max;
	resize_seam_carv_random(src, width_ratio, height_ratio,20);

	imshow("Seam carving", src);
}

void init_gui(){
	src = imread("Broadway_tower_edit.jpg");
	//dst = imread("Broadway_tower_edit.jpg");
	/// Create Windows
	namedWindow("Seam carving", 1);

	width_slider = 100;
	height_slider = 100;
	width_ratio = 1;
	height_ratio = 1;



	/// Create Trackbars
	char WidthTrackbarName[50];
	sprintf(WidthTrackbarName, "Width : %d", width_slider_max);

	char HeightTrackbarName[50];
	sprintf(HeightTrackbarName, "Height : %d", height_slider_max);

	createTrackbar(WidthTrackbarName, "Seam carving", &width_slider, width_slider_max, on_trackbar_width);
	createTrackbar(HeightTrackbarName, "Seam carving", &height_slider, height_slider_max, on_trackbar_height);

	/// Show some stuff
	on_trackbar_width(width_slider, 0);
	on_trackbar_height(height_slider, 0);

	waitKey(0);
}