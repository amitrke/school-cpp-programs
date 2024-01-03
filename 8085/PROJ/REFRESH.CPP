void refresh_common(int fcs, int fac, int fz, int fs, int fp)
{
  switch (fcs)
    {
      case 8 :break;
      case 0 : cs = 0 ; break;
      case 1 : cs = 1 ; break;
      case 2 :
	    {
	      if ( cs == 1) cs = 0;
	      if ( cs == 0) cs = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a > 255)
		{
		  cs = 1;
		  a = a - 256;
		}
	      else
		{
		  cs = 0;
		}
	      break;
	    }
    }//end of switch fcs

  switch (fac)
    {
      case 8 :break;
      case 0 : ac = 0 ; break;
      case 1 : ac = 1 ; break;
      case 2 :
	    {
	      if ( ac == 1) ac = 0;
	      if ( ac == 0) ac = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a > 255)
		{
		  ac = 1;
		  a = a - 256;
		}
	      else
		{
		  ac = 0;
		}
	      break;
	    }
    }//end of switch fac

  switch (fz)
    {
      case 8 :break;
      case 0 : z = 0 ; break;
      case 1 : z = 1 ; break;
      case 2 :
	    {
	      if ( z == 1) z = 0;
	      if ( z == 0) z = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a == 0)
		{
		  z = 1;
		}
	      else
		{
		  z = 0;
		}
	      break;
	    }
    }//end of switch z

    switch (fs)
    {
      case 8 :break;
      case 0 : s = 0 ; break;
      case 1 : s = 1 ; break;
      case 2 :
	    {
	      if ( s == 1) s = 0;
	      if ( s == 0) s = 1;
	      break;
	    }
      case 7 :
	    {
	      if (a < 0)
		{
		  s = 1;
		  a = abs(a);
		}
	      else
		{
		  s = 0;
		}
	      break;
	    }
    }//end of switch s


    switch (fp)
    {
      case 8 :break;
      case 0 : p = 0 ; break;
      case 1 : p = 1 ; break;
      case 2 :
	    {
	      if ( p == 1) p = 0;
	      if ( p == 0) p = 1;
	      break;
	    }
      /*case 7 :
	    {
	      if (a < 0)
		{
		  s = 1;
		  a = abs(a);
		}
	      else
		{
		  s = 0;

		}
	      break;
	    }
      */
    }//end of switch s
}

void ud_hl()
{
  // update hl
  char s1[32],s2[16];
  h = 26;l = 33;
  strcpy(s1,dec_2_binstring(h));
  strcpy(s2,dec_2_binstring(l));
  strcat(s1,s2);
  hl = str_2_dec(s1);
}

void ud_bc()
{
  // update bc
  char s1[32],s2[16];
  strcpy(s1,dec_2_binstring(b));
  strcpy(s2,dec_2_binstring(c));
  strcat(s1,s2);
  bc = str_2_dec(s1);
}
void ud_de()
{
  // update de
  char s1[32],s2[16];
  strcpy(s1,dec_2_binstring(d));
  strcpy(s2,dec_2_binstring(e));
  strcat(s1,s2);
  de = str_2_dec(s1);
}

void ud_b_c()
{
   long templong;
   char tempstring2[16],m[16];

   //update b&c
   strcpy(tempstring2 , int_2_string(bc));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(m);
   c = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   b = bin_2_dec(templong);
}
void ud_d_e()
{
   long templong;
   char tempstring2[16],m[16];
   //update de pair
   strcpy(tempstring2 , int_2_string(de));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(tempstring2);
   e = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   d = bin_2_dec(templong);
}
void ud_h_l()
{
  long templong;
   char tempstring2[16],m[16];
  //update hl pair
   strcpy(tempstring2 , int_2_string(hl));
   strcpy(m,tempstring2);
   templong = str_2_8bit_lower(tempstring2);
   l = bin_2_dec(templong);
   templong = str_2_8bit_higher(m);
   h = bin_2_dec(templong);
}

