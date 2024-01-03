#ifndef __run1__
#include<iostream.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#endif

long str_2_dec(char *inputstr)
{
  int loop,readval,m;
  long multp,ans=0,temp1;
 for (loop = 15;loop >= 0 ;loop --)
   {
     if (inputstr[loop] =='1') readval = 1;
	else
	  readval =0;
      temp1 = 1;
      for ( m = 0 ; m < 15-loop ; m++)
	{
	  temp1 = temp1 * 2;
	 /* if ((temp1 > 9999) && (temp1 < 10005))
	    temp1 = 10000;
	    */
	}
      multp = readval * temp1;
      ans += multp;
   }

 return ans;
}
char *int_2_string(long inputnumber)
{
  char result[16]="";
  char abc[16]="";
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

    while(strlen(result) <= 15)
     {
	strcat(result,"0");
     };
    strrev(result);
  //cout<< result;
  strcpy(abc,result);
  return abc;
}

char *dec_2_binstring(int inputnumber)
{
  char result[10]="";
  char  *abc;
  strcpy(abc,"");
  div_t div1;
  div1.quot = inputnumber;
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

int bin_2_dec(long inputnum)
{
  ldiv_t res1;
  int m;
  int temp1 = 1;
  long temp,loop = 0,multp,ans = 0;
  do{
   res1 = ldiv(inputnum,10);
   inputnum = res1.quot;
   temp = res1.rem;
   //multp = pow(2,loop);
      temp1 = 1;
      for ( m = 0 ; m < loop ; m++)
	{
	  temp1 = temp1 * 2;
	  /*if ((temp1 > 9999) && (temp1 < 10005))
	    temp1 = 10000;
	    */
	}

   ans += temp * temp1;
   loop++;
  }while(inputnum >= 1);
  return ans;
}

int string_2_int( char *str)
{
  int current = strlen(str) - 1;
  int powerfactor = 0;
  int result = 0;
  do{
    if (str[current] == '1')
      {
	result = result + pow(2,powerfactor);
      }
    current--;
    powerfactor++;
  }while(current >= 0);

  return result;
}

long str_2_8bit_lower(char *string2)
{
  long ans=0;
  double temp=1;
  int i,readval,m;
  for (i=15;i>=8;i--)
    {
     temp = 1;
      for ( m = 1 ; m<= 15-i ; m++)
	{
	  temp = temp *10;
	  if ((temp > 9999) && (temp < 10005))
	    temp = 10000;
	  if ((temp > 9999) && (temp < 10005))
	    temp = 10000;
	  if ((temp > 999999) && (temp < 1000505))
	    temp = 1000000;
	  if ((temp > 9999999) && (temp < 10050505))
	    temp = 10000000;
	}
      if (string2[i] == '1') readval = 1;
       else
	readval = 0;
      ans += temp*readval;
    }
  return ans;
}

long str_2_8bit_higher(char *string2)
{
  long ans=0;
  ans=ans;
  double temp ;
  int m,i,readval;
  for (i=7;i>=0;i--)
    {
      //temp = pow(10,7-i);
      temp = 1;
      for ( m = 1 ; m<= 7-i ; m++)
	{
	  temp = temp *10;
	  if ((temp > 9999) && (temp < 10005))
	    temp = 10000;
	  if ((temp > 9999) && (temp < 10005))
	    temp = 10000;
	  if ((temp > 999999) && (temp < 1000505))
	    temp = 1000000;
	  if ((temp > 9999999) && (temp < 10050505))
	    temp = 10000000;
	}
      if (string2[i] == '1') readval = 1;
       else
	readval = 0;
      ans += temp*readval;
    }
  return ans;
}