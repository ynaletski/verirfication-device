
//-------------------------

unsigned int flash_seg   =0xD000;
unsigned int flash_offset=0;

struct arch_str ar_str;
struct arch_str_t tim_000 = {
0,34,1,
30,7,9
};


int f_wr_evt( unsigned int evt )
{
  Last_evt = evt;
  f_prepare_evt ( &ar_str, evt);
  return  f_wr_astr(&ar_str);
}
//----------------------------------
int  f_wr_astr (struct arch_str *s_arch )
{// �����뢠�� �����⮢������ �������� �� ���
long int ltmp;
int i,ret_val;
unsigned int utmp;
char *data;

// if(ICP_error[icp_lst_max] & (Flash_erase_error | Flash_wr_error) ) return -1;

  ret_val=0;
  ltmp= ((long int)flash_offset & 0xffff) + sizeof(ar_str);
  if(ltmp >= (long int)0x10000)
  {
   flash_seg= f_get_next_seg(flash_seg);
   flash_offset=0;
  }
 utmp=flash_offset;
 data=(char *)s_arch;
 for(i=0;i< sizeof(ar_str);i++,data++)
   if (FlashWrite(flash_seg, (flash_offset+i), *data) != 0)
   {
     ICP_error[icp_lst_max] |= Flash_wr_error;
     ret_val=1;
     break;
   }
 flash_offset= utmp + sizeof(ar_str);

 //printf("\n\r Seg=%04x,offset=%04X",flash_seg,flash_offset);
 return ret_val;
}
//----------------------------------
int  f_get_max_n_arch()
{// �����頥� ������⢮ ����ᠭ��� �������
int nn;
unsigned int seg_tmp;
unsigned int  *Flash_ptr_i;

  nn=((long int)flash_offset & 0xffff) / sizeof(ar_str);

  seg_tmp= f_get_prev_seg(flash_seg);
  Flash_ptr_i=(unsigned int  *) _MK_FP_(seg_tmp,(unsigned int)0);

  if(*Flash_ptr_i == 0xffff)
  {
   return nn;
  }
    nn+=(long int)0x10000 / sizeof(ar_str);

  seg_tmp= f_get_prev_seg(seg_tmp);
  Flash_ptr_i=(unsigned int  *) _MK_FP_(seg_tmp,(unsigned int)0);
  if(*Flash_ptr_i == 0xffff)
  {
   return nn;
  }
  nn+=(long int)0x10000 / sizeof(ar_str);
  return nn;
}
//----------------------------------

void  f_print_a_str(int i)
{
 struct arch_str *a_str;
 if( (a_str= f_get_astr(i)) == NULL ) return;
 f_print_str_a(a_str);
}
//----------------------------------

char *rcv_m[]={
"����",
"�ਥ�",
};
char *Rcv_m[]={
"����",
"�ਥ�",
};
// rcv_m[f_rcv]

