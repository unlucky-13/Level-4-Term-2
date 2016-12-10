/// pos,u,r,l
/// spheres , spheres
/// 0 is pressed render the image
void ray_tracing(){
        for(int i=-screen;i<=screen;i++){
            for(int j=-screen;j<=screen;j++){
                Point direction = l*near_distance+r*i+u*j ;
                direction.show() ;
            }
        }

        // go l

}

