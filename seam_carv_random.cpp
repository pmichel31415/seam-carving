#include "seam_carv_random.h"

Mat get_energy(const Mat& I){ //Matrice I en N&B (uchar)
	Mat grad_x, grad_y, grad;
	Mat abs_grad_x, abs_grad_y;

	/// Gradient X
	Sobel(I, grad_x, CV_16S, 1, 0);
	/// Gradient Y
	Sobel(I, grad_y, CV_16S, 0, 1);
	
	convertScaleAbs(grad_x, grad_x);
	convertScaleAbs(grad_y, grad_y);
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad, CV_16S);
	return grad;
}

int get_random_int_in_range(int inf, int sup){
	return inf + rand() % (1 + sup - inf);
}

int get_next_weighted(double x, double y, double z){

	double w1, w2, w3;
	if (x == -1){
		w1 = 0;
		w2 = 1 / y;
		w3 = 1 / z;
	}
	else if (y == -1){
		w1 = 1 / x;
		w2 = 0;
		w3 = 1 / z;
	}
	else if (z == -1){
		w1 = 1 / x;
		w2 = 1 / y;
		w3 = 0;
	}
	else{
		w1 = 1 / x;
		w2 = 1 / y;
		w3 = 1 / z;
	}

	
	double r = (double) rand() / RAND_MAX;
	double weight = w1 + w2 + w3;
	double t1 = w1 / weight;
	double t2 = (w2 + w3) / weight;
	if (r < t1){
		return -1;
	}
	else if (r < t2){
		return 0;
	}
	else{
		return 1;
	}
}

double safe_get(const Mat& E, int y, int x){
	if (y >= E.size().height || y < 0 || x >= E.size().width || x < 0){
		return -1;
	}
	else{
		return static_cast<double>(E.at<short>(y, x));
	}
}

int which_min_paul(double x, double y, double z){
	if (min(x, y) == x && min(x, z) == x){
		return -1;
	}
	if ((min(x, y) == y && min(y, z) == y)){
		return 0;
	}
	else{
		return 1;
	}
}

Path random_walk_x(const Mat& I){
	Path ret;
	Vector<Pixel> path(I.size().height);
	ret.path = path;
	
	ret.path[0].x = get_random_int_in_range(0, I.size().width - 1);
	ret.path[0].y = 0;

	ret.energy = safe_get(I,ret.path[0].y, ret.path[0].x);
	for (int y = 1; y < I.size().height; ++y){

		ret.path[y].x = ret.path[y - 1].x + get_next_weighted(safe_get(I, y, ret.path[y - 1].x - 1), safe_get(I, y, ret.path[y - 1].x), safe_get(I, y, ret.path[y - 1].x + 1));// get_random_int_in_range(-1, 1);
		//check for bounds
		if (ret.path[y].x >= I.size().width){
			ret.path[y].x = I.size().width - 1;
		}
		else if (ret.path[y].x < 0){
			ret.path[y].x = 0;
		}

		ret.path[y].y = y;

		ret.energy += safe_get(I, ret.path[y].y, ret.path[y].x);
	}

	return ret;
}

Path random_walk_y(const Mat& I){
	Path ret;
	Vector<Pixel> path(I.size().width);
	ret.path = path;

	ret.path[0].y = get_random_int_in_range(0, I.size().height - 1);
	ret.path[0].x = 0;

	ret.energy = safe_get(I, ret.path[0].y, ret.path[0].x);
	for (int x = 1; x < I.size().width; ++x){

		ret.path[x].y = ret.path[x - 1].y + get_next_weighted(safe_get(I, ret.path[x - 1].y - 1, x), safe_get(I, ret.path[x - 1].y, x), safe_get(I, ret.path[x - 1].y + 1, x));
		//check for bounds
		if (ret.path[x].y >= I.size().height){
			ret.path[x].y = I.size().height - 1;
		}
		else if (ret.path[x].y < 0){
			ret.path[x].y = 0;
		}

		ret.path[x].x = x;

		ret.energy += safe_get(I, ret.path[x].y, ret.path[x].x);
	}

	return ret;
}

Path min_energy_path(const Vector<Path>& V){
	Path ret=V[0];
	double min = ret.energy;
	for (int k = 1; k < V.size(); ++k){
		if (V[k].energy < min){
			ret = V[k];
			min = ret.energy;
		}
	}
	return ret;
}

Path random_carv_x(const Mat& E, int nb_tries){
	srand(time(NULL));
	//Mat energy = get_energy(E);
	Vector<Path> paths(nb_tries);
	for (int k = 0; k < nb_tries; k++){
		paths[k] = random_walk_x(E);
	}

	return min_energy_path(paths);
}

