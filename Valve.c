

//f_tst(2);
//f_tst1(2);
//f_tst2(2);

void f_en_two_valv();
                  // ��� �������� ���孥�� ������
int valve_mode=1; // 1 - ��� ������� � ࠧ���묨 ��室���
                  // 2 - ॣ㫨�㥬� ������ ������ NO_NC
                  // 3 - ॣ㫨�㥬� ������ � ���யਢ���� UP/DN.

int valve_modeL=0;// ��� �������� ������� ������
                  // 1 - ��� ������� � ࠧ���묨 ��室���
                  // 2 - ॣ㫨�㥬� ������ ������ NO_NC
                  // 3 - ॣ㫨�㥬� ������ � ���யਢ���� UP/DN.
int Flag_Low=0;

void f_reg_valve();
void (*ff_valve)() = f_two_valve;

void f_init_valve()
{
if( Flag_Low == 0)
 switch(valve_mode)
 {
  case 1 : ff_valve=f_two_valve; break;
  case 2 : ff_valve=f_reg_valve; break;
  case 3 : ff_valve=f_reg_valve; break;

  default: ff_valve=NULL; break;
 }
else
 switch(valve_modeL)
 {
  case 1 : ff_valve=f_two_valveL; break;
  case 2 : ff_valve=f_reg_valve; break;
  case 3 : ff_valve=f_reg_valve; break;

  default: ff_valve=NULL; break;
 }


}
//----------------------------------
void f_two_valve()
{
 // ��ᥪ���� ���� �� ����� ���� (���) �������� � ࠧ���묨 ��室���

float ftmp,k_vol1,ftmp1;
int itmp,itmp1;
unsigned long int ltmp;
  // CLP0 - ᠬ� ����让, (#define CLP0 msk_int[num_out7],AVT_CTRL.H )
  // OUT1 - �।��� ������, �� �ࠢ���� � �㭪樨 ���⭮�� ��� ᭨�����
  // ��室�
  // OUT2 - ����訩 ������
  // OUT3 - ����祭�� ����
  // vol_f - �������� ���� ���᪠

     VolT_int= f_int_v2();
     k_vol1=k_vol;

//  VolT_int= s_MVD[0].MassT;
//  summ_v_int=VolT_int*cost_v;
  ftmp=  vol_f-VolT_int;

// � ftmp ᪮�쪮 ���஢ ��⠫���

 itmp=0;
 if(fl_GO == 1)
 {
  if(FL_err)
  {
    flag_O3=0;
   if( flag_ext_t == 0)
   //   Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
    f_stop_cnt();
        f_reg_cmn(13);
    goto m_end;
  }
  TimeOut3=TimeStamp;


  if ( Flag_mass != 0 )
   {

    if(s_MVD[0].Dens > 500.)
    {
      ftmp1 = s_MVD[0].Dens*0.001;
      k_vol1 /= ftmp1;
      ftmp /= ftmp1;
    }
   }
   if(flag_O0)
    if( (ftmp-k_vol1*CL_T0 )> CL_val0) itmp |= CLP0;
    else flag_O0=0;

   if(flag_O1)
    if( (ftmp-k_vol1*CL_T1 )> CL_val[0]) itmp |= OUT1;
    else flag_O1=0;

   if( (ftmp-k_vol1*CL_T2 ) > CL_val[1]  ) itmp |= OUT2;

  if(flag_pool==1)
   if( (ftmp-k_vol1*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7017C[0].time_stamp_pool=ltmp;
     I7060[0].time_stamp_pool=ltmp;
//   I7060[1].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
//   WDOG[0].time_stamp_pool=ltmp;
    }
  if(itmp == 0)
  {// �����襭�� �� ���⨦���� ��������� ��ꥬ�
    vol_mom=VolT_int;
    vol_mom0=vol2;
    flow_mom=k_vol;

    flag_fill_ok=1;
    f_stop_cnt();
        f_reg_cmn(13);

    VolT_id=vol_f;
  }
  else
  {
     if(VolT_id< VolT_int)
             VolT_id= VolT_int;
     if(VolT_id>vol_f)  VolT_id=vol_f;
 //  summ_v_id=VolT_id*cost_v;
  }

//  if(flag_O0|flag_O1)
  {
    f_en_two_valv();
    itmp &= i_dens;
  }
 }  //  if(fl_GO == 1)

 if(flag_O3)
#if defined(BIO_1)
   if( f_timer(TimeOut3,(long int)(Out3_delay_off+T_Pmp_delay ) ))
#else
  #if defined(PMP_LG)
   if( f_timer(TimeOut3,Out3_delay_off+(long int)T_Pmp_LG*100 ) )
  #else
   if( f_timer(TimeOut3,Out3_delay_off ))
  #endif
#endif
  {
   flag_O3=0;
   if( flag_ext_t == 0)
   //  Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
  }
  else
  {
    itmp |= OUT3;
    if( flag_ext_t == 0)
   //    Delta_Ctrl[0]=START_FWD_DELTA;
      f_Drive_Run();
  }
 m_end:

// itmp |= lamp_c;

// i7060_out[0] = itmp;

 OUT_VAR &= ~(CLP0 | OUT1 | OUT2 | OUT3);
 OUT_VAR |= (itmp & Out_en);

 f_out();

 if(flag_prn)
 {
// if(io_1!=itmp)
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }

 if(I7060[0].status)  f_7060(0);
// if(I7060[1].status)  f_7060(1);

 ServiceCOM(I7060[0].port);
// ServiceCOM(I7060[1].port);
 return;
}
/* ---------------------------------------- */
void f_en_two_valv()
{// �㭪�� ���������� ���ﭨ� ���⭮�� � �ନ��� ���� �몫�祭��
 // ������� CL1: i_dens=~OUT1; �� ����室����� 㬥��襭�� ��室� ���᪠
 float ftmp;
   i_dens=0xffff;
// ftmp=s_MVD[0].Press - s_MVD[0].PressG;

/*
 if( s_MVD[0].Press < P_min_valve)
 {
    i_dens &=~CLP0;
    i_dens &=~OUT1;
    i_dens &= ~OUT2;
    time_beg_fill=TimeStamp;
    return;
 }
*/

 if( f_timer(time_beg_fill,cl0_delay_off) == 0 )
  { // ������� ����祭�� CL0 ���� cl0_delay_off �� ��᫥ ��砫� ����������
    i_dens &=~CLP0;
    time_chg_den0=TimeStamp;
  }
/* ==========================
 else
  {
    if( f_timer(time_chg_den0,tim_dens0) != 0 )
    {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den0_Off) )
               {  // ᪮���� 㬥��襭�� ���⭮�� �ॢ�ᨫ� �����⨬� �஢���
                   f_cl0_off();
               }
               else if( fabs(k_Den) <  k_Den0_On)
                   f_cl0_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on0 ) f_cl0_on();
            else if( ftmp < PressLvl_off0) f_cl0_off();
            break;
       //---------------------
      }
    }
  }
============*/

 if( f_timer(time_beg_fill,cl1_delay_off) == 0 )
  { // ������� ����祭�� CL1 ���� cl1_delay_off �� ��᫥ ��砫� ����������
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
 else if(XdN < 0)
  { // ������� ����祭�� CL1 �᫨ ��� ����� �������� �� �����樨
    i_dens &=~CLP0;
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
/*
 if ( Flag_mass != 0 )
 {
  if( (s_MVD[0].MassI-MassStamp) < Value_beg)
  {
    i_dens &=~OUT1;
    time_chg_den=TimeStamp;
  }
 }
 else
*/
  if( (s_MVD[0].VolI-VolStamp) < Vol_beg)
  {
    i_dens &=~OUT1;
    i_dens &=~CLP0;
    time_chg_den=TimeStamp;
  }

/*========================
 else
  {
   if( f_timer(time_chg_den,tim_dens) != 0 )
   {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den_Off) )
               {  // ᪮���� 㬥��襭�� ���⭮�� �ॢ�ᨫ� �����⨬� �஢���
                   f_cl1_off();
               }
               else if( fabs(k_Den) <  k_Den_On)
                   f_cl1_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on1 ) f_cl1_on();
            else if(( ftmp < PressLvl_off1) && (i_dens & OUT1) ) f_cl1_off();
            break;
       //---------------------
      }
   }
  }
===============*/

  if( f_timer(time_beg_fill,cl2_delay_off) ==0 )
  { // ������� ����祭�� CL2 ���� cl21_delay_off �� ��᫥ ��砫� ����������
    i_dens &= ~OUT2;
    time_chg_den2=TimeStamp;
    beg_flch=0;
  }

/*===============
  else
  {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
              f_cl2_on();
              break;
       //---------------------
       case ReducePress:
           if( ftmp > PressLvl_on2 )
              f_cl2_on();
           else if( ftmp < PressLvl_off2)
              f_cl2_off();
           break;
       //---------------------
      }
  }
===============*/
}
/* ---------------------------------------- */
void f_two_valveL()
{
 // ��ᥪ���� ���� �� ����� ���� (���) �������� � ࠧ���묨 ��室���

float ftmp,k_vol1,ftmp1;
int itmp,itmp1;
unsigned long int ltmp;
  // CLP0 - ᠬ� ����让, (#define CLP0 msk_int[num_out7],AVT_CTRL.H )
  // OUT5 - �।��� ������, �� �ࠢ���� � �㭪樨 ���⭮�� ��� ᭨�����
  // ��室�
  // OUT6 - ����訩 ������
  // OUT3 - ����祭�� ����
  // vol_f - �������� ���� ���᪠

     VolT_int= f_int_v2();

//  VolT_int= s_MVD[0].MassT;
//  summ_v_int=VolT_int*cost_v;
  ftmp=  vol_f-VolT_int;

// � ftmp ᪮�쪮 ���஢ ��⠫���

 itmp=0;
 if(fl_GO == 1)
 {
  if(FL_err)
  {
    flag_O3=0;
   if( flag_ext_t == 0)
   //   Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
    f_stop_cnt();
        f_reg_cmn(13);
    goto m_end;
  }
  TimeOut3=TimeStamp;

  k_vol1=k_vol;

  if ( Flag_mass != 0 )
   {

    if(s_MVD[0].Dens > 500.)
    {
      ftmp1 = s_MVD[0].Dens*0.001;
      k_vol1 /= ftmp1;
      ftmp /= ftmp1;
    }
   }
   if(flag_O0)
    if( (ftmp-k_vol1*CL_T0_L )> CL_val_L0) itmp |= CLP0;
    else flag_O0=0;

   if(flag_O1)
    if( (ftmp-k_vol1*CL_T1_L )> CL_val_L[0]) itmp |= OUT5;
    else flag_O1=0;


   if( (ftmp-k_vol1*CL_T2_L ) > CL_val_L[1]  ) itmp |= OUT6;

  if(flag_pool==1)
   if( (ftmp-k_vol1*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7017C[0].time_stamp_pool=ltmp;
     I7060[0].time_stamp_pool=ltmp;
//   I7060[1].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
//   WDOG[0].time_stamp_pool=ltmp;
    }
  if(itmp == 0)
  {// �����襭�� �� ���⨦���� ��������� ��ꥬ�
    vol_mom=VolT_int;
    vol_mom0=vol2;
    flow_mom=k_vol;

    flag_fill_ok=1;
    f_stop_cnt();
        f_reg_cmn(13);

    VolT_id=vol_f;
  }
  else
  {
     if(VolT_id< VolT_int)
             VolT_id= VolT_int;
     if(VolT_id>vol_f)  VolT_id=vol_f;
 //  summ_v_id=VolT_id*cost_v;
  }

//  if(flag_O0|flag_O1)
  {
    f_en_two_valvL();
    itmp &= i_dens;
  }
 }  //  if(fl_GO == 1)

 if(flag_O3)
#if defined(BIO_1)
   if( f_timer(TimeOut3,(long int)(Out3_delay_off+T_Pmp_delay ) ))
#else
  #if defined(PMP_LG)
   if( f_timer(TimeOut3,Out3_delay_off+(long int)T_Pmp_LG*100 ) )
  #else
   if( f_timer(TimeOut3,Out3_delay_off ))
  #endif
#endif

 {
   flag_O3=0;
   if( flag_ext_t == 0)
   //  Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
  }
  else
  {
    itmp |= OUT3;
    if( flag_ext_t == 0)
   //    Delta_Ctrl[0]=START_FWD_DELTA;
      f_Drive_Run();
  }
 m_end:

// itmp |= lamp_c;

// i7060_out[0] = itmp;

 OUT_VAR &= ~(CLP0 | OUT5 | OUT6 | OUT3);
 OUT_VAR |= (itmp & Out_en);

 f_out();

 if(flag_prn)
 {
// if(io_1!=itmp)
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }

 if(I7060[0].status)  f_7060(0);
// if(I7060[1].status)  f_7060(1);

 ServiceCOM(I7060[0].port);
// ServiceCOM(I7060[1].port);
 return;
}
/* ---------------------------------------- */
void f_en_two_valvL()
{// �㭪�� ���������� ���ﭨ� ���⭮�� � �ନ��� ���� �몫�祭��
 // ������� CL1: i_dens=~OUT5; �� ����室����� 㬥��襭�� ��室� ���᪠
 float ftmp;
   i_dens=0xffff;
// ftmp=s_MVD[0].Press - s_MVD[0].PressG;

/*
 if( s_MVD[0].Press < P_min_valve)
 {
    i_dens &=~CLP0;
    i_dens &=~OUT5;
    i_dens &= ~OUT6;
    time_beg_fill=TimeStamp;
    return;
 }
*/
 if( f_timer(time_beg_fill,cl0_delay_off) == 0 )
  { // ������� ����祭�� CL0 ���� cl0_delay_off �� ��᫥ ��砫� ����������
    i_dens &=~CLP0;
    time_chg_den0=TimeStamp;
  }
/* ==========================
 else
  {
    if( f_timer(time_chg_den0,tim_dens0) != 0 )
    {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den0_Off) )
               {  // ᪮���� 㬥��襭�� ���⭮�� �ॢ�ᨫ� �����⨬� �஢���
                   f_cl0_off();
               }
               else if( fabs(k_Den) <  k_Den0_On)
                   f_cl0_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on0 ) f_cl0_on();
            else if( ftmp < PressLvl_off0) f_cl0_off();
            break;
       //---------------------
      }
    }
  }
============*/

 if( f_timer(time_beg_fill,cl1_delay_off) == 0 )
  { // ������� ����祭�� CL1 ���� cl1_delay_off �� ��᫥ ��砫� ����������
    i_dens &=~OUT5;
    time_chg_den=TimeStamp;
  }
 else if(XdN < 0)
  { // ������� ����祭�� CL1 �᫨ ��� ����� �������� �� �����樨
    i_dens &=~CLP0;
    i_dens &=~OUT5;
    time_chg_den=TimeStamp;
  }
/*
 if ( Flag_mass != 0 )
 {
  if( (s_MVD[0].MassI-MassStamp) < Value_beg)
  {
    i_dens &=~OUT5;
    time_chg_den=TimeStamp;
  }
 }
 else
*/
 /*
  if( (s_MVD[0].VolI-VolStamp) < Vol_beg)
  {
    i_dens &=~OUT5;
    i_dens &=~CLP0;
    time_chg_den=TimeStamp;
  }
*/
/*========================
 else
  {
   if( f_timer(time_chg_den,tim_dens) != 0 )
   {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
               if( k_Den < (-k_Den_Off) )
               {  // ᪮���� 㬥��襭�� ���⭮�� �ॢ�ᨫ� �����⨬� �஢���
                   f_cl1_off();
               }
               else if( fabs(k_Den) <  k_Den_On)
                   f_cl1_on();
            break;
       //---------------------
       case ReducePress:

            if( ftmp > PressLvl_on1 ) f_cl1_on();
            else if(( ftmp < PressLvl_off1) && (i_dens & OUT5) ) f_cl1_off();
            break;
       //---------------------
      }
   }
  }
===============*/

  if( f_timer(time_beg_fill,cl2_delay_off) ==0 )
  { // ������� ����祭�� CL2 ���� cl21_delay_off �� ��᫥ ��砫� ����������
    i_dens &= ~OUT6;
    time_chg_den2=TimeStamp;
    beg_flch=0;
  }

/*===============
  else
  {
      switch(ModeReduce)
      {
       default:
       case ReduceDens:
              f_cl2_on();
              break;
       //---------------------
       case ReducePress:
           if( ftmp > PressLvl_on2 )
              f_cl2_on();
           else if( ftmp < PressLvl_off2)
              f_cl2_off();
           break;
       //---------------------
      }
  }
===============*/
}
/* ---------------------------------------- */
/* ---------------------------------------- */
/* ---------------------------------------- */
void  f_en_reg_valv();

float   Vol_beg  =100;  // ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
float Flow_beg=10000;  // 3000, ��砫쭮� ���祭�� ��室� ��� ���������� ����� ��
                       // �஢�� �㪠��,��/�
float dFP_beg=300;


float Flow_min=3600;// 3600 ��室 �� ��ᥪ���� ����,��/�
float    Mass_min=40;  // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
                       // Flow_min - �����⮢�� � ��ᥪ���� ����
float dFP_min=200;

float Flow_min1=7200;  // 11000 ��室 �� ��ᥪ���� ����,��/�
float    Mass_min1=120;    // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
float    dFP_min1=400;

float Flow_min2=30000;  // 45000 ��室 �� ��ᥪ���� ����,��/�
float    Mass_min2=450; // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
float    dFP_min2=800;

float Flow_nom=100000;  // 20000, ��������� ��室 �� ����������,��/�
float dFP_nom=1000;


float Flow_minL =3600;  // 3600 ��室 �� ��ᥪ���� ����,��/�
float Mass_minL =40;    // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
                       // Flow_min - �����⮢�� � ��ᥪ���� ����
float dFP_minL  =200;
float Flow_min1L=7200;  // 11000 ��室 �� ��ᥪ���� ����,��/�
float Mass_min1L=120;   // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
float dFP_min1L =400;
float Flow_min2L=30000; // 45000 ��室 �� ��ᥪ���� ����,��/�
float Mass_min2L=450;   // ��⠢���� ���� ��� ᭨����� ��室� �� ���祭��
float dFP_min2L =800;
float Flow_nomL =100000; // 20000, ��������� ��室 �� ����������,��/�
float dFP_nomL  =1000;




int itmp_vv=0;
void f_reg_valve()
{
 // ��ᥪ���� ���� �� ����� ॣ㫨�㥬��� �������

float ftmp,k_vol1,ftmp1;

unsigned long int ltmp;
  //
  // OUT1 (OUT5) - ����� ��ଠ�쭮 ������
  // OUT2 (OUT6) - ����� ��ଠ�쭮 �������
  //
  // OUT3 - ����祭�� ����
  // vol_f - �������� ���� ���᪠

  // �� ���⨦���� �������� ���� OUT1=0,OUT2=0;

     VolT_int= f_int_v2();
     k_vol1=k_vol;

//  VolT_int= s_MVD[0].MassT;
//  summ_v_int=VolT_int*cost_v;
  ftmp=  vol_f-VolT_int;

// � ftmp ᪮�쪮 ���஢ ��⠫���

 itmp_vv=0;
 if(fl_GO == 1)
 {
  if(FL_err)
  {
    flag_O3=0;
   if( flag_ext_t == 0)
   //   Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
    f_stop_cnt();
        f_reg_cmn(13);
    goto m_end;
  }

  TimeOut3=TimeStamp;

 if( Flag_Low == 0)
 {

   if ( (s_MVD[0].VolI-VolStamp) > Vol_beg)
   {
       Flow_dem = Flow_nom;
       dF_perm = dFP_nom;
   }
   else
   {
       Flow_dem = Flow_beg;
       dF_perm = dFP_beg;
   }
   if(ftmp < Mass_min)
        if(Flow_dem > Flow_min)
        {
          Flow_dem = Flow_min;
          dF_perm  = dFP_min;
        }
   if(ftmp < Mass_min1)
        if(Flow_dem > Flow_min1)
        {
          Flow_dem = Flow_min1;
          dF_perm  = dFP_min1;
        }
   if(ftmp < Mass_min2)
        if(Flow_dem > Flow_min2)
        {
           Flow_dem = Flow_min2;
           dF_perm  = dFP_min2;
        }
 }
 else // ( Flag_Low != 0)
 {
   Flow_dem = Flow_nomL;
   dF_perm = dFP_nomL;

   if(ftmp < Mass_minL)
        if(Flow_dem > Flow_minL)
        {
          Flow_dem = Flow_minL;
          dF_perm  = dFP_minL;
        }
   if(ftmp < Mass_min1L)
        if(Flow_dem > Flow_min1L)
        {
          Flow_dem = Flow_min1L;
          dF_perm  = dFP_min1L;
        }
   if(ftmp < Mass_min2L)
        if(Flow_dem > Flow_min2L)
        {
           Flow_dem = Flow_min2L;
           dF_perm  = dFP_min2L;
        }
 }

  if ( Flag_mass != 0 )
   {

    if(s_MVD[0].Dens > 500.)
    {
      ftmp1 = s_MVD[0].Dens*0.001;
      k_vol1 /= ftmp1;
      ftmp /= ftmp1;
    }
   }

if( Flag_Low == 0)
{
  if( (ftmp-k_vol1*CL_T2 )> CL_val[1]) itmp_vv |= OUT2 | OUT1;
/*
  else
  {
   if(flag_prn)
   {
     printf("\n\rftmp=%g,k_vol1=%g,CL_val[1]=%g",ftmp,k_vol1,CL_val[1]);

   }

  }
*/
}
else
{
  if( (ftmp-k_vol1*CL_T2_L )> CL_val_L[1]) itmp_vv |= OUT6 | OUT5;
/*
  else
  {
   if(flag_prn)
   {
     printf("\n\rftmp=%g,k_vol1=%g,CL_val[1]=%g",ftmp,k_vol1,CL_val[1]);

   }

  }
*/
}
  if(flag_pool==1)
   if( (ftmp-k_vol1*CL_T3 )<= 0)
    {
     flag_pool=0;
     ltmp=TimeStamp+CL_T4;
     I7017C[0].time_stamp_pool=ltmp;
//   I7060[0].time_stamp_pool=ltmp;
//   I7060[1].time_stamp_pool=ltmp;
//   MMI.time_stamp_pool=ltmp;
//   WDOG[0].time_stamp_pool=ltmp;
    }


  if(itmp_vv == 0)
  {// �����襭�� �� ���⨦���� ��������� ��ꥬ�
    vol_mom=VolT_int;
    vol_mom0=vol2;
    flow_mom=k_vol;

    flag_fill_ok=1;
    f_stop_cnt();
        f_reg_cmn(13);

    VolT_id=vol_f;
  }
  else
  {
     if(VolT_id< VolT_int)
             VolT_id= VolT_int;
     if(VolT_id>vol_f)  VolT_id=vol_f;
  }

  if(fl_GO == 1)
  {
      f_en_reg_valv();
      itmp_vv &= i_dens;
  }
 }  //  if(fl_GO == 1)

 if(flag_O3)

#if defined(BIO_1)
   if( f_timer(TimeOut3,(long int)(Out3_delay_off+T_Pmp_delay ) ))
#else
  #if defined(PMP_LG)
   if( f_timer(TimeOut3,Out3_delay_off+(long int)T_Pmp_LG*100 ) )
  #else
   if( f_timer(TimeOut3,Out3_delay_off ))
  #endif
#endif

   {
   flag_O3=0;
   if( flag_ext_t == 0)
   //  Delta_Ctrl[0]=STOP_FWD_DELTA;
      f_Drive_Stop();
   }
   else
   {
    itmp_vv |= OUT3;
    if( flag_ext_t == 0)
   //    Delta_Ctrl[0]=START_FWD_DELTA;
      f_Drive_Run();

   }
 m_end:

// itmp |= lamp_c;
// i7060_out[0] = itmp;

 OUT_VAR &= ~( OUT1 | OUT2 | OUT5 | OUT6 | OUT3);
 OUT_VAR |= (itmp_vv & Out_en);

 f_out();

 if(flag_prn)
 {
   if(io_1!=OUT_VAR)
   {
    printf("\r\nOut= %02x,%ld ms",OUT_VAR,TimeStamp-time_beg_fill);
   }
   io_1=OUT_VAR;
 }

 if(I7060[0].status)  f_7060(0);
// if(I7060[1].status)  f_7060(1);

 ServiceCOM(I7060[0].port);
// ServiceCOM(I7060[1].port);
 return;
}
/* ---------------------------------------- */
float P_min_valve=0.05; // ���, �������쭮� �������� �� ���஬ �������� 㢥����� �⥯��� ������ ���⨫�
float P_min_valveL=0.05; // ���, �������쭮� �������� �� ���஬ �������� 㢥����� �⥯��� ������ ���⨫�
int State_UpDn=HOLD;

void f_UP_DN();

void  f_en_reg_valv()
{
 // �㭪�� �ନ��� ���㠫�� ���祭�� ��� OUT1,OUT2 � ���� ��᪨ �몫�祭��
 // �� �᭮����� 横���ࠬ�� ࠡ��� � ��������� ���祭��
 // �ॡ㥬�� ����稭� ������ ���⨫� Hop  � ⥪�饣� ���ﭨ� ���⨫�
 // Hop_cur

   i_dens=0xffff;

  if( f_timer(time_beg_fill,cl2_delay_off) ==0 )
  { // ������� ����祭�� CL2 ���� cl21_delay_off �� ��᫥ ��砫� ����������
//  i_dens &= ~(OUT1|OUT2);
    time_chg_den2=TimeStamp;
    State_UpDn = DN ;
    beg_flch=0;
//  return;
  }
  else f_UP_DN(); // ������ ���ﭨ� ���⨫�

   // valve_mode :            1     ;            2             ;          3
   // OUT1       : ����訩 ������   ; ����� ��ଠ�쭮 ������ ;  /DN - ������� �������� (OUT1=0)
   // OUT2       : ����訩 ������   ; ����� ��ଠ�쭮 ������� ;   UP - ������ �������� (OUT2=1)

 if( Flag_Low == 0)
 {
  if(valve_mode==2)
  {   // ���孨� �����
    if(State_UpDn == HOLD)  i_dens &= ~(OUT2);            // ��ଠ�쭮�⮪���� ����祭
    else if(State_UpDn == UP ) ;                          // ��� ����祭�
    else if(State_UpDn == DN )   i_dens &= ~(OUT1|OUT2);  // ��� �몫�祭�
  }
  else if(valve_mode==3)
  {
    if(State_UpDn == HOLD)  i_dens &= ~(OUT2);     // ��� OUT1=1,OUT2=0 - ��� ���⠪�� �몫�祭�
    else if(State_UpDn == UP ) ;                        //  OUT1=1,OUT2=1      ���⠪�� "����"=1, "����"=0
    else if(State_UpDn == DN ) i_dens &= ~(OUT1| OUT2); //  OUT1=0,OUT2=0      ���⠪�� "����"=0, "����"=1
  }
 }
 else
 {    // ������ �����
  if(valve_mode==2)
  {
    if(State_UpDn == HOLD)  i_dens &= ~(OUT6);            // ��ଠ�쭮�⮪���� ����祭
    else if(State_UpDn == UP ) ;                          // ��� ����祭�
    else if(State_UpDn == DN )   i_dens &= ~(OUT5|OUT6);  // ��� �몫�祭�
  }
  else if(valve_mode==3)
  {
    if(State_UpDn == HOLD)  i_dens &= ~(OUT6);     // ��� OUT5=1,OUT6=0 - ��� ���⠪�� �몫�祭�
    else if(State_UpDn == UP ) ;                        //  OUT5=1,OUT6=1      ���⠪�� "����"=1, "����"=0
    else if(State_UpDn == DN ) i_dens &= ~(OUT5| OUT6); //  OUT5=0,OUT6=0      ���⠪�� "����"=0, "����"=1
  }
 }

}
/* ---------------------------------------- */
long int Per_up_min_v=50;
long int Per_up_max_v=400;
long int Per_dn_min_v=50;
long int Per_dn_max_v=400;
long int Tim_hld=400;

long int Per_UP_dl=30; // �६� ����祭�� ������� UP
long int Per_DN_dl=30; // �६� ����祭�� ������� DN

long int Per_up_min_vL=50;
long int Per_up_max_vL=400;
long int Per_dn_min_vL=50;
long int Per_dn_max_vL=400;
long int Tim_hldL     =400;
long int Per_UP_dlL   =30; // �६� ����祭�� ������� UP
long int Per_DN_dlL   =30; // �६� ����祭�� ������� DN

long int Tim_up=400;
long int Tim_dn=400;
long int time_ch_v=0;

void f_UP_DN()
{
 // ������ ���ﭨ� ���⨫� �� �᭮�����
 // �ॡ㥬�� ����稭� ������ ���⨫� Hop, ⥪�饣� ���ﭨ� ���⨫�
 // Hop_cur � ⥪�饩 �⠤�� ���⨫�
 long int ltmp;

if( Flag_Low == 0)
  switch(State_UpDn)
  {
   case HOLD:
    {
      if( f_timer(time_ch_v,Tim_hld) == 0 ) break;
      ltmp= Hop - Hop_cur;
      if(ltmp > Per_up_min_v)
       { // UP
         if( s_MVD[0].Press < P_min_valve)
         {
             Hop= Hop_cur;
             YfN=Hop<<n_shft;
             XfN_2  = 0;
             XfN_1  = 0;
             break;
         }
         State_UpDn=UP;
         time_ch_v=TimeStamp;
         if(ltmp > Per_up_max_v)
         {
           ltmp = Per_up_max_v;
           Hop_cur+=ltmp;
           Hop= Hop_cur;
           YfN=Hop<<n_shft;
           XfN_2  = 0;
           XfN_1  = 0;
         }
         else
         {
           Hop_cur+=ltmp;
         }
           Tim_up=ltmp+Per_UP_dl;

       }
      else if(ltmp < -Per_dn_min_v)
       { // DN
         State_UpDn=DN;
         time_ch_v=TimeStamp;

         if(ltmp < -Per_dn_max_v)
         {
           ltmp = -Per_up_max_v;
           Hop_cur+=ltmp;
           Hop= Hop_cur;
           YfN=Hop<<n_shft;
           XfN_2  = 0;
           XfN_1  = 0;
         }
         else
         {
          Hop_cur+=ltmp;
         }
         Tim_dn=Per_DN_dl-ltmp;
       }
     break;
    }
   case UP  :
    {
     if( f_timer(time_ch_v,Tim_up) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   case DN  :
    {
     if( f_timer(time_ch_v,Tim_dn) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   default:
         State_UpDn=HOLD;
         time_ch_v=TimeStamp;
  }
 else
  switch(State_UpDn)
  {
   case HOLD:
    {
      if( f_timer(time_ch_v,Tim_hldL) == 0 ) break;
      ltmp= Hop - Hop_cur;
      if(ltmp > Per_up_min_vL)
       { // UP
         if( s_MVD[0].Press < P_min_valveL)
         {
             Hop= Hop_cur;
             YfN=Hop<<n_shft;
             XfN_2  = 0;
             XfN_1  = 0;
             break;
         }
         State_UpDn=UP;
         time_ch_v=TimeStamp;
         if(ltmp > Per_up_max_vL)
         {
           ltmp = Per_up_max_vL;
           Hop_cur+=ltmp;
           Hop= Hop_cur;
           YfN=Hop<<n_shft;
           XfN_2  = 0;
           XfN_1  = 0;
         }
         else
         {
           Hop_cur+=ltmp;
         }
           Tim_up=ltmp+Per_UP_dlL;

       }
      else if(ltmp < -Per_dn_min_vL)
       { // DN
         State_UpDn=DN;
         time_ch_v=TimeStamp;

         if(ltmp < -Per_dn_max_vL)
         {
           ltmp = -Per_up_max_vL;
           Hop_cur+=ltmp;
           Hop= Hop_cur;
           YfN=Hop<<n_shft;
           XfN_2  = 0;
           XfN_1  = 0;
         }
         else
         {
          Hop_cur+=ltmp;
         }
         Tim_dn=Per_DN_dlL-ltmp;
       }
     break;
    }
   case UP  :
    {
     if( f_timer(time_ch_v,Tim_up) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   case DN  :
    {
     if( f_timer(time_ch_v,Tim_dn) == 0 ) break;
     State_UpDn=HOLD;
     time_ch_v=TimeStamp;
     break;
    }

   default:
         State_UpDn=HOLD;
         time_ch_v=TimeStamp;
  }
}
/* ---------------------------------------- */


