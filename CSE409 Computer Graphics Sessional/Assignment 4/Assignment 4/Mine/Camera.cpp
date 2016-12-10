// Sandy Hill,  for ECE661
// a Camera class for flying through 3D scenes.
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <math.h>

//#include "camera.h" //includes SDL.h; Declares Ray as a class
//<<<<<<<<<<<<<<<<<< drawOpenGL >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*void Camera:: drawOpenGL(Scene& scn)
	{
		//first set the lights for openGL
		float globalAmbient[4];
		scn.ambient.build4tuple(globalAmbient); //build 4tuple for global ambient
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
		int num, lightNum = GL_LIGHT0; //grab defined int for GL's light0
		float colr[4], posn[4]; // arrays to hold openGL lights: color and position
		setModelViewMatrix(); // for this camera set up
		setProjectionMatrix(); // for this camera
		Light *p;
		for(p = scn.light, num = 0; p && num < 8; p = p->next, lightNum++, num++)
		{ // set up to 8 OpenGL lights
			(p->color).build4tuple(colr);
			(p->pos).build4tuple(posn);
			float zero[] = {0.0,0.0,0.0,1.0}; // sources don't have ambient component
			glLightfv(lightNum,GL_AMBIENT,zero); //lights don't have their own ambient part
			glLightfv(lightNum,GL_DIFFUSE,colr); // tell openGL diffuse light color
			glLightfv(lightNum,GL_SPECULAR,colr); // tell openGl specualt light color
			glLightfv(lightNum,GL_POSITION,posn);
			glEnable(lightNum); // enable it after specifying its properties
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glClearColor(scn.background.red, scn.background.green, scn.background.blue,0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for(GeomObj* q = scn.obj; q ; q = q->next)
			q->drawOpenGL(); // draw it
		glFlush();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< rayTrace >>>>>>>>>>>>>>>>>>>>>>
void Camera :: raytrace(Scene& scn, int blockSize)
{
		glMatrixMode(GL_MODELVIEW); glLoadIdentity(); //set to identity
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0,nCols,0,nRows); // whole screen is the window
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING); // so glColor3f() will work
		Ray theRay;
		theRay.setStart(eye);
		float blockWidth  = 2 * W / (float)nCols;
		float blockHeight = 2 * H / (float)nRows;
		Color3 clr;
		float x, y;

		for(int row = 0; row < nRows; row += blockSize)
		{
			for(int col = 0; col < nCols; col += blockSize)
			{
				//build the ray's direction
				theRay.row = row; theRay.col = col; // for screen extents
				theRay.recurseLevel = 0;
				theRay.numInside = 0; // ray is outside all objects.
				x = -W + col * blockWidth;
				y = -H + row * blockHeight;
				theRay.setDir( -nearDist * n.x + x * u.x + y * v.x,
							   -nearDist * n.y + x * u.y + y * v.y,
							   -nearDist * n.z + x * u.z + y * v.z);

				clr.sett(scn.shade(theRay)); // get color of this ray
				clr.add(scn.ambient);//add ambient light
				glColor3f(clr.red,clr.green,clr.blue); // set current color
				glRecti(col,row,col+blockSize, row + blockSize);
			}
		}

} */
// end of raytrace
//<<<<<<<<<<<<<<<<<<<<<<< default constructor >>>>>>>>>>>>>>>>>
void Camera :: setDefaultCamera(void)
{ // make default camera
	setShape(45.0f, 640/(float)480, 0.1f, 200.0f); // good default values here
	sett(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);
}
//<<<<<<<<<<<<<<<<<<< setDisplay >>>>>>>>>>>>
void Camera :: setDisplay(int numRows, int numCols)
{ // tell camera screen size
	nRows = numRows; 	nCols = numCols;
}
//<<<<<<<<<<<<<<<<<<<< set >>>>>>>>>>>>>>>>>>>
void Camera :: sett(Point3 Eye, Point3 look, Vector3 up)
{ // make u, v, n vectors
	eye.sett(Eye);
	n.sett(eye.x - look.x, eye.y - look.y,eye.z - look.z);
	u.sett(up.cross(n));
	v.sett(n.cross(u));
	u.normalize(); v.normalize(); n.normalize();
	setModelViewMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<< set - takes 9 params >>>>>>>>>>>>>>>>>
void Camera :: sett(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz)
{
	Point3 e(ex, ey, ez);
	Point3 look(lx, ly, lz);
	Vector3 Up(upx, upy, upz);
	sett(e,look, Up);
}
//<<<<<<<<<<<<<<<< setModelViewMatrix >>>>>>>>>>>>>>>>
void Camera :: setModelViewMatrix(void)
{ // load modelview matrix with existing camera values
	float m[16];
	Vector3 eVec(eye.x, eye.y, eye.z);
	m[0] =  u.x; m[4] =  u.y; m[8]  =  u.z;  m[12] = -eVec.dot(u);
	m[1] =  v.x; m[5] =  v.y; m[9]  =  v.z;  m[13] = -eVec.dot(v);
	m[2] =  n.x; m[6] =  n.y; m[10] =  n.z;  m[14] = -eVec.dot(n);
	m[3] =  0;   m[7] =  0;   m[11] =  0;    m[15] = 1.0;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m);
}
//<<<<<<<<<<<<<<<<<<<<<< setProjectionMatrix >>>>>>>>>>>>>
void Camera:: setProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(viewAngle, aspect, nearDist, farDist);
	glMatrixMode(GL_MODELVIEW); // set its mode back again
}
//<<<<<<<<<<<<<<<<<<<<<<< setShape >>>>>>>>>>>>>>>>
void Camera :: setShape(float vAngle, float asp, float nr, float fr)
{ // load projection matrix and camera values
	viewAngle = vAngle; // viewangle in degrees - must be < 180
	aspect = asp; nearDist = nr; farDist = fr;
	H = nearDist * tan(3.14159265 * viewAngle/(2.0 * 180));
	W = aspect * H;
	setProjectionMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<< setAspect >>>>>>>>>>>>>>>>>>>>>>
void Camera:: setAspect(float asp)
{
	aspect = asp; W = aspect * H;
  	setShape(viewAngle,aspect,nearDist,farDist);
}
//<<<<<<<<<<<<<<<<<<<<<<< getShape >>>>>>>>>>>>>>>>
void Camera :: getShape(float& vAngle, float& asp, float& nr, float& fr)
{
	vAngle = viewAngle;	asp = aspect;
	nr = nearDist; fr = farDist;
}
//<<<<<<<<<<<<<<<<<<<<<< slide >>>>>>>>>>>>>>>>>>>>>>..
void Camera :: slide(double du, double dv, double dn)
{ // slide both eye and lookAt by amount du * u + dv * v + dn * n;
	eye.x += du * u.x + dv * v.x + dn * n.x;
	eye.y += du * u.y + dv * v.y + dn * n.y;
	eye.z += du * u.z + dv * v.z + dn * n.z;
	setModelViewMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<< rotAxes >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void Camera:: rotAxes(Vector3& a, Vector3& b, float angle)
{ // rotate orthogonal vectors a (like x axis) and b(like y axia) through angle degrees
	float ang = 3.14159265/180*angle;
	float C = cos(ang), S = sin(ang);
	Vector3 t(C * a.x + S * b.x, C * a.y + S * b.y, C * a.z + S * b.z); // tmp for a vector
	b.sett(-S * a.x + C * b.x, -S * a.y + C * b.y,-S * a.z + C * b.z);
	a.sett(t.x, t.y, t.z); // put tmp into a'
}
//<<<<<<<<<<<<<<<<<<<<<<<< roll >>>>>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: roll(float angle)
{
	rotAxes(u, v, -angle); setModelViewMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<< pitch >>>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: pitch(float angle)
{
	rotAxes(n, v, angle); setModelViewMatrix();
}
//<<<<<<<<<<<<<<<<<<<<<<<<< yaw >>>>>>>>>>>>>>>>>>>>>>>>
void Camera :: yaw(float angle)
{
	rotAxes(u, n, -angle); setModelViewMatrix();
}
