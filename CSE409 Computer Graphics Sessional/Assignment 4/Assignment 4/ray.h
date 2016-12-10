class Ray{
public:

	Point start,direction ;
	Ray(){
	}
	Ray(Point a,Point _direction){
		direction=  normalize(_direction);
		start=a ;
	}
};
