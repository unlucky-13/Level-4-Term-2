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

