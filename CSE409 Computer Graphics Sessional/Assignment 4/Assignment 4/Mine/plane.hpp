


class Plane : public Object
{
public:

    Vector N,D;
    float armLength;

    Plane( const Vector& a_Normal, const Vector& a_D , float _armLength) : N(a_Normal), D(a_D ), armLength(_armLength) {

        type = PLANE;
    };
    Vector& getNormal()
    {
        return N;
    }
    Vector& GetD()

    {
        return D;
    } // check if the checker board intersects with the square
    int intersect( Ray& a_Ray, float& a_Dist )
    {
        Vector pi;
     //   float h=30;
        float d = N.dot(a_Ray.direction) ;
        if (d != 0)
        {
            float dist = (-( N.dot( a_Ray.origin)) + N.dot(D)) / d;
            if (dist > 0)
            {
                pi = a_Ray.origin + a_Ray.direction * dist;

                if(pi.x>=D.x-1 && pi.x<=D.x+armLength && pi.y>=D.y-1 && pi.y<=D.y+armLength &&
                        pi.z>=D.z-1 && pi.z<=D.z+armLength)
                {
                    if (dist < a_Dist)
                    {
                        a_Dist = dist;
                        return HIT;
                    }
                }

            }
        }
        return MISS;
    }


    Vector getNormal( Vector& a_Pos )
    {
        return N;
    }


};
