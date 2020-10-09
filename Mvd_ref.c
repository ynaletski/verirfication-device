//14.04.2020 YN -----\\//-----
#define ELITE_MVD


float relative_error (float A, float X)
{
  float Dlt=0;
  if(X == 0) Dlt = 0;
  else
  {
    Dlt = (A-X)/X;
  }
  return Dlt;
}

long int tm_mvdref;

struct s_icp_dev MVDref[max_MVD]=
{
// device 1
0,                // status
2,                // port
11,                // addr
"MVD/R1",          // name[8]
06,               // baudrate_cod
0x00,             // type
0x00,             // format
0x00,             // channels
"B1.7",           // firmware
1,                // protocol
1,                // CRC_flag
400,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&MVDref_Rqst[0],   // *request
//--------------------------------
// device 2
//--------------------------------
0,                // status
1,                // port
3,                // addr
"MVD/R2",        // name[8]
06,               // baudrate_cod
0x00,             // type
0x00,             // format
0x00,             // channels
"B1.7",           // firmware
1,                // protocol
1,                // CRC_flag
200,              // pool_time
0,                // time_stamp_pool;
0,                // time_stamp_snd
0,                // time_stamp_rcv
0,                // n_transaction
0,                // n_success
0,                // n_timeout_error
0,                // n_CRC_error
&MVDref_Rqst[1],   // *request
};
/*----------------------------*/
struct COM_rqst MVDref_Rqst[max_MVD]={
//----------------------
// device 1
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVDref_rd,            //  answ_com
f_MVDref_rd,            //  answ_flt
"MVD/R1",              //  name
0,                     //  n_dev номер устройства в группе однотипных устройств
&MVDref[0],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
//--------------------------
// device 2
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVDref_rd,            //  answ_com
f_MVDref_rd,            //  answ_flt
"MVD/R2",              //  name
1,                     //  n_dev номер устройства в группе однотипных устройств
&MVDref[1],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
};
/*----------------------------*/
struct COM_rqst MVDref_Rqst_T[max_MVD]={
//----------------------
// device 1
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVDref_rd_t,            //  answ_com
f_MVDref_rd_t,            //  answ_flt
"MVD/R1",               //  name
0,                     //  n_dev номер устройства в группе однотипных устройств
&MVDref[0],               //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,        //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
//--------------------------
// device 2
//--------------------------
0,                     //  состояние запроса
ffgets_com_rtu,        //  gets_com
f_MVDref_rd_t,            //  answ_com
f_MVDref_rd_t,            //  answ_flt
"MVD/R2",               //  name
1,                     //  n_dev номер устройства в группе однотипных устройств
&MVDref[1],             //  *ICP_dd
0,                     //  текущая функция
ToutAnsMVD_rtu,         //  timeout
0,                     //  time_stamp
0,                     //  com_lgth
1,                     //  CRC_flag
"",                    //  com[]
};
/*----------------------------*/
struct s_MVD_dev s_MVDref[max_MVD]=
{
0 , //int r_addr;       // address of MODBUS register
0,  //int n;            // number of data - for read coils and ascii
0,  //int type;         // data type
0,  //int i;            // int,coil value for write
0,  //int exc;          // exception
0,  //long int  l;      // long
0,    //float f;          // float

-1.0, //float FlowM;         // float
-1.0, //float FlowV;         // float
-1.0, //float MassI;        // float
-1.0, //float MassT;         // float
-1.0,  //float VolI;          // float
-1.0, //float VolT;          // float
-1.0, //float VolTd;         // float
-1.0, //float Temp;          // float
-1.0, //float TempR;         // float
-1.0, //float Dens;          // float
-1.0, //float Press;         // float
-1.0, //float Compos;        // float
 0.0, //float PressG;        // float
-1.0, //float PressB;        // float
-1.0, //float PressD;        // float
-1.0, //float PressGN;       // float
-1.0, //float Volt_A         // float
-1.0, //float Volt_DC        // float

"",   //char c[n_coil_b]; // coil(s) value(s) read from MVD
"",   //char a[n_char_b]; // ascii
0,    //int reg_err;
};

int MVDref_fn[max_MVD]={0,0};    // регистр функций драйвера

