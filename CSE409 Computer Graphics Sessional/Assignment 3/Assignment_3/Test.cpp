#include<bits/stdc++.h>
#include "Vector.h"
#define EPS 1e-10
using namespace std ;
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
    return ret ;
}

int main(void){
    Vector v1(4,5,-3) ;
    Vector v2(3,1,-13) ;
    Vector v3(5,1,-11) ;
    vector<Vector>vv ;
    vv.push_back(v1) ;
    vv.push_back(v2) ;
    vv.push_back(v3) ;

    vv = ClippingByZ(vv,-5,10) ;
    for(int i=0;i<(int)vv.size();i++){
        cout<<vv[i].x<<" "<<vv[i].y<<" "<<vv[i].z<<endl ;
    }
    return 0 ;
}
