
#define Test 0  // 1 - тестовый режим без MVD

#define AIR_SW  0  // 1 - OUT4 открывет клапан доступа воздуха в сливной ркв вернеоналива

///ccc///// was: #define CUT_SW  1
//now:
#define CUT_SW  0  // 1 - OUT 4 открывет отсечной клапан при отпуске
////////////////////////////////////

///ccc/////////////
#define CLP_SW 1 // 1 - OUT9 и OUT10 дополнительные клапана верхнего и нижнего налива 
/////////////////////

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <time.h>
#include <sys\types.h>
#include <sys\timeb.h>

#include "device.h"

#include "PROC.h"

#if defined(MMI_ICP)
#include "MMI.h"
#endif

#if defined(MMI_NEW)
#include "MMI_NEW.h"
#endif

//#include "ekd.h"

#include "queue.h"
#include "icp.h"
#include "host.h"
#include "7017c.h"
#include "i7060.h"
#include "i7041.h"
#include "ofp.h"
#include "eee.h"
#include "rtu.h"
#include "sk.h"

#if defined(RTU_Delta)
#include "delta.h"
#endif

#if defined(RTU_Delta_C)
#include "deltaC.h"
#endif

#include "MVD.h"
#include "tsd.h"
#include "arch.h"
#include "avt_ctrl.h"
#include "reg.h"
#include "cor_adc.h"
#include "slave.h"
#include "valve.h"
#include "ref_t.h"
#include "md5.h"

//14.04.2020 YN -----\\//-----
#if defined(ELITE_MVD)
#include "MVD_ref.h"
#endif
//14.04.2020 YN -----//\\-----