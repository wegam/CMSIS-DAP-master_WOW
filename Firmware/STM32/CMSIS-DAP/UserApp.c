#ifndef __DAP_CODE_C__
#define __DAP_CODE_C__

#include "CMSIS_Conf.H"
#include "DAP.h"				

#include "SW_DP.h"			//20170328
#include "JTAG_DP.h"		//20170328

//#include "DAP.c"
//#include "SW_DP.c"
//#include "JTAG_DP.c"		

void UserAppInit(CoreDescriptor_t *core);
void UserAppAbort(void);

__attribute__((section("USERINIT")))
const UserAppDescriptor_t UserAppDescriptor = 
{
	&UserAppInit,
	&DAP_ProcessCommand,
	&UserAppAbort
};

CoreDescriptor_t * pCoreDescriptor;

void UserAppInit(CoreDescriptor_t *core)
{
	pCoreDescriptor = core;
	DAP_Setup();
}

void UserAppAbort(void)
{
	DAP_TransferAbort = 1;		//将传输中止标志置1，中止传输
}



#endif
