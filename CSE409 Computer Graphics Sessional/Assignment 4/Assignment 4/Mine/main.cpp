#include<windows.h>
#include<glut.h>
#include "consts.hpp"

//#include "Camera.h"

#include "object.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "cube.hpp"
#include "world.hpp"

#include "bitmap_image.hpp"

#include "Tracer.h"

//Camera cam;


int drawgrid,drawaxes,draw ;
void drawSquare(float a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }
    glEnd();
}

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

void drawGrid()
{
    int i;

    {
        glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_LINES);
        {
            for(i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;


                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);


                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
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



void keyboardListener(unsigned char key, int x,int y)
{
    switch(key)
    {

    case '1':

        cam.yaw(.8);
        break;
    case '2':

        cam.yaw(-.8);
        break;
    case '3':
        cam.pitch(-.8);
        break;
    case '4':
        cam.pitch(.8);
        break;
    case '5':
        cam.roll(.8);
        break ;
    case '6':
        cam.roll(-.8);
        break ;
    case '0':
        initTracing(cam) ;
        break ;
    default:
        break;
    }

}


void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
        cam.slide(0,0,.8);
       //

        break;
    case GLUT_KEY_UP:
        cam.slide(0,0,-.8);
        //
        break;

    case GLUT_KEY_RIGHT:
        cam.slide(.8,0,0);
        break;
    case GLUT_KEY_LEFT:
        cam.slide(-.8,0,0);
        break;

    case GLUT_KEY_PAGE_UP:
        cam.slide(0,.8,0);

        //
        break;
    case GLUT_KEY_PAGE_DOWN:
        cam.slide(0,-.8,0);
        //
        break;

    default:
        break;
    }

}

void animate()
{
    glutPostRedisplay();
}

            ////            Square class start
class Square{
	public:
	double Len ;
	Color color ;
    Point direction,Normal ;
    int i,j,n,m ;
    double coeff_reflection,coeff_diff ;
	Square(){
	}
	Square(int _i,int _j,int _n,int _m,Point _Normal,Point _direction,double _Len){
        i = _i ; j=_j ; n = _n ; m=_m ; Normal = _Normal ; direction = _direction ;  Len=_Len ;direction=_direction ;
        if (i%2==0 && j%2==0)  color = ( Color( 0.0, 0.0, 0.0 ) );
        else if(i%2==0 && j%2!=0) color = ( Color( 1.0, 1.0, 1.0) );
        else if (i%2!=0 && j%2!=0) color = ( Color( 0.0, 0.0, 0.0) );
        else if(i%2!=0 &&  j%2==0) color = ( Color( 1.0, 1.0, 1.0) );
        coeff_reflection = 0.3 ; /// fixed for squares
        coeff_diff=1.00 ;     /// fixed for squares
	}
	bool inside(Point& p){ /// check if the point is inside the square
            if(p.x>=direction.x-1 && p.x<=direction.x+Len && p.y>=direction.y-1 && p.y<=direction.y+Len && p.z>=direction.z-1 && p.z<=direction.z+Len) return 1 ;
            return 0 ;
	}
	bool intersect(Ray direction_ray,double& min_t){ /// check if the direction ray intersects the square
        Point intersectionPoint ;
        double d = Normal.dot(direction_ray.direction) ;
        if(d!=0){
                double t = (-Normal.dot(direction_ray.start)+Normal.dot(direction))/d ;
                if(t>0){
                    intersectionPoint = direction_ray.start+direction_ray.direction*t ;
                    if(inside(intersectionPoint) && t<min_t){
                        min_t = t ;
                        return 1 ;
                    }
                }
        }
        return 0 ;
	}
	void draw(){
		glPushMatrix();
            {
                glTranslatef(m*30+15,n*30+15,0 );
                glColor3f(color.r,color.g,color.b) ;
                drawSquare(Len/2);
            }
        glPopMatrix() ;
	}
};

//              square class end
//<<<<<<<<<<<<<<<<<<<<<<< display >>>>>>>>>>>>>>>>>>>>>>>>>>
void display(void)
{
    drawAxes() ;
    drawGrid() ;
    // glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glClearColor(0,0,0,0);


    glMatrixMode(GL_MODELVIEW);
    //  glLoadIdentity();
    cam.setModelViewMatrix(); // for this camera set up
    cam.setProjectionMatrix();



    for(int i=0; i<world.nCubes; i++)
    {
        Cube c = world.allCubes[i];

        glPushMatrix();
        {
            glTranslatef( c.lowPoint.x + c.armLength/2.0 , c.lowPoint.y + c.armLength/2.0 , c.lowPoint.z + c.armLength/2.0 );
            glColor3f(c.color.x, c.color.y, c.color.z);
            glutSolidCube(c.armLength);

        }
        glPopMatrix();

    }


    for(int i=0,m=-5; i<10; i++,m++)
    {
        for(int j=0,n=-5; j<10; j++,n++)
        {
            glPushMatrix();
            {
                glTranslatef(m*30+15,n*30+15,0 );
                if (i%2==0 && j%2==0)glColor3f( 0.0f, 0.0f, 0.0f );
                else if(i%2==0 && j%2!=0)glColor3f( 1.0f, 1.0f, 1.0f  );
                else if (i%2!=0 && j%2!=0)glColor3f( 0.0f, 0.0f, 0.0f );
                else if(i%2!=0 &&  j%2==0)glColor3f( 1.0f, 1.0f, 1.0f  );


                drawSquare(15);
            }
            glPopMatrix();
        }
    }




    for(int i=0; i<world.nObjects; i++)
    {

        Object* ob = world.allObjects[i];

        if(ob->type == Object::SPHERE)
        {

            Sphere* sp = (Sphere*) ob;

            glPushMatrix();
            {
                glTranslatef( sp->center.x, sp->center.y, sp->center.z );
                glColor3f(sp->color.x, sp->color.y, sp->color.z );
                glutSolidSphere(sp->radius,20,20);

            }
            glPopMatrix();

        }

    }
    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}
void init(){

    drawgrid=0;
	drawaxes=1;
	char name[55] ;
    double radius,ambient,diffuse,specular,reflection,shineness,x,y,z,r,g,b,height,width ;
    /*
    FILE *fp ;
    fp = fopen("description.txt","r") ;
    fscanf(fp,"%d %d %d",&N,&screen,&recursionLevel) ;
    while(N--){
        fscanf(fp,"%s",name) ;
        if(strcmp(name,"sphere")==0){
                /*
                fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&x,&y,&z,&radius,&r,&g,&b,&ambient,&diffuse,&specular,&reflection,&shineness) ;
                sp = Sphere(Point(x,y,z),radius,Color(r,g,b),ambient,diffuse,specular,reflection,shineness) ;
                spheres.push_back(sp) ;
                */
      //  }
       // else{ /// this is a pyramid
            /*
            fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&x,&y,&z,&width,&height,&r,&g,&b,&ambient,&diffuse,&specular,&reflection,&shineness) ;
            py = Pyramid(Point(x,y,z),width,height,Color(r,g,b),ambient,diffuse,specular,reflection,shineness) ;
            pyramids.push_back(py) ;
            */
     //   }
   // }
    //*/
    // now set up the camera

    world.loadFromFile();
    cam.sett(50.0f,-80.0f,100.0, 0,0.25f,0, 0,0,1);
    cam.setShape(80.0,1.0,1.0, 10000.0);
    cam.setDisplay(nPixel, nPixel);
}
int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitWindowSize(768, 768);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
    glutCreateWindow("Ray Casting");
    init() ;

    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();

    return 0;
}
