#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include<dos.h>
#include <conio.h>

int main(void)
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
   int mx = getmaxx(),my = getmaxy();
   /* draw a line */
   setcolor(1);
   rectangle(0, 0, mx, my);
   settextstyle(4,0,6);
   setcolor(12);
   outtextxy(90,10,"Bootable CD-ROM");
   int radius;

      setcolor(7);
   settextstyle(5,0,3);
   outtextxy(300,70,"Version 1.4");
   setcolor(10);
   settextstyle(10,0,2);
   outtextxy(30,90,"INCLUDES..");

   setcolor(11);
   settextstyle(7,0,3);
   outtextxy(130,170,"Windows 2000");
   outtextxy(130,200,"Windows 98");
   outtextxy(130,230,"Windows 95");
   outtextxy(130,260,"Device Drivers");

   setcolor(14);
   settextstyle(2,0,5);
   outtextxy(330,175,"RBDC9-VTRC8-D7972-J97JY-PRVMG");
   outtextxy(330,210,"MBDYG-9GDHJ-HBMFQ-6KY78-4JQJQ");
   outtextxy(330,240,"14396-0017292-85453");

   setcolor(9);
   settextstyle(5,0,1);
   outtextxy(4,440,"Mail me at : Amit_kumar8@yahoo.com or Radioactiveamit@hotmail.com");

     for(radius = 1;radius<=25;radius++)
     {
       setcolor(radius);
       circle(30,30,radius);
       delay(40);
     }
   for(radius = 1;radius<=500;radius++)
     {
       line(40,80,40+radius,80);
       delay(10);
     }

   /* clean up */
   getch();
   closegraph();
   return 0;
}

