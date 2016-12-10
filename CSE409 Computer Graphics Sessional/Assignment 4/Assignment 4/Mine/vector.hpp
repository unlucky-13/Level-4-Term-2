


class Vector
{
public:
    Vector() : x( 0.0f ), y( 0.0f ), z( 0.0f ) {};
    Vector( float a_X, float a_Y, float a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) {};
    void normalize()
    {
        float l = 1.0f / length();
        x *= l;
        y *= l;
        z *= l;
    }
    float length()
    {
        return (float)sqrt( x * x + y * y + z * z );
    }


    float dot( Vector other )
    {
        return x * other.x + y * other.y + z * other.z;
    }
    Vector cross( Vector b )
    {
        return Vector( y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x );
    }
    void operator += ( const Vector& other )
    {
        x += other.x;
        y += other.y;
        z += other.z;
    }
    void sett(float dx, float dy, float dz)
    {
        x = dx;
        y = dy;
        z = dz;
    }
    void sett(const Vector& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    void operator += ( Vector* other )
    {
        x += other->x;
        y += other->y;
        z += other->z;
    }
    void operator -= (const Vector& other )
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }
    void operator -= ( Vector* other )
    {
        x -= other->x;
        y -= other->y;
        z -= other->z;
    }
    void operator *= ( float f )
    {
        x *= f;
        y *= f;
        z *= f;
    }
    void operator *= (const Vector& other )
    {
        x *= other.x;
        y *= other.y;
        z *= other.z;
    }
    void operator *= ( Vector* other )
    {
        x *= other->x;
        y *= other->y;
        z *= other->z;
    }
    Vector operator- () const
    {
        return Vector( -x, -y, -z );
    }




    friend Vector operator + ( const Vector& v1, const Vector& v2 )
    {
        return Vector( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
    }
    friend Vector operator - ( const Vector& v1, const Vector& v2 )
    {
        return Vector( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
    }
    friend Vector operator + ( const Vector& v1, Vector* v2 )
    {
        return Vector( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z );
    }
    friend Vector operator - ( const Vector& v1, Vector* v2 )
    {
        return Vector( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z );
    }
    friend Vector operator * ( const Vector& v, float f )
    {
        return Vector( v.x * f, v.y * f, v.z * f );
    }
    friend Vector operator * ( const Vector& v1, const Vector& v2 )
    {
        return Vector( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
    }
    friend Vector operator * ( float f, const Vector& v )
    {
        return Vector( v.x * f, v.y * f, v.z * f );
    }
    float x, y, z;

};

typedef Vector Color;
