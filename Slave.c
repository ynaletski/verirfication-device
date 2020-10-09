
//----------------------------------
// ����� �ਭ������ ᢥ���
int    CMD_IN   = 0;
int    CMD_OUT_p = 0;

int State_SLVm=0;
int reg_cmnm;
int Reg_errm;
int I11m;
int I12m;


#if defined(PMP_LG)
int T_Pmp_LG=0;
int OUT_Pmp=0;
#endif


#if defined(BIO_1)
int OUT_or=0;
int OUT_Pmp=0;
float T_Pmp_delay=0;
#endif
int reg_cmn=0;

float n_id_af=0;

void (*ff_Slv)() = NULL;

int flag_Slv=0;
int flag_ZT=0; // �ਧ��� �ᯥ譮�� ���㫥��� Total

int ComPortSlv = 4;
float dose_dlvr_sl=0;

int AddrSlv=1;
int cod_float=1;
int State_SLV=0;
int Last_evt=0;
int sw_mmi_slv=0;
int sw_dlv_slv=0;

int  WD_PMP_flag=0;
int  WD_PMP_Fl=0;
#define WD_PMP_P1 (2000)
long int WD_PMP_time=0;
long int WD_PMP_t1=0;
long int WD_PMP_Per=20000; // ����稭� ⠩���� �� �ਥ�� ᮮ�饭��

int Slv_fict=0;
int Slv_fict1=0;
int Slv_fict2=0;
int Slv_fict3=0;
int Slv_fict4=0;

int flag_slvrtu=0;
int fl_slv_out=0;

long int byte_timout_slv= 8 ;
long int out_delay_slv = 5 ;

void *list_Slv_int[]={

&n_sl_int1,      // 0 �����.��६ int
&n_sl_flt1,      // 1 �����.��६ float

&INP_OFP,        // 2  ����ﭨ� ����஫��� ��९�������
&ICP_error[7],   // 3  ॣ���� �訡�� �ࠩ��� OFP

&sw_ver[0],      // 4  ����� ��, 6 ASCII ᨬ�����
&sw_ver[2],      // 5
&sw_ver[4],      // 6

&CMD_IN ,   // &Slv_int[6],     // 7   CMD_REG ॣ���� �������

&State_SLVm,      // 8   ����ﭨ� ���᪠
&Last_evt,       // 9   ��᫥���� ᮡ�⨥ ����ᠭ��� � ��ୠ�
&Reg_errm,        // 10    &FL_err,         // 10  ���� �訡��, 0 - OK

&I11m,           // 11 ICP_error[9]  ��� �訡�� �㭪樮��஢����
&I12m,           // 12 ICP_error[10] ���७�� ॣ���� �訡��
&ICP_error[1],   // 13  ॣ���� �訡�� �ࠩ��� MVD
&ICP_error[2],   // 14  ॣ���� �訡�� �ࠩ��� 7060

#if defined(ICP_7041)
&ICP_error[4],   // 15  ॣ���� �訡�� �ࠩ��� 7017
#else
&ICP_error[3],   // 15  ॣ���� �訡�� �ࠩ��� 7017
#endif


&ICP_error[6],   // 16  ॣ���� �訡�� �ࠩ��� DELTA
&WD_PMP_Per,     // 17  ��ਮ� ��஦����� ⠩��� Host,ms
                 //     0 - ⠩��� �⪫�祭
&mode_hst,       // 18  1 - ����� ����� ���� �� ���
//&Slv_int[10],    // 19  ���⢥ত���� ���� ��� ������ = Strt_cmd(0x55)
//&Slv_int[11],    // 20
&reg_cmnm,           // 19 =62  ������ ॣ���� ���ﭨ�
&sw_mmi_slv,        // 20 =63  ���� MMI

&INP_VARi0,       // 21 ॣ���� ����.�室�� � ��⮬ �����ᨨ
&OUT_VARi0,       // 22 ॣ���� ����.��室��

&DriveState[0],    // 23 ॣ���� ����ﭨ� DELTA
&DriveError[0],    // 24 ॣ���� �訡��  DELTA
&DriveCurrent[0],  //&Delta_current[0],  // 25 ⮪ � ����

&DriveSV[0],       // 26 ⥪.����. �����  �ਢ���
&DriveSA[0],       // 27 ⥪.����. �६��� ࠧ����
&DriveSD[0],       // 28 ⥪.����. �६��� ����������

&Drive_SV_beg[0],   // 29 ���.����. ����� �ਢ���
&Drive_SA_beg[0],   // 30 ���.����. �६��� ࠧ����
&Drive_SD_beg[0],   // 31 ���.����. �६��� ����������


#if defined(BIO_1)
&OUT_or,            // 32 �ࠢ����� ��������� � ���ᮬ �� MODBUS
&OUT_Pmp,           // 33 �ࠢ����� ���ᮬ
#else
  #if defined(PMP_LG)
&T_Pmp_LG,          // 32 T delay PMP off 1 == 0.1 sec
&OUT_Pmp,           // 33 �ࠢ����� ���ᮬ
  #else
&Slv_int[2],        // 32 䨪⨢��� ��६�����
&Slv_int[2],        // 33 䨪⨢��� ��६�����
  #endif

#endif

&Slv_int[2],        // 34 䨪⨢��� ��६�����

&s_MVD[0].reg_err,  // 35 ॣ���� �訡�� MVD
&type_liq,          // 36  1 Crude Oils
                    //     2 Fuel Oils   - ���⮯����
                    //     3 Jet group
                    //     4 Kerosene
                    //     5 Gazolines   - ������
                    //     6 Lubricating Oils
//&mode_r,            // 37 ०�� �ࠢ�.���������
&result_dlv,        // 37 १���� �����襭�� ���᪠

&Flag_Low  ,        // 38  1 - ������ �����
&Flag_mass ,        // 39  1 - ���� �� ����
&flag_prok ,        // 40  1 - �ப�窠
&mode_temp ,        // 41  1 - ���譨� �ମ���� ��� D_ref, 0 - MVD
&mode_refD ,        // 42  1 - ��।����� � ����� �ਥ�� D_ref


&str_prod[0],       // 43  ��ப� � ��������� �த��
&str_prod[2],       // 44
&str_prod[4],       // 45
&str_prod[6],       // 46
&str_prod[8],       // 47
&str_prod[10],      // 48
&str_prod[12],      // 49
&str_prod[14],      // 50
&str_prod[16],      // 51
&str_prod[18],      // 52


&type_dlv ,         // 53  ⨯ ������ 1 - ���孨�, 2 - ������
&sect_num ,         // 54  ����� ᥪ樨 - �⮡ࠦ����
&sect_mass,         // 55  ���� ���᪠, ��  - �⮡ࠦ����
&sect_vol ,         // 56  ��ꥬ ���᪠,� - �⮡ࠦ����
&sect_rslt,         // 57  ����ﭨ� �������
                    //   0  - ������ �� �����襭
                    //   1  - ������ �����襭
                    //  -1  - ������ �४�饭 �� 'ESC'
                    //
                    //
&en_bot[4],         // 58  Start_High
&en_bot[12],        // 59  Start_Low
&en_bot[ 6],        // 60  ���᮫�
&en_bot[ 7],        // 61  �࠯

//&reg_cmnm,           // 62  ������ ॣ���� ���ﭨ�
&reg_cmn,           // 62  ������ ॣ���� ���ﭨ�
&sw_mmi_slv,        // 63  ���� MMI

&str_dsp1[0],       // 64  ��ப� 1
&str_dsp1[2],       // 65
&str_dsp1[4],       // 66
&str_dsp1[6],       // 67
&str_dsp1[8],       // 68
&str_dsp1[10],      // 69
&str_dsp1[12],      // 70
&str_dsp1[14],      // 71
&str_dsp1[16],      // 72
&str_dsp1[18],      // 73
&str_dsp1[20],      // 74
&str_dsp1[22],      // 75
&str_dsp1[24],      // 76
&str_dsp1[26],      // 77
&str_dsp1[28],      // 78

&str_dsp2[0],       // 79  ��ப� 2
&str_dsp2[2],       //
&str_dsp2[4],       //
&str_dsp2[6],       //
&str_dsp2[8],       //
&str_dsp2[10],      //
&str_dsp2[12],      //
&str_dsp2[14],      //
&str_dsp2[16],      //
&str_dsp2[18],      //
&str_dsp2[20],      //
&str_dsp2[22],      //
&str_dsp2[24],      //
&str_dsp2[26],      //
&str_dsp2[28],      //

&str_dsp3[0],       // 94  ��ப� 3
&str_dsp3[2],       //
&str_dsp3[4],       //
&str_dsp3[6],       //
&str_dsp3[8],       //
&str_dsp3[10],      //
&str_dsp3[12],      //
&str_dsp3[14],      //
&str_dsp3[16],      //
&str_dsp3[18],      //
&str_dsp3[20],      //
&str_dsp3[22],      //
&str_dsp3[24],      //
&str_dsp3[26],      //
&str_dsp3[28],      //

&str_dsp4[0],       // 109 ��ப� 4
&str_dsp4[2],       //
&str_dsp4[4],       //
&str_dsp4[6],       //
&str_dsp4[8],       //
&str_dsp4[10],      //
&str_dsp4[12],      //
&str_dsp4[14],      //
&str_dsp4[16],      //
&str_dsp4[18],      //
&str_dsp4[20],      //
&str_dsp4[22],      //
&str_dsp4[24],      //
&str_dsp4[26],      //
&str_dsp4[28],      //

&str_dsp5[0],       // 124 ��ப� 5
&str_dsp5[2],       //
&str_dsp5[4],       //
&str_dsp5[6],       //
&str_dsp5[8],       //
&str_dsp5[10],      //
&str_dsp5[12],      //
&str_dsp5[14],      //
&str_dsp5[16],      //
&str_dsp5[18],      //
&str_dsp5[20],      //
&str_dsp5[22],      //
&str_dsp5[24],      //
&str_dsp5[26],      //
&str_dsp5[28],      //

&str_dsp6[0],       // 139 ��ப� 6
&str_dsp6[2],       //
&str_dsp6[4],       //
&str_dsp6[6],       //
&str_dsp6[8],       //
&str_dsp6[10],      //
&str_dsp6[12],      //
&str_dsp6[14],      //
&str_dsp6[16],      //
&str_dsp6[18],      //
&str_dsp6[20],      //
&str_dsp6[22],      //
&str_dsp6[24],      //
&str_dsp6[26],      //
&str_dsp6[28],      //


&str_dsp7[0],       // 154 ��ப� 7
&str_dsp7[2],       //
&str_dsp7[4],       //
&str_dsp7[6],       //
&str_dsp7[8],       //
&str_dsp7[10],      //
&str_dsp7[12],      //
&str_dsp7[14],      //
&str_dsp7[16],      //
&str_dsp7[18],      //
&str_dsp7[20],      //
&str_dsp7[22],      //
&str_dsp7[24],      //
&str_dsp7[26],      //
&str_dsp7[28],      //

&Password,        // 169
&Password_m,        // 170
NULL                //

};

