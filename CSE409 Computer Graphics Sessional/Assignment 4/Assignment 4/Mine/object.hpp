#include "Ray.hpp"



class Object
{
public:
    static const int SPHERE = 1;
    static const int PLANE = 0;
    static const int HIT	=	 1;
    static const int MISS  =	 0;
    static const int INSIDE_OBJ = -1;

    bool isLight;
    int type;
    Color color;
    float coeff_reflection, coeff_diff, coeff_amb, coeff_spec,shininess;

    Object() {
        isLight = false;
    }


    virtual int intersect( Ray& a_Ray, float& a_Dist ) = 0;
    virtual Vector getNormal( Vector& a_Pos ) = 0;


};

