#include "WIn32_Window_Manager.h"
#include"Keyboard_Win32.h"
#include"WSML_Internal.h"
#include"test_or_examples/DWM_Examples.h"

using namespace std;

BOOL CALLBACK
Enum_SYstem_Windows_Proc(HWND Window_handle, LPARAM LParam)
{
	cout << "(Window_handle) : " << Window_handle << "\n";

	Count_Data.Count++;

	return TRUE;
};

void Top_Level_Windows()
{
	EnumWindows(Enum_SYstem_Windows_Proc, 0);

	cout << "\n(Top level Window Handle Count): " << Count_Data.Count << "\n\n";
}

static BOOL
CALLBACK Monitor_enum_Proc(HMONITOR Monitor_, HDC, LPRECT, LPARAM)
{
	if (Global_Properties.Monitor->PM_Present_count >= 6)
	{
		return FALSE;
	}

	MONITORINFOEX Monitor_Info_Struct = { };

	Monitor_Info_Struct.cbSize = sizeof(Monitor_Info_Struct);

	GetMonitorInfoW(Monitor_, &Monitor_Info_Struct);

	DEVMODE _Dev_Mode_ = { };

	_Dev_Mode_.dmSize = sizeof(_Dev_Mode_);

	EnumDisplaySettingsW(Monitor_Info_Struct.szDevice, ENUM_CURRENT_SETTINGS, &_Dev_Mode_);

	StringCchCopyW(Global_Properties.Monitor->Monitor_Name, _countof(Global_Properties.Monitor->Monitor_Name), Monitor_Info_Struct.szDevice);

	Global_Properties.Monitor->PM_Width = _Dev_Mode_.dmPelsWidth;
	Global_Properties.Monitor->PM_Height = _Dev_Mode_.dmPelsHeight;

	int32_u X_DPI = 96, Y_DPI = 96;

	GetDpiForMonitor(Monitor_, MDT_EFFECTIVE_DPI, &X_DPI, &Y_DPI);

	Global_Properties.Monitor->X_Dpi = X_DPI;
	Global_Properties.Monitor->Y_Dpi = Y_DPI;

	Global_Properties.Monitor->DPI_Scale = (float)Global_Properties.Monitor->X_Dpi / 96.0f;

	int Width_Region = Monitor_Info_Struct.rcMonitor.right - Monitor_Info_Struct.rcMonitor.left;
	int Height_Region = Monitor_Info_Struct.rcMonitor.bottom - Monitor_Info_Struct.rcMonitor.top;

	int Workable_Width_Region = Monitor_Info_Struct.rcWork.right - Monitor_Info_Struct.rcWork.left;
	int Workable_Height_Region = Monitor_Info_Struct.rcWork.bottom - Monitor_Info_Struct.rcWork.top;

	Global_Properties.Monitor->PM_Virtual_Width = Width_Region;
	Global_Properties.Monitor->PM_Virtual_Height = Height_Region;

	Global_Properties.Monitor->PM_V_Workable_Width = Workable_Width_Region;
	Global_Properties.Monitor->PM_V_Workable_Height = Workable_Height_Region;

	Global_Properties.Monitor->PM_Present_count++;

	return TRUE;
};

/***************************************************************************************/
/***********   System Enumeration & Procedures | Above ONLY!   *************************/
/***************************************************************************************/

/***************************************************************************************/
/***********   Window Enumeration & Procedures | Below ONLY!   *************************/
/***************************************************************************************/

