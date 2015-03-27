//
// ===============================================================================
//                                To do list
// ===============================================================================
//
//
// - transfrom y_carve... en epaississant
// - finir le forward computing
// - ameliorer la structure => creer une classe seam_carv ?
// - regler les coeff sur get_energy
//


# include "seam_carv_dynamic.h"

//  Table de données
struct Node{
    long data;
    int path;
    
};
// ===============================================================================
//                                Table class for dsc
// ===============================================================================

class Table: public Vector<Node> {
    int m,n;
    
    static const int UP = -1;
    static const int LFT = -1;
    static const int MID = 0;
    static const int DWN = 1;
    static const int RGT = 1;
    
private:
    
    inline Node operator()(int i, int j) const{ return (*this)[i+m*j];} //pour les methodes utilisant des const
    inline Node& operator()(int i, int j) {return (*this)[i+m*j];}
    
    inline int width(){
        return n;
    }
    inline int height(){
        return m;
    }
    
    struct Min{
        long value;
        int index;
    };
    
    static Min which_min(long x, long y){
        Min min;
        if(MIN(x,y)==x){
            min.index =0;
            min.value =x;
        }
        else{
            min.index=1;
            min.value =y;
        }
        return min;
    }
    
    static Min which_min(long x, long y, long z){
        Min min;
        if(MIN(x, y)==x && MIN(x, z)==x){
            min.index =0;
            min.value =x;
        }
        if((MIN(x,y)==y && MIN(y,z)==y)){
            min.index =1;
            min.value =y;
        }
        if((MIN(x,z)==z && MIN(y,z)==z)){
            min.index =2;
            min.value =z;
        }
        return min;
    }

// ============================ Backward seamcarving ============================
    
//  Backward seamcarving horizontal
    
