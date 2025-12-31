#ifndef WIN32_PHYS_MONITOR_PROPERTIES_H
#define	WIN32_PHYS_MONITOR_PROPERTIES_H


#include"Runtime_variables.h"
#include"Win32_properties.h"
#include"Win32_Keyboard_properties.h"


void Physical_Monitor_Position(HWND Monitor_handle);

struct Physical_Screen_Info
{
	int X_Min;
	int X_Max;
	int Y_Min;
	int Y_Max;

	int dpi_Scaled_Height;
	int dpi_Scaled_Width;
	int dpi_Scaled_X;
	int dpi_Scaled_Y;
};

Physical_Screen_Info Physical_Monitor_Dimensions(HWND Monitor_handle);

void Start_Up_Hardware_info();

#endif // !WIN32_PHYS_MONITOR_PROPERTIES_H
