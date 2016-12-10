using namespace std ;
#include <bits/stdc++.h>
//#include <glut.h>
#include <windows.h>
#include "color.h"
#include "points.h"
#include "triangle.h"
#include "ray.h"
/*
void drawSquare(double Len,double z)
{
	glBegin(GL_QUADS);{
		glVertex3f(0,0,z);
		glVertex3f(Len,0,z);
		glVertex3f(Len,Len,z);
		glVertex3f(0,Len,z);
	}glEnd();
}
*/
class Square{
	public:
	Point centre ;
	double Len ;
	Color color ;

	Square(){
	}
	Square(Point _centre,double _Len,Color _color){
		centre=_centre ;
		Len=_Len ;
		color=_color ;
	}
	Point normal(){			/// in the form of ax+by+cz+d=0
			Point A = centre ;
			Point B = centre+Point(Len,0,0) ;
			Point C = centre+Point(0,Len,0) ;
			Point Normal = cross(B-A,C-A) ;
			Normal  = normalize(Normal) ;
            Normal.d = -Normal.x*A.x-Normal.y*A.y-Normal.z*A.z ;
            cout<<Normal.x<<"i+"<<Normal.y<<"j+"<<Normal.z<<"z+"<<Normal.d<<endl ;
			/// now find d
			return Normal ;
	}
	bool inside(Point p){ /// check if the point is inside the square
            Point A = centre ;
            Point B = centre+Point(Len,0,0) ;
            Point C = centre+Point(Len,Len,0) ;
            Point D = centre+Point(0,Len,0) ;

            double area1 = Triangle(p,A,B,color).area() ;
            double area2 = Triangle(p,B,C,color).area() ;
            double area3 = Triangle(p,C,D,color).area() ;
            double area4 = Triangle(p,A,D,color).area() ;
            double area5 = Triangle(A,B,C,color).area() ;
            double area6 = Triangle(A,C,D,color).area() ;

            cout<<area5+area6-area1-area2-area3-area4<<endl ;
            if(fabs(area5+area6-area1-area2-area3-area4)<1e-11){
					return 1 ;
            }else{
				return 0 ;
            }
	}
	/*
	void draw(){
		glTranslated(centre.x,centre.y,centre.z) ;
		glColor3f(color.r,color.g,color.b) ;
		drawSquare(Len,centre.z) ;
		glTranslated(-centre.x,-centre.y,-centre.z) ;
	}
	*/
};
double Find_intersection(Point planeEquation,Ray directionRay){

            double t =  -(planeEquation.d+planeEquation.z*directionRay.start.z+planeEquation.y*directionRay.start.y+planeEquation.x*directionRay.start.x)/(planeEquation.z*directionRay.direction.z+planeEquation.y*directionRay.direction.y+planeEquation.x*directionRay.direction.x) ;
            //cout<<t<<endl ;
            return t ;
}
int main(void){
    Square sq = Square(Point(20,20,0),20,Color(1,1,1)) ;
    Point pos = Point(30,30,30) ;
    Point direction = Point(0,0,-1) ;
    (pos+direction*10).show() ;
    Ray direction_ray = Ray(pos,direction) ;
    double  t = Find_intersection(sq.normal(),direction_ray) ;
    Point intersection = direction_ray.start+direction_ray.direction*t ;
    intersection.show() ;
    if(sq.inside(intersection)){
        cout<<"OK"<<endl ;
    }

   // cout<<sq.inside(Point(20,20,0))<<endl ;
   // sq.normal().show() ;
    return 0 ;
}
