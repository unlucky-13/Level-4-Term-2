#define EPS 1e-10
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
            double theta = acos(v0.dot(v1)/(v0.Value()*v1.Value())) ;
            return fabs(0.5*v0.Value()*v1.Value()*sin(theta)) ;
        }
        bool onTriangle(Vector P){
        /// checks if the point p is on the triangle or not
                double area1 = Triangle(v0,v1,P).area() ;
                double area2 = Triangle(v1,v2,P).area() ;
                double area3 = Triangle(v0,v2,P).area() ;
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
