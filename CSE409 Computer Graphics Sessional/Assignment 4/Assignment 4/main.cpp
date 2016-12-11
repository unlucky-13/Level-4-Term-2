using namespace std ;
#include <bits/stdc++.h>
//#include<windows.h>
#include<glut.h>
#include "bitmap_image.hpp"

#define MAX_T 100000000.00
#define EPS 1e-6
int screen=500,drawaxes,drawgrid,recursionLevel;
void drawSquare(double a)
{
    glBegin(GL_QUADS);
    {
        glVertex3f( a, a,0);
        glVertex3f( a,-a,0);
        glVertex3f(-a,-a,0);
        glVertex3f(-a, a,0);
    }
    glEnd();
}
void drawGrid(){
{
        if(drawgrid==0) return ;
        glColor3f(0.6, 0.6, 0.6);
        glBegin(GL_LINES);
        {
            for(int i=-8; i<=8; i++)
            {

                if(i==0)
                    continue;

                glVertex3f(i*10, -90, 0);
                glVertex3f(i*10,  90, 0);

                glVertex3f(-90, i*10, 0);
                glVertex3f( 90, i*10, 0);
            }
        }
        glEnd();
    }
}
///////////////////////////////////////////////////////////////////Color/////////////////////////////////////////////////////////////////////////////////
class Color{
public:
        double r,g,b ;
public:
    Color(){
        r=g=b=0 ;
    }
    Color(double _r,double _g,double _b){
        r=_r ; g=_g; b=_b ;
    }
    Color operator+(const Color& col){
        double rr=r+col.r ;
        double gg=g+col.g ;
        double bb=b+col.b ;
        return Color(rr,gg,bb) ;
    }
    Color operator * (double val){
        double rr=r*val ;
        double gg=g*val ;
        double bb=b*val ;
        return Color(rr,gg,bb) ;
    }
    Color operator * (Color col){
        double rr=r*col.r ;
        double gg=g*col.g ;
        double bb=b*col.b ;
        return Color(rr,gg,bb) ;
    }
};
//////////////////////////////////////////////////////////////Color/////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////Point-Vector/////////////////////////////////////////////////////////////////////
class Point
{
public:
    double x,y,z;
    Point(double _x, double _y, double _z){
        x = _x; y = _y; z = _z;
    }
    void equal(double _x, double _y, double _z){
        x = _x;
        y = _y;
        z = _z;
    }
    void equal(const Point& p){
        x = p.x;
        y = p.y;
        z = p.z;
    }

    Point(){
        x = y = z = 0;
    }
    double dot( Point other ){
        return x * other.x + y * other.y + z * other.z;
    }
	Point operator * (const Point &other)const{
        return Point(x*other.x,y*other.y,z*other.z) ;
    }
    Point operator * (const double &scale)const{
        return Point(x*scale,y*scale,z*scale) ;
    }
    Point operator + (const Point &other)const{
        return Point(x+other.x,y+other.y,z+other.z) ;
    }
    Point operator - (const Point &other)const{
        return Point(x-other.x,y-other.y,z-other.z) ;
    }
    Point cross( Point b ){
        return Point( y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x );
    }
    double value(){
        return (double)sqrt(x*x+y*y+z*z);
    }
     void normalize(){
        double val = 1.0/value();
        x *= val; y *= val; z *= val;
    }
};

Point pos,u,v,n,look,up ;
double angle,near_distance,far_distance,aspect,W,H ;
//////////////////////////////////////////////////////////////Ray//////////////////////////////////////////////////////////////////////////////
class Ray{
public:
    Point P0;
    Point dir;
    Ray() {

        P0 = Point( 0, 0, 0 );
        dir = Point( 0, 0, 0 );
    }
    Ray( const Point& _P0, const  Point& _dir ){
        P0 = _P0;
        dir = _dir;

    }
};
//////////////////////////////////////////////////////////////Ray//////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////Square ////////////////////////////////////////////////////////////////////////////

