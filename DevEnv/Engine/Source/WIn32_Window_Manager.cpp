#include "WIn32_Window_Manager.h"
#include"Keyboard_Win32.h"
#include<iostream>

using namespace std;

struct Window_handle_count
{
	int Count;
};

#define MAX_WH_LIST		10
#define MAX_PM_COUNT	10

struct WIn32_HWND_List
{
	HWND Active_instances[MAX_WH_LIST];
};

typedef struct WIN32_CLIENT
{
	int					Height;
	int					Width;
	Wide_Char			Title;
	HINSTANCE			h_Current_Instance;
	HINSTANCE			h_Previous_Instance;
	PWSTR				p_Command_Line;
	HWND				Client_Window_Handle;
	bool				Currently_Running;
	bool				Active_Black_title_Bar;
	int					n_Command_Show;
} WIN32_CLIENT;


struct Physical_Monitor
{
	wchar_t Monitor_Name[32];
	int PM_Present_count;
	int PM_Width;
	int PM_Height;

	int PM_Virtual_Width;
	int PM_Virtual_Height;

	int32_u X_Dpi;
	int32_u Y_Dpi;

	float DPI_Scale;

	int PM_V_Workable_Width;
	int PM_V_Workable_Height;

	HWND DEF_Monitor_handle;

};

struct Window_Data
{
	int					Process_owned_WI_count			= 0;
	int					Window_instance_Count			= 0;
	bool				Class_Registry					= false;
	WIn32_HWND_List		Data							= { };
	Physical_Monitor	Monitor							[MAX_PM_COUNT];
};

Window_Data Deafult_Window = { };

WNDCLASSW DEAFULT_WINDOW_CLASS = { };

Window_handle_count Data;

BOOL CALLBACK
Enum_Windows_Proc(HWND Window_handle, LPARAM LParam)
{
	cout << "(Window_handle) : " << Window_handle << "\n";

	Data.Count++;

	return TRUE;
};

void Top_Level_Windows()
{
	EnumWindows(Enum_Windows_Proc, 0);

	cout << "\n(Top level Window Handle Count): " << Data.Count << "\n\n";
}

LRESULT CALLBACK
Default_Window_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	switch (Message)
	{
		case WM_DESTROY:
		{
			Retrieve_Window_Destruction_By_User(Window);

			Deafult_Window.Process_owned_WI_count--;

			if (( Deafult_Window.Process_owned_WI_count) == 0)
			{
				cout << "\n\nActive Window list Empty! ONLY DLL handle Active\n";

				PostQuitMessage(0);
				
				UnregisterClassW(DEAFULT_WINDOW_CLASS.lpszClassName, DEAFULT_WINDOW_CLASS.hInstance);
				
			}

			return 0;
		}
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			Keyboard_Data(Window, Message, WParam, LParam);

			cout << Return_Virtual_Code() << "\t | VK CODE  \n";
			cout << Return_Key_Flags() << "\t | KEY FLAG    \n";
			cout << Return_Scan_Code() << "\t | SCAN CODE   \n\n";

			break;
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
	}
	return DefWindowProcW(Window, Message, WParam, LParam);
};

