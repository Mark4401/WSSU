#include"WSML/Pulse.h"
#include"WSML_Internal.h"
#include"WIn32_Window_Manager.h"

using namespace std;

void Init_Program(Start_Up_Properties Option)
{
	switch (Option)
	{
	case DPI_AWARENESS_TRUE:

		Global_Properties.Monitor->DPI_Awareness_Status = true;
		
		Display_DPI_Properties(true);
		
		break;
	case DPI_AWARENESS_FALSE:
		
		Display_DPI_Properties(false);
		
		break;
	default:
		break;
	}
}

bool System_Queue()
{
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