int f_print_str_a(struct arch_str *a_str)
{
 int ii,itmp;
 float ftmp,ftmp1;
 struct tm *tdat;
 int f_rcv;

 if(a_str->event & (int)RCV_FLG)
       f_rcv=1;
 else
       f_rcv=0;

  tdat = localtime( &a_str->time );
  printf("\r\n%02d.%02d.%02d %02d:%02d:%02d",
  tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

//  printf("\n\r%02d.%02d.%02d %02d:%02d:%02d" ,a_str->day,a_str->month,a_str->year,a_str->hour,a_str->min,a_str->sec);
 /*
  if(a_str->VolI>= 0.)
     printf(" V=%10.3f" ,a_str->VolI);
  else
     printf(" ------------ ");
*/

 if( (a_str->event==slt_wr_jrnI) || (a_str->event==slt_wr_jrnF)  );
 else
  if((a_str->MassI != vBIG_P) && (a_str->MassI != M_one)  )
//   printf(" M=%10.3f" ,a_str->MassI);
     printf(" M=%10.3f V=%10.3f" ,a_str->MassI,a_str->VolI);
  else
     printf(" ------------" );

 switch( (int)( a_str->event & ~(int)RCV_FLG) )
 {
  case evt_beg_eq:
    printf(" ���� %s� � ��ࠢ������� �������� ��஢�� 䠧�",rcv_m[f_rcv]);
    goto m_val0;

  case slt_wr_jrnF:
    printf(" ���祭�� ������ MVD,float:");
    printf("\r\n Addr=%5.0f, n= %2.0f:",a_str->MassI,a_str->VolI/2.);
    printf(" %g",a_str->u.fill.VolT);

    if( a_str->VolI  > 2 )
      printf(", %g", a_str->u.fill.Amount);

    if( a_str->VolI  > 4 )
      printf(", %g", a_str->u.fill.UnitPrice);

    if( a_str->VolI  > 6 )
      printf(", %g", a_str->u.fill.Density);

    if( a_str->VolI  > 8 )
      printf(", %g", a_str->u.fill.Temp);

    break;

  case slt_wr_jrnI:
    printf(" ���祭�� ������ MVD,int:");
    printf("\r\n Addr=%5.0f, n= %2.0f:",a_str->MassI,a_str->VolI);

    for(ii=0;ii<a_str->VolI;ii++)
    {
      printf(" %d",a_str->u.err.err[ii] );
    }
    break;

  case evt_start_fL:
    printf(" ���� ����.������ ");
    goto m_val0;
  case evt_start_f:
    printf(" ���� ����.������ ");
m_val0:
    if(a_str->u.fill.VolT != vBIG_P)
     {
      if ( Flag_mass != 0 )
        printf("\r\n���� %8.3f ��; " ,a_str->u.fill.VolT    );  //%8.3f
      else
        printf("\r\n���� %8.3f � ; " ,a_str->u.fill.VolT    );  //%8.3f
     }
    else
      printf("\r\n ��� ����஢��  ; " );  //%8.3f
//    printf("\r\n���� %8.3fxxx ��; " ,a_str->u.fill.VolT    );  //%8.3f
//  printf("��.%6g ��;",a_str->u.fill.Amount  );  //%6.0f
//  printf("���� %6g ��/�;" ,a_str->u.fill.UnitPrice);
m_val1:
    printf("����.%7.3f ��/�3;" ,a_str->u.fill.Density);
//    printf("����.MVD %6.2fC;" ,a_str->u.fill.Temp);
    printf("����. %6.2fC;" ,a_str->u.fill.Temp);
    printf("\r\n�������� %6.3f ���  ;" ,a_str->u.fill.UnitPrice);
//    printf("����. %6.2fC;" ,a_str->u.fill.Amount);

    break;

  case evt_cont_f:
    printf(" �த������� %s� ",rcv_m[f_rcv]);
    goto m_val;
  case evt_end_gas:
    printf(" %s ��ࢠ�.� ��室���� ��� ������ 䠧�",Rcv_m[f_rcv]);
    goto m_val;
  case evt_end_f:
    printf(" �����襭� ��  ");

m_val:
    printf("\r\n���� %s� %8.3f ��;V=%8.3f �; " ,rcv_m[f_rcv],a_str->u.fill.VolT,a_str->u.fill.Amount );  //%8.3f
    goto m_val1;
/*
    printf("����.%7.3f ��/�3;" ,a_str->u.fill.Density);
    printf("����.%6.2fC;" ,a_str->u.fill.Temp);

    break;
*/
  case evt_exp_f:
    printf(" �����襭�.��५�� > �����⨬���");
    goto m_val;
  case evt_exm_f:
    printf(" �����襭�.������� > �����⨬���");
    goto m_val;

  case evt_est_f:
    printf(" %s ��ࢠ� ��������",Rcv_m[f_rcv]);
    goto m_val;
  case evt_est_fh:
    printf(" %s ��ࢠ� Host ",Rcv_m[f_rcv]);
    goto m_val;
  case evt_err_f:
    printf(" %s  ��ࢠ�:�訡�� ",Rcv_m[f_rcv]);
    goto m_val;

  case evt_ep1_f:
    printf(" %s  ��ࢠ�:������� Host",Rcv_m[f_rcv]);
    goto m_val;

  case evt_overfl:
    printf(" %s  ��ࢠ�:��⠭�� ��⮪�",Rcv_m[f_rcv]);
    goto m_val;

  case evt_ES_off:
    printf(" %s  ��ࢠ�:����� ��.������",Rcv_m[f_rcv]);
    goto m_val;

  case evt_UZA_off:
    printf(" %s  ��ࢠ�:��� ᨣ���� ���.",Rcv_m[f_rcv]);
    goto m_val;
  case evt_LVL_off:
    printf(" %s  ��ࢠ�:������ �஢���.",Rcv_m[f_rcv]);
    goto m_val;
  case evt_TRAP_off:
    printf(" %s  ��ࢠ�:�࠯ �� � ࠡ.���.",Rcv_m[f_rcv]);
    goto m_val;
  case evt_CONS_off:
    printf(" %s  ��ࢠ�:���᮫� �� � ࠡ.���.",Rcv_m[f_rcv]);
    goto m_val;

  case evt_DLT_off:
    printf(" %s  ��ࢠ�:���� �� ����祭",Rcv_m[f_rcv]);
    goto m_val;

  case evt_wd_pmp:
    printf(" %s  ��ࢠ�:������� �裡 � �����.",Rcv_m[f_rcv]);
    goto m_val;

  case evt_eq_pr :
    printf(" ���� ��ࠢ������� �������� ������� 䠧.");
    goto m_val;

  case evt_stop_eq :
    printf(" ������.��ࠢ������� �������� ���.䠧.");
    goto m_val;

  case evt_no_dev:
    printf(" ���� �� �ਭ��,Dr");
    goto m_val0;

  case evt_clr_err:
    printf(" ���� �訡��. ");
    break;

  case evt_MVD_CL_strt:
    printf(" ���� �����஢�� ��室����");
    break;

  case evt_MVD_CL_BS1 :
    printf(" !���-�� ������.��夬.�� ���᪥");
    break;

  case evt_MVD_CL_BS2 :
    printf(" !���� ����᪠ ������.��室����");
    break;

  case evt_MVD_CL_OK :
    printf(" ���-�� ��夬.�����襭� �ᯥ譮");
    break;

  case evt_MVD_CL_TM :
    printf(" ������� �����஢�� ��室����");
    break;

  case evt_ch_date:
    printf(" �������� ���.");
    break;
  case evt_ch_time:
    printf(" �������� �६�.");
    break;
  case evt_ch_sum :
    printf(" ���室 �� ��⭥� �६�.");
    break;
  case evt_ch_win :
    printf(" ���室 �� ������ �६�.");
    break;

  case evt_res:
    printf(" ������� \"����\"");
    break;
  case evt_Slot:
    printf(" ������ ���䨣.� MVD");
    break;
  case evt_chg_param:
    if(a_str->u.fill.VolT == Par_VF)
    {
     printf(" !������� �����⥫� ��ꥬ�");
    }
    else if(a_str->u.fill.VolT == Par_MF)
    {
     printf(" !������� �����⥫� �����");
    }
    else if(a_str->u.fill.VolT == Par_PASS)
    {
     printf(" !������� ��஫�");
    }
    else if(a_str->u.fill.VolT == Par_ID)
    {
     printf(" !������� ID");
     printf("\r\n�뫮 :%8ld; ",(long int)a_str->u.fill.Amount  );
     printf("�⠫�:%8ld" ,(long int)a_str->u.fill.UnitPrice);
     break;
    }
    else
    {
     printf(" !������� ��ࠬ��� ");
     printf("N%g",a_str->u.fill.VolT );
    }
    printf("\r\n�뫮:%8g;  ",a_str->u.fill.Amount  );
    printf("�⠫�:%8g" ,a_str->u.fill.UnitPrice);
    break;
  case evt_exit:
    printf(" �������\"��室 � ��\"");
    break;
  case evt_re:
    printf(" �⥭�� ����.�� EEPROM");
    break;
  case evt_re_err:
    printf(" ��.�⥭�� ����.EEPROM");
    break;
  case evt_we_err:
    printf(" ��.����� ����.EEPROM");
    break;
  case evt_we:
    printf(" ������ ����.� EEPROM");
    break;

  case evt_wrong_start:
    printf(" C��� %s� �� �ਭ��,Er",rcv_m[f_rcv]);
    goto m_val;

  case evt_err:
  case evt_none:
 mm_0:
    itmp=0;
    for(ii=0;(ii<=icp_lst_max)&& (ii<10) ;ii++)
      itmp |= a_str->u.err.err[ii];
  if(itmp)
  {
    printf(" �訡��:");
 mm_e:
    printf("%04X" ,a_str->u.err.err[0] );    // MVD
    printf(" %01X" ,a_str->u.err.err[1] );   // 7060
    printf(" %01X" ,a_str->u.err.err[2] );   // 7041
    printf(" %01X" ,a_str->u.err.err[3] );   // 7017
    printf(" %01X" ,a_str->u.err.err[4] );   // TSD[0]
    printf(" %01X" ,a_str->u.err.err[5] );   // Drive
    printf(" %04X" ,a_str->u.err.err[6] );   // OFP
    printf(" %01X" ,a_str->u.err.err[7] );   // MMI
    printf(" %04X:" ,a_str->u.err.err[8] );  // System
    printf("%04X" ,a_str->u.err.err[9] );    // ���
  }
  else
    printf(" �訡�� ��� ");

  break;

  case evt_t_on:
    printf(" ����祭�� ���ன�⢠ ");
    break;
  case evt_t_off:
    printf(" �몫�祭�� ���ன�⢠ ");
    break;
  default:

    if( (a_str->event & evt_start_hst) == evt_start_hst )
    {

    ii=a_str->event;
    printf("\r\n������� Host ");

    if(ii & 4)
      printf("����� ");
    else
      printf("���� ");

    if(ii & 1)
      printf("������� ������ ");
    else
      printf("���孥�� ������ ");

    if(ii & 2)
      printf("�� ����.\r\n���� %8.3f ��; " ,a_str->u.fill.VolT );
    else
      printf("�� ��ꥬ�.\r\n����  %8.3f � ; " ,a_str->u.fill.VolT    );

     goto m_val1;
    }
    else
       printf(" ��� ᮡ��� �� �ᯮ����");
    break;
 }
return 0;
}

//----------------------------------
struct arch_str *f_get_astr(int nn )
{// �����頥� 㪠��⥫� �� ������� ᮡ��� � ������� ����஬
 // nn == 0 - ��ࢠ� ����ᠭ��� �������
long int ltmp;
unsigned int seg_tmp,seg_tmp_1,seg_tmp_2;
unsigned int offset_tmp;
int mm,jj;
struct arch_str *a_str;

  mm=(long int)0x10000 / sizeof(ar_str);

  seg_tmp_1= f_get_prev_seg(flash_seg);
  seg_tmp_2=f_get_prev_seg(seg_tmp_1);

 if( nn < mm)
 {
   offset_tmp= nn * sizeof(ar_str);
   a_str=(struct arch_str *) _MK_FP_(seg_tmp_1,0);
   if(a_str->event == (unsigned int)0xffff)
     seg_tmp=flash_seg;
   else
   {
     a_str=(struct arch_str *) _MK_FP_(seg_tmp_2,0);
     if(a_str->event == (unsigned int)0xffff)
       seg_tmp=seg_tmp_1;
     else
       seg_tmp=seg_tmp_2;
   }
 }
 else
 {
  if((nn-mm)<mm)
  {
   offset_tmp= (nn-mm) * sizeof(ar_str);

   a_str=(struct arch_str *) _MK_FP_(seg_tmp_2,0);

   if(a_str->event == (unsigned int)0xffff)
     seg_tmp= flash_seg;
   else
     seg_tmp= seg_tmp_1;
  }
  else
  {
   offset_tmp= (nn-mm-mm) * sizeof(ar_str);
   seg_tmp= flash_seg;
  }
 }

 a_str=(struct arch_str *) _MK_FP_(seg_tmp,offset_tmp);
 if(a_str->event == (unsigned int)0xffff) return NULL;
 return a_str;
}

//----------------------------------
unsigned int retf_seg;
unsigned int retf_iii;
unsigned int retl_offs,retl_seg=0;
struct arch_str *f_get_fst_stor()
{ // �����頥� 㪠��⥫� �� ����� ������
unsigned int seg_tmp,seg_tmp_2,offs_tmp,utmp;
struct arch_str *ar_str_ptr;

 // ��।������ ��砫� ��ୠ��

  seg_tmp= f_get_prev_seg(flash_seg);
  ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,(unsigned int)0);
  if(ar_str_ptr->event != 0xffff)
  {
   seg_tmp_2= f_get_prev_seg(seg_tmp);
   ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp_2,(unsigned int)0);
   if(ar_str_ptr->event != 0xffff)
   {
    seg_tmp=seg_tmp_2;
   }
  }
  else
  {
    seg_tmp= flash_seg;
    ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,(unsigned int)0);
