void drawSphere(Point centre,double radius,int slices,int stacks)
{
	glTranslated(centre.x,centre.y,centre.z) ;
	struct Point Points[slices+7][stacks+7];
	int i,j;
	double h,r;
	//generate Points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(M_PI/2));
		r=radius*cos(((double)i/(double)stacks)*(M_PI/2));
		for(j=0;j<=slices;j++)
		{
			Points[i][j].x=r*cos(((double)j/(double)slices)*2*M_PI);
			Points[i][j].y=r*sin(((double)j/(double)slices)*2*M_PI);
			Points[i][j].z=h;
		}
	}
	//draw quads using generated Points
	for(i=0;i<stacks;i++)
	{
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(Points[i][j].x,Points[i][j].y,Points[i][j].z);
				glVertex3f(Points[i][j+1].x,Points[i][j+1].y,Points[i][j+1].z);
				glVertex3f(Points[i+1][j+1].x,Points[i+1][j+1].y,Points[i+1][j+1].z);
				glVertex3f(Points[i+1][j].x,Points[i+1][j].y,Points[i+1][j].z);
                //lower hemisphere
                glVertex3f(Points[i][j].x,Points[i][j].y,-Points[i][j].z);
				glVertex3f(Points[i][j+1].x,Points[i][j+1].y,-Points[i][j+1].z);
				glVertex3f(Points[i+1][j+1].x,Points[i+1][j+1].y,-Points[i+1][j+1].z);
				glVertex3f(Points[i+1][j].x,Points[i+1][j].y,-Points[i+1][j].z);
			}glEnd();
		}
	}
	glTranslated(-centre.x,-centre.y,-centre.z) ;
}

class Sphere{
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
        glColor3f(color.r,color.g,color.b) ;
        drawSphere(centre,radius,100,100) ;
    }
};