void Black_Title_Bar(HWND Window_handle)
{
	BOOL dark_mode = true;

	DwmSetWindowAttribute(Window_handle,
		DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
	
	//ShowWindow(Window_handle, SW_HIDE);
	//ShowWindow(Window_handle, SW_SHOW);
}

void Set_Window_info(const wchar_t* title, int Width, int Height, bool Black_title_bar)
{
	if (Deafult_Window.Class_Registry == false)
	{
		DEAFULT_WINDOW_CLASS.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		DEAFULT_WINDOW_CLASS.lpfnWndProc = Default_Window_Proc;
		DEAFULT_WINDOW_CLASS.hInstance = GetModuleHandle(nullptr);
		DEAFULT_WINDOW_CLASS.lpszClassName = L"DEF_WINDOW_CALSS";

		if (!RegisterClassW(&DEAFULT_WINDOW_CLASS))
		{
			cout << GetLastError() << "\n";
			cerr << "\nWindow Registration Failed!\n";
			exit(EXIT_FAILURE);
		};
	}
	
	Deafult_Window.Class_Registry = true;

	HWND DEF_Screen = CreateWindowExW
	(
		0,
		DEAFULT_WINDOW_CLASS.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		0,
		0,
		Width,
		Height,
		NULL,
		NULL,
		DEAFULT_WINDOW_CLASS.hInstance,
		NULL
	);

	if (!DEF_Screen)
	{
		cerr << "\nWindow Creation Failed!\n";
		exit(EXIT_FAILURE);
	}
	else if ( Black_title_bar == true )
	{
		Black_Title_Bar(DEF_Screen);
	}
	else
	{
		// addictions go here if applicable 
	}

	ShowWindow(DEF_Screen, SW_SHOW);

	if (Deafult_Window.Window_instance_Count < MAX_WH_LIST)
	{
		Deafult_Window.Process_owned_WI_count++;

		cout << "Window Index: " << Deafult_Window.Window_instance_Count << "\n";
		
		Deafult_Window.Data.Active_instances[Deafult_Window.Window_instance_Count++] = DEF_Screen;

		cout << "Window Handle: " << DEF_Screen << "\n";
	}
}

void Retrieve_Window_Destruction_By_User(HWND Window)
{
	for (int I = 0; I < Deafult_Window.Window_instance_Count; I++)
	{
		if (Deafult_Window.Data.Active_instances[I] == Window)
		{
			cout << "\nWindow closed by user action!\t" << "(HWND_Handle): " << Deafult_Window.Data.Active_instances[I];
		}
	}
}

void ALL_Process_Window_Lists()
{
	if (Deafult_Window.Process_owned_WI_count == 0 )
	{
		cout << "NON Primary Window created! program will continue indefensibly without Post Code 0!" << "\n";

		exit(EXIT_FAILURE);
	}

	for (int I = 0; I < Deafult_Window.Window_instance_Count; I++)
	{
		BOOL True_or_False = IsWindowUnicode(Deafult_Window.Data.Active_instances[I]);
		cout << "\nWindow Index: " << I << "\t(HWND_Handle): " << Deafult_Window.Data.Active_instances[I] << "\t"
			<< "(Unicode Window): " << (True_or_False ? "True" : "False");

	}
}

bool Queue()
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
};

static BOOL
CALLBACK Monitor_enum_Proc(HMONITOR Monitor_, HDC, LPRECT, LPARAM)
{
	if (Deafult_Window.Monitor->PM_Present_count >= 6)
	{
		return FALSE;
	}

	MONITORINFOEX Monitor_Info_Struct = { };

	Monitor_Info_Struct.cbSize = sizeof(Monitor_Info_Struct);

	GetMonitorInfoW(Monitor_, &Monitor_Info_Struct);

	DEVMODE _Dev_Mode_ = { };

	_Dev_Mode_.dmSize = sizeof(_Dev_Mode_);

	EnumDisplaySettingsW(Monitor_Info_Struct.szDevice, ENUM_CURRENT_SETTINGS, &_Dev_Mode_);

	StringCchCopyW(Deafult_Window.Monitor->Monitor_Name, _countof(Deafult_Window.Monitor->Monitor_Name), Monitor_Info_Struct.szDevice);

	Deafult_Window.Monitor->PM_Width = _Dev_Mode_.dmPelsWidth;
	Deafult_Window.Monitor->PM_Height = _Dev_Mode_.dmPelsHeight;

	GetDpiForMonitor(Monitor_, MDT_EFFECTIVE_DPI, &Deafult_Window.Monitor->X_Dpi, &Deafult_Window.Monitor->Y_Dpi);

	Deafult_Window.Monitor->DPI_Scale = Deafult_Window.Monitor->X_Dpi / 96.0f;

	Deafult_Window.Monitor->PM_Virtual_Height = Deafult_Window.Monitor->PM_Height / Deafult_Window.Monitor->DPI_Scale;
	Deafult_Window.Monitor->PM_Virtual_Width = Deafult_Window.Monitor->PM_Width / Deafult_Window.Monitor->DPI_Scale;

	int PM_V_Temp_Workable_Width_Region = Monitor_Info_Struct.rcWork.right - Monitor_Info_Struct.rcWork.left;
	int PM_V_Temp_Workable_Height_Region = Monitor_Info_Struct.rcWork.bottom - Monitor_Info_Struct.rcWork.top;

	Deafult_Window.Monitor->PM_V_Workable_Height = PM_V_Temp_Workable_Height_Region / Deafult_Window.Monitor->DPI_Scale;
	Deafult_Window.Monitor->PM_V_Workable_Width = PM_V_Temp_Workable_Width_Region / Deafult_Window.Monitor->DPI_Scale;

	Deafult_Window.Monitor->PM_Present_count++;

	return TRUE;
};

