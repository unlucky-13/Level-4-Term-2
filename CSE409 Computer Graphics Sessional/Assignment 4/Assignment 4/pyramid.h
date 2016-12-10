class Pyramid{
    Point LeftMost ;
    double width,height;
    Color color ;
    double ambient,diffuse,specular,reflection,shineness ;
public:
    Pyramid(){

    }
    Pyramid(Point _LeftMost,double _width,double _height,Color _color,double _ambient,double _diffuse,double _specular,double _reflection,double _shineness){
        LeftMost=_LeftMost ; width=_width ; height=_height ; color = _color ; ambient = _ambient ; diffuse=_diffuse ; specular=_specular ; reflection = _reflection ; shineness=_shineness ;
    }
    void draw(){

        glTranslated(LeftMost.x,LeftMost.y,LeftMost.z) ;
        glColor3f(color.r,color.g,color.b) ;
    //    drawSquare(width,LeftMost.z) ;
        Triangle(Point(0,0,height),Point(width,width,LeftMost.z),Point(width,-width,LeftMost.z),color).draw() ;
        Triangle(Point(0,0,height),Point(width,-width,LeftMost.z),Point(-width,-width,LeftMost.z),color).draw() ;
        Triangle(Point(0,0,height),Point(-width,-width,LeftMost.z),Point(-width,width,LeftMost.z),color).draw() ;
        Triangle(Point(0,0,height),Point(-width,width,LeftMost.z),Point(width,width,LeftMost.z),color).draw() ;
        glTranslated(-LeftMost.x,-LeftMost.y,-LeftMost.z) ;
    }
};
