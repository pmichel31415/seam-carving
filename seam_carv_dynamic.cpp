# include "seam_carv_dynamic.h"

//  Table de données
struct Node{
    long data;
    int path;
};

class Table: public Vector<Node> {
    int m,n;
    
public:
    
    Table(){}
    Table(int M, int N):Vector<Node>(M*N){
        m=M;
        n=N;
        for(int i =0; i< height() ; i++){
            for(int j =0; j< width(); j++){
                operator()(i,j).path =0;
                operator()(i,j).data=0;
            }
        }
    }
    
    inline Node operator()(int i, int j) const{ return (*this)[i+m*j];} //pour les methodes utilisant des const
    inline Node& operator()(int i, int j) {return (*this)[i+m*j];}
    
    inline int width(){
        return n;
    }
    inline int height(){
        return m;
    }
    
    
    
    void generate(const Mat& energy){ // energy matrice de meme taille que l'objet, de type CV_8U
        
        int t=0;
        for(int j =0; j<width(); j++){
            for(int i = 0; i<height(); i++){
                // initialisation sur la premiere colone
                if(j==0){
                    operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)); //carré des energies --> magouilleuse style
                    
                }
                //cas general
                else{
                    //cas particulier pour la ligne sup
                    if(i==0){
                        t = which_min(operator()(i+MID,j-1).data, operator()(i+DWN,j-1).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + operator()(i+MID+t,j-1).data;
                        operator()(i,j).path = MID+t;
                    }
                    //cas particulier pour la ligne inf
                    if(i==height()-1){
                        t = which_min(operator()(i+UP,j-1).data, operator()(i+MID,j-1).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + operator()(i+UP+t,j-1).data;
                        operator()(i,j).path = UP+t;
                    }
                    //cas general
                    if(i>0 && i<height()-1){
                        t = which_min(operator()(i+UP,j-1).data, operator()(i+MID,j-1).data, operator()(i+DWN,j-1).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + operator()(i+UP+t,j-1).data;
                        operator()(i,j).path = UP+t;
                    }
                }
            }
        }
        
    } //transformer en private
    
    Path get_min_path(){
        //determination de la min de sum(energy)
        long min = operator()(0, width()-1).data;
        int i_min=0;
        for(int i=0; i<height(); i++){
            if(min > operator()(i,width()-1).data){
                min = operator()(i,width()-1).data;
                i_min = i;
            }
        }
        
        Path p;
        p.path = Vector<Pixel>(width());
        for(int j=width()-1; j>=0; j--){
            p.path[j].x = j;
            p.path[j].y = i_min;
            i_min += operator()(i_min,j).path;
        }
        
        return p;
    }
    
};

//functions returns which is min (not min value, but which is min)
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


//

//Dynamic Programming method for seam carving

void dsc(const Mat& I){ //Matrice I en N&B (uchar)
    //    Table table; // structure de données pour determiner les chemins
    Mat energy = get_energy(I); // "carte" d'energie
    Mat reslt = I.clone();
    
    imshow("original", I); waitKey();
    
    for(int i=1; i<=100; i++){
        Table table(reslt.rows, reslt.cols);
        table.generate(energy);
        Path p = table.get_min_path();
        e_carve_y(reslt, p, 0);
        e_carve_y(energy, p, 0);
    }
    imshow("images", reslt);
    waitKey();
    
    
    //    cvtColor(I, reslt, COLOR_GRAY2RGB); //matrice pour tacer un chemin (test)
    
    //passage sur le chemin
    //    for(int j=table.width()-1; j>=0; j--){
    //        reslt.at<Vec3b>(i_min,j) = Vec3b(0,0,255);
    //        i_min += table(i_min,j).path;
    //    }
    
    
    
    
}
