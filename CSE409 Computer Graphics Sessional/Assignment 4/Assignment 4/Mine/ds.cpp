#include "ds.h"


// Vector3 methods
Vector3 Vector3 :: cross(Vector3 b) //return this cross b
{
	Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	return c;
}
float Vector3 :: dot(Vector3 b) // return this dotted with b
{return x * b.x + y * b.y + z * b.z;}

void Vector3 :: normalize()//adjust this vector to unit length
{
	double sizeSq = x * x + y * y + z * z;
	if(sizeSq < 0.0000001)
	{
		cerr << "\nnormalize() sees vector (0,0,0)!!!";
		x = 1; // lousy cope - can you do better?
		return; // returns (1,0,0) - yuck!
	}
	float scaleFactor = 1.0/(float)sqrt(sizeSq);
	x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
}
