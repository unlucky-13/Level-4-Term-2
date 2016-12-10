#ifndef DS_H
#define DS_H

#include <string>
#include <iostream>
#include <fstream>
#include <strstream>
using namespace std;
#include <windows.h>
#include <assert.h>
#include <math.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>


#define PI 3.14159265


//@@@@@@@@@@@@@@@@@@ Vector3 class @@@@@@@@@@@@@@@@
class Vector3{
public:
	float x,y,z;
	void sett(float dx, float dy, float dz){ x = dx; y = dy; z = dz;}
	void sett(const Vector3& v){ x = v.x; y = v.y; z = v.z;}
	void flip(){x = -x; y = -y; z = -z;} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{ x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
	void normalize();//adjust this vector to unit length
	Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}
	Vector3(Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3(){x = y = z = 0;} //default constructor
	Vector3 cross(Vector3 b); //return this cross b
	float dot(Vector3 b); // return this dotted with b
};


#endif // DS_H
