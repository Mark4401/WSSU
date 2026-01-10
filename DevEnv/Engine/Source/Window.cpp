#include "WSSU/Window.h"
#include"Runtime_variables.h"
#include"WIn32_Window_Manager.h"
#include"WSSU_Internal.h"

using namespace std;




void Retrieve_All_Active_Window_instances()
{
    Top_Level_Windows();
}

void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, Window_Position Position)
{
    int X = 0, Y = 0;
    int MAX_WIDTH = Global_Properties.Monitor->PM_Width;
    int MAX_HEIGHT = Global_Properties.Monitor->PM_Height;

    int MAX_V_WIDTH = Global_Properties.Monitor->PM_V_Workable_Width;
    int MAX_V_HEIGHT = Global_Properties.Monitor->PM_V_Workable_Height;

    bool DPI_Awareness_state = Global_Properties.Monitor->DPI_Awareness_Status;

    if (!(Width <= MAX_V_WIDTH) || !(Height <= MAX_V_HEIGHT))
    {
        cerr << "Either Width or Height workable maximums!\n";
        exit(EXIT_FAILURE);
    }

    switch (Position)
    {
        case POS_TOP_LEFT:
        {
            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);
            //Global_Properties.Monitor.
            //Create_Win32_Window()

            break;
        }
        case POS_TOP_CENTER: 
        {

            break;
        }
        case POS_TOP_RIGHT:
        {
            break;
        }
        case CENTER_LEFT:
        {
            break;
        }
        case CENTER:
        {
            break;
        }
        case CENTER_RIGHT:
        {
            break;
        }
        case POS_BOTTOM_LEFT:
        {
            break;
        }
        case POS_BOTTOM_CENTER:
        {
            break;
        }
        case POS_BOTTOM_RIGHT:
        {
            break;
        }
        default:
            break;
    }
}



void Process_Lists()
{
    ALL_Process_Window_Lists();
}

