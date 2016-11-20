using namespace std ;
#include<bits/stdc++.h>
#include "bitmap_image.hpp"
///                                                                 VECTOR
                    class Vector{
    public:
    double  x,y,z ;
    public:
    Vector(){
    }
    Vector(double _x,double _y,double _z){
        x=_x ; y = _y ; z=_z ;
    }
public:
    Vector operator * (const double &scale)const{
        return Vector(x*scale,y*scale,z*scale) ;
    }
    void normalize(){
        double scale = sqrt(x*x+y*y+z*z) ;
        x/=scale ;
        y/=scale ;
        z/=scale ;
    }
    Vector operator + (const Vector &other)const{
        return Vector(x+other.x,y+other.y,z+other.z) ;
    }
    Vector operator - (const Vector &other)const{
        return Vector(x-other.x,y-other.y,z-other.z) ;
    }
    Vector cross(const Vector &otherVector){
        double xx = (y*otherVector.z-z*otherVector.y) ;
        double yy = (otherVector.x*z-x*otherVector.z) ;
        double zz = (x*otherVector.y-otherVector.x*y) ;
        return Vector(xx,yy,zz) ;
    }
    double dot(const Vector &otherVector){
        return (x*otherVector.x+y*otherVector.y+z*otherVector.z) ;
    }
    double Value(){
        return sqrt(x*x+y*y+z*z) ;
    }
} ;

///                                                                 VECTOR

///                         COLOR

            class Color{
public:
        double r,g,b ;
        Color(){
        }
        Color(double _r,double _g,double _b){
            r=_r ; g=_g; b=_b ;
        }
} ;
///
#define EPS 1e-10


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
class Triangle{
public:
    Vector v0,v1,v2 ;
    Color color ;
    public:
        Triangle(){             /// Default constructor
        }
        Triangle(Vector _v0,Vector _v1,Vector _v2){
            v0=_v0 ; v1=_v1 ; v2=_v2 ;
        }
        Triangle(Matrix M1,Matrix M2,Matrix M3){
            v0=Vector(M1.M[0][0],M1.M[0][1],M1.M[0][2]) ;
            v1=Vector(M2.M[0][0],M2.M[0][1],M2.M[0][2]) ;
            v2=Vector(M3.M[0][0],M3.M[0][1],M3.M[0][2]) ;
        }
        double area(){
            Vector AB = v1-v0 ;
            Vector AC = v2-v0 ;
            //cout<<(AB.Value()*AC.Value())<<endl ;
            if(fabs(AB.Value()*AC.Value())<=EPS) return 0 ; // two points are same
            double theta = acos(AB.dot(AC)/(AB.Value()*AC.Value())) ;
           // cout<<v0.dot(v1)/(v0.Value()*v1.Value())<<" "<<theta<<endl ;
            return fabs(0.5*AB.Value()*AC.Value()*sin(theta)) ;
        }
        bool onTriangle(Vector P){
        /// checks if the point p is on the triangle or not
                double area1 = Triangle(v0,v1,P).area() ;
                double area2 = Triangle(v1,v2,P).area() ;
                double area3 = Triangle(v0,v2,P).area() ;
             //   cout<<area1<<" "<<area2<<" "<<area3<<endl ;
               // cout<<area()<<endl ;
                if(fabs(area()-area1-area2-area3)<=EPS) return 1 ;
                return 0 ;
        }
        void print(){
            printf("-----------------------------------\n") ;
            printf("%.7f %.7f %.7f\n",v0.x,v0.y,v0.z) ;
            printf("%.7f %.7f %.7f\n",v1.x,v1.y,v1.z) ;
            printf("%.7f %.7f %.7f\n",v2.x,v2.y,v2.z) ;
            printf("Color is -> %.7f %.7f %.7f\n",color.r,color.b,color.g) ;
            printf("-----------------------------------\n") ;
        }
};
/// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CLIPPING Z AXIS STARTS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

