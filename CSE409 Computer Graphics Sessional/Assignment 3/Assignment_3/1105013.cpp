using namespace std ;
#include<bits/stdc++.h>
#include "Vector.h"
#include "Color.h"
#include "Matrix.h"
#include "Triangle.h"
#include "ReadZ.h"
#include "Clipping.h"
#include"bitmap_image.hpp"

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
    fscanf(fileToRead,"%lf %lf %lf",&rrr,&bbb,&ggg) ;
    Color BackGround(rrr,bbb,ggg) ;


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
            fscanf(fileToRead,"%lf %lf %lf",&rrr,&bbb,&ggg) ;
            fprintf(fileToWrite,"%.10f %.10f %.10f\n",rrr,bbb,ggg) ; /// printing the color to the file
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
                    fscanf(fileToRead,"%lf %lf %lf\n",&rrr,&bbb,&ggg) ;
                   // cout<<rrr<<" "<<bbb<<" "<<ggg<<endl ;
                    vec = ClippingByZ(vec,-far,-near) ;
                   // cout<<vec.size()<<endl ;
                    for(int i=0;i<(int)vec.size();i++){
                        if(i==3) fprintf(fileToWrite,"%.10f %.10f %.10f\n\n",rrr,bbb,ggg) ;
                        fprintf(fileToWrite,"%.10f %.10f %.10f\n",vec[i].x,vec[i].y,vec[i].z) ;
                    }
                    fprintf(fileToWrite,"%.10f %.10f %.10f\n\n",rrr,bbb,ggg) ;
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
   P.M[1][1]=near/tt ;
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
            M.M[3][0]=1 ;
           // M.Print() ;
            M = P*M ;
            ///M.Print() ;
            vec.push_back(Vector(M.M[0][0]/M.M[3][0],M.M[1][0]/M.M[3][0],M.M[2][0]/M.M[3][0])) ;
            fprintf(fileToWrite,"%.7f %.7f %.7f\n",M.M[0][0]/M.M[3][0],M.M[1][0]/M.M[3][0],M.M[2][0]/M.M[3][0]) ;
            countt++ ;
            if(vec.size()==3) {
                    Triangle triangle(vec[0],vec[1],vec[2]) ;
                    fscanf(fileToRead,"%lf %lf %lf",&rrr,&bbb,&ggg) ;
                    triangle.color = Color(rrr,bbb,ggg) ;
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
            zBuffer[i][j]= -1e10;
        }
   }

    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!STAGE FIVE
    for(int I=0;I<(int)triangles.size();I++){
            for(int i=0;i<screen_width;i++){
                    for(int j=0;j<screen_height;j++){
                        double Z =ReadZ(triangles[I],i,j) ;
                        if(Z>zBuffer[i][j]){
                            zBuffer[i][j] = Z ;
                            pixelBuffer[i][j]=triangles[i].color ;
                        }
                    }
            }
    }
    ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!NOW DRAW THE IMAGE
    bitmap_image image(screen_width,screen_height);  // Creating an image
    for(int i=0;i<screen_width;i++){
        for(int j=0;j<screen_height;j++){
            image.set_pixel(i,j,pixelBuffer[i][j].r,pixelBuffer[i][j].b,pixelBuffer[i][j].g);  // Setting some pixels as red
        }
    }
    image.save_image("1105013.bmp");    // Saving the image in a file
    return 0 ;
}

