// A program to stimulate Seico's Database management
// Created by Amit Kumar
// (c) 1999 Amit_logic_streams
#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<fstream.h>
#include"tools.cpp"
#include"help.cpp"
#include"used.cpp"
#include"mainfil.cpp"
#include"purchase.cpp"
#include"viewer.cpp"
#include"del.cpp"

void main_menu();

struct dt
  {
    int date,month,year;
  };
struct m1
  {
    char compo[25];
    int quan;
  } main1;

struct o1
  {
    char compo[25];
    int quan;
    date datex;
    char man[30];
  }io;

void main()
{
  welcome_screen();
  main_menu();
}// end of main
void main_menu()
{
  clrscr();
  aout(2,"컴컴MAIN MENU컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�");
  cout<<"\n\tH --> Help"
	<<"\n\tP --> An item is purchased"
	<<"\n\tU --> A component is used"
	<<"\n\tV --> View various data bases"
	<<"\n\tD --> Delete records"
	<<"\n\tX --> Exit";

  char choice = status_bar(" Enter choice");
  redo:
  // filter correct choices
  if ((choice != 'h') && (choice != 'p') && (choice != 'u')
	&& (choice != 'v') && (choice != 'd') && (choice != 'x'))
	{
	  choice = status_bar(" Incorrect choice - Try Again");
	  goto redo;
	}
  // transfer control according to the given choices
  switch (choice)
    {
      case 'h':help_main();
      case 'p':item_purchased();
      case 'u':item_used();
      case 'v':view_database();
      case 'd':delete_records();
      case 'x':exit_main();
    }// end of switch

}
