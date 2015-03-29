#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "gui.h"

#include "seam_carv.h"
#include "seam_carv_dynamic.h"
#include "seam_carv_random.h"

using namespace cv;
using namespace std;


int main (int argc, char *argv[]){
//    argv[1] -> path entree
//    argv[2] -> dim image de sortie
//    argv[3] -> path de sortie
//    argv[4] -> methode
//    argv[5] -> nb_tries si methode = 3
  
    Mat Img = imread(argv[1]);
    Size original(Img.cols, Img.rows);
    
    int method = atoi(argv[4]) ;
   
    Size wanted(atoi( ((string)argv[2]).substr(0, ((string)argv[2]).find("x")).c_str() ), atoi( ((string)argv[2]).substr(((string)argv[2]).find("x") +1, ((string)argv[2]).length()).c_str()));
    
    Mat I;
    Size scaled;
    resize(Img, I, scaled = scale(Img, wanted));
    
    time_t start = time(NULL);
    
    switch(method) {
        case 1:{
            imwrite((string)argv[3], back_dsc(I, wanted));
            break;
        }
        case 2:{
            imwrite((string)argv[3], forw_dsc(I, wanted));
            break;
        }
        case 3:{
            resize_seam_carv_random(I, wanted, atoi(argv[5]));
            imwrite((string)argv[3], I);
            break;
        }
            
        default:{
            cout << "Error : not a correct method" << endl;
            break;
        }
    }
    
	cout << "Duration : " << (time(NULL) - start) << endl;
    
}
