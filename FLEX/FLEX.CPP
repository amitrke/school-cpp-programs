// (c) - Amit logic streams INC.
// Project started on 23rd november 1999

#include<iostream.h>
#include<graphics.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<fstream.h>
#include<alloc.h>
#include"\tc\scap\loader.cpp"
#include"engine.cpp"
#include"starter.cpp"
#include"welcome.cpp"


void main()
{
  initilize_graphics();

  //welcome_screen();
  cls(0);
  int fx_col = 15, fx_bkcol = 0, fx_m_speed = 1;

  amit_needs_mouse(); // initilise mouse



  do{
    gra_m_loc(563,5,fx_col); // print current location of pionter
    check_n_hilight_mainmenu(fx_col);//hiligits , dehiligits the mainmenu

    if ( (m_button() == 1) && (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 10) && (m_x() <= 57))
       {
	 menupop_file(fx_col);
       }
    if ( (m_button() == 1) && (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 57) && (m_x() <= 100))
       {
	 menupop_edit();
       }
    if ( (m_button() == 1) && (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 106) && (m_x() <= 154))
       {
	  menupop_color();
       }
    if ( (m_button() == 1) && (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 160) && (m_x() <= 208))
       {
	 menupop_shape();
       }
    if ( (m_button() == 1) && (m_y() >= 1) && (m_y() <= 11) && (m_x() >= 219) && (m_x() <= 260))
       {
	 menupop_help();
       }
  }while(!kbhit());
  close_graphics();//graphics are colsed & crt mode is restored

}//end of main