//  Если записать значение функции в регистр функции , например:
//  ComSK_fn[0]= RES_SK_ERR;  драйвер выполнит заданную функцию - в данном случае
// пошлет в устройство ComSK команду сброса привода.
//  После постановки запроса с установленной функцией в очередь на вывод в COM,
// регистр функции очищается драйвером.

int MVDref_sw[max_MVD]={0,0};

unsigned int MVDref_inp_err[max_MVD]={0,0};  // счетчик ошибок ввода

int MVDref_seq[16]={
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
mSlot, mSlot,mSlot, mSlot,
};

int MVDref_fl[max_MVD]={0,0};

unsigned char MVDref_Rd_Slot[]={1,3,0x02,0xae,0x00,0x10};  // R687-1  - Slot data , 16 registers 16 bit

void f_MVDref(int ii)
{
 // ii - номер устройства
 //  Функция циклически шлет запрос на получение данных  из
 // устройства MVD  '01 03 01A2 0001' - R419 - регистр ошибки,
 //
 //   Период посылки MVDref[ii].pool_time мс.
 //
 //    Если  регистр функции != 0 - заданная функция выполняется
 //  в первую очередь ( приоритет выше, чем приоритет циклического опроса).
 //   После постановки запроса с указанной функцией в очередь COM порта
 //  в регистр функции записывается F_PROGRESS
 //  После приема ответа от устройства в регистр функции запишется либо 0 - OK,
 // либо F_FAULT

int i,fn,sw,i2,itmp;
long int i1,l_tmp;
//union  { float f; unsigned long l; } o;
unsigned char buf_tmp[20];

 if(MVDref[ii].status == 0) return;

 if( MVDref_fl[ii] >= 0 )
            f_init_MVDref(ii);

  if((MVDref_Rqst[ii].status == Req_Flt) ||
     (MVDref_Rqst[ii].status == Req_OK));
  else return;

 if(f_queue_chk(MVDref[ii].port)== 0) return;// очередь переполнена

 if((MVDref_fn[ii] != 0) && (MVDref_fn[ii] < F_PROGRESS))
      fn=MVDref_fn[ii];
 else if( f_timer(MVDref[ii].time_stamp_pool,MVDref[ii].pool_time ))
      fn=MVD_RD_P;
 else return;

      switch(fn)
      {
        case MVD_RD_I :
           // чтение данных Integer
            buf_tmp[5]=1;
 m_rdi:
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=3;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
            buf_tmp[4]=0;
            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case  MVD_RD_L :
          case  MVD_RD_F:


           // чтение данных Long, Float

           buf_tmp[5]=2;
          goto m_rdi;

        case MVD_RD_NI :


           SLT3_N=s_MVDref[ii].n;
           SLT3_A=s_MVDref[0].r_addr;
           buf_tmp[5]=s_MVDref[ii].n;

          goto m_rdi;

          case MVD_RD_C:
           // чтение данных Coil
            buf_tmp[1]=1;
     m_rdc:
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
            buf_tmp[4]=(s_MVDref[ii].n>> 8) & 0xff;
            buf_tmp[5]= s_MVDref[ii].n & 0xff;
            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case MVD_RD_S:
           // чтение данных String
            buf_tmp[1]=3;
            goto m_rdc;

          case MVD_WR_I :
           // запись данных Integer
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=6;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
            buf_tmp[4]=(s_MVDref[ii].i>> 8) & 0xff;
            buf_tmp[5]= s_MVDref[ii].i & 0xff;
            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case MVD_WR_L :
           // запись данных Long
            i1=11;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
             l_tmp=s_MVDref[ii].l;
            buf_tmp[7]=(l_tmp >> 24) & 0xff;         // количество регистров
            buf_tmp[8]=(l_tmp >> 16) & 0xff;         // количество регистров
            buf_tmp[9]=(l_tmp >> 8)  & 0xff;         // количество регистров
            buf_tmp[10]=l_tmp & 0xff;    // количество регистров

            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case MVD_WR_F :
           // запись данных Float
            i1=11;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
/*
            o.f=s_MVDref[ii].f;
            buf_tmp[7] =(o.l >> 8 ) & 0xff;
            buf_tmp[8] =(o.l >> 0 ) & 0xff;
            buf_tmp[9] =(o.l >> 24)  & 0xff;
            buf_tmp[10]=(o.l >> 16) & 0xff;
*/

   f_set_float( &buf_tmp[7],s_MVDref[ii].f,MVD_fl_ord[0]);

            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case MVD_WR_C :
           // запись данных Coil
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=5;
            buf_tmp[2]=((s_MVDref[ii].r_addr-1)>> 8) & 0xff;
            buf_tmp[3]= (s_MVDref[ii].r_addr-1) & 0xff;
//          if(s_MVDref[ii].w_coil != 0)
            if(s_MVDref[ii].i != 0)
               buf_tmp[4]= 0xff;
            else
               buf_tmp[4]= 0;
            buf_tmp[5]= 0;
            MVDref_fn[ii]=F_PROGRESS;
            s_MVDref[ii].type=fn;
            s_MVDref[ii].exc=-1;
            break;

          case MVD_RD_P:  // циклическое  чтение состояния
          // формирует команды чтения
             MVDref_sw[ii]=(MVDref_sw[ii]+1) & 0xf;
             sw=MVDref_seq[MVDref_sw[ii]];
             i1=6;
             MVDref_fn[ii]=0;
             switch (sw)
             {
              case mSlot:
             _fmemcpy(buf_tmp,MVDref_Rd_Slot,(long int)i1);
                break;

              default:
                return;
             }
             buf_tmp[0]=MVDref[ii].addr;
             fn+=sw;
             break;

          default:
          MVDref_fn[ii]=0;
          return;
      }
           MVDref_Rqst[ii].function = fn;
           i2=i1;
           f_prepareRTU(buf_tmp,&i2);
           _fmemcpy(MVDref_Rqst[ii].Cmd,buf_tmp,(long)i2);
           MVDref_Rqst[ii].cmd_lgth=i2;
           MVDref_Rqst[ii].time_stamp=TimeStamp;
           MVDref[ii].time_stamp_pool=TimeStamp;
           MVDref[ii].n_transaction++;
           f_queue_put(MVDref[ii].port, &MVDref_Rqst[ii]) ;
}
/*----------------------------*/
int f_MVDref_WR(int ii,int fn,int addr,int i_val,long int l_val,float f_val)
{
 // записывает значение в регистр MVDref
 // ii - номер устройства
int i,sw,i2,itmp;
long int i1;
//union  { float f; unsigned long l; } o;
unsigned char buf_tmp[20];

 if(MVDref[ii].status == 0)
#if(SIM0 != 0)
 {
   MVDref_t_rslt[0]=1;
   return 1;
 }
#else
   return 0;
#endif

  if((MVDref_Rqst_T[ii].status == Req_Flt) ||
     (MVDref_Rqst_T[ii].status == Req_OK));
  else return 0;

 if(f_queue_chk(MVDref[ii].port)== 0) return 0;// очередь переполнена
     switch(fn)
      {
          case MVD_WR_I :
           // запись данных Integer
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=6;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]=(i_val>> 8) & 0xff;
            buf_tmp[5]= i_val & 0xff;
            break;

          case MVD_WR_L :
           // запись данных Long
            i1=11;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт
            buf_tmp[7]=(l_val >> 24) & 0xff;         // количество регистров
            buf_tmp[8]=(l_val >> 16) & 0xff;         // количество регистров
            buf_tmp[9]=(l_val >> 8)  & 0xff;         // количество регистров
            buf_tmp[10]=l_val & 0xff;    // количество регистров

            break;

          case MVD_WR_F :
           // запись данных Float
            i1=11;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=16;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            buf_tmp[4]= 0;  // количество регистров
            buf_tmp[5]= 2;  // --|
            buf_tmp[6]= 4;  // количество байт

/*
            o.f=f_val;
            buf_tmp[7] =(o.l >> 8 ) & 0xff;
            buf_tmp[8] =(o.l >> 0 ) & 0xff;
            buf_tmp[9] =(o.l >> 24)  & 0xff;
            buf_tmp[10]=(o.l >> 16) & 0xff;
*/
            f_set_float( &buf_tmp[7],f_val,MVD_fl_ord[0]);
            break;

          case MVD_WR_C :
           // запись данных Coil
            i1=6;
            buf_tmp[0]=MVDref[ii].addr;
            buf_tmp[1]=5;
            buf_tmp[2]=((addr-1)>> 8) & 0xff;
            buf_tmp[3]= (addr-1) & 0xff;
            if(i_val != 0)
               buf_tmp[4]= 0xff;
            else
               buf_tmp[4]= 0;
            buf_tmp[5]= 0;
            break;

          default:
          return 0;
      }

           MVDref_Rqst_T[ii].function = fn;
           i2=i1;
           f_prepareRTU(buf_tmp,&i2);
           _fmemcpy(MVDref_Rqst_T[ii].Cmd,buf_tmp,(long)i2);
           MVDref_Rqst_T[ii].cmd_lgth=i2;
           MVDref_Rqst_T[ii].time_stamp=TimeStamp;
           MVDref[ii].n_transaction++;
           f_queue_put(MVDref[ii].port, &MVDref_Rqst_T[ii]) ;
           return 1;
}
/*----------------------------*/

