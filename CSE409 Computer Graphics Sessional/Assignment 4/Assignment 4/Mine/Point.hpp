


class Point
{
public:
    float x,y,z;

    Point(float xx, float yy, float zz)
    {
        x = xx;
        y = yy;
        z = zz;
    }


    void sett(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    void sett(const Point& p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }

    Point()
    {
        x = y = z = 0;
    }

};

