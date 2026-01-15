#ifndef WSML_INTERNAL_H
#define WSML_INTERNAL_H

#include<Runtime_variables.h>

#define MAX_WH_LIST		10
#define MAX_PM_COUNT	10
#define	MAX_CHAR_LENGHT 256

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

struct Outer_Borders
{	
	bool DWM_Edit_Mode;
	int Top;
	int Bottom;
	int Left;
	int Right;
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

enum Program_protocal_Codes
{
	PROG_INIT_SUCCESSFUL,
	PROG_INIT_FAILURE
};

struct Program_protocal
{
	int Program_initialized_Code = 1;
};


extern Program_protocal				P_Protical;

extern Program_Deafult_Properties	Global_Properties;

extern Window_handle_count			Count_Data;

extern Outer_Borders				DWM_Edges;

#endif // !WSML_INTERNAL_H
