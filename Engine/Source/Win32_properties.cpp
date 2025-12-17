#include"Win32_properties.h"
#include"Runtime_variables.h"

using namespace std;

bool Actively_running_status = true;

LRESULT CALLBACK
Main_Wincow_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_DESTROY:
	{
		Actively_running_status = false;

		cout << "\nWindow closed\n";

		PostQuitMessage(0);

		return 0;
	}
	case WM_PAINT:
	{
		// Window painting at resize 
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Window, &ps);

		// All painting occurs here, between BeginPaint and EndPaint.

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(Window, &ps);
	}
	return 0;
	}

	return DefWindowProcW(Window, Message, WParam, LParam);
};

void Black_Title_Bar(HWND Window_handle)
{
	BOOL dark_mode = true;

	DwmSetWindowAttribute(Window_handle,
		DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
	ShowWindow(Window_handle, SW_HIDE);
	ShowWindow(Window_handle, SW_SHOW);
}

bool Win32_Event_Queue(bool Active_state)
{
	Actively_running_status = Active_state;
	MSG Message_Loop = { };

	while (PeekMessageW(&Message_Loop, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message_Loop);
		DispatchMessageW(&Message_Loop);

		if (Message_Loop.message == WM_QUIT)
		{
			Actively_running_status = false;

			break;
		}
	}


	return Actively_running_status;
}


bool Primary_Win32_Window_Class_Register = false;

WIN32_CLIENT* Create_Window_Properties(int Height, int Width, const wchar_t* App_title, bool Dark_title_bar)
{
	WIN32_CLIENT* Window = new WIN32_CLIENT();

	Window->Memory.ID_type				= DEFAULT_WINDOW_ID;
	Window->Memory.Memory				= nullptr;
	Window->Height						= Height;
	Window->Width						= Width;
	Window->Title						= App_title;
	Window->Active_Black_title_Bar		= Dark_title_bar;

	Window->h_Current_Instance			= GetModuleHandle(nullptr);
	Window->h_Previous_Instance			= nullptr;
	Window->p_Command_Line				= GetCommandLineW();
	Window->n_Command_Show				= SW_SHOWDEFAULT;
	Window->Currently_Running			= true;
	
	Wide_Char Window_CLass_Name = App_title;

	if (!Primary_Win32_Window_Class_Register)
	{
		WNDCLASSW Win32_Client_CLASS = { };

		Win32_Client_CLASS.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		Win32_Client_CLASS.lpfnWndProc		= Main_Wincow_Proc;
		Win32_Client_CLASS.hInstance		= Window->h_Current_Instance;
		Win32_Client_CLASS.lpszClassName	= Window_CLass_Name;
		
		if ( !RegisterClassW(&Win32_Client_CLASS) )
		{
			delete Window;
			cerr << "\nWindow Registration Failed!\n";
			exit(EXIT_FAILURE);
		}
		
		Primary_Win32_Window_Class_Register = true;
	}

	Window->Client_Window_Handle = CreateWindowExW(
		0, Window_CLass_Name, Window->Title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT,
		Window->Width, Window->Height,
		NULL, NULL, Window->h_Current_Instance, NULL
	);

	if (!Window->Client_Window_Handle)
	{
		delete Window;
		cerr << "\nWindow creation Failed!\n";
		exit(EXIT_FAILURE);
	};

	if ( Window->Active_Black_title_Bar )
	{
		Black_Title_Bar(Window->Client_Window_Handle);
	};
	
	return Window;
}



void Delete_Win32_Window_Porperties(WIN32_CLIENT* Window_Properties)
{
	if (!Window_Properties)
	{
		return;
	}

	if (Window_Properties->Client_Window_Handle)
	{
		DestroyWindow(Window_Properties->Client_Window_Handle);
		Window_Properties->Client_Window_Handle = nullptr;
	}

	cout << "\nWin32 Window properties & memory deleted --> User Event!\n";

	delete Window_Properties;
}


