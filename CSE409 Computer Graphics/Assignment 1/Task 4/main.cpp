#include <bits/stdc++.h>
using namespace std ;
//#include <windows.h>
#include <glut.h>

#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double radius1,radius2,side,radius3, rotateangle1,rotateangle2,rotateangle3;
struct Point
{
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
    /*
    void operator = (const Point &other)const{
        x = other.x ;
        y= other.y ;
        z = other.z ;
        return ;
    }
    */
    void show(){
        cout<<x<<" "<<y<<" "<<z<<endl ;
       // cout<<(x*x+y*y+z*z)<<endl ;
    }
    Point cross(Point &otherVector){

        double x = (y*otherVector.z-z*otherVector.y) ;
        double y = (otherVector.x*z-x*otherVector.z) ;
        double z = (x*otherVector.y-otherVector.x*y) ;
        return Point(x,y,z) ;
    }
};
Point normalize(Point p){
    double scale = 1/sqrt(p.x*p.x+p.y*p.y+p.z*p.z) ;
    return p*scale ;
}
Point Rotation(Point rotationVector,Point fixedVector,double rotationAngle){
    fixedVector = normalize(fixedVector) ; // unit vector
    Point perpendicular = fixedVector.cross(rotationVector) ;
    return rotationVector*cos(rotationAngle)+perpendicular*sin(rotationAngle) ;
}

Point pos,u,l,r,normalizedu,normalizedl,normalizedr,unitDirectionVector1,unitDirectionVector2,topPoint1,topPoint2,fixedDirectionVector ;

void drawAxes()
{
	if(drawaxes==1)
	{
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
void drawHand(double radius){
    glTranslated(0,0,-radius) ;
    glScaled((5/radius),(5/radius),1) ;
    glutWireSphere(radius,15,15) ;
    glScaled(radius/5,radius/5,1) ;
}
void drawTriangle(double side) //
{
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);{
                glVertex3f(0,0,side/2) ;
                glVertex3f(-side/2,0,0) ;
                glVertex3f(side/2,0,0) ;
        }glEnd() ;
}
void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1': // look up
            rotateangle1++ ;
            unitDirectionVector1 = Rotation(unitDirectionVector1,fixedDirectionVector,(rotateangle1*2*M_PI)/360.00) ;
            unitDirectionVector1 = normalize(unitDirectionVector1) ;
           // cout<<acos(unitDirectionVector1.z/unitDirectionVector1.x)<<endl ;
            unitDirectionVector1.show() ;
            topPoint2 = topPoint1+unitDirectionVector1*(2.00*radius1) ;
            topPoint2.show() ;
            //unitDirectionVector2 = unitDirectionVector1 ;
			break;
        case '2':
             rotateangle1-- ;
            break ;
        case '3':
            rotateangle2++ ;
            unitDirectionVector1 = Rotation(unitDirectionVector2,fixedDirectionVector,rotateangle2) ;
            break ;
        case '4':
            rotateangle2-- ;
            break ;
        case '5':
            rotateangle3++ ;
            break ;
        case '6':
            rotateangle3-- ;
            break ;
		default:
			break;
	}
}



void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraHeight -= 3.0;
            pos = pos-normalizedl*2.00 ;
			break;
		case GLUT_KEY_UP:		// up arrow key
		//	cameraHeight += 3.0;
            pos = pos+normalizedl*2.00 ;
			break;

		case GLUT_KEY_RIGHT:
			//cameraAngle += 0.03;
			pos = pos+normalizedr*2.00 ;
			break;
		case GLUT_KEY_LEFT:
			pos = pos-normalizedr*2.00 ;
			break;
		case GLUT_KEY_PAGE_UP:
			pos = pos+normalizedu*2.00 ;
			break;
		case GLUT_KEY_PAGE_DOWN:
			pos = pos-normalizedu*2.00 ;
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

	/********************jinis
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
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	glRotated(rotateangle1,1,0,0) ;
//	glTranslated(0,0,-radius1) ;
	drawHand(radius1) ;
	glTranslated(0,0,-radius1) ;
	glRotated(rotateangle2,1,0,0) ;
	drawHand(radius2) ;
	glTranslated(0,0,-radius2-side/2) ;
	drawTriangle(side) ;
	glTranslated(-side/2,0,0) ;
	glRotated(rotateangle3,1,0,0) ;
	glScaled(.2,.2,1) ;
	drawHand(radius3) ;
//	glRotated(-rotateangle3,1,0,0) ;
	glTranslated(2.5*side,0,radius3) ;
	//glRotated(rotateangle3,1,0,0) ;
	drawHand(radius3) ;
	glTranslated(2*side,0,radius3) ;
	drawHand(radius3) ;

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=0;
	drawaxes=1;
	cameraHeight=150.0;
	cameraAngle=1.0;
	angle=0;
	pos.x=pos.y=100;
	pos.z=0 ;
    //////////////////////////// up vector ////////////////////
    u.x=u.y=0 ;
    u.z=1 ;
    /////////////////////////// right vector ////////////////////
    r.x=-1.00/sqrt(2) ;
    r.y=1.00/sqrt(2) ;
    r.z =0 ;
    ///////////////////////////// left vector////////////////////
    l.x=r.x ;
    l.y=r.x ;
    l.z=0 ;
	//clear the screen
	normalizedl = normalize(l) ;
	normalizedu = normalize(u) ;
	normalizedr = normalize(r) ;
	glClearColor(0,0,0,0);
	radius1=30 ;
    radius2=20 ;
    radius3=5 ;
	side=10 ;
    rotateangle1= 0 ;
    rotateangle2=0 ;
    rotateangle3=0 ;
    fixedDirectionVector.y=1 ;
    fixedDirectionVector.x=fixedDirectionVector.z=0 ;
	unitDirectionVector1.x=unitDirectionVector1.y=0 ;
	unitDirectionVector1.z=-1 ;
	unitDirectionVector2 = unitDirectionVector1 ;
	topPoint1 = Point(0,0,0) ;
	topPoint2 = Point(0,0,-2*radius1) ;
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
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Task 4 ");

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
