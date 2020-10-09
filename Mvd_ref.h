//14.04.2020 YN -----\\//-----
float relative_error (float A, float X);

extern struct s_icp_dev MVDref[];
extern struct COM_rqst MVDref_Rqst[];

extern struct s_MVD_dev s_MVDref[];

extern int MVDref_fn[];     // регистр функций драйвера
extern int MVDref_fl[];

extern int MVDref_t_rslt[];

void f_MVDref(int ii);
void f_MVDref_rd(int ii);
int f_MVDref_WR(int ii,int fn,int addr,int i_val,long int l_val,float f_val);
void f_MVDref_rd_t(int ii);
void f_init_MVDref(int ii);

extern int flag_mvdref_ton;

extern long int tm_mvdref;
//14.04.2020 YN -----//\\-----