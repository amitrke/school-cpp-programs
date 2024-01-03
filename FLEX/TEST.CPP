#include<iostream.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<fstream.h>
#include"\tc\scap\loader.cpp"

void main()
{
  clrscr();
  amit_needs_mouse();
  do{
     if (m_button() == 1)
       {
	 cout <<"\nyou clicked..!";
	 cout <<"xxwwee\n\n";
       }
     }while(!kbhit());

}