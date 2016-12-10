struct Point{

    double x,y,z,d;
    Point(){

    }
    Point(double _x,double _y,double _z){
        x=_x;
        y =_y;
        z=_z ;
    }
	Point(const Point& p){
        x=p.x;
        y =p.y;
        z=p.z ;
    }
    Point operator * (const Point &other)const{
        return Point(x*other.x,y*other.y,z*other.z) ;
    }
    Point operator * (const double &scale)const{
        return Point(x*scale,y*scale,z*scale) ;
    }
    Point operator + (const Point &other)const{
        return Point(x+other.x,y+other.y,z+other.z) ;
    }
    Point operator - (const Point &other)const{
        return Point(x-other.x,y-other.y,z-other.z) ;
    }
    double value(){
        return sqrt(x*x+y*y+z*z) ;
    }
    double dot(Point &otherVector){
        return x*otherVector.x+y*otherVector.y+z*otherVector.z ;
    }
    void show(){
        cout<<x<<" "<<y<<" "<<z<<endl ;
    }
    void normalize(){
        double scale = 1.00/sqrt(x*x+y*y+z*z) ;
        x*=scale ;
        y*=scale ;
        z*=scale ;
    }
};
Point cross(Point p1,Point p2){

        double x = (p1.y*p2.z-p1.z*p2.y) ;
        double y = (p2.x*p1.z-p1.x*p2.z) ;
        double z = (p1.x*p2.y-p2.x*p1.y) ;
        return Point(x,y,z) ;
}
Point normalize(Point p){
    double scale = 1.00/sqrt(p.x*p.x+p.y*p.y+p.z*p.z) ;
    return p*scale ;
}
Point Rotation(Point rotationVector,Point fixedVector,double rotationAngle){
    fixedVector = normalize(fixedVector)*rotationVector.value() ; // unit vector
    Point perpendicular = cross(fixedVector,rotationVector) ;
    Point ret  =  rotationVector*cos(rotationAngle)+perpendicular*sin(rotationAngle) ;
    return  ret;
}
