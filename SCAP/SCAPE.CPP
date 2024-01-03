//Game - Scape Created by Amit Kumar

#include<iostream.h>
#include<fstream.h>
#include<graphics.h>
#include<math.h>
#include<dos.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include"loader.cpp"
#include"flirt.cpp"

void main()
{

  initilize_graphics(); // initilize graphics
  setbkcolor(0);
  image_retrive("non.img");
  // display welcome screen

  amit_needs_mouse();//initilize mouse

  int scan1,scan2,scan3,scan4;
  int x = m_x() , y = m_y();
  int prevx,prevy,xdiff,ydiff,jumps = 0;
  outtextxy(1,5,mess[jumps]);

  changecursor(c[1]);
  m_showptr();
  m_setposn(3,15);
  m_speed(26,42,64);

  do{
      x = m_x() ; y = m_y();
      prevx = m_x() ; prevy = m_y();

      scan1 = getpixel( x , y );scan2 = getpixel( x + 4 , y );
      scan3 = getpixel( x , y + 4 );scan4 = getpixel( x + 4 , y + 4 );
      if ((scan1 != 0)||(scan2 != 0)||(scan3 != 0)||(scan4 != 0))
	{
	  jumps++;
	  setcolor(0);
	  outtextxy(1,5,"께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께");
	  outtextxy(2,5,"께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께");
	  outtextxy(3,5,"께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께께");
	  setcolor(14);
	  outtextxy(1,5,mess[jumps]);
	  delay(100);
	}
     //xdiff = abs(m_x() -  prevx);
    // ydiff = abs(m_y() -  prevy);

    // if ((xdiff > 35) || (ydiff > 35) ) break;
   if (jumps >= 10) break;
  }while( !kbhit() );

   close_graphics(); // come back to crt mode
}// end of main