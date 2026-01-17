#include "DWM_Examples_demo.h"
#include<iostream>

using namespace std;

void DWM_Examples()
{

    Init_Program(DPI_AWARENESS_FALSE, ENABLE_DWM_EDIT);

    Extend_Outer_Window_Borders(10, 10, 10, 10);

    Init_Window(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)",
        1920, 1080, true, CENTER);

    Init_Window(L"Test_Window!",
        400, 400, true, POS_TOP_LEFT);

    Init_Window(L"Test_Window! 2",
        400, 400, true, POS_TOP_RIGHT);

    Process_Lists();

    Window window[3];

    window[0].Address = Return_Window_Adress(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)");
    window[1].Address = Return_Window_Adress(L"Test_Window!");
    window[2].Address = Return_Window_Adress(L"Test_Window! 2");

    cout << "\n" << window[0].Address << "\n"
        << window[1].Address << "\n"
        << window[2].Address << "\n";

    while (System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();
}