LRESULT CALLBACK
Default_Window_Proc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{	
	switch (Message)
	{
		case WM_ACTIVATEAPP:
		{
			cout << "\nWindow called / Active Focus!\n";

			return TRUE;
		}
		case WM_CREATE:
		{
			cout << "\nWindow Created!\n";

			return TRUE;
		}
		case WM_DESTROY:
		{
			Retrieve_Window_Destruction_By_User(Window);

			Global_Properties.Process_owned_WI_count--;

			if ((Global_Properties.Process_owned_WI_count) == 0)
			{
				cout << "\n\nActive Window list Empty! ONLY DLL handle Active\n";

				PostQuitMessage(0);

				UnregisterClassW(Global_Properties.DEAFULT_WINDOW_CLASS.lpszClassName, Global_Properties.DEAFULT_WINDOW_CLASS.hInstance);

			}

			return 0;
		}
		case WM_GETMINMAXINFO:
		{
			MINMAXINFO Window_Size_Info;

			//Window_Size_Info.

			break;
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

	if (!DWM_Edges.DWM_Edit_Mode == false)
	{
		DWM_Exmaple_1(Window, Message, WParam, LParam);
	}

	return DefWindowProcW(Window, Message, WParam, LParam);
};

/***************************************************************************************/
/***********   Window Enumeration & Procedures | Above ONLY!   *************************/
/***************************************************************************************/

/***************************************************************************************/
/***********   System Properties & Debug Info  | Below ONLY!   *************************/
/***************************************************************************************/

void Display_DPI_Properties(bool state)
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

	if (!state == true)
	{
		cout << "\n(DPI_Active_Awareness_Context_State):  OFF" << "\n\n";
	}
	else
	{
		SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

		cout << "\n(DPI_Active_Awareness_Context_State):  ACTIVE" << "\n\n";
	}


	// DEF stands for Default; DEF is just my own short hand definition.

	Global_Properties.Monitor->DEF_Monitor_handle = GetDesktopWindow();

	Global_Properties.Data.Active_instances[Global_Properties.Window_instance_Count++] = Global_Properties.Monitor->DEF_Monitor_handle;

	// WIll stop GetWindowRect from complaining of retying 
	if (!Global_Properties.Monitor->DEF_Monitor_handle) { cerr << GetLastError() << "\n"; return; };

	cout << "(MEMORY ADDRS) of DEF: " << Global_Properties.Monitor->DEF_Monitor_handle << "\n\n";

	RECT DEF_Handle_Dimensions;


	//GetClientRect(DEF_handle, &DEF_Handle_Dimensions);
	if (!GetWindowRect(Global_Properties.Monitor->DEF_Monitor_handle, &DEF_Handle_Dimensions)) { cerr << GetLastError() << "\n"; return; };

	cout << "Primary Physical Display Properties:\n\n";
	cout << "DEF (LEFT): " << DEF_Handle_Dimensions.left << "\t" << "DEF (RIGHT): " << DEF_Handle_Dimensions.right << "\n"
		<< "DEF (TOP): " << DEF_Handle_Dimensions.top << "\t" << "DEF (BOTTOM): " << DEF_Handle_Dimensions.bottom << "\n\n";

	POINT DEF_Position = { 0 , 0 };

	HWND Position_handle = WindowFromPoint(DEF_Position);

	cout << "POS (ADDRS): " << Position_handle << "\n\n"
		<< "POS (X): " << DEF_Position.x << "\t" << "POS (Y): " << DEF_Position.y << "\n\n";

	EnumDisplayMonitors(nullptr, nullptr, Monitor_enum_Proc, 0);

	for (int I = 0; I < Global_Properties.Monitor->PM_Present_count; I++)
	{
		const Physical_Monitor& PM_List = Global_Properties.Monitor[I];

		wcout << L"Monitor: \t" << PM_List.Monitor_Name << "\n\n";

		wcout << L"Physical Resolution: \t"
			<< PM_List.PM_Width << L"x" << PM_List.PM_Height << "\n";

		wcout << L"Virtual Resolution: \t" << PM_List.PM_Virtual_Width << L"x" << PM_List.PM_Virtual_Height << "\n";

		wcout << L"Workable Virtual Resolution: \t" << PM_List.PM_V_Workable_Width << L"x" << PM_List.PM_V_Workable_Height << "\n";

		wcout << L"DPI: \t" << PM_List.X_Dpi << "\n";

		wcout << L"DPI Scale factor: \t" << (PM_List.DPI_Scale * 100.0f) << "\n";

		wcout << L"X and Y DPI vals: \t" << PM_List.X_Dpi << L"\t" << PM_List.Y_Dpi << "\n";
	}
}

/***************************************************************************************/
/***********   System Properties & Debug Info  | Above ONLY!   *************************/
/***************************************************************************************/

/***************************************************************************************/
/***********   Window Creation & MetaData????? | Below ONLY!   *************************/
/***************************************************************************************/

void Black_Title_Bar(HWND Window_handle)
{
	BOOL dark_mode = true;

	DwmSetWindowAttribute(Window_handle,
		DWMWA_USE_IMMERSIVE_DARK_MODE, &dark_mode, sizeof(dark_mode));
}

void Create_Win32_Window(const wchar_t* title, int X_Pos, int Y_Pos, int Width, int Height, bool Black_title_bar)
{
	if (Global_Properties.Class_Registry == false)
	{
		Global_Properties.DEAFULT_WINDOW_CLASS.style = CS_VREDRAW | CS_OWNDC;
		Global_Properties.DEAFULT_WINDOW_CLASS.lpfnWndProc = Default_Window_Proc;
		Global_Properties.DEAFULT_WINDOW_CLASS.hInstance = GetModuleHandle(nullptr);
		Global_Properties.DEAFULT_WINDOW_CLASS.lpszClassName = L"DEF_WINDOW_CALSS";

		if (!RegisterClassW(&Global_Properties.DEAFULT_WINDOW_CLASS))
		{
			cout << GetLastError() << "\n";
			cerr << "\nWindow Registration Failed!\n";
			exit(EXIT_FAILURE);
		};
	}
	
	Global_Properties.Class_Registry = true;

	HWND DEF_Screen = CreateWindowExW
	(
		0,
		Global_Properties.DEAFULT_WINDOW_CLASS.lpszClassName,
		title,
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		X_Pos,
		Y_Pos,
		Width,
		Height,
		NULL,
		NULL,
		Global_Properties.DEAFULT_WINDOW_CLASS.hInstance,
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

	if (Global_Properties.Window_instance_Count < MAX_WH_LIST)
	{
		Global_Properties.Process_owned_WI_count++;

		cout << "Window Index: " << Global_Properties.Window_instance_Count << "\n";
		
		Global_Properties.Data.Active_instances[Global_Properties.Window_instance_Count++] = DEF_Screen;

		cout << "Window Handle: " << DEF_Screen << "\n";
	}
}

static void Retrieve_Window_Destruction_By_User(HWND Window)
{
	for (int I = 0; I < Global_Properties.Window_instance_Count; I++)
	{
		if (Global_Properties.Data.Active_instances[I] == Window)
		{
			cout << "\nWindow closed by user action!\t" << "(HWND_Handle): " << Global_Properties.Data.Active_instances[I];
		}
	}
}

void ALL_Process_Window_Lists()
{
	if (Global_Properties.Process_owned_WI_count == 0 )
	{
		cout << "NON Primary Window created! program will continue indefensibly without Post Code 0!" << "\n";

		exit(EXIT_FAILURE);
	}

	for (int I = 0; I < Global_Properties.Window_instance_Count; I++)
	{
		BOOL True_or_False = IsWindowUnicode(Global_Properties.Data.Active_instances[I]);
		cout << "\nWindow Index: " << I << "\t(HWND_Handle): " << Global_Properties.Data.Active_instances[I] << "\t"
			<< "(Unicode Window): " << (True_or_False ? "True" : "False");

	}
}

void Forground_Window()
{
	HWND Forground_handle = GetForegroundWindow();

	cout << Forground_handle << "\n";
}

/***************************************************************************************/
/***********   Window Creation & MetaData????? | Above ONLY!   *************************/
/***************************************************************************************/

