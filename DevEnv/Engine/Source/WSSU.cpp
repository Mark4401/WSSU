#include "WSSU.h"
#include"Runtime_variables.h"
#include"WIn32_Window_Manager.h"

using namespace std;

void Default_Systen_info()
{
    Physical_Display_Properties();
}

void Get_Window_System_Active_List()
{
    Top_Level_Windows();
}

void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar)
{
    Set_Window_info(title, Width, Height, Black_title_bar);
}

void Process_Lists()
{
    ALL_Process_Window_Lists();
}

bool Events()
{
    return Queue();
}