int n_sl_int=(sizeof(list_Slv_int) / sizeof(list_Slv_int[0])) - 1 ;
int n_sl_int1=(sizeof(list_Slv_int) / sizeof(list_Slv_int[0])) - 1 ;

float *list_Slv_flt[]={
&Slv_float[0],      // 0 F1000 ���࠭� �������
&Slv_float[1],      // 1 F1002 ����� ���࠭��
              // १�ࢭ� ��६����
&Vol_beg,           // 2 F1004  ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
&P_min_valve,       // 3 F1006 �������쭮� ��������  ���, �� ���஬ �������� 㢥����� �⥯���
                    //    ������ ���⨫�
&T_Ref,             // 4 F1008  ���७᭠� ⥬������,C (15)
&D_ref,             // 5 F1010  ���⭮��� �ਢ������� � ��७᭮� ⥬������
&V_ref,             // 6 F1012  ��ꥬ ���᪠ �ਢ������ � ��७᭮� ⥬������
&Temp_a,            // 7 F1014  ��������� ���饭���� ���⥯த��
&Dens_a,            // 8 F1016 ���⭮��� ���饭���� ���⥯த��
&dose_dlvr_sl,      // 9 F1018
              // ����� �� ��室����
&s_MVD[0].MassI,    // 10 F1020  ���� ������ୠ� ( ����������騩 ���稪) Mass inventory ,I263
&s_MVD[0].MassT,    // 11 F1022 ���� � ⥪�饩 ����樨 ���᪠ (total)   Mass total     ,I259
&s_MVD[0].FlowM,    // 12 F1024  ���ᮢ� ��室, ��/�                      Mass flow      ,I247
&s_MVD[0].Dens,     // 13 F1026 ���⭮��� ��/�3                            Density        ,I249
&s_MVD[0].Temp,     // 14 F1028 ���������,                               Temperature    ,I251
&s_MVD[0].VolI,     // 15 F1030 ��ꥬ �������� ( ����������騩 ���稪) Volume invntory,I265

&s_MVD[0].VolT,     // 16 F1032 ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
&s_MVD[0].FlowV,    // 17 F1034 ��ꥬ�� ��室, �/�
//&s_MVD[0].PressG,   // 18 F1036
&n_id_af,            //18 F1036 = F1070 ��� ����㯠 ��⮬�����

                    // ����� ���������� ���稪��
&s_MVD[0].TempR,    // 19 F1038  ⥬������ �� ���譥�� ���稪�
&s_MVD[0].Press,    // 20 F1040  �������� �� ���譥�� ���稪�

&P_dem,             // 21 F1042 �������� ��������  10000 = 1 ���
&LIM_P,             // 22 F1044 ���� ���� max,12800 = 1 ��
&LIM_M,             // 23 F1046 ���� ���� min,12800 = 1 ��
                           // ���孨� �����
&Flow_beg,          // 24 F1048 ���室 ��砫��, �/�
&Flow_nom,          // 25 F1050 ���室 ���������, �/�
&Flow_min,          // 26 F1052 ���室 ����������  , �/�
&Flow_min1,         // 27 F1054 ���室 ���������� 1, �/�
&Flow_min2,         // 28 F1056 ���室 ���������� 2, �/�
&Com_Baud_Slave,    // 29 F1058 ����� ������ �� Modbus

                           // ������ �����
&Flow_nomL,          // 30 F1060 ���室 ���������, �/�
&Flow_minL,          // 31 F1062 ���室 ���������� , �/�
&Flow_min1L,         // 32 F1064 ���室 ���������� 1, �/�
&Flow_min2L,         // 33 F1066 ���室 ���������� 2, �/�

&Dens_cmn_f,         // 34 F1068 ����饥 ���祭�� ���⭮�� �� 15 �, ��/�3

#if defined(BIO_1)
&T_Pmp_delay,        // 35 F1070 ����প� �몫�祭�� ���� ��᫥ ����砭�� ���᪠
#else
&n_id_af,            // 35 F1070 ��� ����㯠 ��⮬�����
#endif
&s_MVD[0].PressG,    // 36 F1072

NULL

};
float Com_Baud_Slave=9600;
long int *list_Slv_lng[]={
                    // Addr = 1058
//&Com_Baud_Slave,    //  29  ����� ������ �� Modbus

NULL
};

