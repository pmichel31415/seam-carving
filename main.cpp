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
  
    Mat Img = imread(argv[1]);
    Size original(Img.cols, Img.rows);
    
    int method = stoi((string)argv[4]) ;
   
    Size wanted(stoi( ((string)argv[2]).substr(0, ((string)argv[2]).find("x")) ), stoi( ((string)argv[2]).substr(((string)argv[2]).find("x") +1, ((string)argv[2]).length())));
    
    Mat I;
    Size scaled;
    resize(Img, I, scaled = scale(Img, wanted));
    
    switch(method) {
        case 1:{
            imwrite((string)argv[3], dsc(I, wanted));
            break;
        }
        case 2:{
            break;
        }
            
        default:{
            cout << "Error : not a correct method" << endl;
            break;
        }
    }
    
}