bool isInside(Vector v,double zNear,double zFar){
    if(v.z<=zFar && zNear<=v.z){
        return 1 ;
    }
    return 0 ;
}
Vector Intersection(Vector v1,Vector v2,double zNear,double zFar){
    double t1   = (zNear-v1.z)/(v2.z-v1.z) ;
    double t2   = (zFar-v1.z)/(v2.z-v1.z) ;
    Vector vec ;
    double t ;
    if(t1>=0 && t1<=1.00){
        t = t1 ;
    }
    if(t2>=0 && t2<=1.00){
        t = t2 ;
    }
    vec.x = v1.x+t*(v2.x-v1.x) ;
    vec.y = v1.y+t*(v2.y-v1.y) ;
    vec.z = v1.z+t*(v2.z-v1.z) ;
   /// printf("You  are in trouble Mazhar!!!!!!!!!!!!!!!") ;
    return vec ;
}

vector<Vector> ClippingByZ(vector<Vector>vec,double zNear,double zFar){
    vector<Vector>inside,outside,ret ;
    for(int i=0;i<(int)vec.size();i++){
        if(isInside(vec[i],zNear,zFar)){
                inside.push_back(vec[i]) ;
        }else{
            outside.push_back(vec[i]) ;
        }
    }
    if(inside.size()==3){
      ///      puts("No cliiping") ;
        // all points are inside
        for(int i=0;i<(int)inside.size();i++){
            ret.push_back(inside[i]) ;
        }
    }
    else if(inside.size()==2){
            for(int i=0;i<(int)inside.size();i++){
                Vector v = Intersection(inside[i],outside[0],zNear,zFar) ;
                ret.push_back(inside[0]) ;
                ret.push_back(inside[1]) ;
                ret.push_back(v) ;
            }
    }
    else if(inside.size()==1){
            ret.push_back(inside[0]) ;
            for(int i=0;i<(int)outside.size();i++){
                    Vector vec = Intersection(outside[i],inside[0],zNear,zFar) ;
                    ret.push_back(vec) ;
            }
    }
    else{
            /// Either it is the worst case or outside the range
    }
  //  printf("%d\n",(int)ret.size()) ;
    return ret ;
}
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!CLIPPING Z AXIS END !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



double ReadZ(Triangle T,double i,double j){
    /// find the equation of the plane
    Vector PQ = T.v0-T.v1  ;
    Vector PR = T.v0-T.v2  ;
    Vector n = PQ.cross(PR) ;
    double  Z = (n.x*(i-T.v0.x)+n.y*(j-T.v0.y))/(-n.z)+T.v0.z ; /// ?????? is it correct
    //cout<<i<<" "<<j<<" "<<Z<<endl ;
    Vector P(i,j,Z) ;
    if(T.onTriangle(P)){
        return Z ;
    }
    return 1e11 ;
}


#define EPS 1e-10


















