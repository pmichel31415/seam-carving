# include "seam_carv.h"
# include "seam_carv_dynamic.h"

Mat toGrad(const Mat& I){ //Matrice I en N&B (uchar)
    Mat grad_x, grad_y, grad;
    
    /// Gradient X
    Sobel( I, grad_x, CV_16S, 1, 0);
    /// Gradient Y
    Sobel( I, grad_y, CV_16S, 0, 1);
    
    convertScaleAbs( grad_x, grad_x );
    convertScaleAbs( grad_y, grad_y );
    addWeighted(grad_x, 0.5, grad_y, 0.5, 0, grad);
    
    return grad;
}


//function returns which is min (not min value, but which is min)
int which_min(long x, long y){
    if(MIN(x,y)==x){
        return 0;
    }
    else{
        return 1;
    }
}

int which_min(long x, long y, long z){
    if(MIN(x, y)==x && MIN(x, z)==x){
        return 0;
    }
    if((MIN(x,y)==y && MIN(y,z)==y)){
        return 1;
    }
    else{
        return 2;
    }
}

//Dynamic Programming method for seam carving

void dsc(const Mat& I){ //Matrice I en N&B (uchar)
    Table<node> table(I.rows, I.cols); // structure de données pour determiner les chemins
    Mat grad = toGrad(I); // "carte" d'energie
    
    //initialisation a 0
    for(int i =0; i<table.height(); i++){
        for(int j =0; j<table.width(); j++){
            table(i,j).path =0;
            table(i,j).data=0;
        }
    }
    
    int t=0;
    for(int j =0; j<table.width(); j++){
        for(int i = 0; i<table.height(); i++){
            // initialisation sur la premiere colone
            if(j==0){
                table(i,j).data = (long)grad.at<uchar>(i,j);// short <-- type de grad CV_16S
                
            }
            //cas general
            else{
                //cas particulier pour la ligne sup
                if(i==0){
                    t = which_min(table(i+MID,j-1).data, table(i+DWN,j-1).data);
                    table(i,j).data = (long)grad.at<uchar>(i,j) + table(i+MID+t,j-1).data;
                    table(i,j).path = MID+t;
                }
                //cas particulier pour la ligne inf
                if(i==table.height()-1){
                    t = which_min(table(i+UP,j-1).data, table(i+MID,j-1).data);
                    table(i,j).data = (long)grad.at<uchar>(i,j) + table(i+UP+t,j-1).data;
                    table(i,j).path = UP+t;
                }
                //cas general
                if(i>0 && i<table.height()-1){
                    t = which_min(table(i+UP,j-1).data, table(i+MID,j-1).data, table(i+DWN,j-1).data);
                    table(i,j).data = (long)grad.at<uchar>(i,j) + table(i+UP+t,j-1).data;
                    table(i,j).path = UP+t;
                }
            }
        }
    }
    
    Mat reslt;
    cvtColor(grad, reslt, COLOR_GRAY2RGB); //matrice pour tacer un chemin (test)
   
    //determination du chemin minimisant sum(energie)
    //calcul sur la derniere colone
    long min = table(0,table.width()-1).data;
    int i_min=0;
    for(int i=0; i<table.height(); i++){
        if(min > table(i,table.width()-1).data){
            min = table(i,table.width()-1).data;
            i_min = i;
        }
    }
   
    //passage sur le chemin
    for(int j=table.width()-1; j>=0; j--){
        reslt.at<Vec3b>(i_min,j) = Vec3b(0,0,255);
        i_min += table(i_min,j).path;
    }
    
    imshow("path", reslt);
    waitKey();
    
}