int  MVDref_t_err[max_MVD]={0,0};
int  MVDref_t_rslt[max_MVD]={0,0};

void f_MVDref_rd_t(int ii)
{   // принят ответ на команду записи в MVDref
// ii - номер порта
// заносит принятые данные в переменные
//
 struct COM_rqst *request;
 int i,nn,i1,im;
 int count,tmp;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // номер устройства MVDref (0,1..)

 count=n_bcom[ii];  // длина команды
 if(count < 3)
   {
      goto m_tout_err;
   }
 if(f_check_crc_RTU(cb_COM[ii],count)==0)
   {
      goto m_crc_err;
   }
 if(cb_COM[ii][1] & 0x80)
   {
     s_MVDref[nn].exc=cb_COM[ii][2];
     goto m_crc_err;
//   goto m_end;
   }
    // ответ на команду записи
  if ((cb_COM[ii][1] == 6)  || (cb_COM[ii][1] == 16) ||(cb_COM[ii][1] == 5));
  else  goto m_crc_err;
  MVDref_t_rslt[nn]+=1;
 m_end:
  MVDref[nn].n_success++;
  MVDref_inp_err[nn]=0;
  f_queue_free(ii,&MVDref_Rqst_T[nn]);
  MVDref_t_err[nn]=0;
  return;

m_crc_err:
 MVDref[nn].time_stamp_rcv=0;
 MVDref[nn].n_CRC_error++;
 goto m_err;

m_tout_err:
 MVDref[nn].time_stamp_rcv=0;
 MVDref[nn].n_timeout_error++;

m_err:
 MVDref_t_err[nn]++;

 f_queue_free(ii,&MVDref_Rqst_T[nn]);
 if(MVDref_t_err[nn]>=MVD_max_t_err)
 {
   MVDref_t_err[nn]=MVD_max_t_err;
   f_icp_error(&MVDref[nn],WR_ERR );
 }
 else
 {
  MVDref_Rqst_T[nn].time_stamp=TimeStamp;
  f_queue_put(ii, &MVDref_Rqst_T[nn]) ;
 }
  MVDref[nn].n_transaction++;
}
//-----------------------------------------
unsigned long int MVDrefit[max_MVD];
int n_send_ref[max_MVD];
int flag_mvdref_fst=0;
int flag_mvdref_ton=0;
int ii_MVDref_i=0;
int ii_MVDref_fl=0;