void Physical_Display_Properties()
{	
	/*
		Returns either  1 or 0 i.e. (TRUE or DALSE)
		
		- true if:
			- the program has Access to full Monitor/Display Physical Properties:
				- Hardware level resolution no-matter the current scale in windows settings.
		- false if:
			- the Program has Access ONLY to the virtual Monitor/Display Properties 
				- And will remain unaware of Hardware Resolution. Always Thinking the Scale is set to 100% 
	*/
	BOOL DPI_Active_Awareness_Context_State = SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	if (DPI_Active_Awareness_Context_State == true) (cout << "\n(DPI_Active_Awareness_Context_State):  ACTIVE" << "\n\n");
	if (DPI_Active_Awareness_Context_State == false) (cout << "\n(DPI_Active_Awareness_Context_State):  OFF"<< "\n\n");
	//HWND DEF_handle =  GetWindow(GetDesktopWindow(), GW_HWNDFIRST);

	// DEF stands for Default; DEF is just my own short hand definition.
	
	Deafult_Window.Monitor->DEF_Monitor_handle = GetDesktopWindow();

	Deafult_Window.Data.Active_instances[Deafult_Window.Window_instance_Count++] = Deafult_Window.Monitor->DEF_Monitor_handle;

	// WIll stop GetWindowRect from complaining of retying 
	if (!Deafult_Window.Monitor->DEF_Monitor_handle) { cerr << GetLastError() << "\n"; return; };

	cout << "(MEMORY ADDRS) of DEF: " << Deafult_Window.Monitor->DEF_Monitor_handle << "\n\n";

	RECT DEF_Handle_Dimensions;


	//GetClientRect(DEF_handle, &DEF_Handle_Dimensions);
	if (!GetWindowRect(Deafult_Window.Monitor->DEF_Monitor_handle, &DEF_Handle_Dimensions)) { cerr << GetLastError() << "\n"; return; };

	cout << "Primary Physical Display Properties:\n\n";
	cout << "DEF (LEFT): " << DEF_Handle_Dimensions.left << "\t" << "DEF (RIGHT): " << DEF_Handle_Dimensions.right << "\n"
		<< "DEF (TOP): " << DEF_Handle_Dimensions.top << "\t" << "DEF (BOTTOM): " << DEF_Handle_Dimensions.bottom << "\n\n";

	POINT DEF_Position = {0 , 0};

	HWND Position_handle = WindowFromPoint(DEF_Position);

	cout << "POS (ADDRS): " << Position_handle << "\n\n"
		<< "POS (X): " << DEF_Position.x << "\t" << "POS (Y): " << DEF_Position.y << "\n\n";

	EnumDisplayMonitors(nullptr, nullptr, Monitor_enum_Proc, 0);

	for (int I = 0; I < Deafult_Window.Monitor->PM_Present_count; I++)
	{
		const Physical_Monitor& PM_List = Deafult_Window.Monitor[I];

		wcout << L"Monitor: " << PM_List.Monitor_Name << "\n";
		
		wcout << L"Physical Resolution: " 
			<< PM_List.PM_Width << L"x" << PM_List.PM_Height << "\n";
		wcout << L"DPI: " << PM_List.X_Dpi << "\n";
		wcout << L"DPI Scale factor: " << (PM_List.DPI_Scale * 100.0f) << "\n";
		wcout << L"Virtual Resolution: " << PM_List.PM_Virtual_Width << L"x" << PM_List.PM_Virtual_Height << "\n";
		wcout << L"Workable Virtual Resolution: " << PM_List.PM_V_Workable_Width << L"x" << PM_List.PM_V_Workable_Height << "\n\n";

		wcout << L"X and Y DPI vals: " << PM_List.X_Dpi << L"\t" << PM_List.Y_Dpi << "\n";
	}
}
