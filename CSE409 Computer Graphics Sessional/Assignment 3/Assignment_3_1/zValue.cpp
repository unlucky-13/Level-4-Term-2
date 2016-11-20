using namespace std ;
#include <bits/stdc++.h>
#include "Color.h"
#include "Matrix.h"
#include "Vector.h"
#include "Triangle.h"

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
    return -1e10 ;
}
int main(void){
    Triangle TT(Vector(0,0,1),Vector(1,0,0.4),Vector(1,1,1)) ;
    cout<<ReadZ(TT,1,1) ;
    return 0 ;
}
