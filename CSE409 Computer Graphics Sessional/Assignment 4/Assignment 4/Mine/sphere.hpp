
class Sphere : public Object
{
public:

   Vector center;
    float sqRadius, radius, rRadius;

    Sphere( const Vector& a_Centre, float a_Radius ){

        center = a_Centre;
        sqRadius =a_Radius * a_Radius;
        radius = a_Radius;
        rRadius = 1.0f / a_Radius;

        type = SPHERE;

        }


    int intersect( Ray& a_Ray, float& a_Dist )
    {
        Vector v = a_Ray.origin - center;
        float b = -v.dot( a_Ray.direction );
        float det = (b * b) - v.dot(v) + sqRadius;
        int retval = MISS;
        if (det > 0)
        {
            det = sqrtf( det );
            float i1 = b - det;
            float i2 = b + det;
            if (i2 > 0)
            {
                if (i1 < 0)
                {
                    if (i2 < a_Dist)
                    {
                        a_Dist = i2;
                        retval = INSIDE_OBJ;
                    }
                }
                else
                {
                    if (i1 < a_Dist)
                    {
                        a_Dist = i1;
                        retval = HIT;
                    }
                }
            }
        }
        return retval;
    }

    Vector getNormal( Vector& a_Pos )
    {
        return (a_Pos - center) * rRadius;
    }


};


