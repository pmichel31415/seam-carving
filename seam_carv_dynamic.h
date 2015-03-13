
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

#define UP -1
#define MID 0
#define DWN 1

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
    
    T operator()(int i, int j) const{ return (*this)[i+m*j];} //pour les methodes utilisant des const
    T& operator()(int i, int j) {return (*this)[i+m*j];}

    int width(){
        return n;
    }
    int height(){
        return m;
    }
};

Mat toGrad(const Mat& I);
int which_min(long x, long y);
int which_min(long x, long y, long z);
void dsc(const Mat& I);

#endif
