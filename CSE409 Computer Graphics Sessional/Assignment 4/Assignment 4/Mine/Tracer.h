World world;

Object* traceRay( Color& acc_color, Ray& ray,  int a_Depth, float& a_Dist )
{
    if (a_Depth > nBumps) return 0;
    // trace primary ray
    a_Dist = 1000000.0f;
    Vector pi;//point of intersection

    Object* prim = 0;
    //acc_color = Color( 0, 0, 0);
    int result;
    float n= 1000005.0f;
    // find the nearest intersection
    for ( int s = 0; s < world.GetNrObjects(); s++ )
    {
        Object* pr = world.GetObject( s );
        int res;
        res = pr->intersect( ray, a_Dist );
        if (res)
        {

            {
                prim = pr;
                result = res;
            }
        }
    }

    if (!prim)
    {
        acc_color = Color( 0, 0, 0); // it hit's noting
        return 0;
    }

    // handle intersection
    if (prim->isLight)
    {
        // we hit a light, stop tracing
        acc_color = Color( 1.0f, 1.0f, 1.0f );
    }
    else
    {
        // determine color at point of intersection
        ray.direction.normalize() ;
        pi = ray.origin + ray.direction * a_Dist;
        // trace lights
        acc_color += 0.4*prim->color;
        for ( int l = 0; l < world.GetNrObjects(); l++ )
        {
            Object* p = world.GetObject( l );
            if (p->isLight)
            {
                Object* light = p;

                float shade = 1.0f;
                if (light->type == Object::SPHERE)
                {
                    Vector L = ((Sphere*)light)->center - pi;
                    float tdist = L.length();
                    L *= (1.0f / tdist);
                    Ray r = Ray( pi + L * EPSILON, L );
                    for ( int s = 0; s < world.GetNrObjects(); s++ )
                    {
                        Object* pr = world.GetObject( s );
                        if ((pr != light) && (pr->intersect( r, tdist )))
                        {
                            shade = 0;
                            break;
                        }
                    }
                }

                // calculate diffuse shading
                Vector L = ((Sphere*)light)->center - pi;
                L.normalize();
                Vector N = prim->getNormal( pi );
                if (prim->coeff_diff > 0)
                {
                    float dot = N.dot(L);
                    if (dot > 0)
                    {
                        float diff = dot * prim->coeff_diff* shade;
                        // add diffuse component to ray color
                        acc_color += diff *( prim->color * light->color);
                    }
                }

                if (prim->coeff_spec > 0)
                {
                    // point light source: sample once for specular highlight
                    Vector V = ray.direction;
                    Vector R = L - 2.0f * L.dot(N) * N;
                    float dot = V.dot(R);
                    if (dot > 0)
                    {
                        float spec = powf( dot, 25 ) * prim->coeff_spec* shade ;
                        // add specular component to ray color
                        acc_color += spec * light->color;
                    }
                }
            }


        }
        float refl = prim->coeff_reflection;
        if (refl > 0.0f)
        {
            Vector N = prim->getNormal( pi );
            Vector R = ray.direction - 2.0f * ray.direction.dot(N) * N;
            if (a_Depth < nBumps)
            {
                Color rc( 0, 0, 0 );
                float dist;
                Ray ray( pi + R * EPSILON, R );
                // ray.SetOrigin(pi+ R * EPSILON);
                traceRay( rc, ray, a_Depth + 1, dist );
                acc_color += refl * rc * prim->color;
            }
        }

    }

    return prim;
}

void initTracing(Camera& cam)
{

    printf("w h %f %f\n", cam.W, cam.H);

    Ray theRay;
    theRay.origin = (Vector(cam.eye.x,cam.eye.y,cam.eye.z));
    float blockWidth  = 2 *cam.W / (float)cam.nCols;
    float blockHeight = 2 *cam.H / (float)cam.nRows;


    printf("%f %f\n", blockWidth, blockHeight);

    float x, y;
    bitmap_image image(nPixel,nPixel);

    for(int row = 0; row < cam.nRows; row ++)
    {
        for(int col = 0; col < cam.nCols; col ++)
        {
            Color clr(0,0,0);

            x = -cam.W + col * blockWidth;
            y = -cam.H + row * blockHeight;
  //          printf("%d %d: x: %f, y %f ", row, col, x,y);

            theRay.direction =  Vector(-cam.nearDist * cam.n.x + x * cam.u.x + y *cam.v.x,
                                       -cam.nearDist * cam.n.y + x * cam.u.y + y * cam.v.y,
                                       -cam.nearDist * cam.n.z + x * cam.u.z + y * cam.v.z);
            theRay.direction.normalize();


            int a_Depth=1;
            float a_RIndex=1 ,a_Dist=10 ;


            traceRay( clr, theRay, a_Depth,  a_Dist );


            float r=clr.x*256.0,g=clr.y*256.0,b=clr.z*256.0;
            if(r>255) r=255;
            if(g>255) g=255;
            if(b>255) b=255;



//        printf("%d %d :: %f, %f %f\n", col,cam.nRows-row, r,g,b);
        image.set_pixel(row,col,r,g,b);

        }

     //   printf("Done row: %d\n", row);
    }
    printf("Saving the image\n") ;
    image.save_image("output.bmp");

}
