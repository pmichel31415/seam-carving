#ifndef GUI_H
#define GUI_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;



/**
* @function on_trackbar_width
* @brief Callback for trackbar
*/
void on_trackbar_width(int, void*);
/**
* @function on_trackbar_height
* @brief Callback for trackbar
*/
void on_trackbar_height(int, void*);

void init_gui();


#endif