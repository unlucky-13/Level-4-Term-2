#include<bits/stdc++.h>
using namespace std ;
//#include<windows.h>
#include <glut.h>
#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;

struct Point{

    double x,y,z;
    Point(){

    }
    Point(double _x,double _y,double _z){
        x=_x;
        y =_y;
        z=_z ;
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

Point pos,u,l,r,normalizedu,normalizedl,normalizedr;
void drawAxes(){

	if(drawaxes==1){
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);{
			glVertex3f( 100,0,0);
			glVertex3f(-100,0,0);

			glVertex3f(0,-100,0);
			glVertex3f(0, 100,0);

			glVertex3f(0,0, 100);
			glVertex3f(0,0,-100);
		}glEnd();
	}
}


void drawGrid(){
	int i;
	if(drawgrid==1){
		glColor3f(0.6, 0.6, 0.6);	//grey
		glBegin(GL_LINES);{
			for(i=-8;i<=8;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -90, 0);
				glVertex3f(i*10,  90, 0);

				//lines parallel to X-axis
				glVertex3f(-90, i*10, 0);
				glVertex3f( 90, i*10, 0);
			}
		}glEnd();
	}
}

void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '5': // tilt // r fixed
            //u.show() ;
            u = Rotation(u,l,(M_PI/180)*3) ;
            //u.show() ;
            r = Rotation(r,l,(M_PI/180)*3) ;
			break;
        case '6': // tilt // r fixed
            u = Rotation(u,l,-(M_PI/180)*3) ;
            r = Rotation(r,l,-(M_PI/180)*3) ;
           // cout<<u.dot(l)<<endl ;
            break ;
        case '1': // look right   u fixed
            l = Rotation(l,u,(M_PI/180)*3) ;
            r = Rotation(r,u,(M_PI/180)*3) ;
            break ;
        case '2': // u fixed
            l = Rotation(l,u,-(M_PI/180)*3) ;
            r = Rotation(r,u,-(M_PI/180)*3) ;
            break ;
        case '3': // r fixed
            l = Rotation(l,r,(M_PI/180)*3) ;
            u = Rotation(u,r,(M_PI/180)*3) ;
            break ;
        case '4': // r fixed
            l = Rotation(l,r,-(M_PI/180)*3) ;
            u = Rotation(u,r,-(M_PI/180)*3) ;
            break ;
		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
            pos = pos-normalize(l)*2.00 ;
			break;
		case GLUT_KEY_UP:		// up arrow key
            pos = pos+normalize(l)*2.00 ;
			break;
		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			pos = pos+normalize(r)*2.00 ;
			break;
		case GLUT_KEY_LEFT:
			pos = pos-normalize(r)*2.00 ;
			break;
		case GLUT_KEY_PAGE_UP:
			pos = pos+normalize(u)*2.00 ;
			break;
		case GLUT_KEY_PAGE_DOWN:
			pos = pos-normalize(u)*2.00 ;
			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}


void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}
void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(pos.x,pos.y,pos.z, pos.x+l.x,pos.y+l.y,pos.z+l.z,u.x,u.y,u.z);
	glMatrixMode(GL_MODELVIEW);
	/****************************
	/ Add your objects from here
	****************************/
	//add objects
    //l.dot(u) ;
	drawAxes();
	drawGrid();
	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	//angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){

	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	//cameraHeight=150.0;
	//cameraAngle=1.0;
	angle=0;
	pos.x=pos.y=100;
	pos.z=0  ;
    //////////////////////////// up vector ////////////////////
    u.x=u.y=0 ;
    u.z=1 ;
    /////////////////////////// right vector ////////////////////
    r.x=(-1.00)/sqrt(2) ;
    r.y=(1.00)/sqrt(2) ;
    r.z =0 ;
    ///////////////////////////// left vector////////////////////
    l.x=(-1.00)/sqrt(2) ;
    l.y=(-1.00)/sqrt(2) ;
    l.z=0 ;

	//clear the screen
	normalizedl = normalize(l) ;
	normalizedu = normalize(u) ;
	normalizedr = normalize(r) ;
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();
	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
  //  cout<<r.dot(l)<<endl ;
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Fully Controllable Camera");


//    Point p(0,0,1) ;
 //   Point p1 = Rotation(p,Point(0,1,0),M_PI/2) ;
  //  p1.show() ;


	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