class Square{
	public:
	double Len ;
	Color color = Color(0,0,0) ;
    Point D,N ;
    int i,j,n,m ;
    double reflection,diffuse,specular,ambient  ;
	Square(int _i,int _j,int _n,int _m,Point _Normal,Point _dir,double _Len){
        i = _i ; j=_j ; n = _n ; m=_m ; N = _Normal ; D = _dir ;  Len=_Len ;
        if (i%2==0 && j%2==0)  color =  Color( 0.0, 0.0, 0.0)  ;
        else if(i%2==0 && j%2!=0) color =  Color( 1.0, 1.0, 1.0) ;
        else if (i%2!=0 && j%2!=0) color =  Color( 0.0, 0.0, 0.0) ;
        else if(i%2!=0 &&  j%2==0) color =  Color( 1.0, 1.0, 1.0) ;
        reflection = 0.3 ; /// fixed for squares
        diffuse=1.00 ;     /// fixed for squares
        specular =0 ;
	}
	Square(Point Mid,Color col,double _Len,double _ambient,double _diffuse,double _reflection,double _specular){
        N = Point(0,0,1) ; D = Mid ; Len=_Len ; diffuse = _diffuse ; reflection=_reflection ; specular=_specular ; color = col ; ambient=_ambient ;
	}
    void P(){
        cout<<i<<" "<<j<<" "<<n<<" "<<m<<endl ;
    }
	double intersect( Ray& directionRay){
        Point intersectionPoint;
        double d = N.dot(directionRay.dir) ;
        if (d != 0)
        {
            double dist = (-( N.dot( directionRay.P0)) + N.dot(D)) / d;
            if (dist > 0)
            {
                intersectionPoint = directionRay.P0 + directionRay.dir * dist;

                if(intersectionPoint.x>=D.x-1 && intersectionPoint.x<=D.x+Len && intersectionPoint.y>=D.y-1 && intersectionPoint.y<=D.y+Len &&
                        intersectionPoint.z>=D.z-1 && intersectionPoint.z<=D.z+Len)
                {
                        return dist;

                }
            }
        }
        return MAX_T;
    }
	void draw(){
		glPushMatrix();
            {
                glTranslatef(D.x,D.y,D.z);
                glColor3f(color.r,color.g,color.b) ;
                drawSquare(Len/2);
            }
        glPopMatrix() ;
	}
	Point getNormal(Point &P){
        return N ;
	}
};

//////////////////////////////////////////////////////////////////Square////////////////////////////////////////////////////////////////////////////////
class Sphere{
    public:
    Point centre ;
    double radius;
    Color color ;
    double ambient,diffuse,specular,reflection,shineness ;
    public:
	Sphere(){
	}
    Sphere(Point _centre,double _radius,Color _color,double _ambient,double _diffuse,double _specular,double _reflection,double _shineness){
        centre=_centre ; radius = _radius ; color = _color ; ambient = _ambient ; diffuse=_diffuse ; specular=_specular ; reflection = _reflection ; shineness=_shineness ;
    }
    void draw(){
        glPushMatrix();
            {
                glTranslatef(centre.x,centre.y,centre.z );
                glColor3f(color.r,color.g,color.b );
                glutSolidSphere(radius,20,20);

            }
        glPopMatrix();
    }
    double intersect(Ray & directionRay){
        Point Line = directionRay.P0 - centre;
        double b = -Line.dot( directionRay.dir );
        double delta = (b * b) - Line.dot(Line) + radius*radius;
        double  T = MAX_T;
        if (delta > 0){
            delta = sqrt(delta);
            double  D1 = b - delta;
            double D2 = b + delta;
            if (D2 > 0){
                if (D1 < 0){
                        T = D2 ;
                }
                else{
                        T = D1;
                }
            }
        }
        return T;
    }
    Point getNormal(Point& P){
            return (P - centre) *radius;
    }
};
class Light{
public:
    Color color ;
    Point centre ;
    double radius ;
    Light(){

    }
    Light(double x,double y,double z){
        centre = Point(x,y,z) ;
        color  = Color(1.0,1.0,1.0) ;
        radius = 3.00 ;
    }
    double intersect(const Ray & directionRay){
        Point Line = directionRay.P0 - centre;
        double b = -Line.dot( directionRay.dir );
        double delta = (b * b) - Line.dot(Line) + radius*radius;
        double  T = MAX_T;
        if (delta > 0){
            delta = sqrt(delta);
            double  D1 = b - delta;
            double D2 = b + delta;
            if (D2 > 0){
                if (D1 < 0){
                        T = D2 ;
                }
                else{
                        T = D1;
                }
            }
        }
        return T;
    }
    void draw(){
        glPushMatrix();
            {
                glTranslatef(centre.x,centre.y,centre.z );
                glColor3f(color.r,color.g,color.b );
                glutSolidSphere(radius,20,20);
            }
        glPopMatrix();
    }
};
////////////////////////////////////////////////////////            Class triangle///////////////////////////////////////////////
class Triangle{
public:
    Point x,y,z ;
    Color color ;
    double diffuse,reflection, specular ,ambient ;

