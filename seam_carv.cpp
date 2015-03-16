#include "seam_carv.h"

Mat get_energy(const Mat& I){ //Matrice I en N&B (uchar)
	Mat grad_x, grad_y, grad;

	/// Gradient X
	Sobel(I, grad_x, CV_16S, 1, 0, 3, 1, 0, BORDER_CONSTANT);
	/// Gradient Y
	Sobel(I, grad_y, CV_16S, 0, 1, 3, 1, 0, BORDER_CONSTANT);


	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);

	return grad;
}

void carve_x(Mat& src, Path seam, int nb_tries){


	int src_c;
	for (int r = 0; r < src.rows; ++r){

		for (int c = 0; c < src.cols - 1; ++c){

			if (c >= seam.path[r].x){

				src_c = c + 1;
			}
			else{
				src_c = c;
			}

			src.at<Vec3b>(r, c) = src.at<Vec3b>(r, src_c);


		}
	}

	Rect ROI(0, 0, src.cols - 1, src.rows);
	Mat dst = src(ROI);
	src = dst;

}
void add_x(Mat& src, Path seam, int nb_tries){
	Rect ROI(0, 0, 1, src.rows);

	Mat row = src(ROI);
	hconcat(src, row, src);
	for (int r = 0; r < src.rows; ++r){

		for (signed int c = (src.cols - 1); c >= 0; --c){
			if (c > seam.path[r].x){
				src.at<Vec3b>(r, c) = src.at<Vec3b>(r, c - 1);
			}
			else if (c == seam.path[r].x){
				src.at<Vec3b>(r, c) = (src.at<Vec3b>(r, c - 1) / 2.0 + src.at<Vec3b>(r, c) / 2.0);
			}
			else{
				src.at<Vec3b>(r, c) = src.at<Vec3b>(r, c);
			}
		}
	}
}

void e_carve_x(Mat& src, Path seam, int nb_tries){


	int src_c;
	for (int r = 0; r < src.rows; ++r){

		for (int c = 0; c < src.cols - 1; ++c){

			if (c >= seam.path[r].x){

				src_c = c + 1;
			}
			else{
				src_c = c;
			}

			src.at<uchar>(r, c) = src.at<uchar>(r, src_c);


		}
	}

	Rect ROI(0, 0, src.cols - 1, src.rows);
	Mat dst = src(ROI);
	src = dst;

}

void e_add_x(Mat& src, Path seam, int nb_tries){
	Rect ROI(0, 0, 1, src.rows);

	Mat row = src(ROI);
	hconcat(src, row, src);
	for (int r = 0; r < src.rows; ++r){

		for (signed int c = (src.cols - 1); c >= 0; --c){

			if (c > seam.path[r].x){
				src.at<uchar>(r, c) = src.at<uchar>(r, c - 1);
			}
			else if (c == seam.path[r].x){
				src.at<uchar>(r, c) = uchar(255);
			}
		}
	}
}

void carve_y(Mat& src, Path seam, int nb_tries){


	int src_r;
	for (int c = 0; c < src.cols; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r >= seam.path[c].y){
				src_r = r + 1;
			}
			else{
				src_r = r;
			}

			src.at<Vec3b>(r, c) = src.at<Vec3b>(src_r, c);

		}
	}

	Rect ROI(0, 0, src.cols, src.rows - 1);
	Mat dst = src(ROI);
	src = dst;

}
void add_y(Mat& src, Path seam, int nb_tries){
	Rect ROI(0, 0, src.cols, 1);

	Mat col = src(ROI);
	vconcat(src, col, src);
	for (int c = 0; c < src.cols - 1; ++c){

		for (signed int r = (src.rows - 1); r >= 0; --r){

			if (r > seam.path[c].y){
				src.at<Vec3b>(r, c) = src.at<Vec3b>(r - 1, c);
			}
			else if (r == seam.path[c].y){
				if (r != 0){
					src.at<Vec3b>(r, c) = (src.at<Vec3b>(r - 1, c) / 2.0 + src.at<Vec3b>(r, c) / 2.0);
				}

			}

		}
	}
}

void e_carve_y(Mat& src, Path seam, int nb_tries){


	int src_r;
	for (int c = 0; c < src.cols; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r >= seam.path[c].y){
				src_r = r + 1;
			}
			else{
				src_r = r;
			}

			src.at<uchar>(r, c) = src.at<uchar>(src_r, c);

		}
	}

	Rect ROI(0, 0, src.cols, src.rows - 1);
	Mat dst = src(ROI);
	src = dst;

}

void e_add_y(Mat& src, Path seam, int nb_tries){
	Rect ROI(0, 0, src.cols, 1);

	Mat col = src(ROI);
	vconcat(src, col, src);
	for (int c = 0; c < src.cols - 1; ++c){

		for (signed int r = (src.rows - 1); r >= 0; --r){

			if (r > seam.path[c].y){
				src.at<uchar>(r, c) = src.at<uchar>(r - 1, c);
			}
			else if (r == seam.path[c].y){
				src.at<uchar>(r, c) = uchar(255);
			}
		}
	}
}


//void e_carve_y(Mat& src, Path seam, int e){
//    int src_r;
//	for (int c = 0; c < src.cols; ++c){
//        for (int r = 0; r < src.rows - 1; ++r){
//
//            if(r< seam.path[c].y - e) src_r = r;
//			if(r > seam.path[c].y + e) src_r = r + 1+2*e;
//
//			src.at<uchar>(r, c) = src.at<uchar>(src_r, c);
//
//		}
//	}
//
//	Rect ROI(0, 0, src.cols, src.rows - 1);
//	Mat dst = src(ROI);
//	src = dst;
//}

