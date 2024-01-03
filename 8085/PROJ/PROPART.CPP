case 0xce: // aci data
   {
      fscanf(fp,"%x",&temphex);
     if (label_chk.flag == 0)
       {
         a = a + temphex + cs;
         refresh_flags();
       }

   }
case 0x8f:// adc a
   {
     if (label_chk.flag == 0)
       {
         a = a + a + cs;
         refresh_flags();
       }
   }
case 0x88:// adc b
   {
     if (label_chk.flag == 0)
        {
          a = a + b + cs;
          refresh_flags();
        }
   }
case 0x89:// adc c
   {
     if (label_chk.flag == 0)
      {
        a = a + c + cs;
        refresh_flags();
      }
   }
case 0x8a:// adc d
   {
     if (label_chk.flag == 0)
       {
         a = a + d + cs;
         refresh_flags();
       }
   }
case 0x8b:// adc e
   {
     if (label_chk.flag == 0)
           {
             a = a + e + cs;
             refresh_flags();
           }
   }
case 0x8c:// adc h
   {
     if (label_chk.flag == 0)
       {
         a = a + h + cs;
         refresh_flags();
       }
   }
case 0x8d:// adc l
   {
     if (label_chk.flag == 0)
       {
         a = a + l + cs;
         refresh_flags();
       }
   }
case 0x8e:// adc m
   {
     if (label_chk.flag == 0)
       {
         a = a + hl + cs;
         refresh_flags();
       }
   }

// add instructions

case 0x87://add a
   {
      if  (label_chk.flag == 0)
        {
          a = a + a;
          refresh_flags();
        }
   }
case 0x87://add a
   {
      if  (label_chk.flag == 0)
        {
          a = a + a;
          refresh_flags();
        }
   }
case 0x80://add b
   {
      if  (label_chk.flag == 0)
        {
          a = a + b;
          refresh_flags();
        }
   }
case 0x81://add c
   {
      if  (label_chk.flag == 0)
        {
          a = a + c;
          refresh_flags();
        }
   }
case 0x82://add d
   {
      if  (label_chk.flag == 0)
        {
          a = a + d;
          refresh_flags();
        }
   }
case 0x83://add e
   {
      if  (label_chk.flag == 0)
        {
          a = a + e;
          refresh_flags();
        }
   }
case 0x84://add h
   {
      if  (label_chk.flag == 0)
        {
          a = a + h;
          refresh_flags();
        }
   }
case 0x85://add l
   {
      if  (label_chk.flag == 0)
        {
          a = a + l;
          refresh_flags();
        }
   }
case 0x86://add m
   {
      if  (label_chk.flag == 0)
        {
          a = a + hl;
          refresh_flags();
        }
   }

case 0xc6: // adi data
   {
      fscanf(fp,"%x",&temphex);
     if (label_chk.flag == 0)
       {
         a = a + temphex;
         refresh_flags();
       }

   }

//ana ins

case 0xa7://ana a
   {
      if  (label_chk.flag == 0)
        {
          a = a & a;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa0://ana b
   {
      if  (label_chk.flag == 0)
        {
          a = a & b;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa1://ana c
   {
      if  (label_chk.flag == 0)
        {
          a = a & c;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa2://ana d
   {
      if  (label_chk.flag == 0)
        {
          a = a & d;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa3://ana e
   {
      if  (label_chk.flag == 0)
        {
          a = a & e;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa4://ana h
   {
      if  (label_chk.flag == 0)
        {
          a = a & h;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa5://ana l
   {
      if  (label_chk.flag == 0)
        {
          a = a & l;
          refresh_flags(0,1,7,7,7);
        }
   }
case 0xa6://ana m
   {
      if  (label_chk.flag == 0)
        {
          a = a & hl;
          refresh_flags(0,1,7,7,7);
        }
   }

case 0xe6://ani data
   {
      fscanf(fp,"%x",&temphex);     
      if  (label_chk.flag == 0)
        {
          a = a & temphex;
          refresh_flags(0,1,7,7,7);
        }
   }

case 0xcd: //call label
    {
      fscanf(fp,"%x",&temphex);     
      if  (label_chk.flag == 0)
        {
          label_chk.flag = 1;
          label_chk.locaddr = temphex;

        }
      
    }
