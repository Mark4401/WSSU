#ifndef WSML_INTERNAL_H
#define WSML_INTERNAL_H

#include<Runtime_variables.h>

#define MAX_WH_LIST		10
#define MAX_PM_COUNT	10

struct Window_handle_count
{
	int Count;
};

struct WIn32_HWND_List
{
	HWND Active_instances[MAX_WH_LIST];
};

struct Physical_Monitor
{
	wchar_t Monitor_Name[125];
	int PM_Present_count;
	int PM_Width;
	int PM_Height;

	int PM_Workable_Width;
	int PM_Workable_Height;

	int PM_Virtual_Width;
	int PM_Virtual_Height;

	int32_u X_Dpi;
	int32_u Y_Dpi;

	float DPI_Scale;

	int PM_V_Workable_Width;
	int PM_V_Workable_Height;

	HWND DEF_Monitor_handle;

	bool DPI_Awareness_Status;

};

struct Program_Deafult_Properties
{
	WNDCLASSW			DEAFULT_WINDOW_CLASS;
	int					Process_owned_WI_count;
	int					Window_instance_Count;
	bool				Class_Registry;
	WIn32_HWND_List		Data;
	Physical_Monitor	Monitor[MAX_PM_COUNT];
};

extern Program_Deafult_Properties	Global_Properties;

extern Window_handle_count			Count_Data;



#endif // !WSML_INTERNAL_H
