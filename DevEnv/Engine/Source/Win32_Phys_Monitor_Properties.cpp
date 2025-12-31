#include"Win32_Phys_Monitor_Properties.h"

using namespace std;

void Physical_Monitor_Position(HWND Monitor_handle)
{
	RECT			Window_Dimensions = { };
	MONITORINFO		Monitor_info = { };

	HMONITOR Monitor = MonitorFromPoint
	(
		POINT{ 0, 0 },
		MONITOR_DEFAULTTONEAREST
	);

	Monitor_info.cbSize = sizeof(Monitor_info);

	GetMonitorInfoW(Monitor, &Monitor_info);

	GetWindowRect(Monitor_handle, &Window_Dimensions);

	cout << "Window Dimensions Top: " << Window_Dimensions.top << "\n";
	cout << "Window Dimensions Bottom: " << Window_Dimensions.bottom << "\n";
	cout << "Window Dimensions Left: " << Window_Dimensions.left << "\n";
	cout << "Window Dimensions Right: " << Window_Dimensions.right << "\n";

	int Window_Width_Dim = Window_Dimensions.right - Window_Dimensions.left;
	int Window_Height_Dim = Window_Dimensions.bottom - Window_Dimensions.top;


	int Perfered_Monitor_X_Pos = Monitor_info.rcWork.right - Window_Width_Dim;
	int Perfered_Monitor_Y_Pos = Monitor_info.rcWork.top;

	BOOL Active_Pos = SetWindowPos(
		Monitor_handle, nullptr,
		Perfered_Monitor_X_Pos, Perfered_Monitor_Y_Pos, 0, 0,
		SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE
	);

	if (!Active_Pos)
	{
		cout << GetLastError();
	}
}

#define INITIALX_96DPI 50 
#define INITIALY_96DPI 50 
#define INITIALWIDTH_96DPI 100 
#define INITIALHEIGHT_96DPI 50 

