
#include "Point.hpp"
#include "common.h"

class Camera
{
public:
    Point eye;
    Vector u, v, n;
    float aspect, nearDist, farDist, viewAngle, W, H;
    void setModelViewMatrix()
    {
        // load modelview matrix with existing camera values
        float m[16];
        Vector eVec(eye.x, eye.y, eye.z);
        m[0] =  u.x;
        m[4] =  u.y;
        m[8]  =  u.z;
        m[12] = -eVec.dot(u);
        m[1] =  v.x;
        m[5] =  v.y;
        m[9]  =  v.z;
        m[13] = -eVec.dot(v);
        m[2] =  n.x;
        m[6] =  n.y;
        m[10] =  n.z;
        m[14] = -eVec.dot(n);
        m[3] =  0;
        m[7] =  0;
        m[11] =  0;
        m[15] = 1.0;
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(m);
    }
//public:
    int nRows, nCols;
    Camera()
    {
        // make default camera
        setDefaultCamera();
    }
    void printCamera(void);
    void roll(float angle)
    {
        rotAxes(u, v, -angle);
        setModelViewMatrix();
    }
    void pitch(float angle)
    {
        rotAxes(n, v, angle);
        setModelViewMatrix();
    }
    void yaw(float angle)
    {
        rotAxes(u, n, -angle);
        setModelViewMatrix();
    }
    void slide(double du, double dv, double dn)
    {
        // slide both eye and lookAt by amount du * u + dv * v + dn * n;
        eye.x += du * u.x + dv * v.x + dn * n.x;
        eye.y += du * u.y + dv * v.y + dn * n.y;
        eye.z += du * u.z + dv * v.z + dn * n.z;
        setModelViewMatrix();
    }
    void sett(Point Eye,  Point look, Vector up)
    { // make u, v, n vectors
	eye.sett(Eye);
	n.sett(eye.x - look.x, eye.y - look.y,eye.z - look.z);
	u.sett(up.cross(n));
	v.sett(n.cross(u));
	u.normalize(); v.normalize(); n.normalize();
	setModelViewMatrix();
}
    void sett(float ex, float ey, float ez, float lx, float ly, float lz, float upx, float upy, float upz)
    {
        Point e(ex, ey, ez);
        Point look(lx, ly, lz);
        Vector Up(upx, upy, upz);
        sett(e,look, Up);
    }
    void setDisplay(int numRows, int numCols)
    {
        // printf("saskdjas") ;
        // tell camera screen size
        nRows = numRows;
        nCols = numCols;
    }
    void setProjectionMatrix()
    {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(viewAngle, aspect, nearDist, farDist);
        glMatrixMode(GL_MODELVIEW); // set its mode back again
    }
    void setShape(float _viewAngle, float _aspect, float _Near, float _Far)
    {
        // load projection matrix and camera values
        viewAngle = _viewAngle; // viewangle in degrees - must be < 180
        aspect = _aspect;
        nearDist = _Near;
        farDist = _Far;
        H = nearDist * tan(3.14159265 * viewAngle/(2.0 * 180));
        W = aspect * H;
        setProjectionMatrix();
    }

    void rotAxes(Vector& a, Vector& b, float angle)
    {
        // rotate orthogonal vectors a (like x axis) and b(like y axia) through angle degrees
        float ang = 3.14159265/180*angle;
        float C = cos(ang), S = sin(ang);
        Vector t(C * a.x + S * b.x, C * a.y + S * b.y, C * a.z + S * b.z); // tmp for a vector
        b.sett(-S * a.x + C * b.x, -S * a.y + C * b.y,-S * a.z + C * b.z);
        a.sett(t.x, t.y, t.z); // put tmp into a'
    }
    void setDefaultCamera()
    {
        // make default camera
        setShape(80.0f, 1, 0.1f, 200.0f); // good default values here
        sett(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0, 1, 0);
    }

};

