#include"WSML/Pulse.h"
#include"WSML_Internal.h"
#include"WIn32_Window_Manager.h"
//#include"test_or_examples/DWM_Examples.h"

using namespace std;

void Init_Program(Start_Up_Properties Option, enum DWM Edit_Option)
{
	switch (Option)
	{
	case DPI_AWARENESS_TRUE:

		Global_Properties.Monitor->DPI_Awareness_Status = true;
		
		if (Edit_Option == ENABLE_DWM_EDIT)
		{
			DWM_Edges.DWM_Edit_Mode = true;
		}

		Display_DPI_Properties(true);
		
		P_Protical.Program_initialized_Code = PROG_INIT_SUCCESSFUL;

		break;
	case DPI_AWARENESS_FALSE:

		//Global_Properties.Monitor->DPI_Awareness_Status = false;
		
		if (Edit_Option == ENABLE_DWM_EDIT)
		{
			DWM_Edges.DWM_Edit_Mode = true;
		}
		
		Display_DPI_Properties(false);

		P_Protical.Program_initialized_Code = PROG_INIT_SUCCESSFUL;

		break;
	default:
		break;
	}
}

bool System_Queue()
{
	if (P_Protical.Program_initialized_Code == PROG_INIT_FAILURE)
	{
		cerr << "\nInit_Program() call needed\n";
		exit(EXIT_FAILURE);
	}
	bool Active_state = true;

	MSG Message_Loop = { };

	while (PeekMessageW(&Message_Loop, 0, 0, 0, PM_REMOVE))
	{
		if (Message_Loop.message == WM_QUIT)
		{
			Active_state = false;

			cout << "\nWM_QUIT win32 message called!\n";



			return Active_state;
		}

		TranslateMessage(&Message_Loop);
		DispatchMessageW(&Message_Loop);
	}

	return Active_state;
}
