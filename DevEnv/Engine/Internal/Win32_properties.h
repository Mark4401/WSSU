#ifndef WIN32_PROPERTIES_H
#define WIN32_PROPERTIES_H

#include"Runtime_variables.h"

/*

	_ LEGACY STRUCTS
	_ REFERENCE USE ONLY!

typedef struct WIN32_IO_DATA
{
	int16_u				Message;
	WPARAM				Wparam;
	LPARAM				LParam;
} WIN32_IO_DATA;

typedef struct WIN32_Keyboard_info
{
	WIN32_IO_DATA		*Info;
	int32_u				Key_code_number;
	bool				Key_code_state;
} WIN32_Keyboard_info;

typedef struct WIN32_MEMORY
{
	void*				Memory;
	int					ID_type;
} WIN32_MEMORY;

*/
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


#endif // !WIN32_PROPERTIES_H