//    if(ar_str_ptr->event == 0xffff) return NULL; //qqqqq
  }

//  seg_tmp - ��砫�� ᥣ����
 retf_seg=seg_tmp;
 ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,(unsigned int)0);
 return ar_str_ptr;
}
//-------------------------------
struct arch_str *f_get_lst_stor()
{ // �����頥� 㪠��⥫� �� ��᫥���� ������

 struct tm *tdat;

unsigned int seg_tmp,offs_tmp;
struct arch_str *ar_str_ptr;
time_t ltime1;
long int ltmp;

  if(flash_offset != 0)
  {
    seg_tmp=flash_seg;
    offs_tmp=flash_offset-sizeof(ar_str);
    ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,offs_tmp);
 m1:
    ltime1= f_get_time(ar_str_ptr);
    if(ltime1 < 0)
    {
//    printf("\r\n return NULL ");
      retl_seg=seg_tmp;
      retl_offs=offs_tmp;
      return NULL;
    }
  }
  else
  {
    ltmp=0x10000;
    ltmp=((ltmp/(long int)sizeof(ar_str))-1) * (int)sizeof(ar_str);
    offs_tmp=ltmp & 0xffff;
    seg_tmp= f_get_prev_seg(flash_seg);
    ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,offs_tmp);

    if(ar_str_ptr->event == 0xffff) return NULL;
    else goto m1;
  }

 retl_seg=seg_tmp;
 retl_offs=offs_tmp;