    Triangle(){
    }
    Triangle(Point _x,Point _y,Point _z,Color _color,double _ambient,double _diffuse,double _reflection,double _specular){
        x=_x ; y=_y ; z=_z ; color=_color ; diffuse = _diffuse ; reflection=_reflection ; specular=_specular ;  ambient=_ambient ;
    }
    void draw(){
        glColor3f(color.r,color.g,color.b) ;
        glBegin(GL_TRIANGLES);
                glVertex3f(x.x,x.y,x.z);
                glVertex3f(y.x,y.y,y.z);
                glVertex3f(z.x,z.y,z.z);
        glEnd();
    }
    bool rayTriangleIntersect(
    const Point &orig, const Point &dir,
    const Point &v0, const Point &v1, const Point &v2,
    float &t, float &u, float &v){
    // compute plane's normal
    Point v0v1 = v1 - v0;
    Point v0v2 = v2 - v0;
    // no need to normalize
    Point N = v0v1.cross(v0v2); // N
    float denom = N.dot(N);

    // Step 1: finding P

    // check if ray and plane are parallel ?
    float NdotRayDirection = N.dot(dir);
    if (fabs(NdotRayDirection) < EPS) // almost 0
        return false; // they are parallel so they don't intersect !

    // compute d parameter using equation 2
    float d = N.dot(v0);

    // compute t (equation 3)
    t = (N.dot(orig) + d) / NdotRayDirection;
    // check if the triangle is in behind the ray
    if (t < 0) return false; // the triangle is behind

    // compute the intersection point using equation 1
    Point P = orig + dir*t;

    // Step 2: inside-outside test
    Point C; // vector perpendicular to triangle's plane

    // edge 0
    Point edge0 = v1 - v0;
    Point vp0 = P - v0;
    C = edge0.cross(vp0);
    if (N.dot(C) < 0) return false; // P is on the right side

    // edge 1
    Point edge1 = v2 - v1;
    Point vp1 = P - v1;
    C = edge1.cross(vp1);
    if ((u = N.dot(C)) < 0)  return false; // P is on the right side

    // edge 2
    Point edge2 = v0 - v2;
    Point vp2 = P - v2;
    C = edge2.cross(vp2);
    if ((v = N.dot(C)) < 0) return false; // P is on the right side;

    u /= denom;
    v /= denom;

    return true; // this ray hits the triangle
}
    double intersect(Ray& directionRay){
            float t, u, v;
            Point orig = directionRay.P0 ;
            Point dir = directionRay.dir ;
            bool res = rayTriangleIntersect(orig,dir,z,y,x,t,u,v) ;
            if(res){
                return t ;
            }
            return MAX_T ;
    }
    Point getNormal(Point &p){
        Point v0v1 = y - x;
        Point v0v2 = z - x;
        // no need to normalize
        Point N = v0v1.cross(v0v2); // N
        return N ;
    }
    double area(){
            Point AB = y-x ;
            Point AC = z-x ;
            //cout<<(AB.Value()*AC.Value())<<endl ;
            if(fabs(AB.value()*AC.value())<=EPS) return 0 ; // two points are same
            double theta = acos(AB.dot(AC)/(AB.value()*AC.value())) ;
            return fabs(0.5*AB.value()*AC.value()*sin(theta)) ;
    }
};
//////////////////////////////////////////////////////              Class triangle////////////////////////////////////////////
vector<Square>squares ;
vector<Sphere>spheres ;
vector<Light>lights ;
vector<Triangle>triangles ;
Point getNormal(int i,int j,Point P){
    if(i==1){
        return squares[j].getNormal(P) ;
    }
    else if(i==2){
        return spheres[j].getNormal(P) ;
    }
    return Point(0,0,0) ; /// arbirart output
}
double getdiffuse(int i,int j){
    if(i==1){
        return squares[j].diffuse ;
    }
    else if(i==2){
        return spheres[j].diffuse ;
    }
    return 0 ;
}
Color getColor(int i,int j){
    if(i==1){
        return squares[j].color ;
    }
    else if(i==2){
        return spheres[j].color ;
    }
    else if(i==3){
        return lights[j].color ;
    }
    else if(i==4){
        return triangles[j].color ;
    }
    return Color(0,0,0) ;
}
double getspec(int i,int j){
    if(i==1){
        return squares[j].specular ;
    }
    else if(i==2){
        return spheres[j].specular ;
    }
    return 0 ;
}
double getReflection(int i,int j){
    if(i==1){
        return squares[j].reflection ;
    }
    else if(i==2){
        return spheres[j].reflection ;
    }
    return 0 ;
}

