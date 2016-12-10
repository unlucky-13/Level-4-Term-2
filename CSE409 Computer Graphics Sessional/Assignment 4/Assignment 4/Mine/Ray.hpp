class Ray
{
public:

    Vector origin;
    Vector direction;

    Ray() {

        origin = Vector( 0, 0, 0 );
        direction = Vector( 0, 0, 0 );
    }

    Ray( const Vector& _origin, const  Vector& _direction ){

        origin = _origin;
        direction = _direction;

    }



};