struct mvd_init MVDref_i[]=
{
 655,258, // Mass total     687 --
 656,248, // Density        689 --
 657,250, // Temperature    691 --
 658,262, // Mass inventory 693 --
 659,264, // Volume invntry 695 --
 660,246, // Mass flow      697 --
 661,260, // Volume total   699 --
// 662,418, // Error          701 --
 662,244, // Error          701 --
//39,73,  // unit for mass flow,kg/s
  39,75,  // unit for mass flow,kg/hour
  40,92,  // Density unit kg/m3 --
  45,61,  // unit for mass total,61- kg, 60-g
  46,41,  // unit for volume total, l
  41,32,  // unit for temperature, C
  42,24,  // Volume flow  l/sec
  17,0 ,  // Flow direction code: 0 - Forward flow  only
// 662,252, // Volume flow    701 --
// 663,246, // Mass flow      703 --
// 665,256, // Pressure       705 --
};

int ii_MVDref_max=sizeof(MVDref_i) / sizeof(MVDref_i[0]);

//----------------------------------------------
void f_init_MVDref(int ii)
 {
  if((MVDref_fn[0] != 0) && (MVDref_fn[0] != F_FAULT))
  {
    return;
  }
  switch (MVDref_fl[ii])
   {
    case 0:

//     MVDref_fl[ii]=-1; // qqqqqq

      n_send_ref[ii]=0;
       MVDref_fl[ii]++;
       break;

    case 1:  // проверяет текущее значение порядка
             // следования байт в регистрах float
             // если не 1 , то устанавливает =1.

      if(MVDref_fn[ii] != 0) break;
      MVDref_fn[ii]=MVD_RD_I;;
      s_MVDref[0].r_addr=521; // I521  Byte order code for float registers
      MVDref_fl[ii]++;
      break;

    case 2:

      flag_mvdref_ton=1;
      if(sw_mmi==0) f_prn_begin();

      if((MVDref_fn[0] == F_FAULT) || (s_MVDref[ii].i == 1) )
       { // byte order is correct or RFT9739 device connected
         MVDref_fl[ii]=3;
         ii_MVDref_i=0;
         ii_MVDref_fl=0;
         n_send_ref[ii]=0;
         break;
       }
       MVDref_fn[ii]=MVD_WR_I;
       s_MVDref[ii].r_addr=521; // I521  Byte order code  for float registers
       s_MVDref[ii].i = 1;
       if((n_send_ref[ii]++) > 3)
       {
         flag_mvdref_ton=0;
         f_icp_error(&MVDref[ii],WR_ERR );
         MVDref_fl[ii]=-1;
       }
       MVDref_fl[ii]=1;
       break;

    case 3:
      MVDref_fn[ii]=MVD_RD_I;
      s_MVDref[0].r_addr=MVDref_i[ii_MVDref_i].addr;
      MVDref_fl[ii]=4;
      break;

    case 4:
      if(s_MVDref[ii].i == MVDref_i[ii_MVDref_i].val);
      else ii_MVDref_fl=1;
      ii_MVDref_i++;
      if(ii_MVDref_i >= ii_MVD_max)
      {
        if( ii_MVDref_fl == 0 )
        { // значения записаны корректно
//   printf("\r\n Slot OK,%d values",ii_MVDref_i);
         MVDref_fl[ii]=53;
         break;
        }
        else
        { // значения нужно записать

         if((n_send_ref[ii]++) > 3)
         { // за 3 попытки записать не удалось
           flag_mvdref_ton=0;
      //     f_icp_error(&MVDref[ii],WR_ERR );
           f_icp_errS(MVD_cfg);

           MVDref_fl[ii]=-1;
           break;
         }

//   printf("\r\n Slot need to write");
         f_wr_evt(evt_Slot);
         MVDref_fl[ii]=5;
         ii_MVDref_i=0;
         ii_MVDref_fl=0;
         break;
        }
      }
      else
      {
        MVDref_fl[ii]=3;
        break;
      }

 //--------------------------
    case 5: // запись значений Slot
      MVDref_fn[ii]=MVD_WR_I;;
      s_MVDref[ii].r_addr=MVDref_i[ii_MVDref_i].addr;
      s_MVDref[ii].i = MVDref_i[ii_MVDref_i].val;

      ii_MVDref_i++;
      if(ii_MVDref_i >= ii_MVD_max)
      {  // все значения записаны , проверить запись

//   printf("\r\n Slot is wrote,%d values",ii_MVDref_i);
         ii_MVDref_i=0;
         ii_MVDref_fl=0;
         MVDref_fl[ii]=3;
         break;
      }
      break;
//------------------------------------

    case 53:
    if( f_timer(0L,TimeMVD_Init ) )
       flag_mvdref_fst = 0;
    else
      if(f_get_icp_error(&MVDref[ii]))
        flag_mvdref_fst = 1;

     MVDref_fl[ii]++;
     case 54:
     if(flag_mvdref_fst)
       if( f_timer(0L,TimeMVD_Init ) == 0 ) break;
      flag_mvdref_ton=0;
      f_icp_error(&MVDref[ii],0 );
    if(sw_mmi==0) f_prn_begin();

// printf("\n\r MVD init finished");// qqq

       MVDref[ii].n_transaction    = 0;
       MVDref[ii].n_success        = 0;
       MVDref[ii].n_timeout_error  = 0;
       MVDref[ii].n_CRC_error      = 0;

       MVDrefit[ii]=TimeStamp;
       MVDref_fl[ii]++;
       break;

     case 55:

       if((fl_VI==0) || (fl_MI==0)) return;
       if( f_timer(MVDrefit[ii],TimeMVD_evt ) == 0 ) break;
// printf("\n\r evt_none");// qqq
       f_wr_evt(evt_none);
       MVDref_fl[ii]=-1;
       break;
    case -1:
       break;
    default:break;
   }
 }
