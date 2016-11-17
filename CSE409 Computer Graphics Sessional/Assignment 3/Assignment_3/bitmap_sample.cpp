#include"bitmap_image.hpp"


int main()
{
    bitmap_image image(500,300);  // Creating an image
    for(int i=0;i<200;i++)
        for(int j=0;j<50;j++)
            image.set_pixel(i,j,255,0,0);  // Setting some pixels as red

    image.save_image("sample.bmp");    // Saving the image in a file

    return 0;
}
