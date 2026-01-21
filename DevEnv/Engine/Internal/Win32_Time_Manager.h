#ifndef WIN32_TIMER_MANAGER_H
#define WIN32_TIMER_MANAGER_H

#include<Runtime_variables.h>

VOID CALLBACK Main_Timer_Proc(HWND Window_handle, UINT Timer_Message, UINT_PTR Timer_Id, DWORD Time_Mlis);

int Main_Timer();

void Terminate_Main_Timer();

#endif // !WIN32_TIMER_MANAGER_H