//-----------------------------------------
long int tim_snd_MVDref;
long int lerr_MVDref=0;
//float VolI_beg=0;

void f_MVDref_rd(int ii)
{
// ii - номер порта
// заносит принятые данные в переменные
//
 struct COM_rqst *request;
 int i,nn,fn,i1,im;
 int count,tmp;
 float ftmp;

 union  { int i; char ch[2]; } o;

 request=COM_que[ii].request[COM_que[ii].empt_ptr];
 nn=request->n_dev; // номер устройства MVD (0,1..)
 fn=request->function;

 count=n_bcom[ii];  // длина команды
 if(count < 3)
   {
      goto m_tout_err;
   }
 if(f_check_crc_RTU(cb_COM[ii],count)==0)
   {
      goto m_crc_err;
   }
 if(cb_COM[ii][1] & 0x80)
   {
     s_MVDref[nn].exc=cb_COM[ii][2];
     MVDref_fn[nn]=F_FAULT ;
     if(fn==MVD_RD_NI)
     {
       Flag_sl3=-1;
       Sl3_nn= 0;
     }
     goto m_end;
   }
 if(( fn & 0xf8)==MVD_RD_P) // ответ на команду циклического опроса
  {
      fn &= 0x7;
      switch(  fn )
      {
      case mErr:  // чтение регистра ошибки , int
    //в ответ на 01 03 01 a2 00 01 приходит:
    //  01 03 02 00 05 78 47
        fl_rd_err=1;
        s_MVDref[nn].reg_err=(cb_COM[ii][4] & 0xff) | ( ((unsigned int)cb_COM[ii][3] << 8) &0xff00)  ;
        if(s_MVDref[nn].reg_err & 0x8000)
        {
          if( f_get_icp_error(&MVDref[nn]) != 0 ) break;
          f_icp_error(&MVDref[nn],Drive_ERR | ( s_MVDref[nn].reg_err & 0xffff) );
        }
        else flag_mvdref_fst=0;

        break;
      case mVolT:     // чтение Vol total
        s_MVDref[nn].VolT= f_get_float( cb_COM[ii], 1);

//      summ_v=s_MVDref[nn].VolT*cost_v;
        {
         tim_snd_MVDref=Tm_snd[ii];
         f_prep_int_v2();
        }
        break;

      case mDens:    // чтение Density
         s_MVDref[nn].Dens = f_get_float( cb_COM[ii], 1);
         tim_snd_MVDref=Tm_snd[ii];
//         f_prep_int_dens();
         break;
/*
      case mFlowM:    // чтение mass Flow
        s_MVDref[nn].FlowM=  f_get_float( cb_COM[ii], 1);
         break;
*/

      case mSlot:    // чтение Slot data

       if(count < 33)
       {
         goto m_tout_err;
       }
        s_MVDref[nn].MassT= f_get_float( &cb_COM[ii][0], 1);
//      s_MVDref[nn].Dens=  f_get_float( &cb_COM[ii][4], 1);
        ftmp = f_get_float( &cb_COM[ii][4], 1);
        if(ftmp <=0) ftmp=0.00000001;
        s_MVDref[nn].Dens = ftmp;

        s_MVDref[nn].Temp=  f_get_float( &cb_COM[ii][8], 1);
        s_MVDref[nn].MassI=  f_get_float( &cb_COM[ii][12], 1);
        s_MVDref[nn].VolI =  f_get_float( &cb_COM[ii][16], 1);
//      s_MVDref[nn].FlowV =  f_get_float( &cb_COM[ii][16], 1); // 9,10
        s_MVDref[nn].FlowM=  f_get_float( &cb_COM[ii][20], 1);
//      if(s_MVDref[nn].Dens > 0.00000002) s_MVDref[nn].FlowV=s_MVDref[nn].FlowM/(s_MVDref[nn].Dens/1000.);
        if(s_MVDref[nn].Dens > 0.00000002) s_MVDref[nn].FlowV=s_MVDref[nn].FlowM/(s_MVDref[nn].Dens/K_mul_F);
        s_MVDref[nn].VolT =  f_get_float( &cb_COM[ii][24], 1);
//        s_MVDref[nn].reg_err=  f_get_int( &cb_COM[ii][28]);
        lerr_MVDref= (long int)f_get_float( &cb_COM[ii][28],1);

        tmp=0x03 & lerr_MVDref;
        if(lerr_MVDref)
        {
         if(lerr_MVDref & 0x000007) tmp |=0x8000;
         if(lerr_MVDref & 0x000004) tmp |=0x0008;
         if(lerr_MVDref & 0x000008) tmp |=0x0010;
         if(lerr_MVDref & 0x200000) tmp |=0x8080;
        }
        s_MVDref[nn].reg_err=tmp;
//----------------------------------------------
    //    s_MVDref[nn].reg_err= 0xffff & (long int)f_get_float( &cb_COM[ii][28],1);

//      s_MVDref[nn].VolT =  s_MVDref[nn].VolI - VolI_beg;

        tim_snd_MVDref=Tm_snd[ii];
     /*
        if(flag_prok != 0)
        {
          s_MVDref[nn].VolT  = 0;
          s_MVDref[nn].MassT = 0;
        }
     */
        //рассчитывает падение давления вследствие скорости
        s_MVDref[0].PressB= FctBern*s_MVDref[0].FlowM*s_MVDref[0].FlowM/s_MVDref[0].Dens;

        //рассчитывает s_MVDref[0].Compos и s_MVDref[0].PressG
//      f_get_pressDT(s_MVDref[0].Dens,s_MVDref[0].Temp);
//      s_MVDref[0].PressG=0;

        f_prep_int_MassF();


 //     if( mode_refD == 1 )
        {
          f_cnt_DnsA();
        }

//        f_prep_int_dens();
        if(s_MVDref[nn].reg_err & 0x8000)
        {
          if( f_get_icp_error(&MVDref[nn]) != 0 ) break;
          f_icp_error(&MVDref[nn],Drive_ERR | ( s_MVDref[nn].reg_err & 0xffff) );
        }
        else flag_mvdref_fst=0;

//      if((Delta[0].status !=0) ||  (ComSK[0].status !=0) )


        f_reg_D(); // регулятор запаса по кавитации

        f_reg_F(); // регулятор расхода

        f_flow_chk();

        fl_rd_err=1;
        fl_MI=1;
        fl_VI=1;
        break;

      case mMassT:    // чтение mass total
        s_MVDref[nn].MassT=  f_get_float( cb_COM[ii], 1);
        tim_snd_MVDref=Tm_snd[ii];
        f_prep_int_Mass();
         break;
//    case mFlowV:    // чтение volume Flow
//      s_MVDref[nn].FlowV=  f_get_float( cb_COM[ii], 1);
//       break;
      case mTemp:    // чтение volume Flow
        s_MVDref[nn].Temp=  f_get_float( cb_COM[ii], 1);
         break;
      case mVolI:    // чтение Vol inv-ry
        s_MVDref[nn].VolI=  f_get_float( cb_COM[ii], 1);
        fl_VI=1;
         break;
      case mMassI:    // чтение Mass inv-ry
        s_MVDref[nn].MassI=  f_get_float( cb_COM[ii], 1);
        fl_MI=1;
     // fl_VI=1;
         break;
      default:
           //      goto m_tout_err;
               goto m_crc_err;
      }
  }
 else
  switch(fn)
 {
   case MVD_RD_I: // чтение Int
     s_MVDref[nn].i=(cb_COM[ii][4] & 0xff) | ( ((unsigned int)cb_COM[ii][3] << 8) &0xff00)  ;
     MVDref_fn[nn]=0;
     break;

  case MVD_RD_F: // чтение Float

    if(cb_COM[ii][1] != 3)
    {
     goto m_crc_err;
    }
    if(cb_COM[ii][2] != 4)
    {
       goto m_crc_err;
    }
    s_MVDref[nn].f = f_get_float( cb_COM[ii], 1);
    MVDref_fn[nn]=0;
    break;

  case MVD_RD_L: // чтение Long
    if(cb_COM[ii][1] != 3)
    {
     goto m_crc_err;
    }
    if(cb_COM[ii][2] != 4)
    {
       goto m_crc_err;
    }
    s_MVDref[nn].l =
          ( (unsigned long)(cb_COM[ii][6]) & 0x000000ff) |
          ( ((unsigned long)cb_COM[ii][5] << 8) &0xff00) |
          ( ((unsigned long)cb_COM[ii][4] << 16) &0xff0000)  |
          ( ((unsigned long)cb_COM[ii][3] << 24) &0xff000000);
    MVDref_fn[nn]=0;
    break;
  case  MVD_RD_C: // чтение Coil

     if(cb_COM[ii][1] != 1) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;(i<im)&(i<n_coil_b) ;i++,i1++)
     {
       s_MVDref[nn].c[i]=cb_COM[ii][i1]&0xff;
     }
     MVDref_fn[nn]=0;
     break;

  case  MVD_RD_S: // чтение String

     if(cb_COM[ii][1] != 3) goto m_err;
     im=cb_COM[ii][2];
     i1=3;
     for(i=0;(i<im)&&(i< (n_char_b-1)) ;i++,i1++)
     {
      s_MVDref[nn].a[i]=cb_COM[ii][i1];
     }
     s_MVDref[nn].a[i]=0;
     MVDref_fn[nn]=0;
     break;
  case  MVD_RD_NI: // чтение n Int reg в Slot3_dat[]


     if(cb_COM[ii][1] != 3) goto m_err;
     im=cb_COM[ii][2] >> 1;
     i1=3;

     for(i=0;(i<im) && (i <= max_lgth_sl3) ;i++,i1+=2)
     {
      o.ch[0]=cb_COM[ii][i1+1];
      o.ch[1]=cb_COM[ii][i1];
      Slot3_dat[i] = o.i;
     }

     Flag_sl3++;
     if(Flag_sl3 < 0) Flag_sl3=32767;

     if(Sl3_fl_jrn==1)
           f_wr_evt(slt_wr_jrnI);
     else if(Sl3_fl_jrn==2)
           f_wr_evt(slt_wr_jrnF);

     MVDref_fn[nn]=0;
     break;
  default:
    // ответ на команду записи
    if ((cb_COM[ii][1] == 6)  || (cb_COM[ii][1] == 16) ||(cb_COM[ii][1] == 5));
    else
    {
      goto m_crc_err;
    }
    MVDref_fn[nn]=0;
    break;
 }

 m_end:
  MVDref[nn].n_success++;
  MVDref_inp_err[nn]=0;
  f_queue_free(ii,&MVDref_Rqst[nn]);
  return;

m_crc_err:
 MVDref[nn].time_stamp_rcv=0;
 MVDref[nn].n_CRC_error++;
 goto m_err;

m_tout_err:
 MVDref[nn].time_stamp_rcv=0;
 MVDref[nn].n_timeout_error++;

m_err:
 MVDref_inp_err[nn]++;

 if (fn>0)
  if(( fn & 0xf8) != MVD_RD_P)
 {
// printf("\r\n if(( fn & ~0x7) != MVD_RD_P)  %d , %d",( fn & ~0x7),MVD_RD_P);
   if(fn==MVD_RD_NI)
   {
    Flag_sl3=-1;
    MVDref_fn[nn]=0;
    Sl3_nn= 0;
    MVDref_inp_err[nn]--;
   }
   else
     MVDref_fn[nn]=fn;
 }
 if(MVDref_inp_err[nn]>=MVD_max_inp_err)
 {
   MVDref_inp_err[nn]=MVD_max_inp_err;
   f_icp_error(&MVDref[nn],RD_ERR );

 }
 f_queue_free(ii,&MVDref_Rqst[nn]);
}
/* ---------------------------------------- */

//14.04.2020 YN -----//\\-----