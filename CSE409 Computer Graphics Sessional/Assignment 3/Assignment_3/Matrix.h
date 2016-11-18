class Matrix{
public:
    double x,y,z ;
    Color color ;
    int row,col ;
    double **M ;
    Matrix(int row,int col){
        this->row = row ;
        this->col = col ;
        M = new double*[row] ;
        for(int i=0;i<row;i++){
            M[i] = new double[col] ;
            for(int j=0;j<col;j++){
                M[i][j] = (i==j) ? 1 : 0 ;
            }
        }
    }
    Matrix(){ // default constructor
        row = col=100 ;
        M = new double*[row] ;
        for(int i=0;i<row;i++){
            M[i] = new double[col] ;
            for(int j=0;j<col;j++){
                    M[i][j] = (i==j) ? 1 : 0 ;
            }
        }
    }
public: // functions
    void Print() ;
    Matrix operator * (const Matrix &Mat) ;
    Matrix operator * (const double &scale) ;
    Matrix operator + (const Matrix &Mat) ;
} ;

void Matrix::Print(){
    cout<<"Row -> "<<row<<" " <<" col -> "<< col<<endl ;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%10f",M[i][j]) ;
        }
        cout<<endl ;
    }
    return ;
}

Matrix Matrix::operator*(const Matrix &Mat){
        ///Print() ;
        if(col!=Mat.row){
            throw "MATRIX DIMENSION MISMATCH" ;
        }else{
            Matrix ret(row,Mat.col) ;
            for(int i=0;i<row;i++){
                for(int j=0;j<Mat.col;j++){
                        ret.M[i][j]=0 ;
                        for(int k=0;k<col;k++){
                            ret.M[i][j]+= Mat.M[k][j]*M[i][k] ;
                        }
                    //    cout<<ret.M[i][j]<<endl ;
                }
            }
            return ret;
        }
}
Matrix Matrix::operator*(const double &scale){

            Matrix ret(row,col) ;
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                        ret.M[i][j]=M[i][j]*scale ;
                }
            }
            return ret;
}

Matrix Matrix::operator+(const Matrix &Mat){
        if(Mat.col!=col || Mat.row!=row){
            throw "MATRIX DIMENSION MISMATCH" ;
        }else{
            Matrix ret(Mat.row,Mat.col) ;
            for(int i=0;i<Mat.row;i++){
                for(int j=0;j<Mat.col;j++){
                    ret.M[i][j]=M[i][j]+Mat.M[i][j] ;
                }
            }
            return ret;
        }
}