void ray_tracing(Ray& directionRay,int Level,Color & col){
    if(Level>recursionLevel){
        col = Color(0,0,0) ;
    }
    double min_t = MAX_T ;
    int I=-1,J=-1 ;
    ///     Intersecting with the squares on the plane
    for(int i=0;i<(int)squares.size();i++){
        double t = squares[i].intersect(directionRay) ;
        if(t<min_t){
                I = 1 ;
                J = i ;
                min_t=t ;
        }
    }
    ///         Now with the spheres
    for(int i=0;i<(int)spheres.size();i++){
        double  t = spheres[i].intersect(directionRay) ;
        if(t<min_t){
                I = 2 ;
                J = i ;
                min_t=t ;
        }
    }
    //
    for(int i=0;i<(int)lights.size();i++){
        double  t = lights[i].intersect(directionRay) ;
        if(t<min_t){
                return  ;
                I = 3 ;
                J = i ;
                min_t=t ;
        }
    }
    for(int i=0;i<(int)triangles.size();i++){
        double  t = triangles[i].intersect(directionRay) ;
        if(t<min_t){
                I = 4 ;
                J = i ;
                min_t=t ;
        }
    }
    col = getColor(I,J) ;
    /// determine the color at the point
    /*
    directionRay.dir.normalize() ;
    Point intersectionPoint = directionRay.P0+directionRay.dir*min_t ;
    /// Trace light
    col=col+getColor(I,J)*0.4 ;
    for(int i=0;i<(int)lights.size();i++){
        double shade = 1.0 ;
        Point L = lights[i].centre-intersectionPoint ;
        double dist = L.value() ;
        L =L*(1.00/dist) ;
        Ray r = Ray(intersectionPoint+L*EPS,L) ;
        for(int k=0;k<(int)squares.size();k++){
            if(squares[k].intersect(r)<dist){ /// it intersects
                shade=0 ;
                break ;
            }
        }
        for(int k=0;k<(int)squares.size();k++){
            if(squares[k].intersect(r)<dist){ /// it intersects
                shade=0 ;
                break ;
            }
        }
        /// calculate diffuse shading
         L = lights[i].centre-intersectionPoint ;
         L.normalize() ;
         Point N  =getNormal(I,J,intersectionPoint) ;
         double diffuse=getdiffuse(I,J) ;
         double dot = N.dot(L) ;
         if(dot>0){
            double diff = dot*diffuse*shade ;
            col = col + getColor(I,J)*lights[i].color*diff ;
         }
         /// calculate specular shading
         Point V  = directionRay.dir ;
         Point R = L - N*(2.0*L.dot(N)) ;
         dot = V.dot(R) ;
         if(dot>0){
            double spec = pow(dot,25)*getspec(I,J)*shade ;
            col = col+lights[i].color*spec ;
         }

    }
    // Now handling the reflection

    double reflection  = getReflection(I,J) ;
    Point N = getNormal(I,J,intersectionPoint) ;
    Point R  = directionRay.dir-N*directionRay.dir.dot(N)*2.00 ;
    if(Level<recursionLevel){
        Color newColor(0,0,0) ;
        //double dist ;
        Ray newRay = Ray(intersectionPoint+R*EPS,R) ;
        ray_tracing(newRay,Level+1,newColor) ;
        col = col + newColor*getColor(I,J)*reflection ;
    }
*/
}

