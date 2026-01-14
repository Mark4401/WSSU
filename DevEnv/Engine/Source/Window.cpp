#include "WSML/Window.h"
#include"Runtime_variables.h"
#include"WIn32_Window_Manager.h"
#include"WSML_Internal.h"

using namespace std;


void Retrieve_All_Active_Window_instances()
{
    Top_Level_Windows();
}

void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, enum Window_Position Position)
{
    int X = 0, Y = 0;

    int MAX_WIDTH = Global_Properties.Monitor->PM_Width;
    int MAX_HEIGHT = Global_Properties.Monitor->PM_Height;

    int MAX_V_WIDTH = Global_Properties.Monitor->PM_V_Workable_Width;
    int MAX_V_HEIGHT = Global_Properties.Monitor->PM_V_Workable_Height;

    if (!(Width <= MAX_V_WIDTH) || !(Height <= MAX_V_HEIGHT))
    {
        cerr << "\nEither Width or Height exceeds workable maximum limit size!\n";
        exit(EXIT_FAILURE);
    }

    switch (Position)
    {
        case POS_TOP_LEFT:
        {
            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case POS_TOP_CENTER: 
        {
            X = ((MAX_V_WIDTH - Width) / 2 );

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case POS_TOP_RIGHT:
        {

            X = (MAX_V_WIDTH - Width);
            
            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case CENTER_LEFT:
        {
            Y = ((MAX_V_HEIGHT - Height) / 2 );

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);
            
            break;
        }
        case CENTER:
        {
            
            Y = ((MAX_V_HEIGHT - Height) / 2);

            X = ((MAX_V_WIDTH - Width) / 2);

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case CENTER_RIGHT:
        {
            Y = ((MAX_V_HEIGHT - Height) / 2);
            
            X = (MAX_V_WIDTH - Width);

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case POS_BOTTOM_LEFT:
        {
            Y = (MAX_V_HEIGHT - Height);

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

            break;
        }
        case POS_BOTTOM_CENTER:
        {
            Y = (MAX_V_HEIGHT - Height);

            X = ((MAX_V_WIDTH - Width) / 2);

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);
            break;
        }
        case POS_BOTTOM_RIGHT:
        {
            Y = (MAX_V_HEIGHT - Height);

            X = (MAX_V_WIDTH - Width);

            Create_Win32_Window(title, X, Y, Width, Height, Black_title_bar);

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