//  printf("\r\nf_get_lst_stor() : seg_tmp=%04x,offs_tmp=%04x  ",seg_tmp,offs_tmp);
 return ar_str_ptr;
}
//-------------------------------

void f_prepare_evt (struct arch_str *s_arch, unsigned int evt )
{
  struct tm  mdat;
  TIME_DATE tim_dat;
  int year,month,day,hour,min,sec,i;
union  { float f; char c[4]; } o;

  s_arch->event=evt;
// switch ((int)evt)
 switch( (int)( evt & ~(int)RCV_FLG) )
 {
   case evt_t_off:

 mdat.tm_year = ((int)(ReadNVRAM( nr_year ))&0xff)+100;
 mdat.tm_mon   = ReadNVRAM( nr_month)-1 ;
 mdat.tm_mday  = ReadNVRAM( nr_day  ) ;
 mdat.tm_hour  = ReadNVRAM( nr_hour ) ;
 mdat.tm_min   = ReadNVRAM( nr_min  ) ;
 mdat.tm_sec   = ReadNVRAM( nr_sec  ) ;

 s_arch->time  = mktime( &mdat );

 o.c[0]= ReadNVRAM( nr_v0 );
 o.c[1]= ReadNVRAM( nr_v1 );
 o.c[2]= ReadNVRAM( nr_v2 );
 o.c[3]= ReadNVRAM( nr_v3 );
 s_arch->VolI   = o.f;
 o.c[0]= ReadNVRAM( nr_m0 );
 o.c[1]= ReadNVRAM( nr_m1 );
 o.c[2]= ReadNVRAM( nr_m2 );
 o.c[3]= ReadNVRAM( nr_m3 );
 s_arch->MassI  = o.f;
   return;

   case evt_t_on:
   break;


   case evt_start_hst:
     s_arch->event |= (Flag_Low & 1) | ((Flag_mass & 1) << 1 )| ((flag_dlv_fst & 1) << 2) ;
     goto m_strt;

   case evt_wrong_start:
   case evt_no_dev:
   case evt_start_f:
   case evt_start_fL:
   case evt_beg_eq:
m_strt:
    s_arch->u.fill.VolT       = volume_f;
    s_arch->u.fill.Amount     = s_MVD[0].TempR;
    s_arch->u.fill.UnitPrice  = s_MVD[0].Press;
    s_arch->u.fill.Density    = s_MVD[0].Dens;
    s_arch->u.fill.Temp       = s_MVD[0].Temp;
   break;

   case evt_cont_f :   // �த������� ���᪠
   case evt_exm_f  :   // �������
   case evt_exp_f  :   // ��५��
   case evt_end_f  :   // End OK
   case evt_end_gas:   // ��� ������ 䠧�
   case evt_est_f  :   // Command Stop filling
   case evt_est_fh :   // Command Stop from Host
   case evt_err_f  :   // Error Stop filling
   case evt_ep1_f  :   // Host  Stop filling
   case evt_overfl :   // ��९�������
   case evt_ES_off :   // ES
   case evt_UZA_off:   // ���
   case evt_LVL_off:   // �஢���
   case evt_TRAP_off:  // �࠯
   case evt_CONS_off:  // ���᮫�
   case evt_DLT_off:   // DELTA
   case evt_eq_pr  :   // ��ࠢ������� �������� ������� 䠧�
   case evt_wd_pmp :   // ������� �裡

    s_arch->u.fill.VolT=s_MVD[0].MassT;

//  s_arch->u.fill.Amount     = s_MVD[0].TempR;
    s_arch->u.fill.Amount     = s_MVD[0].VolT;;
    s_arch->u.fill.UnitPrice  = s_MVD[0].Press;
//  s_arch->u.fill.Density    = s_MVD[0].Dens;
//  s_arch->u.fill.Temp       = s_MVD[0].Temp;

    s_arch->u.fill.Density    = Dens_a;
    s_arch->u.fill.Temp       = Temp_a;

//    s_arch->u.fill.Density    = Dens0;
//    s_arch->u.fill.Temp       = Temperature1;

   break;

    case evt_chg_param:   // ������� ��ࠬ��� �१ MMI

    s_arch->u.fill.VolT       = chg_nn_par;
    s_arch->u.fill.Amount     = chg_old;
    s_arch->u.fill.UnitPrice  = chg_new;
   break;

    case slt_wr_jrnI:   // ������ ᫮� � 楫묨 ॣ���ࠬ�

    s_arch->VolI      = SLT3_N;
    s_arch->MassI     = SLT3_A;

    for(i=0;i<10 ;i++)
      s_arch->u.err.err[i]  = Slot3_dat[i];

   goto mm_end;

    case slt_wr_jrnF:   // ������ ᫮� � float ॣ���ࠬ�

    s_arch->VolI      = SLT3_N;
    s_arch->MassI     = SLT3_A;

    if(SLT3_N>0)
      s_arch->u.fill.VolT      = f_get_float_i( &Slot3_dat[0]);

    if(SLT3_N>2)
      s_arch->u.fill.Amount    = f_get_float_i( &Slot3_dat[2]);

    if(SLT3_N>4)
      s_arch->u.fill.UnitPrice = f_get_float_i( &Slot3_dat[4]);

    if(SLT3_N>6)
      s_arch->u.fill.Density   = f_get_float_i( &Slot3_dat[6]);

    if(SLT3_N>8)
      s_arch->u.fill.Temp      = f_get_float_i( &Slot3_dat[8]);

    goto mm_end;

   case evt_err    :
   case evt_clr_err:
   case evt_ch_date:
   case evt_ch_time:
   case evt_ch_sum :
   case evt_ch_win :
   case evt_res    :
   case evt_Slot   :
   case evt_exit   :
   case evt_re     :
   case evt_re_err :
   case evt_we     :
   case evt_we_err :
   case evt_MVD_CL_strt :
   case evt_MVD_CL_BS1  :
   case evt_MVD_CL_BS2  :
   case evt_MVD_CL_OK   :
   case evt_MVD_CL_TM   :


 m1:
  for(i=1;i<11;i++)
    s_arch->u.err.err[i-1]  = ICP_error[i];
    break;
   default:
    s_arch->event=evt_none;
    goto m1;
 }

 s_arch->VolI   = s_MVD[0].VolI;
 s_arch->MassI  = s_MVD[0].MassI;
mm_end:
 GetTimeDate(&tim_dat);
 mdat.tm_year  = tim_dat.year -1900 ;
 mdat.tm_mon   = tim_dat.month-1 ;
 mdat.tm_mday  = tim_dat.day   ;
 mdat.tm_hour  = tim_dat.hour  ;
 mdat.tm_min   = tim_dat.minute;
 mdat.tm_sec   = tim_dat.sec   ;
 s_arch->time  = mktime( &mdat );


}
//-------------------------
struct arch_str ar_str;

