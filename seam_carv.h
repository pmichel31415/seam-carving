
#ifndef seam_carv_Header_h
#define seam_carv_Header_h

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>

using namespace cv;
using namespace std;

#define LEFT -1
#define MID 0
#define RIGHT 1

struct node{
    long data;
    int path;
};

//  Table de données
template <typename T>
class Table: public Vector<T> {
    int m,n;
    
public:
    Table(){}
    Table(int M, int N):Vector<T>(M*N){
        m=M;
        n=N;
    }
    
    T operator()(int i, int j) const{ return (*this)[i+m*j];}
    T& operator()(int i, int j) {return (*this)[i+m*j];}
    
};

Mat toGrad(const Mat& I);

#endif