void callModelViewMatrix(){
float *ModelViewMatrix = new float[16];
        ModelViewMatrix[0] =  u.x;
        ModelViewMatrix[1] =  v.x;
        ModelViewMatrix[2] =  n.x;
        ModelViewMatrix[3] =  0;
        ModelViewMatrix[4] =  u.y;
        ModelViewMatrix[5] =  v.y;
        ModelViewMatrix[6] =  n.y;
        ModelViewMatrix[7] =  0;
        ModelViewMatrix[8]  =  u.z;
        ModelViewMatrix[9]  =  v.z;
        ModelViewMatrix[10] =  n.z;
        ModelViewMatrix[11] =  0;
        ModelViewMatrix[12] = -pos.dot(u);
        ModelViewMatrix[13] = -pos.dot(v);
        ModelViewMatrix[14] = -pos.dot(n);
        ModelViewMatrix[15] = 1.0;
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(ModelViewMatrix);
}
void inline settingProjectionMatrix(){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(angle, aspect, near_distance,far_distance);
        glMatrixMode(GL_MODELVIEW);
}
    void rotate(Point& a, Point& b, float angle)
    {
        // rotate orthogonal vectors a (like x axis) and b(like y axia) through angle degrees
        double theta = M_PI/(180.00*angle);
        Point t(a*cos(theta)+b*sin(theta)) ;
        b  = (a*-sin(theta)+b*cos(theta)) ;
        a = Point(t) ;
    }

    void Look_at_a_angle(float angle)
    {
        rotate(u, v, -angle);
        callModelViewMatrix();
    }
    void tillted(float angle)
    {
        rotate(n, v, angle);
        callModelViewMatrix();
    }
    void Look_Left_RIght(float angle)
    {
        rotate(u, n, -angle);
        callModelViewMatrix();
    }
    void Go_Forward_Backward(double dx, double dy, double dz)
    {
        Point FB( dx * u.x + dy * v.x + dz * n.x ,dx * u.y + dy * v.y + dz * n.y,dx * u.z + dy * v.z + dz * n.z);
        pos = pos+FB ;
        callModelViewMatrix();
    }
void ray_tracing()
{

    cout<<"Camera : "<<W<<"::"<<H<<endl ;

    Ray projectionRay;
    projectionRay.P0 = (Point(pos.x,pos.y,pos.z));
    double width = 2 *W / (double)screen;
    double heigtht = 2 *H / (double)screen;
   // cout<<"CCC"<<cam.nCols<<endl ;

    cout<<"Block width:"<<width<<" : "<<width<<endl ;
    bitmap_image image(screen,screen);

    for(int i = 0; i < screen;i++){
        for(int j = 0; j < screen; j ++){
            double x = -W + j * width;
            double y = -H + i * heigtht;

            projectionRay.dir =  Point(n*-near_distance+u*x+v*y) ;
            projectionRay.dir.normalize();

            Color draw_color   ;
            ray_tracing(projectionRay,1,draw_color);
            image.set_pixel(i,j,draw_color.r*255.00,draw_color.g*255.00,draw_color.b*255.00);
        }
        cout<<"Processed Row::"<<i<<endl ;
    }
    cout<<"Saving the image"<<endl ;
    image.save_image("output.bmp");

}

void keyboardListener(unsigned char key, int x,int y){
    switch(key){
    case '1':
        Look_Left_RIght(.5);
        break;
    case '2':
        Look_Left_RIght(-.5);
        break;
    case '3':
        tillted(-.5);
        break;
    case '4':
        tillted(.5);
        break;
    case '5':
        Look_at_a_angle(.5);
        break ;
    case '6':
        Look_at_a_angle(-.5);
        break ;
    case '0':
        ray_tracing() ;
        break ;
    default:
        break;
    }
}

void specialKeyListener(int key, int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_DOWN:
        Go_Forward_Backward(0,0,.5);
        break;
    case GLUT_KEY_UP:
        Go_Forward_Backward(0,0,-.5);
        break;
    case GLUT_KEY_RIGHT:
        Go_Forward_Backward(.5,0,0);
        break;
    case GLUT_KEY_LEFT:
        Go_Forward_Backward(-.5,0,0);
        break;
    case GLUT_KEY_PAGE_UP:
        Go_Forward_Backward(0,.5,0);
        break;
    case GLUT_KEY_PAGE_DOWN:
        Go_Forward_Backward(0,-.5,0);
        break;
    default:
        break;
    }
}
void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN){		// 2 times?? in ONE click? -- solution is checking DOWN or UP
				drawaxes=1-drawaxes;
			}
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}
void animate()
{
    glutPostRedisplay();
}