void f_get_flash_p()
{
unsigned int seg_tmp;
unsigned long int i,i1,vd,ve;
char  *Flash_ptr_c;
struct arch_str *a_str;

 seg_tmp=0xD000;

 vd= get_vdate((unsigned int)0xD000);
 ve= get_vdate((unsigned int)0xE000);

 if((vd==0)&&(ve==0))
  {  // �� ᥪ��� ��饭�, ��砫� �����
    flash_seg=0xD000;
    flash_offset=0;
    return;
  }
  i=0;
  if(vd>i)
   {i=vd; seg_tmp=0xD000;}
  if(ve>i)
   {i=ve; seg_tmp=0xE000;}

   Flash_ptr_c=(char *) _MK_FP_(seg_tmp,(unsigned int)0);

   for(i=sizeof(ar_str),i1=0;i<= 0xffff;i+= sizeof(ar_str),i1+= sizeof(ar_str) )
     if(Flash_ptr_c[i]== (char)0xff)
     { // ᥣ���� � ��᫥���� ��⮩ �������� �� ���������
      flash_seg=seg_tmp;
      flash_offset=i;
      return;
     }

    flash_seg=f_get_next_seg(seg_tmp);
    flash_offset=0;
    return;
}
//-----------------
unsigned int f_get_next_seg(unsigned int seg)
{
unsigned int seg_tmp;

 if(seg==0xD000) seg_tmp=0xE000;
 else if(seg==0xE000) seg_tmp=0xD000;

 Flash_ptr=(unsigned long int *) _MK_FP_(seg_tmp,(unsigned int)0);
 if(*Flash_ptr==0xffffffff) ;
 else  if( FlashErase(seg_tmp) != 0)
 {
  ICP_error[icp_lst_max] |= Flash_erase_error;
 }
 return seg_tmp;
}
//-------------------
unsigned int f_get_nxt_seg(unsigned int seg)
{
unsigned int seg_tmp;

 if(seg==0xC000) seg_tmp=0xD000;
 else
  if(seg==0xD000) seg_tmp=0xE000;
 else if(seg==0xE000) seg_tmp=0xD000;
 return seg_tmp;
}
//-------------------
unsigned int f_get_prev_seg(unsigned int seg)
{
unsigned int seg_tmp;

 if(seg==0xD000) seg_tmp=0xE000;
 else if(seg==0xE000) seg_tmp=0xD000;

 return seg_tmp;
}
//-------------------
unsigned long int get_vdate(unsigned int seg)
{
 // �᫨ ��� �� ���४⭠ , ᥪ�� ��頥���
 struct arch_str *a_str;
 unsigned long int ltmp;
 struct tm *tdat;

 a_str=(struct arch_str *) _MK_FP_(seg,(unsigned int)0);

 if(a_str->event == (unsigned int)0xffff)
 {
   return 0;
 }

 tdat = localtime(&a_str->time);
 if( tdat == NULL ) goto erase;
 return a_str->time;

erase:
    if( FlashErase(seg) != 0)
    {
     ICP_error[icp_lst_max] |= Flash_erase_error;
    }
  return 0;
}
//-------------------
struct arch_str_t ahour00=
{
0,       //   sec
0,       //   min
8,       //   hour
};
//-------------------
struct arch_str_t adate00=
{
0,       //   sec
0,       //   min
0,       //   hour
1,       //   day
1,       //   month
9,       //   year
};
//-------------------
//                   sec min hour
struct tm  mhour00 = { 0, 0,  8 };
//                sec min hour day   month-1, year-1900
struct tm  mdat0= { 0, 34, 01,   30,     6,   109 };
struct tm  mdat = { 0, 0, 12,   25,     11,    88 };
time_t ltime0,ltime;
//----------------------------
time_t f_get_time(struct arch_str *ar_str_ptr)
{
 return ar_str_ptr->time;
/*
struct tm  mdat;
    mdat.tm_sec  = ar_str_ptr->sec  ;
    mdat.tm_min  = ar_str_ptr->min  ;
    mdat.tm_hour = ar_str_ptr->hour ;
    mdat.tm_mday = ar_str_ptr->day  ;
    mdat.tm_mon  = ar_str_ptr->month-1;
    mdat.tm_year = ((int)(ar_str_ptr->year)&0xff)+100;
    return mktime( &mdat );
*/
}
//-------------------------------
void f_prepare_t(struct arch_str_t *s_arch)
{
  TIME_DATE tim_dat;
 GetTimeDate(&tim_dat);
 s_arch->year  = tim_dat.year -2000 ;
 s_arch->month = tim_dat.month ;
 s_arch->day   = tim_dat.day   ;
 s_arch->hour  = tim_dat.hour  ;
 s_arch->min   = tim_dat.minute;
 s_arch->sec   = tim_dat.sec   ;
}

