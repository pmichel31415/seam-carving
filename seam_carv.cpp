#include "seam_carv.h"

Mat toGrad(const Mat& I){ //Matrice I en N&B (uchar)
    Mat grad_x, grad_y, grad;
    Mat abs_grad_x, abs_grad_y;
    
    /// Gradient X
    Sobel( I, grad_x, CV_16S, 1, 0);
    /// Gradient Y
    Sobel( I, grad_y, CV_16S, 0, 1);
    
    convertScaleAbs( grad_x, grad_x );
    convertScaleAbs( grad_y, grad_y );
    addWeighted( grad_x, 0.5, grad_y, 0.5, 0, grad);
    
    return grad;
}


//function returns which is min (not min value, but which is min)
int which_min(int x, int y){
    if(min(x,y)==x){
        return 0;
    }
    else{
        return 1;
    }
}

int which_min(int x, int y, int z){
    if(min(x,y,z)==x){
        return 0;
    }
    if((min(x,y,z)==y)){
        return 1;
    }
    else{
        return 2;
    }
}

//Dynamic Programming method for seam carving

void dsc(const Mat& I){
    Table<node> table(I.rows, I.cols);
    Mat grad = toGrad(I);
    
    for(int i =0; i<table.width(); i++){
        for(int j =0; j<table.height(); j++){
            table(i,j).path =0;
            table(i,j).data=0;
        }
    }
    
    int t=0;
    for(int j =0; j<table.width(); j++){
        for(int i =0; i<table.height(); i++){
            if(j==0){
                table(i,j).data = grad.at<short>(i,j);// short <-- type de gradd CV_16S
                table(i,j).path = 0;
            }
            else{
                //most left col, have no upper-left pixel
                if(i==0){
                    t = which_min(table(i+MID,j-1).data, table(i+RIGHT,j-1).data);
                    table(i,j).data = grad.at<short>(i,j) + table(i+MID+t,j-1).data;
                    table(i,j).path = MID+t;
                }
                //most right col, have no upper-right pixel
                if(i==table.width()-1){
                    t = which_min(table(i+LEFT,j-1).data, table(i+MID,j-1).data);
                    table(i,j).data = grad.at<short>(i,j) + table(i+LEFT+t,j-1).data;
                    table(i,j).path = LEFT+t;
                }
                else{
                    t = which_min(table(i+LEFT,j-1).data, table(i+MID,j-1).data, table(i+RIGHT,j-1).data);
                    table(i,j).data = grad.at<short>(i,j) + table(i+LEFT+t,j-1).data;
                    table(i,j).path = LEFT+t;
                }
            }
        }
    }
    
    //dispensable
    Vector<long> sums(table.height());
    for(int i=0; i<table.height(); i++){
        sums[i] = table(i,table.width()-1).data;
    }
    
    //sort sums --> find path from min sums
    
}