#define MAXN 1000
#define PI acos(-1)
char fileNames[][11] = { "stage1.txt","stage2.txt","stage3.txt"} ;
char buffer[111] ;
Color pixelBuffer[MAXN][MAXN] ;
double zBuffer[MAXN][MAXN] ;
int main(void){

   FILE *fileToWrite,*fileToRead ;
   double x,y,z ,arr[5],angle,aspectRatio,fovY,near,far,rrr,bbb,ggg;
   int stageNo=0,DIMENSION=4,lineNo=0,screen_height,screen_width ;
   ///          STAGE 1
   fileToRead = fopen("scene.txt","r") ;
   fileToWrite  = fopen(fileNames[stageNo++],"w+") ;
   Matrix IdentityMatrix(DIMENSION,DIMENSION) ;
   Vector eye,up,look ;
   stack<Matrix>S ;
   stack<int>stack_track ;
   S.push(IdentityMatrix) ;
   stack_track.push(S.size()) ;

    fscanf(fileToRead,"%lf %lf %lf",&eye.x,&eye.y,&eye.z) ;
    fscanf(fileToRead,"%lf %lf %lf",&look.x,&look.y,&look.z) ;
    fscanf(fileToRead,"%lf %lf %lf",&up.x,&up.y,&up.z) ;
    fscanf(fileToRead,"%lf %lf %lf %lf",&fovY,&aspectRatio,&near,&far) ;
    fscanf(fileToRead,"%d %d",&screen_width,&screen_height) ;
    fscanf(fileToRead,"%lf %lf %lf",&rrr,&ggg,&bbb) ;
    Color BackGround(rrr,bbb,ggg) ;
   // near*=-1 ;
    //far*=-1 ;
    while(fscanf(fileToRead,"%s",buffer)!=EOF){
        if(strcmp(buffer,"triangle")==0){
             Matrix top = S.top() ;
            Matrix Mat(DIMENSION,1) ;
            for(lineNo=0;lineNo<3;lineNo++){
                for(int i=0;i<3;i++){
                    fscanf(fileToRead,"%lf",&Mat.M[i][0]) ;
                }
                Mat.M[3][0]=1 ;
              //  top.Print() ;
               //f Mat.Print() ;
                Mat = top*Mat ;
             //   Mat.Print() ;
                fprintf(fileToWrite,"%.10f %.10f %.10f\n",Mat.M[0][0],Mat.M[1][0],Mat.M[2][0]) ;
            }
            fscanf(fileToRead,"%lf %lf %lf",&rrr,&ggg,&bbb) ;
            fprintf(fileToWrite,"%.10f %.10f %.10f\n",rrr,ggg,bbb) ; /// printing the color to the file
            fprintf(fileToWrite,"\n") ;
        }
        else if(strcmp(buffer,"translate")==0){
            for(int i=0;i<3;i++){
                fscanf(fileToRead,"%lf",&arr[i]) ;
            }
            arr[3]=1 ;
            Matrix translationMatrix(DIMENSION,DIMENSION) ;
            for(int i=0;i<DIMENSION;i++){
                    translationMatrix.M[i][DIMENSION-1]=arr[i] ;
            }
         //   cout<<"Translation Matrix " ;
           // translationMatrix.Print() ;
            Matrix top = S.top() ;      ///S.pop() ;
       //     cout<<"Top"<<endl ;
          //  top.Print() ;
            top  = top*translationMatrix ;
       //     top.Print() ;
            S.push(top) ;
        }
        else if(strcmp(buffer,"scale")==0){
             for(int i=0;i<3;i++){
                fscanf(fileToRead,"%lf",&arr[i]) ;
             }
             arr[3]=1 ;
             Matrix scaleMatrix(DIMENSION,DIMENSION) ;
             for(int i=0;i<DIMENSION;i++){
                scaleMatrix.M[i][i]=arr[i] ;
             }
            // cout<<"Scaling Matrix"<<endl ;
           //  scaleMatrix.Print();
            Matrix top = S.top() ;  ///S.pop() ;
            top = top*scaleMatrix ;
            S.push(top) ;
        }
        else if(strcmp(buffer,"rotate")==0){
            fscanf(fileToRead,"%lf",&angle) ;
            angle = (PI*angle)/180.00 ;
            for(int i=0;i<DIMENSION-1;i++){
                fscanf(fileToRead,"%lf",&arr[i]) ;
            }
            // normalizing
            double scale = sqrt(arr[0]*arr[0]+arr[1]*arr[1]+arr[2]*arr[2]) ;
            for(int i=0;i<DIMENSION-1;i++){
				arr[i]/=scale ;
			}
            Matrix rotationMatrix(DIMENSION-1,DIMENSION-1) ;
            rotationMatrix = rotationMatrix*cos(angle) ;
            double sign=-1 ;
            for(int i=0;i<DIMENSION-1;i++){
                for(int j=0;j<DIMENSION-1;j++){
                    rotationMatrix.M[i][j] += (1-cos(angle))*arr[i]*arr[j] ;
                    if(i!=j){
                        for(int k=0;k<3;k++){
                            if(k!=i && k!=j){
                                rotationMatrix.M[i][j] +=(sign*arr[k]*sin(angle)) ;
                                sign*=-1 ;
                            }
                        }
                    }
                }
                sign*=-1 ;
            }

        //    rotationMatrix.Print() ;
            Matrix rotationMatriX(DIMENSION,DIMENSION) ;
            for(int i=0;i<DIMENSION-1;i++){
                for(int j=0;j<DIMENSION-1;j++){
                    rotationMatriX.M[i][j] = rotationMatrix.M[i][j] ;
                }
                rotationMatriX.M[i][DIMENSION-1]=0 ;
            }
            for(int k=0;k<DIMENSION;k++){
                rotationMatriX.M[3][k]= k==3?1:0 ;
            }
            //rotationMatriX.Print() ;
            Matrix top = S.top() ;  ///S.pop() ;
            top = top*rotationMatriX ;
            S.push(top) ;
        }
        else if(strcmp(buffer,"push")==0){
                stack_track.push(S.size()) ;
        }
        else if(strcmp(buffer,"pop")==0){
                int k = stack_track.top() ; stack_track.pop() ;
                while((int)S.size()>k){
                    S.pop() ;
                }
        }
        else if(strcmp(buffer,"end")==0){
                while(!S.empty()) S.pop() ;
                while(!stack_track.empty()) stack_track.pop() ;
                break ;
        }
   }
   fclose(fileToRead) ;
   fclose(fileToWrite) ;

   ///          STAGE 2
   fileToRead = fopen(fileNames[stageNo-1],"r") ;
   fileToWrite  = fopen(fileNames[stageNo++],"w") ;
   Vector l = look-eye ;
   l.normalize() ;
   Vector r = l.cross(up) ;
   r.normalize() ;
   Vector u = r.cross(l) ;
   u.normalize();
   //cout<<l.dot(u)<<endl ;
  // cout<<l.dot(r)<<endl ;
  // cout<<u.dot(r)<<endl ;
  // u.normalize() ;
   Matrix T(DIMENSION,DIMENSION) ;
   //cout<<eye.x<<endl ;
   T.M[0][3]=-eye.x ;
   T.M[1][3]=-eye.y ;
   T.M[2][3]=-eye.z ;
   T.M[3][3]=1 ;
  ///
  //  T.Print() ;
   Matrix R(DIMENSION,DIMENSION) ;
   ///
   R.M[0][0] = r.x ;
   R.M[0][1] = r.y ;
   R.M[0][2] = r.z ;
   R.M[0][3] = 0 ;
   ///
   R.M[1][0] = u.x ;
   R.M[1][1] = u.y ;
   R.M[1][2] = u.z ;
   R.M[1][3] = 0 ;
    ///

   R.M[2][0] = -l.x ;
   R.M[2][1] = -l.y ;
   R.M[2][2] = -l.z ;
   R.M[2][3] = 0 ;
    ///

   R.M[3][0] = 0 ;
   R.M[3][1] = 0 ;
   R.M[3][2] = 0 ;
   R.M[3][3] = 1 ;

   //T.Print() ;
  //R.Print() ;
   Matrix V = R*T ;
   //V.Print() ;
   Matrix M (DIMENSION,1) ;
   M.M[3][0]=1 ;
  /// V.Print() ;
    vector<Vector>vec ;
    int countt=0 ;
    while(fscanf(fileToRead,"%lf %lf %lf",&M.M[0][0],&M.M[1][0],&M.M[2][0])==3){
            M = V*M ;
            vec.push_back(Vector(M.M[0][0],M.M[1][0],M.M[2][0])) ;
            if(vec.size()==3){
                    fscanf(fileToRead,"%lf %lf %lf\n",&rrr,&ggg,&bbb) ;
                   // cout<<rrr<<" "<<bbb<<" "<<ggg<<endl ;
                    vec = ClippingByZ(vec,-far,-near) ;
                   // cout<<vec.size()<<endl ;
                    for(int i=0;i<(int)vec.size();i++){
                        if(i==3) fprintf(fileToWrite,"%.10f %.10f %.10f\n\n",rrr,ggg,bbb) ;
                        fprintf(fileToWrite,"%.10f %.10f %.10f\n",vec[i].x,vec[i].y,vec[i].z) ;
                    }
                    if(vec.size()>0) fprintf(fileToWrite,"%.10f %.10f %.10f\n\n",rrr,ggg,bbb) ;
                    vec.clear() ;
            }
    }

   fclose(fileToRead) ;
   fclose(fileToWrite) ;
   /// STAGE 3
   fileToRead = fopen(fileNames[stageNo-1],"r") ;
   fileToWrite  = fopen(fileNames[stageNo++],"w") ;
   double fovX =  fovY*aspectRatio ;
   double tt = near*tan((PI*(fovY/2.00))/180) ;
   double rr = near*tan((PI*(fovX/2.00))/180) ;
   Matrix P(DIMENSION,DIMENSION) ;

   P.M[0][0]=near/rr ;
   P.M[0][1]=0 ;
   P.M[0][2]=0 ;
   P.M[0][3]=0 ;

   P.M[1][0]=0 ;
   P.M[1][1]=-near/tt ;
   P.M[1][2]=0 ;
   P.M[1][3]=0 ;

   P.M[2][0]=0 ;
   P.M[2][1]=0 ;
   P.M[2][2]=-(far+near)/(far-near) ;
   P.M[2][3]=-(2*far*near)/(far-near) ;

   P.M[3][0]=0 ;
   P.M[3][1]=0 ;
   P.M[3][2]=-1 ;
   P.M[3][3]=0 ;
   ///P.Print() ;
   vec.clear() ;
   vector<Triangle>triangles ;
    while(fscanf(fileToRead,"%lf %lf %lf",&M.M[0][0],&M.M[1][0],&M.M[2][0])==3){
            M.M[3][0]=1.00 ;
           // M.Print() ;
            M = P*M ;
            ///M.Print() ;
            vec.push_back(Vector(M.M[0][0]/M.M[3][0],M.M[1][0]/M.M[3][0],M.M[2][0]/M.M[3][0])) ;
            fprintf(fileToWrite,"%.11f %.11f %.11f\n",M.M[0][0]/M.M[3][0],M.M[1][0]/M.M[3][0],M.M[2][0]/M.M[3][0]) ;
            countt++ ;
            if(vec.size()==3) {
                    Triangle triangle(vec[0],vec[1],vec[2]) ;
                    fscanf(fileToRead,"%lf %lf %lf",&rrr,&ggg,&bbb) ;
                    triangle.color = Color(rrr,ggg,bbb) ;
                    triangles.push_back(triangle) ;
                    fprintf(fileToWrite,"\n") ;
                    vec.clear() ;
            }
   }
   fclose(fileToRead) ;
   fclose(fileToWrite) ;

   for(int i=0;i<(int)triangles.size();i++){
        triangles[i].print() ;
   }

   ///puts("OKKKKKKKK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!") ;
   for(int j=0;j<screen_height;j++){
        for(int i=0;i<screen_width;i++){
            pixelBuffer[i][j] = BackGround ;
            zBuffer[i][j]= 1e10;
        }
   }

    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!STAGE FIVE
    for(int I=0;I<(int)triangles.size();I++){
            for(int i=0;i<=screen_width;i++){
                    for(int j=0;j<=screen_height;j++){

                            double II = (2.00/(screen_width))*((double)i+.5)-1 ;
                            double JJ = (2.00/(screen_height))*((double)j+.5)-1 ;
                          //  cout<<II<<" "<<JJ<<endl ;
                            double pZ =ReadZ(triangles[I],II,JJ) ;
                          //  cout<<II<<" "<<JJ<<" "<<Z<<endl ;
                            if(pZ<zBuffer[i][j]){
                                zBuffer[i][j] = pZ ;
                                pixelBuffer[i][j]=triangles[I].color ;
                        }
                    }
            }
    }
    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!NOW DRAW THE IMAGE
    bitmap_image image(screen_width,screen_height);  // Creating an image
    for(int i=0;i<=screen_width;i++){
        for(int j=0;j<=screen_height;j++){
            image.set_pixel(i,j,pixelBuffer[i][j].r,pixelBuffer[i][j].g,pixelBuffer[i][j].b);  // Setting some pixels as red
        }
    }

    image.save_image("1105013.bmp");    // Saving the image in a file
    return 0 ;
}

