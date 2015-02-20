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
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);

	return grad;
}

int get_random_int_in_range(int inf, int sup){
	return inf + rand()*(sup - inf);
}

Path random_walk_x(const Mat& I){
	Path ret;
	Vector<Pixel> path(I.size().height);
	ret.path = path;
	
	ret.path[0].x = get_random_int_in_range(0, I.size().width - 1);
	ret.path[0].y = 0;

	ret.energy = static_cast<double>(I.at<uchar>(ret.path[0].x, ret.path[0].y));
	for (int y = 1; y < I.size().height; y++){

		ret.path[y].x = ret.path[y - 1].x + get_random_int_in_range(-1, 1);
		//check for bounds
		if (ret.path[y].x >= I.size().width){
			ret.path[y].x = I.size().width - 1;
		}
		else if (ret.path[y].x < 0){
			ret.path[y].x = 0;
		}

		ret.path[y].y = y;

		ret.energy += static_cast<double>(I.at<uchar>(ret.path[y].x, ret.path[y].y));
	}

	return ret;
}

Path random_walk_y(const Mat& I){
	Path ret;
	Vector<Pixel> path(I.size().width);
	ret.path = path;

	ret.path[0].y = get_random_int_in_range(0, I.size().height - 1);
	ret.path[0].x = 0;

	ret.energy = I.at<float>(ret.path[0].x, ret.path[0].y);
	for (int x = 1; x < I.size().width; x++){

		ret.path[x].y = ret.path[x - 1].y + get_random_int_in_range(-1, 1);
		//check for bounds
		if (ret.path[x].y >= I.size().height){
			ret.path[x].y = I.size().height - 1;
		}
		else if (ret.path[x].y < 0){
			ret.path[x].y = 0;
		}

		ret.path[x].x = x;

		ret.energy += I.at<float>(ret.path[x].x, ret.path[x].y);
	}

	return ret;
}

Path min_energy_path(const Vector<Path>& V){
	Path ret=V[0];
	double min = ret.energy;
	for (int k = 1; k < V.size(); k++){
		if (V[k].energy < min){
			ret = V[k];
			min = ret.energy;
		}
	}
	return ret;
}

Path random_carv_x(const Mat& I, unsigned int nb_tries){
	Mat energy = get_energy(I);
	Vector<Path> paths;
	for (int k = 0; k < nb_tries; k++){
		paths[k] = random_walk_x(I);
	}

	return min_energy_path(paths);
}

Path random_carv_y(const Mat& I, unsigned int nb_tries){
	Mat energy = get_energy(I);
	Vector<Path> paths;
	for (int k = 0; k < nb_tries; k++){
		paths[k] = random_walk_y(I);
	}

	return min_energy_path(paths);
}

void carve(const Mat& src, Mat& dst){

}