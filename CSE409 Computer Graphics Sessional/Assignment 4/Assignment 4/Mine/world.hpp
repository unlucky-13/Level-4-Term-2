#include <stdio.h>

class World
{


public:

    int nObjects;
    Object** allObjects;
    Cube* allCubes;
    int nCubes;


    World() : nObjects( 0 ), allObjects( 0 ) {}
    ~World()
    {
        delete allObjects;
    }



    void addCube(Vector lowPoint, float armLength, Color color, float amb, float diff, float spec, float refl, float shin)
    {

        allObjects[nObjects     ] = new Plane( Vector( 0, 1, 0 ), Vector(0,0,0 ), armLength);
        allObjects[nObjects + 1 ] = new Plane( Vector( 0, -1, 0 ), Vector(0,armLength,0 ), armLength);
        allObjects[nObjects + 2 ] = new Plane( Vector( 0, 0, -1 ), Vector(0,0,0 ), armLength);
        allObjects[nObjects + 3 ] = new Plane( Vector( 0, 0, 1 ), Vector(0,0,armLength ), armLength);
        allObjects[nObjects + 4 ] = new Plane( Vector( -1, 0, 0 ), Vector(0,0,0 ), armLength);
        allObjects[nObjects + 5 ] = new Plane( Vector( 1, 0, 0 ), Vector(armLength,0,0 ), armLength);

        for(int i=0; i<6; ++i,nObjects++)
        {

            allObjects[nObjects]->coeff_reflection =  refl ;
            allObjects[nObjects]->coeff_diff =  diff ;
            allObjects[nObjects]->coeff_spec = spec;
            allObjects[nObjects]->shininess = shin;
            allObjects[nObjects]->color = color;

        }

        allCubes[nCubes++] = Cube(lowPoint, armLength,color);

    }


    void loadFromFile()
    {
        allObjects = new Object*[500];
        allCubes = new Cube[100];

        nObjects = nCubes= 0;
        int nShapes;

        scanf("%d", &nBumps);

        scanf("%d", &nPixel);


        scanf("%d", &nShapes);

        printf("Bumps: %d\n Number of things: %d\n Resolution: %d x %d\n", nBumps, nShapes, nPixel, nPixel);


        float x,y,z,r,cr,cg,cb;
        float amb, diff, spec, refl, shin;
        for(int i=0; i<nShapes; i++)
        {

            int type;
            scanf("%d", &type);



            if(type == 1)   //Sphere
            {


                printf("%d: Sphere\n", i);
                scanf("%f %f %f", &x, &y, &z);
                scanf("%f", &r);

                allObjects[nObjects] = new Sphere( Vector( x, y, z ), r );


                scanf("%f %f %f", &x, &y, &z);
                allObjects[nObjects]->color = ( Color( x, y, z ) );

                scanf("%f", &x);
                //          spheres[nSpheres].setambient(x);


                scanf("%f", &x);
                allObjects[nObjects]->coeff_diff =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->coeff_spec =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->coeff_reflection =  x ;

                scanf("%f", &x);
                allObjects[nObjects]->shininess =  x ;

                nObjects++;


            }
            else            //Cube
            {



                scanf("%f %f %f", &x, &y, &z);
                scanf("%f", &r);


                scanf("%f %f %f", &cr, &cg, &cb);



                scanf("%f", &amb);


                scanf("%f", &diff);


                scanf("%f", &spec);


                scanf("%f", &refl);


                scanf("%f", &shin);


                addCube(Vector(x,y,z), r, Color(cr,cg,cb), amb, diff, spec, refl, shin);

            }
        }

        int nLightSources;
        scanf("%d", &nLightSources);

        for(int i=0; i<nLightSources; ++i)
        {


            scanf("%f %f %f", &x, &y, &z);

            allObjects[nObjects] = new Sphere( Vector( x, y, z ), 3.0f );
            allObjects[nObjects]->isLight = true ;
            allObjects[nObjects]->color = Color(1.0f,1.0f,1.0f );

            ++nObjects;


        }

        printf("Lights sources: %d\n", nLightSources);





        /// draw the checker board
        int p=nObjects;
        for(int i=0,m=-5; i<10; i++,m++)
        {
            for(int j=0,n=-5; j<10; j++,n++)
            {
                allObjects[p+i*10+j] = new Plane( Vector( 0, 0, 1 ), Vector(m*30,n*30,0 ), 30);

                allObjects[p+i*10+j]->coeff_reflection =  0.3 ;
                allObjects[p+i*10+j]->coeff_diff =  1.0f ;
                if (i%2==0 && j%2==0)allObjects[p+i*10+j]->color = ( Color( 0.0f, 0.0f, 0.0f ) );
                else if(i%2==0 && j%2!=0) allObjects[p+i*10+j]->color = ( Color( 1.0f, 1.0f, 1.0f ) );
                else if (i%2!=0 && j%2!=0) allObjects[p+i*10+j]->color = ( Color( 0.0f, 0.0f, 0.0f ) );
                else if(i%2!=0 &&  j%2==0) allObjects[p+i*10+j]->color = ( Color( 1.0f, 1.0f, 1.0f ) );
            }
        }
        nObjects = p+100;

    }

    int GetNrObjects()
    {
        return nObjects;
    }
    Object* GetObject( int a_Idx )
    {
        return allObjects[a_Idx];
    }

};
