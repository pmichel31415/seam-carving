 #include "seam_carv.h"

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