void display(void)
{
    // glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_NORMALIZE);

    glClearColor(0,0,0,0);


    glMatrixMode(GL_MODELVIEW);
    //  glLoadIdentity();
    callModelViewMatrix(); // for this camera set up
    settingProjectionMatrix();

    /// show checker board
    for(int i=0;i<(int)squares.size();i++){
        squares[i].draw() ;
      //  squares[i].P() ;
    }
    /// show spheres
    for(int i=0;i<(int)spheres.size();i++){
        spheres[i].draw() ;
    }
    /// show the lights
    for(int i=0;i<(int)lights.size();i++){
        lights[i].draw() ;
    }
    for(int i=0;i<(int)triangles.size();i++){
        triangles[i].draw() ;
    }
    glutSwapBuffers();
}

void init(){
    //Taking input from description file
    FILE *fp ;
    fp = fopen("description.txt","r") ;
    Sphere sp ;
   // Pyramid py ;
    int N ;
    char name[55] ;
    double radius,ambient,diffuse,specular,reflection,shineness,x,y,z,r,g,b,height,width ;
    fscanf(fp,"%d %d %d",&recursionLevel,&screen,&N) ;
    //cout<<screen<<endl ;
    while(N--){
        fscanf(fp,"%s",name) ;
        if(strcmp(name,"sphere")==0){
                fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&x,&y,&z,&radius,&r,&g,&b,&ambient,&diffuse,&specular,&reflection,&shineness) ;
                sp = Sphere(Point(x,y,z),radius,Color(r,g,b),ambient,diffuse,specular,reflection,shineness) ;
                spheres.push_back(sp) ;
        }
        else{ /// this is a pyramid
            fscanf(fp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",&x,&y,&z,&width,&height,&r,&g,&b,&ambient,&diffuse,&specular,&reflection,&shineness) ;
           /// each pyramid is represened by 4 triangles and 1 square
                Point Mid = Point(x+width/2,y+width/2,z) ;
                Square sq = Square(Mid,Color(r,g,b),width,ambient,diffuse,reflection,specular) ;
                squares.push_back(sq) ;


                /////////////////////////Now the 4 triangles
                Triangle triangle  ;
                Point Vertex = Mid+Point(0,0,1)*height ;
                Point A = Point(x,y,z) ;
                Point B = A+Point(width,0,0) ;
                Point C = B+Point(0,width,0) ;
                Point D = C+Point(-width,0,0) ;

                triangle = Triangle(Vertex,A,B,Color(0,0,1),ambient,diffuse,reflection,specular) ; triangles.push_back(triangle) ;
                triangle = Triangle(Vertex,B,C,Color(0,0,1),ambient,diffuse,reflection,specular) ; triangles.push_back(triangle) ;
                triangle = Triangle(Vertex,C,D,Color(0,0,1),ambient,diffuse,reflection,specular) ; triangles.push_back(triangle) ;
                triangle = Triangle(Vertex,D,A,Color(0,0,1),ambient,diffuse,reflection,specular) ; triangles.push_back(triangle) ;
        }
    }
    ///
    fscanf(fp," %d",&N) ; /// light sources
    cout<<N<<endl ;
    for(int i=0;i<N;i++){
        fscanf(fp,"%lf %lf %lf ",&x,&y,&z) ;
        lights.push_back(Light(x,y,z)) ;
    }
    fclose(fp) ;

        ////                            equalING UP THE CAMERA


    pos = Point(50.0,-80.0,100.0) ;
    look = Point(100.0, 0,0.25) ;
    up = Point(0,0,1) ;

	n = pos - look;
	u = up.cross(n);
	v = n.cross(u) ;
	u.normalize(); v.normalize(); n.normalize();
	callModelViewMatrix();


    angle = 80.00;
    aspect = 1;
    near_distance = 1;
    far_distance = 10000.0;
    H = near_distance * tan(M_PI * angle/(2.0 * 180));
    W = aspect * H;
    settingProjectionMatrix();


        ///                 CAMERA END

    /// Squares for checker board


    for(int i=0,m=-5; i<10; i++,m++){
        for(int j=0,n=-5; j<10; j++,n++){
                Square sq = Square(i,j,n,m,Point( 0, 0, 1 ), Point(m*30,n*30,0 ),30) ;
                squares.push_back(sq) ;
        }
    }
}
int main(int argc, char **argv){
    init() ;
    glutInit(&argc,argv);
    glutInitWindowSize(screen, screen);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, double buffer, RGB color

    glutCreateWindow("Ray Tracer");
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);	//enable Depth Testing
    glDisable(GL_LIGHTING);
    glViewport(0, 0, screen, screen);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener) ;
    glutMainLoop();

    return 0;
}
