 #include "seam_carv.h"

Mat get_energy(const Mat& I){ //Matrice I en N&B (uchar)
    Mat grad_x, grad_y, grad;
    
    /// Gradient X
    Sobel( I, grad_x, CV_16S, 1, 0);
    /// Gradient Y
	Sobel(I, grad_y, CV_16S, 0, 1);
    
    convertScaleAbs( grad_x, grad_x );
    convertScaleAbs( grad_y, grad_y );
    addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);
    
    return grad;
}

void carve_x(Mat& src, Path seam, int nb_tries){


	int src_c;
	for (int r = 0; r < src.rows; ++r){

		for (int c = 0; c < src.cols - 1; ++c){
			if (c>seam.path[r].x){
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

void e_carve_x(Mat& src, Path seam, int nb_tries){


	int src_c;
	for (int r = 0; r < src.rows; ++r){

		for (int c = 0; c < src.cols - 1; ++c){
			if (c>seam.path[r].x){
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

void carve_y(Mat& src, Path seam, int nb_tries){


	int src_r;
	for (int c = 0; c < src.cols; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r>seam.path[c].y){
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

void e_carve_y(Mat& src, Path seam, int nb_tries){


	int src_r;
	for (int c = 0; c < src.cols; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r>seam.path[c].y){
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