    void back_generate_h(const Mat& energy){ // energy matrice de meme taille que l'objet, de type CV_8U
        
        Min t;
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
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = MID+t.index;
                    }
                    //cas particulier pour la ligne inf
                    if(i==height()-1){
                        t = which_min(operator()(i+UP,j-1).data, operator()(i+MID,j-1).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = UP+t.index;
                    }
                    //cas general
                    if(i>0 && i<height()-1){
                        t = which_min(operator()(i+UP,j-1).data, operator()(i+MID,j-1).data, operator()(i+DWN,j-1).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = UP+t.index;
                    }
                }
            }
        }
        
    }
    
    Path get_min_path_h(){
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
    
// Backward seamcarving vertical
    
    void back_generate_v(const Mat& energy){ // energy matrice de meme taille que l'objet, de type CV_8U
        
        Min t;
        for(int i =0; i<height(); i++){
            for(int j = 0; j<width(); j++){
                // initialisation sur la premiere ligne
                if(i==0){
                    operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)); //carré des energies --> magouilleuse style
                    
                }
                //cas general
                else{
                    //cas particulier pour la col gauche
                    if(j==0){
                        t = which_min(operator()(i-1,j+MID).data, operator()(i-1,j+RGT).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = MID+t.index;
                    }
                    //cas particulier pour la col droite
                    if(j==width()-1){
                        t = which_min(operator()(i-1,j+LFT).data, operator()(i-1,j+MID).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = LFT+t.index;
                    }
                    //cas general
                    if(j>0 && j<width()-1){
                        t = which_min(operator()(i-1,j+LFT).data, operator()(i-1,j+MID).data, operator()(i-1,j+RGT).data);
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = LFT+t.index;
                    }
                }
            }
        }
        
    }
    
    Path get_min_path_v(){
        //determination de la min de sum(energy)
        long min = operator()(height()-1, 0).data;
        int j_min=0;
        for(int j=0; j<width(); j++){
            if(min > operator()(height()-1,j).data){
                min = operator()(height()-1,j).data;
                j_min = j;
            }
        }
        
        Path p;
        p.path = Vector<Pixel>(height());
        for(int i=height()-1; i>=0; i--){
            p.path[i].x = j_min;
            p.path[i].y = i;
            j_min += operator()(i,j_min).path;
        }
        
        return p;
    }
    
// ============================ Forward seamcarving ============================
    
//  Forward seamcarving vertical
    
    int cr(const Mat& I,int i, int j){ //matrice de l'image en uchar
        // ne pas appeler en j = width - 1 ou i=0
        if(j==0) return abs((int)I.at<uchar>(i-1,j)-(int)I.at<uchar>(i,j+1));
        return ( abs((int)I.at<uchar>(i,j+1)-(int)I.at<uchar>(i,j-1)) + abs((int)I.at<uchar>(i-1,j)-(int)I.at<uchar>(i,j+1)) );
    }
    
    int cl(const Mat& I,int i, int j){ //matrice de l'image en uchar
        // ne pas appeler en i= 0 ou j=0
        if(j== width()-1) return abs((int)I.at<uchar>(i-1,j)-(int)I.at<uchar>(i,j-1));
        return ( abs((int)I.at<uchar>(i,j+1)-(int)I.at<uchar>(i,j-1)) + abs((int)I.at<uchar>(i-1,j)-(int)I.at<uchar>(i,j-1)) );
    }
    
    int cv(const Mat& I,int i, int j){ //matrice de l'image en uchar
        if(i==0 && j==width()-1) return 0;
        if(i==0 && j==0) return 0 ;
        return abs((int)I.at<uchar>(i,j+1)-(int)I.at<uchar>(i,j-1));
    }
    
    void forw_generate_v(const Mat& energy){ // energy matrice de meme taille que l'objet, de type CV_8U
        Min t;
        for(int i =0; i<height(); i++){
            for(int j = 0; j<width(); j++){
                // initialisation sur la premiere ligne
                if(i==0){
                    operator()(i,j).data = (long)(energy.at<uchar>(i,j)) + cv(energy, i, j) ;
                }
                
                //cas general
                else{
                    //cas particulier pour la col gauche
                    if(j==0){
                        t = which_min(operator()(i-1,j+MID).data + cv(energy, i, j), operator()(i-1,j+RGT).data + cr(energy, i, j));
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = MID+t.index;
                    }
                    //cas particulier pour la col droite
                    if(j==width()-1){
                        t = which_min(operator()(i-1,j+LFT).data + cl(energy, i, j), operator()(i-1,j+MID).data + cv(energy, i, j));
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = LFT+t.index;
                    }
                    //cas general
                    if(j>0 && j<width()-1){
                        t = which_min(operator()(i-1,j+LFT).data + cl(energy, i, j), operator()(i-1,j+MID).data + cv(energy, i, j) , operator()(i-1,j+RGT).data + cr(energy, i, j));
                        operator()(i,j).data = (long)(energy.at<uchar>(i,j)*energy.at<uchar>(i,j)) + t.value;
                        operator()(i,j).path = LFT+t.index;
                    }
                }
            }
        }
        
    }
    
    
public:

// ============================ Constructor ============================
    
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
    
// ============================ Accesseurs ============================
    
    Path search_path_h(const Mat& energy){ //Mat I en uchar
        back_generate_h(energy);
        return get_min_path_h();
    }
    
    Path search_path_v(const Mat& energy){ //Mat I en uchar
        back_generate_v(energy);
        return get_min_path_v();
    }
    
};



// ===============================================================================
//                                Launching function for dsc
// ===============================================================================



//Dynamic Programming methods for seam carving

Mat back_dsc(const Mat& I, Size wanted){ //Matrice I en RGB
    Mat energy;
    cvtColor(I, energy, CV_RGB2GRAY);
    energy = get_energy(energy); // "carte" d'energie
    Mat reslt = I.clone();
    
    int diff;
    
    if((diff = I.rows - wanted.height) > 0){
        for(int i=1; i<=diff; i++){
            Table table(reslt.rows, reslt.cols);
            Path p = table.search_path_h(energy);
            carve_y(reslt, p, 0);
            e_carve_y(energy, p, 0);
        }
    }
    
    if((diff = I.cols - wanted.width) > 0){
        for(int i=1; i<=diff; i++){
            Table table(reslt.rows, reslt.cols);
            Path p = table.search_path_v(energy);
            carve_x(reslt, p, 0);
            e_carve_x(energy, p, 0);
        }
    }
    
    if((diff = wanted.height - I.rows) > 0){
        for(int i=1; i<=diff; i++){
            Table table(reslt.rows, reslt.cols);
            Path p = table.search_path_h(energy);
            add_y(reslt, p, 0);
            e_add_y(energy, p, 0);
        }
    }
    
    if((diff = wanted.width - I.cols) > 0){
        for(int i=1; i<=diff; i++){
            Table table(reslt.rows, reslt.cols);
            Path p = table.search_path_v(energy);
            add_x(reslt, p, 0);
            e_add_x(energy, p, 0);
        }
    }
    
    return reslt;
}

Mat forw_dsc(const Mat& I, Size wanted){
    return I;
}
    
