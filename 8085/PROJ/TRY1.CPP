#include"hexcal.cpp"
#include<iostream.h>
#include<conio.h>
void main()
{
  clrscr();
  char *num;

  cout<<"Enter binary ..";
  cin>>num;
  cout<<"\nIts dec equvilant is = "<<string_2_int(num);
  getch();
}