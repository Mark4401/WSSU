#include"Win32_properties.h"
#include"Runtime_variables.h"
#include"Win32_Keyboard_properties.h"
#include"Win32_Phys_Monitor_Properties.h"

using namespace std;

LRESULT CALLBACK
Main_Wincow_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
		Keyboard_Data(Window, Message, WParam, LParam);
		
		WIN32_Keyboard_Data(Window, Message, WParam, LParam);

		cout << "| My Method \t" << Return_Virtual_Code() << "\t | Win32  " << Return_Vk() << "\t | VK CODE  \n";
		cout << "| My Method \t" << Return_Key_Flags() << "\t | Win32  " << Return_KeyFlags() << "\t | KEY FLAG    \n";
		cout << "| My Method \t" << Return_Scan_Code() << "\t | Win32  " << Return_ScanCode() << "\t | SCAN CODE   \n\n";

		break;
	}
	case WM_DESTROY:
	{
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

	WNDCLASSW Win32_Client_CLASS = { };

	Win32_Client_CLASS.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Win32_Client_CLASS.lpfnWndProc = Main_Wincow_Proc;
	Win32_Client_CLASS.hInstance = Window->h_Current_Instance;
	Win32_Client_CLASS.lpszClassName = Window_CLass_Name;

	if (!RegisterClassW(&Win32_Client_CLASS))
	{
		delete Window;
		cerr << "\nWindow Registration Failed!\n";
		exit(EXIT_FAILURE);
	}

	Window->Client_Window_Handle = CreateWindowExW(
		BLANK_WINDOW_STYLE, Window_CLass_Name, Window->Title,
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

	// Window Position Arrangement.

	Physical_Screen_Info Monitor_Ref_Data = Physical_Monitor_Dimensions(Window->Client_Window_Handle);

	cout << "\nPhysical Display Dimensions: \n\n";
	cout << "X (LEFT EDGE): " << Monitor_Ref_Data.X_Min << " \t X (RIGHT EDGE): " << Monitor_Ref_Data.X_Max << "\n";
	cout << "Y (TOP EDGE): " << Monitor_Ref_Data.Y_Min << " \t Y (BOTTOM EDGE): " << Monitor_Ref_Data.Y_Max << "\n";

	cout << "\nWindow DPI Scale values: \n\n";
	cout << "Height: " << Monitor_Ref_Data.dpi_Scaled_Height << "\tWight: " << Monitor_Ref_Data.dpi_Scaled_Width << "\n";
	cout << "X Scale: : " << Monitor_Ref_Data.dpi_Scaled_X << "\tY Scale: " << Monitor_Ref_Data.dpi_Scaled_Y << "\n\n";

	Physical_Monitor_Position(Window->Client_Window_Handle);

	return Window;
}


bool Win32_Event_Queue(bool Active_state, WIN32_CLIENT& Data_ref)
{
	Data_ref.Currently_Running = Active_state;
	MSG Message_Loop = { };

	while (PeekMessageW(&Message_Loop, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&Message_Loop);
		DispatchMessageW(&Message_Loop);

		if (Message_Loop.message == WM_QUIT)
		{
			Data_ref.Currently_Running = false;

			return Active_state = false;
		}
	}

	return Active_state = true;
}


void Delete_Win32_Window_Porperties(WIN32_CLIENT& Data_ref)
{
	if (Data_ref.Client_Window_Handle)
	{
		DestroyWindow(Data_ref.Client_Window_Handle);
		Data_ref.Client_Window_Handle = nullptr;
		
		cout << "\nWin32 Window properties & memory deleted --> System Event!\n";
	}
}


