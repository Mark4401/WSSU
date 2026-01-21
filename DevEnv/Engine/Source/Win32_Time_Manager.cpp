#include "Win32_Time_Manager.h"


VOID CALLBACK Main_Timer_Proc(HWND Window_handle, UINT Timer_Message, UINT_PTR Timer_Id, DWORD Time_Mlis)
{

}

int Main_Timer()
{
	UINT_PTR Primrary_timer = SetTimer(NULL, 0, 1000, Main_Timer_Proc);

	return Primrary_timer;
}

void Terminate_Main_Timer()
{
	KillTimer(NULL, 0);
}
