#define __RUN1__
#define MAX_MEM 10
 // define structure for memory calculations
 struct memory{
   int addr;
   int content;
 }mem[10];

#include"memory.cpp"
#include<iostream.h>
#include<stdio.h>
#include<conio.h>

void main()
{
  clrscr();
  write_to_memory(2,10);
  cout<<read_from_memory(2);
  //char *bin = "1111111111111111";
  //int p = ;
  //cout<<"Binary = "<<dec_2_binstring(p);
  //cout<<str_2_dec(bin);
  //cout<<"The lower nibble is ="<<str_2_8bit_lower(bin)<<endl;
  //cout<<string_2_int(int_2_string(str_2_4bit_lower(bin)));
  getch();
  //cout<<"The higher nibble is ="<<str_2_4bit_higher(bin);
}