//-------------------------------
time_t f_get_time_t(struct arch_str_t *ar_str_ptr)
{
struct tm  mdat;
    mdat.tm_sec  = ar_str_ptr->sec  ;
    mdat.tm_min  = ar_str_ptr->min  ;
    mdat.tm_hour = ar_str_ptr->hour ;
    mdat.tm_mday = ar_str_ptr->day  ;
    mdat.tm_mon  = ar_str_ptr->month-1;
    mdat.tm_year = ((int)(ar_str_ptr->year)&0xff)+100;
    return mktime( &mdat );
}
//----------------------------------
float tMassI,tVolI;

int s_mode=2;
//--------------------------------------------

int f_get_d_dat(time_t time_00, int mode)
{ // �����頥� 0 - OK, ����� ����ᠭ� � tMassI,tVolI
  // �᫨ ������ �� ��� ���� ��� - �����頥� -1;

float k_tmp;
//unsigned int seg_tmp,seg_tmp_2,offs_tmp,utmp;
struct arch_str *ar_str_ptr,*ar_str_ptr_1,*ar_str_ptr_p1;
long int ltmp;
int nn,nn1,nn2,nn3,i;
time_t ltim,ltim_1,ltim_p1,ltime_l;
 struct tm *tdat;

 // ��।������ ��砫� ��ୠ��
/*
 printf("\n\r f_get_d_dat()");
*/

      f_cycle1();
/*
  seg_tmp= f_get_prev_seg(flash_seg);
  ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,(unsigned int)0);
  if(ar_str_ptr->event != 0xffff)
  {
   seg_tmp_2= f_get_prev_seg(seg_tmp);
   ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp_2,(unsigned int)0);
   if(ar_str_ptr->event != 0xffff)
   {
    seg_tmp=seg_tmp_2;
   }
  }
  else
  {
    seg_tmp= flash_seg;
    ar_str_ptr=(struct arch_str *) _MK_FP_(flash_seg,(unsigned int)0);
    if(ar_str_ptr->event == 0xffff) return -1;
  }
  ar_str_ptr=(struct arch_str *) _MK_FP_(seg_tmp,(unsigned int)0);

//  seg_tmp - ��砫�� ᥣ����
*/


  ar_str_ptr=f_get_fst_stor();
  ltim= f_get_time(ar_str_ptr);   // �६� ��ࢮ� �����
//seg_tmp=retf_seg;

  ar_str_ptr= f_get_lst_stor();
  ltime_l=f_get_time(ar_str_ptr); // �६� ��᫥���� �����


/*
    tdat = localtime( &ltim );
    printf("\r\nBeg:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

    tdat = localtime( &time_00 );
    printf("\r\nT00:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

    tdat = localtime( &ltime_l );
    printf("\r\nEnd:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/

 if(time_00 < ltim)
 {
   goto m_fault;
 }

 if(time_00 > ltime_l)
 {
   goto m_fault;
 }

 nn=f_get_max_n_arch();
 nn1=0;

for(nn2=4096;nn2>0;nn2=nn2>>1)
{
 nn3=nn1+nn2;
 if(nn3> (nn-1)) continue;

 ar_str_ptr=f_get_astr(nn3);

 if(ar_str_ptr->time > time_00);
 else nn1=nn3;

}
/*
    printf("\n\r Near structure:\n\r");
    tdat = localtime( &ar_str_ptr->time );
    printf("\r\nFound:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/


  // ���� 1-� ������ � ���祭�ﬨ
   for(i=nn1;i>=0;i--)
   {
    ar_str_ptr=f_get_astr(i);
    if( (ar_str_ptr->MassI != vBIG_P) && (ar_str_ptr->MassI != M_one))
    {
     ar_str_ptr_1=f_get_astr(i);
     ltim_1=ar_str_ptr_1->time;
     goto m0;
    }
   }
//  printf("\r\n fault,no value 1, i=%d",i);
m_fault:

   tMassI=BIG_P;
   tVolI=BIG_P;
   return -1;


m0:
  // ���� 2-� ������ � ���祭�ﬨ
   for(i=nn1+1;i<nn;i++)
   {
    ar_str_ptr=f_get_astr(i);
//    if(ar_str_ptr->MassI != vBIG_P)
    if( (ar_str_ptr->MassI != vBIG_P) && (ar_str_ptr->MassI != M_one))
    {
      ar_str_ptr=f_get_astr(i);
      ltim=ar_str_ptr->time;
      goto m_ok;
    }
   }
//  printf("\r\n fault,no value 2, i=%d",i);
   return -1;


m_ok:
// printf("\n\r m_ok");
  if(ltim==time_00)
  {
   tMassI=ar_str_ptr->MassI;
   tVolI =ar_str_ptr->VolI;
 //printf("\r\n 1");
   goto m_prn;
  }
  if(ar_str_ptr_1==NULL)
   {
 //   printf("\r\n 1");
    return -1;
   }

 // �᪮��� �६� ����� ���� 㪠��⥫ﬨ

// printf("\n\rt between 2 moments");
 if((ar_str_ptr->MassI==ar_str_ptr_1->MassI) && (ar_str_ptr->MassI != vBIG_P) && (ar_str_ptr->MassI != M_one)  )
 {
   tMassI=ar_str_ptr->MassI;
   tVolI =ar_str_ptr->VolI;
 //printf("\r\n 2");
   goto m_prn;
 }
 //printf("\r\n 3");
   // ����� �����﫨�� ����� ���� �����ﬨ
  switch(mode)
  {
   case tMin:
   m3:
     tMassI=ar_str_ptr_1->MassI;
     tVolI =ar_str_ptr_1->VolI;
     break;
   case tMax:
    m4:
     tMassI=ar_str_ptr->MassI;
     tVolI =ar_str_ptr->VolI;
     break;
   case tNear:
        if((time_00-ltim_1) < (ltim-time_00))
        {
            goto m3;
        }
        else
        {
            goto m4;
        }
   case tIntrp:
        if(ltim==ltim_1)
        {
          tMassI= ar_str_ptr->MassI;
          tVolI = ar_str_ptr->VolI;
        }
        else
        {
          k_tmp= (float)(time_00-ltim_1)/(float)(ltim-ltim_1);
          tMassI= ar_str_ptr_1->MassI + k_tmp*(ar_str_ptr->MassI-ar_str_ptr_1->MassI);
          tVolI = ar_str_ptr_1->VolI   + k_tmp*(ar_str_ptr->VolI-ar_str_ptr_1->VolI);
        }
        break;
    default:
//  printf("\r\n miss mode =%d",mode);
     goto m3;
  //        return -1;
  }
m_prn:

//  printf("\r\n End ok");
   return 0;
}
//----------------------------------
int f_print_d_str(time_t time_00, int mode)
{
 struct tm *tdat;

  tdat = localtime( &time_00 );
  printf("\n\r%02d.%02d.%02d %02d:%02d:%02d" ,
tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

 if( f_get_d_dat(time_00, mode) < 0)
 {
   printf(" ��� ������");
   return -1;
 }

  if(tMassI>= 0.)
     printf(" ���� %9.2f �� " ,tMassI);
  else
     printf(" ------- ");

  if(tVolI>= 0.)
     printf(" ��ꥬ %9.2f � " ,tVolI);
  else
     printf(" ------- ");

  return 0;
}
//------------------------------------------
unsigned int d_fl_seg=0xD000, d_fl_offs=0;
struct arch_str  *f_get_dat_s(time_t time_00)
{ // �����頥� 㪠��⥫� �� �������� � ����묨
  // ��� NULL ;

struct arch_str *ar_str_ptr;
long int ltmp;
int nn,nn1,nn2,nn3,i;
time_t ltim,ltim_1,ltim_p1,ltime_l;
 struct tm *tdat;

      f_cycle1();

  ar_str_ptr=f_get_fst_stor();
  ltim= f_get_time(ar_str_ptr);   // �६� ��ࢮ� �����

  ar_str_ptr= f_get_lst_stor();
  ltime_l=f_get_time(ar_str_ptr); // �६� ��᫥���� �����

/*
    tdat = localtime( &ltim );
    printf("\r\nBeg:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

    tdat = localtime( &time_00 );
    printf("\r\nT00:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);

    tdat = localtime( &ltime_l );
    printf("\r\nEnd:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/

 if(time_00 < ltim)
 {
   goto m_fault;
 }

 if(time_00 > ltime_l)
 {
   goto m_fault;
 }

 nn=f_get_max_n_arch();
 nn1=0;

for(nn2=4096;nn2>0;nn2=nn2>>1)
{
 nn3=nn1+nn2;
 if(nn3> (nn-1)) continue;

 ar_str_ptr=f_get_astr(nn3);

 if(ar_str_ptr->time > time_00);
 else nn1=nn3;

}
/*
    tdat = localtime( &ar_str_ptr->time );
    printf("\r\nFound:%02d.%02d.%02d %02d:%02d:%02d",
    tdat->tm_mday,tdat->tm_mon+1,tdat->tm_year-100,tdat->tm_hour,tdat->tm_min,tdat->tm_sec);
*/

m_ok:
 retf_iii=nn1;
 return ar_str_ptr;

m_fault:
 retf_iii=0;
 return NULL;
}

//----------------------------------
int f_get_dat_n(time_t time_00)
{ // �����頥� ����� ����� ��� -1 ,�᫨ ��� ������
  // ��� NULL ;
int nn;

 if( f_get_dat_s(time_00)== NULL) return -1;

 return retf_iii;

}

//----------------------------------



//------------------------------------------
