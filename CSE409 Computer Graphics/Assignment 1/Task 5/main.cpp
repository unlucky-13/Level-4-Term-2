#include <bits/stdc++.h>
using namespace std ;
#include <glut.h>

#define pi (2*acos(0.0))
double cameraHeight;
double cameraAngle;
int drawgrid;
int drawaxes;
double angle;
double wheel_angle ;
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
    Point cross(Point &otherVector){

        double x = (y*otherVector.z-z*otherVector.y) ;
        double y = (otherVector.x*z-x*otherVector.z) ;
        double z = (x*otherVector.y-otherVector.x*y) ;
        return Point(x,y,z) ;
    }
    double dot(Point &otherVector){
        return x*otherVector.x+y*otherVector.y+z*otherVector.z ;
    }
    void show(){
        cout<<x<<" "<<y<<" "<<z<<endl ;
    }

};
Point wheelCentre ,directionVector,fixedVector ;
Point normalize(Point p){
    double scale = sqrt(p.x*p.x+p.y*p.y+p.z*p.z) ;
    return p*scale ;
}
Point Rotation(Point rotationVector,Point fixedVector,double rotationAngle){
    Point _rotationVector = normalize(rotationVector) ;
    Point _fixedVector = normalize(fixedVector) ; // unit vector
    if(_rotationVector.dot(_fixedVector)!=0) cout<<"Thye are not perpendicur\n" ;
    Point perpendicular = _fixedVector.cross(_rotationVector) ;
    return rotationVector*cos(rotationAngle)+perpendicular*sin(rotationAngle) ;
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

void draw_wheel(double x, double y, double radius){
	int i;
	int lineAmount = 100;
	Point wheel[lineAmount][2] ;
	GLfloat twicePi = 2.0f * M_PI;
    for(i = 0; i <= lineAmount;i++) {
                wheel[i][0] = Point(x + (radius * cos(i *  twicePi / lineAmount)),y + (radius* sin(i * twicePi / lineAmount)),wheelCentre.z) ;
                wheel[i][1] = Point(x + (radius * cos(i *  twicePi / lineAmount)),y + (radius* sin(i * twicePi / lineAmount)),wheelCentre.z+5) ;
                // now rotate the unit vector
                // now add the rotated vector to this point
               // /*
          //      if(wheel_angle>360) wheel_angle-=360;
            //    Point rotatedVector = Rotation(directionVector,fixedVector,wheel_angle) ;
              //  wheel[i][0] = wheel[i][0]+rotatedVector*((wheel_angle*2*M_PI*radius)/360.00) ;
               // wheel[i][1] = wheel[i][1]+rotatedVector*((wheel_angle*2*M_PI*radius)/360.00) ;
                //*/
    }
    for(int i=0;i<lineAmount;i++){
         glBegin(GL_QUADS);
        {
            glVertex3f(wheel[i][0].x,wheel[i][0].y,wheel[i][0].z);
			glVertex3f(wheel[i][1].x,wheel[i][1].y,wheel[i][1].z);
			glVertex3f(wheel[i+1][1].x,wheel[i+1][1].y,wheel[i+1][1].z);
			glVertex3f(wheel[i+1][0].x,wheel[i+1][0].y,wheel[i+1][0].z);
        }
        glEnd();
    }
    glBegin(GL_QUADS);
        {
            glVertex3f(wheel[0][0].x,wheel[0][0].y,wheel[0][0].z);
			glVertex3f(wheel[lineAmount/2][1].x,wheel[lineAmount/2][1].y,wheel[lineAmount/2][1].z);
			glVertex3f(wheel[lineAmount/2][0].x,wheel[lineAmount/2][0].y,wheel[lineAmount/2][0].z);
            glVertex3f(wheel[0][1].x,wheel[0][1].y,wheel[0][1].z);
        }
    glEnd();

    glBegin(GL_QUADS);
        {
            glVertex3f(wheel[lineAmount/4][0].x,wheel[lineAmount/4][0].y,wheel[lineAmount/4][0].z);
			glVertex3f(wheel[3*lineAmount/4][1].x,wheel[3*lineAmount/4][1].y,wheel[3*lineAmount/4][1].z);
			glVertex3f(wheel[3*lineAmount/4][0].x,wheel[3*lineAmount/4][0].y,wheel[3*lineAmount/4][0].z);
            glVertex3f(wheel[lineAmount/4][1].x,wheel[lineAmount/4][1].y,wheel[lineAmount/4][1].z);
        }
    glEnd();

}
void keyboardListener(unsigned char key, int x,int y){
	switch(key){

		case '1': // look up
            u = Rotation(u,r,(pi/180)*3) ;
            l = Rotation(l,r,(pi/180)*3) ;
			break;
        case '2':
            u = Rotation(u,r,-(pi/180)*3) ;
            l = Rotation(l,r,-(pi/180)*3) ;
            break ;
        case '3':
            l = Rotation(l,u,(pi/180)*3) ;
            r = Rotation(r,u,(pi/180)*3) ;
            break ;
        case '4':
            l = Rotation(l,u,-(pi/180)*3) ;
            r = Rotation(r,u,-(pi/180)*3) ;
            break ;
        case 'w':
            wheelCentre.x =  wheelCentre.x+directionVector.x*2 ;
            break ;
        case 's':
            wheelCentre.x =  wheelCentre.x-directionVector.x*2 ;
            break ;
        case 'a':
            wheel_angle++ ;
            wheelCentre = Rotation(directionVector,fixedVector,wheel_angle*(360/2*M_PI)) ;
            break ;
        case 'd':
            wheel_angle-- ;
            wheelCentre = Rotation(directionVector,fixedVector,wheel_angle*(360/2*M_PI)) ;
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

	gluLookAt(pos.x,pos.y,pos.z+50, pos.x+l.x,pos.y+l.y,pos.z+l.z+50,u.x,u.y,u.z);
	//gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
	//gluLookAt(0,0,200,	0,0,0,	0,1,0);


	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();

    glRotated(wheel_angle,0,0,1) ;
	glTranslated(0,0,25) ;
	glRotated(90,1,0,0) ;
    draw_wheel(wheelCentre.x,wheelCentre.y,25) ;

	glutSwapBuffers();
}


void animate(){
	angle+=0.05;
	//codes for any changes in Models, Camera
	glutPostRedisplay();
}

void init(){
	//codes for initialization
	drawgrid=1;
	//drawaxes=1;
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

	////////////////////////////wheel............................/////////
    wheelCentre.x=wheelCentre.y=wheelCentre.z =0;
	wheel_angle= 0 ;
	directionVector.x=1 ;
	directionVector.y=directionVector.z=0 ;
	fixedVector.x=fixedVector.y=0 ;
	fixedVector.z=1 ;
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

	glutCreateWindow("Task 4");

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
