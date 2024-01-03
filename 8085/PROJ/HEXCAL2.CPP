#ifndef __run1__
#include<iostream.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#endif

char *dec_2_binstring(int inputnumber)
{
  char result[10]="";
  char *abc="";
  div_t div1;

  while(div1.quot > 1)
  {
    div1 = div(inputnumber,2) ;
    if (div1.rem != 0)
	 strcat(result,"1");
    else
	 strcat(result,"0");
    inputnumber = div1.quot;
  }

   if (div1.quot != 0)
	 strcat(result,"1");
    else
	 strcat(result,"0");

     while(strlen(result) <= 7)
     {
	strcat(result,"0");
     };
    strrev(result);
  //cout<< result;
  strcpy(abc,result);
  return abc;
}
