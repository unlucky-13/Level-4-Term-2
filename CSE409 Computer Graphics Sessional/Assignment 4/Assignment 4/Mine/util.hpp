

void addPlanes(Cube cube){



}

void readFromFile()
{

    nObjects = 0;

    scanf("%d", &nBumps);

    scanf("%d", &nPixel);

    scanf("%d", &nObjects);


    printf("Bumps: %d\n Number of objects: %d\n Resolution: %d x %d\n", nBumps, nObjects, nPixel, nPixel);



    float x,y,z,r;
    for(int i=0; i<nObjects; i++)
    {

        int type;
        scanf("%d", &type);



        if(type == 1)   //Sphere
        {



            scanf("%f %f %f", &x, &y, &z);
            scanf("%f", &r);

            spheres[nSpheres] = Sphere(Point(x,y,z),r);

            scanf("%f %f %f", &x, &y, &z);

            spheres[nSpheres].setColor(Color(x,y,z));

            scanf("%f", &x);
            spheres[nSpheres].setambient(x);

            scanf("%f", &x);
            spheres[nSpheres].setdiffuse(x);

            scanf("%f", &x);
            spheres[nSpheres].setspecular(x);

            scanf("%f", &x);
            spheres[nSpheres].setreflection(x);

            scanf("%f", &x);
            spheres[nSpheres].setshininess(x);


            //  spheres[nSpheres].print();

            nSpheres++;


        }
        else            //Cube
        {


            scanf("%f %f %f", &x, &y, &z);
            scanf("%f", &r);

            cubes[nCubes] = Cube(Point(x,y,z),r);

            scanf("%f %f %f", &x, &y, &z);

            cubes[nCubes].setColor(Color(x,y,z));

            scanf("%f", &x);
            cubes[nCubes].setambient(x);

            scanf("%f", &x);
            cubes[nCubes].setdiffuse(x);

            scanf("%f", &x);
            cubes[nCubes].setspecular(x);

            scanf("%f", &x);
            cubes[nCubes].setreflection(x);

            scanf("%f", &x);
            cubes[nCubes].setshininess(x);

            nCubes++;

        }
    }

    scanf("%d", &nLightSources);

    for(int i=0; i<nLightSources; ++i)
    {


        scanf("%f %f %f", &x, &y, &z);
        lights[i] = LightSource(Point(x,y,z));


    }

       printf("     Spheres: %d, cubes: %d, Lights sources: %d\n", nSpheres, nCubes, nLightSources);






}