Path random_carv_y(const Mat& E, int nb_tries){
	srand(time(NULL));
	//Mat energy = get_energy(E);
	Vector<Path> paths(nb_tries);
	for (int k = 0; k < nb_tries; k++){
		paths[k] = random_walk_y(E);
	}

	return min_energy_path(paths);
}

Mat show_path(const Mat& src){
	Mat ret;
	cvtColor(src, ret, COLOR_GRAY2RGB);

	Path p = random_carv_y(src, 10);

	for (int k = 0; k < p.path.size(); ++k){
		ret.at<Vec3b>(p.path[k].y, p.path[k].x) = Vec3b(0, 0, 255);
	}

	return ret;
}

Mat show_all_path(const Mat& src){
	srand(time(NULL));
	Mat ret;
	cvtColor(src, ret, COLOR_GRAY2RGB);
	Mat energy = get_energy(src);
	Vector<Path> paths(100);
	for (int k = 0; k < 100; k++){
		paths[k] = random_walk_y(energy);
		for (int l = 0; l < paths[k].path.size(); ++l){
			ret.at<Vec3b>(paths[k].path[l].y, paths[k].path[l].x) = Vec3b(0, 0, 255);
		}
	}
	Path p = min_energy_path(paths);
	for (int k = 0; k < p.path.size(); ++k){
		ret.at<Vec3b>(p.path[k].y, p.path[k].x) = Vec3b(0, 255, 255);
	}
	return ret;
}

Mat carve_x(const Mat& src,Path seam, int nb_tries){
	Mat ret(src.rows, src.cols - 1, src.type(), Scalar(0, 0, 0));
	

	int src_c;
	for (int r = 0; r < src.rows; ++r){
		
		for (int c = 0; c < src.cols-1; ++c){
			if (c>seam.path[r].x){
				src_c = c + 1;
			}
			else{
				src_c = c;
			}
			
				ret.at<Vec3b>(r, c) = src.at<Vec3b>(r, src_c);
			
			
		}
	}

	return ret;

}

Mat e_carve_x(const Mat& src, Path seam, int nb_tries){
	Mat ret(src.rows, src.cols - 1, src.type(), Scalar(0, 0, 0));


	int src_c;
	for (int r = 0; r < src.rows; ++r){

		for (int c = 0; c < src.cols - 1; ++c){
			if (c>seam.path[r].x){
				src_c = c + 1;
			}
			else{
				src_c = c;
			}

			ret.at<short>(r, c) = src.at<short>(r, src_c);


		}
	}

	return ret;

}

Mat carve_y(const Mat& src, Path seam, int nb_tries){
	Mat ret(src.rows - 1, src.cols, src.type());
	

	int src_r;
	for (int c = 0; c < src.cols ; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r>seam.path[c].y){
				src_r = r + 1;
			}
			else{
				src_r = r;
			}
			
				ret.at<Vec3b>(r, c) = src.at<Vec3b>(src_r, c);
			
		}
	}

	return ret;

}

Mat e_carve_y(const Mat& src, Path seam, int nb_tries){
	Mat ret(src.rows - 1, src.cols, src.type());


	int src_r;
	for (int c = 0; c < src.cols; ++c){

		for (int r = 0; r < src.rows - 1; ++r){
			if (r>seam.path[c].y){
				src_r = r + 1;
			}
			else{
				src_r = r;
			}

			ret.at<short>(r, c) = src.at<short>(src_r, c);

		}
	}

	return ret;

}

void carve(const Mat& src, Mat& dst, int nb_tries){
	int delta_r = src.rows - dst.rows;
	int delta_c = src.cols - dst.cols;
	Path seam;
	Mat buff;
	Mat energy = get_energy(src);
	
	if (delta_r > 0 || delta_c > 0){
		for (int r = 0; r < delta_r; ++r){
			seam = random_carv_y(energy, nb_tries);
			buff = carve_y(src, seam, nb_tries);
			energy = e_carve_y(energy, seam, nb_tries);
			
		}
		for (int c = 0; c < delta_c; ++c){
			seam = random_carv_x(energy, nb_tries);
			buff = carve_x(src, seam, nb_tries);
			energy = e_carve_x(energy, seam, nb_tries);
		}
		dst = buff;
		
	}
	else{
		dst = src;
	}
}

void resize_seam_carv_random(Mat& src, double ratio_x, double ratio_y, int nb_tries){
	int n_rows = ratio_y*src.rows;
	int n_cols = ratio_x*src.cols;
	Mat ret(n_rows, n_cols, src.type(), Scalar(0, 0, 0));

	carve(src, ret, nb_tries);
	src = ret;
}