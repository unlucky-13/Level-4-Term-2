#define EPS 1e-10
class Triangle{
    Point x,y,z ;
    Color color ;
public:
    Triangle(){

    }
    Triangle(Point _x,Point _y,Point _z,Color _color){
        x=_x ; y=_y ; z=_z ;
        color=_color ;
    }
    ///*
    void draw(){
        glColor3f(color.r,color.g,color.b) ;
        glBegin(GL_TRIANGLES);
        glVertex3f(x.x,x.y,x.z);
        glVertex3f(y.x,y.y,y.z);
        glVertex3f(z.x,z.y,z.z);
        glEnd();
    }
    //*/
    double area(){
            Point AB = y-x ;
            Point AC = z-x ;
            //cout<<(AB.Value()*AC.Value())<<endl ;
            if(fabs(AB.value()*AC.value())<=EPS) return 0 ; // two points are same
            double theta = acos(AB.dot(AC)/(AB.value()*AC.value())) ;
           // cout<<v0.dot(v1)/(v0.Value()*v1.Value())<<" "<<theta<<endl ;
            return fabs(0.5*AB.value()*AC.value()*sin(theta)) ;
        }
};
