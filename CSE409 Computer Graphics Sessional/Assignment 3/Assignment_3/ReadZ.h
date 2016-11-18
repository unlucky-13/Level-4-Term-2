double ReadZ(Triangle T,double i,double j){
    /// find the equation of the plane
    Vector PQ = T.v0-T.v1  ;
    Vector PR = T.v0-T.v2  ;
    Vector n = PQ.cross(PR) ;
    double  Z = (n.x*(i-T.v0.x)+n.y*(j-T.v0.y)-n.z*T.v0.z)/(-n.z) ; /// ?????? is it correct
    Vector P(i,j,Z) ;

    if(T.onTriangle(P)){
        return Z ;
    }
    return -1e10 ;
}
