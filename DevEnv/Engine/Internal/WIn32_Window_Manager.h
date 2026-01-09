#ifndef WIN_32_WINDOW_MANAGER_H
#define WIN_32_WINDOW_MANAGER_H

#include<Runtime_variables.h>

void Physical_Display_Properties();

void Top_Level_Windows();

void Set_Window_info(const wchar_t* title, int Width, int Height, bool Black_title_bar);

static void Retrieve_Window_Destruction_By_User(HWND WIndow);

void ALL_Process_Window_Lists();

bool Queue();

#endif // !WIN_32_WINDOW_MANAGER_H
