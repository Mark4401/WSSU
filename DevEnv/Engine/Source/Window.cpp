#include "WSSU/Window.h"
#include"Runtime_variables.h"
#include"WIn32_Window_Manager.h"

using namespace std;

void Default_Systen_info()
{
    Physical_Display_Properties();
}

void Retrieve_All_Active_Window_instances()
{
    Top_Level_Windows();
}

void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, enum Window_Position Position, enum  Window_Type Type)
{
    Set_Window_info(title, Width, Height, Black_title_bar);
}

void Process_Lists()
{
    ALL_Process_Window_Lists();
}