int n_sl_lng=(sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1 ;
int n_sl_lng1=(sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1 ;

int n_sl_flt=((sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1)+ ((sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1) ;
//int n_sl_flt1=((sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1)+ ((sizeof(list_Slv_lng) / sizeof(&FL_err)) - 1) ;
int n_sl_flt1=((sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1);
int n_sl_flt0=(sizeof(list_Slv_flt) / sizeof(&FL_err)) - 1 ;

int Slv_int[20]={
  0,0,0,0,0,
  0,0,0,0,0,
};

//--------------------------------
float Slv_float[20]={
0,
0,
2,
3,
4,
5,
};
//--------------------------------
long int Slv_lng[10]={
  0,1,2,3,4,
  5,6,7,8,9,
};

struct eee_dat S1D;  //T_INT T_INT_L T_FLOAT

// Addr2Slot1 2000
//  �����, �⠥�� ���孨� ����஫��஬

/* ============================
struct eee_dat Slv2_Slot1[]=
{
&CMD_IN             , T_INT   ,  //1   I7     CMD_OUT_p
&State_SLV          , T_INT   ,  //1   I8
&Reg_err            , T_INT   ,  //1   I10
&INP_VARi0          , T_INT   ,  //1   I21
&OUT_VARi0          , T_INT   ,  //1   I22
&s_MVD[0].MassI     , T_FLOAT ,  //2   F1020     ���� ������ୠ� ( ����������騩 ���稪)
&s_MVD[0].MassT     , T_FLOAT ,  //2   F1022     ���� � ⥪�饩 ����樨 ���᪠ (total)
//&s_MVD[0].FlowM     , T_FLOAT ,  //2  F1024     ���ᮢ� ��室, ��/�
&s_MVD[0].FlowV     , T_FLOAT ,  //2            �ꥬ�� ��室, �3/�
&s_MVD[0].Dens      , T_FLOAT ,  //2  F1026     ���⭮��� ��/�3
&s_MVD[0].Temp      , T_FLOAT ,  //2  F1028     ���������,C
&s_MVD[0].VolI      , T_FLOAT ,  //2  F1030     ��ꥬ �������� ( ����������騩 ���稪)
&s_MVD[0].VolT      , T_FLOAT ,  //2  F1032     ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
&Temp_a             , T_FLOAT ,  //2  F1014     ��������� ���饭���� ���⥯த��
&Dens_a             , T_FLOAT ,  //2  F1016     ���⭮��� ���饭���� ���⥯த��
&T_Ref              , T_FLOAT ,  //2  F1008     ���७᭠� ⥬������,C (15)
&D_ref              , T_FLOAT ,  //2  F1010     ���⭮��� �ਢ������� � ��७᭮� ⥬������
&V_ref              , T_FLOAT ,  //2  F1012     ��ꥬ ���᪠ �ਢ������ � ��७᭮� ⥬������
&type_liq           , T_INT   ,  //1  I36       ⨯ ���⥯த��  1 - ⮢�ୠ� �����, 2 - ���⮯����, 5 - ������
};

int Slv2_slt1_lgth= 30 ;
int Slv2_slt1_max=sizeof(Slv2_Slot1) / sizeof(S1D) ;
    ============================== */
//---------------------------------------


struct eee_dat Slv2_Slot1[]=
{

&CMD_IN ,   // &Slv_int[6], // I7 CMD_REG ॣ���� �������
 T_INT   ,

&State_SLVm,// I8   ����ﭨ� ���᪠
 T_INT   ,

&result_dlv,// I37 १���� �����襭�� ���᪠
 T_INT   ,

// ====  I62 - ������ ॣ���� ���ﭨ�
&reg_cmnm,           //1 62  ������ ॣ���� ���ﭨ�
 T_INT   ,

// ====  I63 - ����ﭨ� ���� ���
&sw_mmi_slv,        //2 63  ���� MMI
 T_INT   ,


// ====  I18 - 1 - ����� ����� ���� �� ���
&mode_hst,          //3 18  1 - ����� ����� ���� �� ���
 T_INT   ,
//  I 53
&type_dlv ,         // 53  ⨯ ������ 1 - ���孨�, 2 - ������
 T_INT   ,

// ====  I21 - ॣ���� ����.�室��
&INP_VARi0,         //4 21 ॣ���� ����.�室�� � ��⮬ �����ᨨ
 T_INT   ,

// ====  I22 - ॣ���� ����.��室��
&OUT_VARi0,           //5 22 ॣ���� ����.��室��
 T_INT   ,

// ====  I25 - ⮪ � ����
&DriveCurrent[0],  //6  &Delta_current[0],  // 25 ⮪ � ����
 T_INT   ,

// ====  I10 - ������� �訡�� ��⪨�, 0 - OK
&Reg_errm,          //7    10    &FL_err,         // 10  ���� �訡��, 0 - OK
 T_INT   ,

// ====  I11 - ��� �訡�� �㭪樮��஢���� (�.����)
&ICP_error[9],   //8   11  ��� �訡�� �㭪樮��஢����
 T_INT   ,

// ====  I12 - ����७�� ���� �訡�� �㭪樮��஢���� (�.����)
&ICP_error[10],  //9  12  ���७�� ॣ���� �訡��
 T_INT   ,

// ====  I13 - ॣ���� �訡�� �ࠩ��� MVD   ( ��室���� Micro Motion)
&ICP_error[1],   //10  13  ॣ���� �訡�� �ࠩ��� MVD
 T_INT   ,

// ====  I14 - ॣ���� �訡�� �ࠩ��� 7060  ( ������ ����-�뢮�)
&ICP_error[2],   //11  14  ॣ���� �訡�� �ࠩ��� 7060
 T_INT   ,

// ====  I15 - ॣ���� �訡�� �ࠩ��� 7017  ( ��������� ����)
#if defined(ICP_7041)
&ICP_error[4],   // 15  ॣ���� �訡�� �ࠩ��� 7017
#else
&ICP_error[3],   // 15  ॣ���� �訡�� �ࠩ��� 7017
#endif
 T_INT   ,

// ====  I16 - ॣ���� �訡�� �ࠩ��� DELTA ( ���யਢ�� ����)
&ICP_error[6],   //13  16  ॣ���� �訡�� �ࠩ��� DELTA
 T_INT   ,

// ====  I24 - ॣ���� �訡�� �ਢ��� DELTA
&DriveError[0],   //14   24 ॣ���� �訡��  DELTA
 T_INT   ,

// ====  I35 - ॣ���� �訡�� ��室���� Micro Motion (ॣ���� I419 , p.148 ).
&s_MVD[0].reg_err,  //15   35 ॣ���� �訡�� MVD
 T_INT   ,

// ====  F1014 - �।��� ⥬������ ���饭���� ���⥯த��
&Temp_a,            //17    7 F1014  ��������� ���饭���� ���⥯த��
 T_FLOAT ,

// ====  F1016 - �।��� ���⭮��� ���饭���� ���⥯த��
&Dens_a,            //19  8 F1016 ���⭮��� ���饭���� ���⥯த��
 T_FLOAT ,

// ====  F1020 - ���� ������ୠ� ( ����������騩 ���稪) Mass inventory ,I263
&s_MVD[0].MassI,    //21   10 F1020  ���� ������ୠ� ( ����������騩 ���稪) Mass inventory ,I263
 T_FLOAT ,

// ====  F1022 - ���� � ⥪�饩 ����樨 ���᪠ (total)   Mass total     ,I259
&s_MVD[0].MassT,    //23   11 F1022 ���� � ⥪�饩 ����樨 ���᪠ (total)   Mass total     ,I259
 T_FLOAT ,

// ====  F1024 - ���ᮢ� ��室, ��/�                      Mass flow      ,I247
&s_MVD[0].FlowM,    //25   12 F1024  ���ᮢ� ��室, ��/�                      Mass flow      ,I247
 T_FLOAT ,

// ====  F1026 - ���⭮��� ��/�3                            Density        ,I249
&s_MVD[0].Dens,     //27  13 F1026 ���⭮��� ��/�3                            Density        ,I249
 T_FLOAT ,

// ====  F1028 - ���������,C                              Temperature    ,I251
&s_MVD[0].Temp,     //29   14 F1028 ���������,                               Temperature    ,I251
 T_FLOAT ,

// ====  F1030 - ��ꥬ �������� ( ����������騩 ���稪) Volume invntory,I265
&s_MVD[0].VolI,     //31   15 F1030 ��ꥬ �������� ( ����������騩 ���稪) Volume invntory,I265
 T_FLOAT ,

// ====  F1032 - ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
&s_MVD[0].VolT,     //33   16 F1032 ��ꥬ � ⥪�饩 ����樨 ���᪠ (total)
 T_FLOAT ,

// ====  F1034 - ��ꥬ�� ��室, �/�
&s_MVD[0].FlowV,    //35   17 F1034 ��ꥬ�� ��室, �/�
 T_FLOAT ,

// ====  F1072 - ����� ( ����������: �������� �� �室� ����, ���)
&s_MVD[0].PressG,   //37   36 F1072
 T_FLOAT ,

// ====  F1038 - ⥬������ �� ���譥�� ���稪�, C
&s_MVD[0].TempR,    //39   19 F1038  ⥬������ �� ���譥�� ���稪�
 T_FLOAT ,

// ====  F1040 - �������� �� ���譥�� ���稪�, ��� (�� ��直� ��砩) !!!
&s_MVD[0].Press,    //41   20 F1040  �������� �� ���譥�� ���稪�
 T_FLOAT ,

// ====  F1070 - ��� ����㯠 ��⮬����� - १���� ������� I=300
&n_id_af,            //43   36 F1070 ��� ����㯠 ��⮬�����
 T_FLOAT ,


// ====  I36 - ⨯ ���⥯த��
&type_liq,          //44  36  1 Crude Oils
 T_INT   ,

// ====  I40 - ���� �ப�窨
&flag_prok ,        //45   40  1 - �ப�窠
 T_INT   ,

// ====  I41 - ���筨� ������ � ⥬������ ��� ���᫥��� ���⭮��]
&mode_temp ,        //46   41  1 - ���譨� �ମ���� ��� D_ref, 0 - MVD
 T_INT   ,

// ====  I42 - ����� ���᫥��� �ਢ������� ���⭮��
&mode_refD ,        //47   42  1 - ��।����� � ����� �ਥ�� D_ref
 T_INT   ,

// ====  F1004 - ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
&Vol_beg,           //49   2 F1004  ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
 T_FLOAT ,

// ====  F1006 - �������쭮� �������� ���, �� ���஬ �������� 㢥����� �⥯��� ������ ���⨫�
&P_min_valve,       //51   3 F1006 �������쭮� ��������  ���, �� ���஬ �������� 㢥����� �⥯���
 T_FLOAT ,

// ====  F1042 - �������� ��������,10000 = 1 ��� 3200
&P_dem,             //53   21 F1042 �������� ��������  10000 = 1 ���
 T_FLOAT ,

// ====  F1044 - ����� ��⠭�� ���� max, 204800 = 1 Hz,(default 10240000=50 Hz)
&LIM_P,             //55   22 F1044 ���� ���� max,12800 = 1 ��
 T_FLOAT ,

// ====  F1046 - ����� ��⠭�� ���� min, ��      409600       = 2 Hz, 204800 = 1 Hz
&LIM_M,             //57   23 F1046 ���� ���� min,12800 = 1 ��
 T_FLOAT ,

// ====  F1058 - ����� ������ �� Modbus, ��� (19200)
&Com_Baud_Slave,    //59   29 F1058 ����� ������ �� Modbus
 T_FLOAT ,

};

int Slv2_slt1_lgth= 63 ;
int Slv2_slt1_max=sizeof(Slv2_Slot1) / sizeof(S1D) ;

//---------------------------------------
//---------------------------------------
// Addr2Slot2   3000
// �����, �����뢠��� ���孨� ����஫��஬

struct eee_dat Slv2_Slot2[]=
{
&CMD_IN        , T_INT   ,       // 1   I7     ॣ���� �������
&Slv_float[0]  , T_FLOAT ,       // 2   F1000  ���࠭� �������
&Flow_nom      , T_FLOAT ,       // 2   F1050  ���室 ���������, �/�
&Vol_beg       , T_FLOAT ,       // 2   F1004  ��ꥬ ����� �� �஢�� ����㦥��� �㪠��,�
&Flow_beg      , T_FLOAT         // 2   F1048  ���室 ��砫��, �/�
};
int Slv2_slt2_lgth= 9 ;
int Slv2_slt2_max=sizeof(Slv2_Slot2) / sizeof(S1D) ;
//---------------------------------------

// Addr2Slot3 4000
//  �����, �⠥�� ���孨� ����஫��஬
//  ����� �ਭ��� �� MVD ��᫥ ����� � Slot4

// #define max_lgth_sl3 20 // see. slave.h

int Flag_sl3=0; //     -1 - �訡�� �� �⥭�� ������, �⥭�� ��⠭������
                //      0 - ����� �� ��⮢�
                // =nn >0 - ����� ��諨 nn ࠧ � �� ���⠭�

int Flag_sl31=0; // �ਧ��� ��ࢮ�� �⥭��

int Slot3_dat[max_lgth_sl3];

struct eee_dat Slv2_Slot3[]=
{
&Flag_sl3           , T_INT   ,  //1
&Slot3_dat[0]       , T_INT   ,  //1
&Slot3_dat[1]       , T_INT   ,  //1
&Slot3_dat[2]       , T_INT   ,  //1
&Slot3_dat[3]       , T_INT   ,  //1
&Slot3_dat[4]       , T_INT   ,  //1
&Slot3_dat[5]       , T_INT   ,  //1
&Slot3_dat[6]       , T_INT   ,  //1
&Slot3_dat[7]       , T_INT   ,  //1
&Slot3_dat[8]       , T_INT   ,  //1
&Slot3_dat[9]       , T_INT   ,  //1
&Slot3_dat[10]      , T_INT   ,  //1
&Slot3_dat[11]      , T_INT   ,  //1
&Slot3_dat[12]      , T_INT   ,  //1
&Slot3_dat[13]      , T_INT   ,  //1
&Slot3_dat[14]      , T_INT   ,  //1
&Slot3_dat[15]      , T_INT   ,  //1
&Slot3_dat[16]      , T_INT   ,  //1
&Slot3_dat[17]      , T_INT   ,  //1
&Slot3_dat[18]      , T_INT   ,  //1
&Slot3_dat[19]      , T_INT   ,  //1
};

int Slv2_slt3_lgth= 21 ;
int Slv2_slt3_max=sizeof(Slv2_Slot3) / sizeof(S1D) ;

//---------------------------------------
//---------------------------------------
// Addr2Slot4   5000
// �����, �����뢠��� ���孨� ����஫��஬
// ������ � ��� ᫮� ���樨��� �⥭�� �� MVD

#define  Sl3_tim_default (1000)

int Sl3_addr=0;
int Sl3_lgth=0;
int Sl3_time=0;
int Sl3_time_mul=1;
int Sl3_nn  = -1;

float SLT3_N;
float SLT3_A;


long int Sl3_time_l=0;

struct eee_dat Slv2_Slot4[]=
{
&Sl3_addr      , T_INT   ,       // 1  ���� ॣ���� MVD
&Sl3_lgth      , T_INT   ,       // 1  ������⢮ � 楫��᫥���� ॣ�����
&Sl3_time      , T_INT   ,       // 1  ��ਮ� ����,��
&Sl3_time_mul  , T_INT   ,       // 1  �����⥫� � ��ਮ�� ����
&Sl3_nn        , T_INT   ,       // 1  ������⢮ �⥭��, -1 - 横���᪨
};

int Slv2_slt4_lgth= 5 ;
int Slv2_slt4_max=sizeof(Slv2_Slot4) / sizeof(S1D) ;

//---------------------------------------

//---------------------------------------

unsigned long ComBaudSlv =9600L;
int Com_lgthSlv  =8;
int Com_paritySlv=0;// None  //0-(None);1-(Even);2-(Odd);3-(MARK, always 1); 4-(SPACE,always 0)
int Com_stopSlv  =1;
struct stor_buf *bf_Slv;
int uk_beg_Slv=0;
int uk_fin_Slv=0;

  unsigned char buf_tmpSR[n_buf_RTU_s];
// ==================================================
// ==================================================

/*
void f_send_slv1()
{

        if(fl_slv_out != 0)
         {
          if( f_timer(time_snd[ComPortSlv],out_delay_slv))
           {
            ToComBufn(ComPortSlv,buf_tmpSR,fl_slv_out);
            flag_slvrtu=0;
            fl_slv_out=0;
           }
         }

}
*/
// ==================================================
int nn_comb=0;
void fun_tim_u(void)
{
     if(flag_Slv != 0 )
     {
        if((flag_slvrtu == 0) && (fl_slv_out==0))
        {
         if(ffgets_SlvRTU(ComPortSlv))
         {
           flag_slvrtu = 1;

          _fmemcpy(intrpr.bfcom,&cb_COM[ComPortSlv][0],(long int)(n_bcom[ComPortSlv]-2) );
          nn_comb=n_bcom[ComPortSlv];
          n_bcom[ComPortSlv]=0;

         }
        }

//      f_send_slv1() ;
/*
        if(fl_slv_out != 0)
         {
          if( f_timer(time_snd[ComPortSlv],out_delay_slv))
           {
            ToComBufn(ComPortSlv,buf_tmpSR,fl_slv_out);
            flag_slvrtu=0;
            fl_slv_out=0;
//          n_bcom[ComPortSlv]=0;
           }
         }
*/

     }
}

// ==================================================

/*

void f_send_slv()
{
        if(fl_slv_out != 0)
         {
          if( f_timer(time_snd[ComPortSlv],out_delay_slv))
           {
            ToComBufn(ComPortSlv,buf_tmpSR,fl_slv_out);
            flag_slvrtu=0;
            fl_slv_out=0;
           }
         }
}

*/

// ==================================================

void f_SlaveRTU()
{
int itmp;
//  int  hour,min,sec;
// ������ ������� �� Host (PC) � ��������� �� �� ��⮪��� Modbus RTU

         if((flag_slvrtu != 0) && (fl_slv_out==0))
         {
//          f_stor_Slv(M_RD,cb_COM[ComPortSlv],n_bcom[ComPortSlv]);
            f_intr_SlvRTU();
            flag_slvrtu=0;
         }
}
/*-------------------------------------------*/
void f_get_SlvBuf()
{
  unsigned long int count=0xffff;

    if( ( bf_Slv = (struct stor_buf *)malloc( (size_t)count )) == NULL )
    {
      printf("\n\r!Slave buffer is not allocated.\n\r");
      RestoreCom(1);
      RestoreCom(2);
      RestoreCom(3);
      while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
      RestoreCom(4);
      exit (0);
    }
}
/*-------------------------------------------*/
void f_free_SlvBuf()
{
  free( bf_Slv );
}
/*-------------------------------------------*/
void f_stor_Slv( char type,char *buf,int buf_n)
{
  long int nn;

 bf_Slv[uk_fin_Slv].time = TimeStamp;

 if(buf_n >= mess_lgth ) nn=mess_lgth;
 else nn=buf_n;

 bf_Slv[uk_fin_Slv].type_n=type | (char)nn;

 _fmemcpy(bf_Slv[uk_fin_Slv].messg,buf,nn );
 uk_fin_Slv=(uk_fin_Slv+1)&Slv_b_lgth_1;
}
/*-------------------------------------------*/
#define RTU_min 6
#define n_max_fn 5
#define NN_fict 1000
// ������⢮ ���� � ������� Host

/* =============
// �㭪�� ,  ����� � �����.�㬬.
  1,8, // �⥭�� Coil
  3,8, // �⥭�� Int
  5,8, // ������ Coil
  6,8, // ������ Int
  16,NN_fict, // ������ ��᪮�쪨� ���祭��
=============== */

int n_max_rcv=NN_fict;
int flag_wd_err=0;
int ffgets_SlvRTU(int ComPort)
{

//  �㭪�� �ਭ����� ᨬ���� �� ���� COM ComPort  � ���� cb_COM[ComPort].
//  �� ⠩���� ������� ��⠥��� ��������� � �㭪�� �����頥�
// ���祭�� 1.
//

/* ComPort - ����� COM   1...4 */
 char tmp;
 int tmp1;
 int i;
m1:
     if(IsCom(ComPort)==0)
     {
         if( WD_PMP_Per !=0 )
           if( f_timer(WD_PMP_time,WD_PMP_Per ))
           { // ��� �ᯥ譮�� �ਥ��

            if(WD_PMP_flag != 0)
            {
              WD_PMP_flag=0;
            //  f_icp_errS(WD_host);
                          flag_wd_err=1;
            }
            WD_PMP_time=TimeStamp;
           }

           if( f_timer(WD_PMP_t1,WD_PMP_P1 ))
           { // ��� �ᯥ譮�� �ਥ��
            WD_PMP_Fl=0;
            WD_PMP_t1=TimeStamp;
           }

        if( n_bcom[ComPort] != 0)
         if( f_timer(time_snd[ComPort],byte_timout_slv))
         { // ��⥪ ⠩���� �ਥ�� �⢥� �� �������
m_end:
            if((n_bcom[ComPort] >= RTU_min)&& (cb_COM[ComPort][0]==AddrSlv))
            {
              if(f_check_crc_RTU(cb_COM[ComPort],n_bcom[ComPort])==0)
               {
                  goto m_err;
               }
              n_max_rcv= NN_fict;

   //       WD_PMP_flag=1;
              WD_PMP_time=TimeStamp;
              WD_PMP_t1=TimeStamp;
              WD_PMP_Fl=1;
       /*
              if(ICP_error[icp_lst_max] & WD_host)
              {
               ICP_error[icp_lst_max] &= ~(unsigned int)WD_host;
               ICP_error_c[icp_lst_max]=ICP_error[icp_lst_max];
               for(i=0,tmp1=0;i<=icp_lst_max;i++)
               {
                 tmp1 |=ICP_error[i];
               }
//              printf("\r\n tmp1= %04x",tmp1);

               if(tmp1==0)
               {
                FL_err=0;
                if(sw_mmi==0) f_prn_begin();
               }
              }
       */
              return 1;
            }
            else
             {
m_err:
               n_bcom[ComPort]=0;
               n_max_rcv= NN_fict;
               return 0;
             }
         }
         return 0;
     }
     tmp=ReadCom(ComPort);
     time_snd[ComPort]= TimeStamp;

  #if(Slv_deb_rtu != 0)
   if(flag_prn != 0) // qqqqq
     {
        tmp1=TimeStamp & 0x3ff;
        printf("%04d:%02X ",tmp1, (int)tmp & 0xff);

     }
  #endif

//     ToutAns[ComPort]=byte_timout_rtu[ComPort];

     cb_COM[ComPort][n_bcom[ComPort]]=tmp;
     if( (++n_bcom[ComPort]) >= n_bufcom )
      {
        n_bcom[ComPort]--;
  /*
        printf("\n Command buffer overflow !\n--");
        puts(cb_COM1);
  */
      }

      if(n_bcom[ComPort] == 2)
         n_max_rcv=f_get_numRTU2(ComPort);
      else if ((n_bcom[ComPort] == 7) && (n_max_rcv == NN_fict)  )
         n_max_rcv=f_get_numRTU7(ComPort);

      if(n_bcom[ComPort]>= n_max_rcv) goto m_end;

      goto m1;
}
/*-------------------------------------------*/
int f_get_numRTU2(int ComPort)
{// �� ᮤ�ন���� cb_COM[ComPort][] � ������⢮� ���� n_bcom[ComPort]
 // ������ ����� ���뫪� RTU. �᫨ ����� �� ��।����� - �����頥� NN_fict
 int i_ret;
 switch ((int) cb_COM[ComPort][1])
 {
  case 1:
  case 3:
  case 5:
  case 6:
         i_ret=8;
         break;

  default: i_ret=NN_fict;
 }
 return i_ret;
}
/*-------------------------------------------*/
int f_get_numRTU7(int ComPort)
{// �� ᮤ�ন���� cb_COM[ComPort][] � ������⢮� ���� n_bcom[ComPort]
 // ������ ����� ���뫪� RTU. �᫨ ����� �� ��।����� - �����頥� NN_fict

 int i_ret;

 if( cb_COM[ComPort][1] == 16 )
   i_ret=(((int)cb_COM[ComPort][6]) & 0xff) + 9;
 else
   i_ret=NN_fict;

 return i_ret;
}
/*-------------------------------------------*/

 int i1_slv,i2_slv;

void  f_intr_SlvRTU()
{
  int exc;
  int fn_cod;
  int addr_beg,i,itmp;
  int Slv_addrO,Slv_nmbO;
  float ftmp;
  union  { float f; unsigned long l; } o;
  struct eee_dat *LIn_D;

  // �ਭ��� ������� �஢�७� �� ����஫��� �㬬� � ��室���� � intrpr.bfcom
  //  (��� ����஫쭮� �㬬�)

//---------------------------------------------------
  fn_cod=intrpr.bfcom[1];


#if(Slv_deb_rtu != 0)
     if(flag_prn != 0) // QQQ
     {
      printf("\r\nN= %d ==",nn_comb);
      for(i=0;i< nn_comb;i++)
      printf(" %02X", (intrpr.bfcom[i] & 0X0FF) );

      printf("\r\n");
     }
#endif

  _fmemcpy(buf_tmpSR,intrpr.bfcom,(long int)(8) );
  if(fn_cod== 3)
  {   // �⥭�� Int
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    Slv_nmbO=f_get_intS(&intrpr.bfcom[4]);

    if(Slv_nmbO>125)
        goto m_err_addr;


    if( f_is_int(Slv_addrO) &&  f_is_int(Slv_addrO+Slv_nmbO-1) )
    { // ����襭� ����� int

      buf_tmpSR[0]=AddrSlv;
      buf_tmpSR[1]=fn_cod;
      buf_tmpSR[2]=Slv_nmbO+Slv_nmbO;

      for(i1_slv=3,i=0;(i<Slv_nmbO)&&(i1_slv< (n_buf_RTU_s-3)) ;i++)
       {
//       itmp=Slv_int[Slv_addrO+i];
         itmp=*(int *)list_Slv_int[Slv_addrO+i];
         buf_tmpSR[i1_slv++]=(itmp>>8) & 0xff;
         buf_tmpSR[i1_slv++]= itmp & 0xff;
       }
      goto out_b;
    }
    else
     if( f_is_float(Slv_addrO) &&  f_is_float(Slv_addrO+Slv_nmbO-2) )
     { // ����襭� ����� float
      if(Slv_addrO & 0x01) goto m_err_addr;
      if(Slv_nmbO  & 0x01) goto m_err_val;

      buf_tmpSR[0]=AddrSlv;
      buf_tmpSR[1]=fn_cod;
      buf_tmpSR[2]=Slv_nmbO+Slv_nmbO;
      Slv_nmbO=Slv_nmbO>>1;

      addr_beg=(Slv_addrO-AddrLowFloat)>> 1;
      for(i1_slv=3,i=0;(i<Slv_nmbO)&&(i1_slv< (n_buf_RTU_s-3));i++,i1_slv+=4)
       {
         if((addr_beg+i) < n_sl_flt0)
           f_set_float( &buf_tmpSR[i1_slv],*list_Slv_flt[addr_beg+i],cod_float);
         else
           f_set_float( &buf_tmpSR[i1_slv],(float)*list_Slv_lng[addr_beg+i-n_sl_flt0],cod_float);
//         f_set_long( &buf_tmpSR[i1_slv],*list_Slv_lng[addr_beg+i-n_sl_flt0]);
       }
      goto out_b;

     }
     else if((Slv_addrO == Addr2Slot1 ) && ( Slv_nmbO <= Slv2_slt1_lgth))
     {  // �⥭�� ���孨� ����஫��஬ ������ Slot1

      LIn_D=&Slv2_Slot1[0];

m_slt:
      buf_tmpSR[0]=AddrSlv;
      buf_tmpSR[1]=fn_cod;
      buf_tmpSR[2]=Slv_nmbO+Slv_nmbO;

      for(i1_slv=3,i=0,i2_slv=0;(i<Slv_nmbO)&&(i1_slv< (n_buf_RTU_s-3)) ;i2_slv++)
       {
             switch( LIn_D[i2_slv].l )
             {
              case T_INT:
                f_set_int( &buf_tmpSR[i1_slv], *((int *) LIn_D[i2_slv].ptr)  );
                i1_slv+=2;
                i++;
                break;

              case T_INT_L:
                f_set_long( &buf_tmpSR[i1_slv], *((long int *) LIn_D[i2_slv].ptr) );
                i1_slv+=4;
                i+=2;
                break;

              case T_FLOAT:
                f_set_float( &buf_tmpSR[i1_slv], *((float *) LIn_D[i2_slv].ptr),1 );
                i1_slv+=4;
                i+=2;
                break;
             }
       }
       if(LIn_D== &Slv2_Slot3[0])
                Flag_sl3 = 0 ; // ��� ��⮢�� ������

      goto out_b;

     }
     else if((Slv_addrO == Addr2Slot3 ) && ( Slv_nmbO <= Slv2_slt3_lgth))
     {  // �⥭�� ���孨� ����஫��஬ ������ Slot3

      LIn_D=&Slv2_Slot3[0];
      goto m_slt;
     }
     else if((Slv_addrO == Addr2Slot4 ) && ( Slv_nmbO <= Slv2_slt4_lgth))
     {  // �⥭�� ���孨� ����஫��஬ ������ Slot3

      LIn_D=&Slv2_Slot4[0];
      goto m_slt;
     }
    else goto m_err_addr;
  }
  if(fn_cod== 6)
  {   // ������ Int
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    if( f_is_int(Slv_addrO) )
    { // ������ ������ int
      *(int *)list_Slv_int[Slv_addrO]=f_get_intS(&intrpr.bfcom[4]);
      if((exc=f_int_fnc(Slv_addrO)) != 0)
       {
         CMD_OUT_p = CMD_IN | 0x8000;
         goto m_err;
       }

      CMD_OUT_p = CMD_IN; //  | 0x4000;
      i1_slv=6;
      goto out_b;
    }
    else if(Slv_addrO == Addr2Slot4 )
    {
      Sl3_addr=f_get_intS(&intrpr.bfcom[4]);
      Slv_nmbO=1;
      goto m_slt4;
    }
    else goto m_err_addr;
  }
  if(fn_cod == 16 )
  {   // ������ ��᪮�쪨� ���祭��
    Slv_addrO=f_get_intS(&intrpr.bfcom[2]);
    Slv_nmbO=f_get_intS(&intrpr.bfcom[4]);
    if( f_is_int(Slv_addrO) &&  f_is_int(Slv_addrO+Slv_nmbO-1) )
    { //   ����� int

     for(i1_slv=7,i=0;i<Slv_nmbO;i++,i1_slv+=2)
     {
      *(int *)list_Slv_int[Slv_addrO+i]=f_get_intS(&intrpr.bfcom[i1_slv]);
      if((exc=f_int_fnc(Slv_addrO+i)) != 0)
         goto m_err;
     }

     i1_slv=6;
     goto out_b;

    }
    else if( f_is_float(Slv_addrO) &&  f_is_float(Slv_addrO+Slv_nmbO-2) )
    { //  ����� float
      if(Slv_addrO & 0x01) goto m_err_addr;
      if(Slv_nmbO  & 0x01) goto m_err_val;

      addr_beg=(Slv_addrO-AddrLowFloat)>> 1;
      Slv_nmbO=Slv_nmbO>>1;
      // i1_slv=7-3;
      for(i1_slv=4,i=0;i<Slv_nmbO;i++,i1_slv+=4 )
      {
         if((addr_beg+i) < n_sl_flt0)
            *list_Slv_flt[addr_beg+i]=f_get_float( &intrpr.bfcom[i1_slv], cod_float);
         else
            *list_Slv_lng[addr_beg+i-n_sl_flt0]=f_get_float( &intrpr.bfcom[i1_slv], cod_float);
      }
      i1_slv=6;
      goto out_b;
    }
    else if((Slv_addrO == Addr2Slot2 ) && ( Slv_nmbO <= Slv2_slt2_lgth))
    {
     // Slot2  - �ਭ�� ������� � ���࠭� �������
// printf("\r\n SlvSlot2");
      if(f_set_slv( &Slv2_Slot2[0],Slv_nmbO )) goto m_err_val;
// printf("\r\n CMD_IN=%d",CMD_IN);
      if((exc=f_int_fnc(7)) != 0)
       {

// printf("\r\n exc=%d",exc);
         CMD_OUT_p = CMD_IN | 0x8000;
         goto m_err;
       }
      CMD_OUT_p = CMD_IN; //  | 0x4000;
      i1_slv=6;
      goto out_b;

    }
    else if((Slv_addrO == Addr2Slot4 ) && ( Slv_nmbO <= Slv2_slt4_lgth))
    {
     // Slot4  - �ਭ�� �������  �� �⥭�� ������ �� MVD
// printf("\r\n SlvSlot4");
      if(f_set_slv( &Slv2_Slot4[0],Slv_nmbO )) goto m_err_val;
m_slt4:
     {  // some actions
         Flag_sl3 = 0 ; // ��� ��⮢�� ������
         Flag_sl31 = 0 ;
         fl_sl_tim3=0;
         Sl3_fl_jrn=0;

         if(Slv_nmbO == 1)
         { // �⥭�� ������ ॣ���� � ���� Sl3_addr
           Sl3_lgth= 1;
           Sl3_time =0 ;
           Sl3_time_l=0;
           Sl3_nn= 1;
         }
         else if (Slv_nmbO == 2)
         {  // ������⭮� �⥭�� Sl3_lgth ॣ���஢ � ���� Sl3_addr
           if(Sl3_lgth < 0)
           { // �⬥�� �⥭�� ॣ���஢
             Sl3_nn= 0;
           }
           else
           {
             Sl3_time =0 ;
             Sl3_time_l=0;
             Sl3_nn = 1;
           }
         }
         else if (Slv_nmbO == 3)
         {  // 横���᪮� �⥭�� Sl3_lgth ॣ���஢ � ���� Sl3_addr
           Sl3_time_mul=1;
           Sl3_time_l = Sl3_time;
           if(Sl3_time_l < 0) Sl3_time_l = Sl3_tim_default;
           Sl3_nn= -1;
         }
         else if (Slv_nmbO == 4)
         {  // 横���᪮� �⥭�� Sl3_lgth ॣ���஢ � ���� Sl3_addr
            // �ᯮ������ �����⥫� �६���
           Sl3_time_l = (long int)Sl3_time * (long int)Sl3_time_mul;
           if(Sl3_time_l < 0) Sl3_time_l = Sl3_tim_default;
           Sl3_nn= -1;
         }
         else if (Slv_nmbO == 5)
         {  //  �⥭�� Sl3_nn ࠧ  Sl3_lgth ॣ���஢ � ���� Sl3_addr
           Sl3_time_l = (long int)Sl3_time * (long int)Sl3_time_mul;
           if(Sl3_time_l < 0) Sl3_time_l = Sl3_tim_default;
      //   if(Sl3_nn < 0) Sl3_nn=1;
         }
     }

      i1_slv=6;
      goto out_b;

    }
    else goto m_err_addr;
  }
  else  goto m_err_fn ;

//---------------------------------------------------
m_err_fn  : // �㭪�� �� �ᯮ�����
 exc=01;
 goto m_err;

m_err_addr: // �������⨬� ����
 exc=02;
 goto m_err;

m_err_val : // �������⨬� �����
 exc=03;
 goto m_err;

m_err_slv : // �訡�� � Slave
 exc=04;
 goto m_err;

m_err:

 fn_cod |= 0x80;

 buf_tmpSR[0]=AddrSlv;
 buf_tmpSR[1]=fn_cod;
 buf_tmpSR[2]=exc;
 i2_slv=3;

#if(Slv_deb != 0)

 printf("\n\r====");
 for(i=0;i<i2_slv;i++)
 {
  printf("%02X ",buf_tmpSR[i]);
 }
 printf("====\n\r");
#endif

// f_stor_Slv(M_WR,buf_tmpSR,i2_slv);
 f_prepareRTU(buf_tmpSR,&i2_slv);
// fl_slv_out=i2_slv;

 fl_slv_out=0;
 ToComBufn(ComPortSlv,buf_tmpSR,i2_slv);
 return;

out_b:

 buf_tmpSR[0]=AddrSlv;
 buf_tmpSR[1]=fn_cod;

 i2_slv=i1_slv;

#if(Slv_deb != 0)

 printf("\n\r====");
 for(i=0;i<i2_slv;i++)
 {
  printf("%02X ",buf_tmpSR[i]);
 }
 printf("====\n\r");

#endif

//  f_stor_Slv(M_WR,buf_tmpSR,i2_slv);
 if(f_prepareRTU1(buf_tmpSR,&i2_slv)) goto m_err_val;

//  fl_slv_out=i2_slv;

 fl_slv_out=0;
 ToComBufn(ComPortSlv,buf_tmpSR,i2_slv);

 if(ff_Slv != NULL)
 {
  (*ff_Slv)(); // ���� �㭪樨
  ff_Slv = NULL;
 }
 return;
}
/*-------------------------------------------*/
/*-------------------------------------------*/
int f_is_int(int addr)
{
 if((addr >= AddrLowInt) && (addr <= AddrHighInt) )
    return 1;
 else return 0;
}
/*-------------------------------------------*/
int f_is_float(int addr)
{
 if((addr >= AddrLowFloat) && (addr <= AddrHighFloat) )
    return 1;
 else return 0;
}
/*-------------------------------------------*/
int  f_int_fnc(int Addr)
{ // return 1 - error, 0 - OK
 int i_ret;
 i_ret=0;
 switch( Addr)
 {
  case Cmd_reg:
       switch(*(int *)list_Slv_int[Addr] )
       {
        case 0:
         break;
//--------------------------------------
        case 1:

         if( (valve_mode > 0) && (valve_modeL > 0 ))
           i_ret = RTU_Val;
         else  if(valve_mode > 0)
            {
              Flag_Low = 0;
              Flag_mass= 0;
//            flag_prok=0;
              i_ret= f_start_dlv();
            }
         else  if(valve_modeL > 0)
            {
              Flag_Low = 1;
              Flag_mass= 0;
//            flag_prok=0;
              i_ret= f_start_dlv();
            }
         else
           i_ret = RTU_Val;
         break;
//--------------------------------------


#if !defined(BIO_1)


        case 101:  // ���� ������� ������ �� ��ꥬ�
            if(valve_modeL > 0)
            {
              Flag_Low = 1;
              Flag_mass= 0;
//            flag_prok=0;
              i_ret= f_start_dlv();
            }
         else
           i_ret = RTU_Val;


         break;
//--------------------------------------
        case 121:  // ���� ������� ������ �� ����
            if(valve_modeL > 0)
            {
              Flag_Low = 1;
              Flag_mass= 1;
//            flag_prok=0;
              i_ret= f_start_dlv();
            }
         else
           i_ret = RTU_Val;
         break;
//--------------------------------------
        case 111:  // �த�������  ������� ������ �� ��ꥬ�
            if( (valve_modeL > 0) && (Flag_Low == 1))
            {
              Flag_mass= 0;
        //    flag_prok=0;
              if(Slv_float[0] > s_MVD[0].VolT )
                i_ret = f_start_dlv11();
            }
         else
           i_ret = RTU_Val;

         break;
//--------------------------------------
        case 131:  // �த�������  ������� ������ �� ����
            if( (valve_modeL > 0) && (Flag_Low == 1))
            {
              Flag_mass= 1;
    //        flag_prok=0;
              if(Slv_float[0] > s_MVD[0].MassT )
                i_ret = f_start_dlv11();
            }
         else
           i_ret = RTU_Val;

         break;
//--------------------------------------

#endif


//--------------------------------------
        case 201:  // ���� ���孥�� ������ �� ��ꥬ�
            if(valve_mode > 0)
            {
              Flag_Low = 0;
              Flag_mass= 0;
    //        flag_prok=0;
              i_ret= f_start_dlv();
            }
         else
           i_ret = RTU_Val;

         break;
//--------------------------------------
        case 221:  // ���� ���孥�� ������ �� ����
            if(valve_mode > 0)
            {
              Flag_Low = 0;
              Flag_mass= 1;
         //   flag_prok=0;
              i_ret= f_start_dlv();
            }
         else
           i_ret = RTU_Val;
         break;
//--------------------------------------
        case 211:  // �த�������  ���孥�� ������ �� ��ꥬ�
            if( (valve_mode > 0) && (Flag_Low == 0))
            {
              Flag_mass= 0;
  //          flag_prok=0;
              if(Slv_float[0] > s_MVD[0].VolT )
                i_ret = f_start_dlv11();
            }
         else
           i_ret = RTU_Val;

         break;
//--------------------------------------
        case 231:  // �த�������  ���孥�� ������ �� ����
            if( (valve_mode > 0) && (Flag_Low == 0))
            {
              Flag_mass= 1;
   //         flag_prok=0;
              if(Slv_float[0] > s_MVD[0].MassT )
                i_ret = f_start_dlv11();
            }
         else
           i_ret = RTU_Val;

         break;
//--------------------------------------
        case 300:  // ���� ���� ����㯠 ��⮬�����
         i_ret= f_acces_code();
         break;
//--------------------------------------
        case 310:  // ���� ⨯� ������
         i_ret= f_acces_page();
         break;
//--------------------------------------
        case 320:  // ���� ⨯� ������
         i_ret= f_dsp_16();
         break;
//--------------------------------------
        case 2:
         i_ret= f_stop_dlv();
         break;
        case 3:
         i_ret= f_alm_stop();
         break;
        case 4:
         i_ret= f_rst_slv();
         break;
        case 5:
         i_ret= f_CE_slv();
         break;
        case 6:
         i_ret= f_WE_slv();
         break;
        case 7:
         i_ret= f_Baud_slv();
         break;
        case 8:
         i_ret=f_Zero_slv();
         break;
        case 9:
  //       i_ret=f_SetOut_slv();
         i_ret=f_flow_mod() ;
        break;
//-------------------------------
        case 11:
         i_ret = RTU_Val;
         if( (valve_mode > 0) && (valve_modeL > 0 ));
         else  if(valve_mode > 0)
            { // �த������ ���孨� �����

//           if( (Flag_Low == 0) && (Flag_mass== 0) && (flag_prok==0 ))
             if(Flag_Low == 0)
               if(Slv_float[0] > s_MVD[0].VolT )
                i_ret = f_start_dlv11();
            }
         else  if(valve_modeL > 0)
            { // �த������ ������ �����

//           if( (Flag_Low == 1) &&(Flag_mass== 0) && (flag_prok==0 ))
             if(Flag_Low == 1)
               if(Slv_float[0] > s_MVD[0].VolT )
                i_ret = f_start_dlv11();
            }
        break;
//-------------------------------
        case 17:  // fls
         i_ret= f_fls();
         break;

        default:
           f_cmd_prn();
           i_ret= RTU_Val;
         break;
       }
   default:
       break;

 }
 return i_ret;
}
/*-------------------------------------------*/
int f_stop_dlv()
{ // return 1 - error, 0 - OK
    if(sw_dlv_liq==3)
    {
       MmiGotoxy(0,0);   MmiPuts(list_avt[30]);  //" ���� ��⠭�����            ",//30
       MmiGotoxy(0,1);   MmiPuts(list_avt[35]);  //"      �� ������� Host   =     ",//35
       State_SLV=Cmd_brk;
       result_dlv=2; //  ������� Host

       f_reg_cmn(11);

       sw_dlv_liq=-1;
    }
    else if(sw_dlv_liq>0)
    {
      //  f_stop_cnt();
      //  fl_GO=0;
      //  fl_EQ=0;
      //  OUT_VAR=0;
          sw_dlv_liq=30;
          key__1 = STOP_H;
          result_dlv=2; //  ������� Host
          f_reg_cmn(15);
    }
//  else return RTU_Val;
    return 0;
}
/*-------------------------------------------*/
int f_alm_stop()
{ // return 1 - error, 0 - OK

   f_icp_errS(Hst_alm);
// f_alarm();
// f_stop_cnt();

 return 0;
}
/*-------------------------------------------*/
int f_rst_slv()
{ // return 1 - error, 0 - OK


  StopUserTimerFun();
  RestoreCom(1);
  RestoreCom(2);
  RestoreCom(3);
  while(!IsCom4OutBufEmpty()) ;  /* Wait all message sent out of COM4 */
  RestoreCom(4);
  f_free_SlvBuf();

    f_wr_evt(evt_res);
    _asm cli
    _asm hlt

 return 0;
}
/*-------------------------------------------*/
int f_fls()
{ // return 1 - error, 0 - OK
 flag_Slv=0;

 RestoreCom(ComPortHost);
 InstallCom(ComPortHost,115200L,8,0,1);

 return 0;
}
/*-------------------------------------------*/
int f_CE_slv()
{ // return 1 - error, 0 - OK

 if(FL_err)
    f_cl_error();
// else
//   f_wr_evt(evt_clr_err);

 sw_fst=0;
 return 0;
}
/*-------------------------------------------*/

long int Tim_set_out=2000;
long int time_set_out=0;
int flag_set_out=0;

int f_SetOut_slv()
{ // return 1 - error, 0 - OK
// time_set_out=TimeStamp;
// flag_set_out=1;
// OUT_VAR=(int)Slv_float[0];
 return 0;
}

//------------------------------------------
int f_Zero_slv()
{ // return 1 - error, 0 - OK


          if(sw_dlv_liq >0)
               return RTU_Val;
          else if(fl_zeroing)
               return RTU_Val;
    //      else if ( (s_MVD[0].reg_err & 0x80 ) != 0)
    //           return RTU_Val;



          f_clr_scr_MMI();
          SetDisplayPage(EmptPage);

          if(f_reset_zer_MVD() == 0)
          {
  //          MoveToXY(0,3);
  //          MmiPrintf("Command Zeroing error ");
  //          f_wr_evt(evt_MVD_CL_BS2);

  //          MmiGotoxy(0,6); MmiPuts("ESC,ENTER  Return");
  //          sw_mmi=-1;
            return RTU_Val;
          }

          f_wr_evt(evt_MVD_CL_strt);

        PassWm=0;

          zero_time=TimeStamp;
          if(ff_serv==NULL)
          {

           sw_fst=0;
           sw_mmi=18;
           fl_zeroing=1;
           sw_mvd_m1=0;
           ff_serv=f_MVD_M3;

           State_SLV = Zer_p;
           f_reg_cmn(Zer_p_cmn);
          }
          else
            return RTU_Val;
          return 0;
}
//------------------------------------------
int f_flow_mod()
// ��⠭����� ०�� ��ࠦ���� ���ᮢ��� ��室�
{ // return 1 - error, 0 - OK

        PassWm=0;

         if(sw_dlv_liq >0)
               return RTU_Val;
         else if(fl_zeroing)
               return RTU_Val;

         f_clr_scr_MMI();
         SetDisplayPage(EmptPage);


         State_SLV = Mod_flow_s;
         f_reg_cmn(Mod_flow_s_cmn);
         ff_serv=f_MVD_MM4;

         sw_mvd_m1=20;

   sw_fst=0;
         sw_mmi=122;
         return 0;
}
//------------------------------------------
int f_WE_slv()
{ // return 1 - error, 0 - OK
 ff_Slv=ff_we_slv;
 return 0;
}
/*-------------------------------------------*/
void ff_we_slv()
{
        if(f_wrt_eee()<0)
        {
          f_wr_evt(evt_we_err);
        }
        else
        {
          f_wr_evt(evt_we);
        }
}
/*-------------------------------------------*/
void ff_wr_strt_evt()
{
          f_wr_evt(evt_start_hst);
}
/*-------------------------------------------*/
int f_start_dlv()
{ // return 1 - error, 0 - OK

int i_ret;


        PassWm=0;

#if defined(BIO_1)
 if( (i7060_out[0] & (OUT5 | OUT6)) == 0)
 {
   i_ret = RTU_Val;
   return i_ret;
 }
#endif
   i_ret=0;
 //  State_SLV = Cmd_err;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(Slv_float[0] <= 0)
    i_ret = RTU_Val;
   else if(flag_set_out)
    i_ret = RTU_Val;
   else if(fl_zeroing)
    i_ret = RTU_Val;
   else if(sw_dlv_liq<=0)
   {
       MassStamp=s_MVD[0].MassI;
       VolStamp=s_MVD[0].VolI;
       flag_dlv_fst=0;
       flag_ZT=1;
       flag_prn_mass=0;

       *(int *)list_Slv_int[i_cfm]=0;
       WD_PMP_flag=1;
       State_SLV= Cmd_rcv;
       dose_dlvr= Slv_float[0];
       volume_f = Slv_float[0];
       f_prn_slv1();
       sw_dlv_liq=1;

       PassWm=0;

   sw_fst=0;
       sw_mmi=193;
       Slv_float[1]=Slv_float[0];
       Slv_float[0]=0;
       ff_Slv=ff_wr_strt_evt;
   }
   else
     i_ret = RTU_Val;
   return i_ret;
}
/*-------------------------------------------*/
int f_start_dlv11()
{ // return 1 - error, 0 - OK
  // ���� ��� ���㫥��� Totals - ��� �த�������
int i_ret;


#if defined(BIO_1)
 if( (i7060_out[0] & (OUT5 | OUT6)) == 0)
 {
   i_ret = RTU_Val;
   return i_ret;
 }
#endif


        PassWm=0;


   i_ret=0;
 //  State_SLV = Cmd_err;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(Slv_float[0] <= 0)
    i_ret = RTU_Val;
   else if(sw_dlv_liq<=0)
   {
     if ( Flag_mass != 0 )
     {
         if(Slv_float[0] <= s_MVD[0].MassT)
            return RTU_Val ;
     }
     else
     {
         if(Slv_float[0] <= s_MVD[0].VolT)
            return RTU_Val ;
     }

     if((MassStamp==-1000.)&& (VolStamp==-1000.))
     {
       MassStamp=s_MVD[0].MassI-s_MVD[0].MassT;
       VolStamp=s_MVD[0].VolI - s_MVD[0].VolT;
     }

//   if(flag_ZT == 0)
         flag_dlv_fst=1;
       flag_prn_mass=1;

       *(int *)list_Slv_int[i_cfm]=0;
       WD_PMP_flag=1;
       State_SLV= Cmd_rcv;
           f_reg_cmn(8);

       dose_dlvr= Slv_float[0];
       volume_f = Slv_float[0];
       f_prn_slv1();
       sw_dlv_liq=1;

        PassWm=0;
   sw_fst=0;
       sw_mmi=193;
       Slv_float[1]=Slv_float[0];
       Slv_float[0]=0;
       ff_Slv=ff_wr_strt_evt;


   }
   else
     i_ret = RTU_Val;
   return i_ret;
}
/*-------------------------------------------*/
/*-------------------------------------------*/
int f_cmd_prn()
{ // return 1 - error, 0 - OK

#if(Slv_deb != 0)
 printf(" \n\r== Command %d ==",*(int *)list_Slv_int[4]);
#endif

 return 0;
}
/*-------------------------------------------*/
int f_Baud_slv()
{
int i_ret;
   if(f_get_nb( (long int)Com_Baud_Slave) < 0  )
   {
 fin_e:
    Com_Baud_Slave=ComBaudSlv;
    i_ret = RTU_Val;
   }
   else
   {
     ComBaudSlv = Com_Baud_Slave;

     RestoreCom(ComPortSlv );
     if( InstallCom(ComPortSlv ,ComBaudSlv,Com_lgthSlv,Com_paritySlv,Com_stopSlv) < 0 ) goto fin_e;
     i_ret = 0;
   }
   return i_ret;
}
//--------------------------------
int f_set_slv( struct eee_dat *LIn_D, int Slv_nmbO )
{
int i,i1,i2;
      for(i1=4,i=0,i2=0;i<Slv_nmbO;i2++ )
      {

             switch( LIn_D[i2].l )
             {
              case T_INT:

                *((int *) LIn_D[i2].ptr)=f_get_int(&intrpr.bfcom[i1]);
                i1+=2;
                i++;
                break;

              case T_INT_L:

                *((long int *) LIn_D[i2].ptr)= f_get_long(&intrpr.bfcom[i1+3]);
                i1+=4;
                i+=2;
                break;

              case T_FLOAT:

                *((float *) LIn_D[i2].ptr)  = f_get_float( &intrpr.bfcom[i1], cod_float);
                i1+=4;
                i+=2;
                break;

              default:
                   return 1;
             }
      }

   return 0;
}
//--------------------------------------
int f_acces_code()
{
int i_ret;
   i_ret=0;

        PassWm=0;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(sw_dlv_liq<=0)
   {
     sw_fst=0;
     sw_mmi=200;
   }
   else
     i_ret = RTU_Val;
   return i_ret;

}
//--------------------------------------
int f_acces_page()
{  // ���� ⨯� ������
int i_ret;
   i_ret=0;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(sw_dlv_liq<=0)
   {
     sw_fst=0;
        PassWm=0;
     sw_mmi=210;
   }
   else
     i_ret = RTU_Val;
   return i_ret;

}
//--------------------------------------
int f_dsp_16()
{  // ��ࠦ���� ��ப 1-6
int i_ret;

   sw_fst=0;
   i_ret=0;

   if(FL_err)
    i_ret=RTU_Slv_err;
   else if(sw_dlv_liq<=0)
   {
     sw_fst=0;
        PassWm=0;
     sw_mmi=220;
   }
   else
     i_ret = RTU_Val;
   return i_ret;

}
//--------------------------------------
void f_reg_cmn_clk( )
{
 dose_dlvr_sl =dose_dlvr;


/*
 if(Reg_err) reg_cmn |= 0x8000;
 else  reg_cmn &= 0x7fff;

 reg_cmn= (reg_cmn & 0x80ff);
 reg_cmn |= (( State_SLV << 8 ) & 0x0f00 )  | (( result_dlv << 12 ) & 0x7000 ) ;
*/

}
//--------------------------------------
void f_reg_cmn( int val)
{

 reg_cmn= (reg_cmn & 0xff00) | ( val & 0xff);

}
//--------------------------------------
void f_reg_cmn_h( int val)
{

 reg_cmn= (reg_cmn & 0xff0f) | (( val << 4 ) & 0x0f0 );

}

float ds_1=0.;

void f_mirr()
{
State_SLVm=State_SLV;
reg_cmnm  =reg_cmn;
Reg_errm  =Reg_err;
I11m      =ICP_error[icp_lst_max] ;
I12m      =ICP_error[icp_lst_max+1];

  if(ds_1 != Slv_float[0])
  {
   ds_1 = Slv_float[0];
   if(ds_1 != 0)
     dose_dlvr=Slv_float[0];
  }
}