Physical_Screen_Info Physical_Monitor_Dimensions(HWND Monitor_handle)
{
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	
	Physical_Screen_Info info = {};
	HMONITOR Physical_Monitor_Info = MonitorFromPoint
	(
		POINT{ 0, 0 },
		MONITOR_DEFAULTTONEAREST
	);

	MONITORINFO Mon_info = { };

	Mon_info.cbSize = sizeof(Mon_info);
	
	GetMonitorInfoW(Physical_Monitor_Info, &Mon_info);

	// Maximum 
	int Physical_Screen_X_Minimum = Mon_info.rcWork.left;
	int Physical_Screen_X_Maximum = Mon_info.rcWork.right;

	int Physical_Screen_Y_Minimum = Mon_info.rcWork.top;
	int Physical_Screen_Y_Maximum = Mon_info.rcWork.bottom;


	info.X_Min = Physical_Screen_X_Minimum, info.X_Max = Physical_Screen_X_Maximum,
	info.Y_Min = Physical_Screen_Y_Minimum, info.Y_Max = Physical_Screen_Y_Maximum;

	/*
	cout << "\nPhysical Display Dimensions: \n\n";
	cout << "X (LEFT EDGE): " << Physical_Screen_X_Minimum << " \t X (RIGHT EDGE): " << Physical_Screen_X_Maximum << "\n";
	cout << "Y (TOP EDGE): " << Physical_Screen_Y_Minimum << " \t Y (BOTTOM EDGE): " << Physical_Screen_Y_Maximum << "\n";
	*/
	
	int32_u DPI_ref_amount = GetDpiForWindow(Monitor_handle);

	int dpi_Scaled_X_return_data = MulDiv(INITIALX_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Y_return_data = MulDiv(INITIALY_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Width_return_data = MulDiv(INITIALWIDTH_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);
	int dpi_Scaled_Height_return_data = MulDiv(INITIALHEIGHT_96DPI, DPI_ref_amount, USER_DEFAULT_SCREEN_DPI);

	/*
	cout << "\nWindow DPI Scale values: \n\n";
	cout << "Height: " << dpi_Scaled_Height_return_data << "\tWight: " << dpi_Scaled_Width_return_data << "\n";
	cout << "X Scale: : " << dpi_Scaled_X_return_data << "\tY Scale: " << dpi_Scaled_Y_return_data << "\n\n";
	*/
	
	info.dpi_Scaled_Height = dpi_Scaled_Height_return_data, info.dpi_Scaled_Width = dpi_Scaled_Width_return_data,
	info.dpi_Scaled_X = dpi_Scaled_X_return_data, info.dpi_Scaled_Y = dpi_Scaled_Y_return_data;

	return info;
}

struct Monitor_Meta_Data
{
	WCHAR Monitor_name[32];
	int Hardware_Width;
	int Hardware_Hieght;

	int32_u X_Dpi;
	int32_u Y_Dpi;

	float DPI_Scale;

	float Vurtual_Width;
	float Vurtual_Height;
	float Vurtual_Workable_Width_Area;
	float Vurtual_Workable_Height_Area;
};

static Monitor_Meta_Data mmd_Physica_Monitor[6];
static int mmd_Init_Count = 0;

/*
HMONITOR unnamedParam1,
HDC unnamedParam2,
LPRECT unnamedParam3,
LPARAM unnamedParam4;
*/
// If multiple Monsters are present this will iterate between all.
static BOOL
CALLBACK Monitor_Enum_Proc(HMONITOR Monitor_, HDC, LPRECT, LPARAM)
{
	if (mmd_Init_Count >= 6)
		return FALSE;

	Monitor_Meta_Data& MMD_Info_data = mmd_Physica_Monitor[mmd_Init_Count];

	// Monitor Data
	MONITORINFOEXW Physical_Monitor_Device = { };

	Physical_Monitor_Device.cbSize = sizeof(Physical_Monitor_Device);

	// extract Dimensions 
	GetMonitorInfoW(Monitor_, &Physical_Monitor_Device);

	// extract Monitor Settings

	DEVMODE Dev_mode = { };

	Dev_mode.dmSize = sizeof(Dev_mode);

	EnumDisplaySettingsW(Physical_Monitor_Device.szDevice, ENUM_CURRENT_SETTINGS, &Dev_mode);

	StringCchCopyW(MMD_Info_data.Monitor_name, _countof(MMD_Info_data.Monitor_name), Physical_Monitor_Device.szDevice);

	// Populate MMD_data
	MMD_Info_data.Hardware_Width = Dev_mode.dmPelsWidth;
	MMD_Info_data.Hardware_Hieght = Dev_mode.dmPelsHeight;

	GetDpiForMonitor(Monitor_, MDT_EFFECTIVE_DPI, &MMD_Info_data.X_Dpi, &MMD_Info_data.Y_Dpi);

	MMD_Info_data.DPI_Scale = MMD_Info_data.X_Dpi / 96.0f;

	MMD_Info_data.Vurtual_Width = MMD_Info_data.Hardware_Width / MMD_Info_data.DPI_Scale;
	MMD_Info_data.Vurtual_Height = MMD_Info_data.Hardware_Hieght / MMD_Info_data.DPI_Scale;

	int Vurtual_Workable_Width_region = Physical_Monitor_Device.rcWork.right - Physical_Monitor_Device.rcWork.left;
	int Vurtual_Workable_Height_region = Physical_Monitor_Device.rcWork.bottom - Physical_Monitor_Device.rcWork.top;

	MMD_Info_data.Vurtual_Workable_Width_Area = Vurtual_Workable_Width_region / MMD_Info_data.DPI_Scale;
	MMD_Info_data.Vurtual_Workable_Height_Area = Vurtual_Workable_Height_region / MMD_Info_data.DPI_Scale;

	mmd_Init_Count++;

	return TRUE;
};



void Start_Up_Hardware_info()
{
	// ENable DPI awareness at start-up time to gather the Physical Monitors Resolution
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	//EnableNonClientDpiScaling(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	// 
	EnumDisplayMonitors(nullptr, nullptr, Monitor_Enum_Proc, 0);

	for (int i = 0; i < mmd_Init_Count; i++)
	{
		const Monitor_Meta_Data& m = mmd_Physica_Monitor[i];
		std::wcout << L"Monitor: " << m.Monitor_name << L"\n";
		std::wcout << L"  Physical Resolution: "
			<< m.Hardware_Width << L"x" << m.Hardware_Hieght << L"\n";
		std::wcout << L"  DPI: " << m.X_Dpi << L"\n";
		std::wcout << L"  Scale Factor: " << (m.DPI_Scale * 100.0f) << L"%\n";
		std::wcout << L"  Virtual Resolution: "
			<< m.Vurtual_Width << L"x" << m.Vurtual_Height << L"\n";
		std::wcout << L"  Virtual Work Area: "
			<< m.Vurtual_Workable_Width_Area << L"x" << m.Vurtual_Workable_Height_Area << L"\n\n";
	}
}