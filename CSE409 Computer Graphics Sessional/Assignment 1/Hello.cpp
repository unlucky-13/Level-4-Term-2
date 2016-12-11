#include<stdio.h>
#include<graphics.h>
  //#include<conio.h>

  void main()
  {
              int gd=DETECT, gm,size;
              char *buff;
               initgraph(&gd,&gm," ");
              outtextxy(100,80,"Original  image:");
              rectangle(100,200,200,275);
              size=imagesize(100,200,200,275);
              buf=malloc(size);
              getimage(100,200,200,275,buf);
              outtextxy(100,320,"Captured  image:");
              putimage(100,340,buf,COPY_PUT);
               getch();
               closegraph();
}
