#include<WSML/WSML.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Init_Program(DPI_AWARENESS_FALSE, ENABLE_DWM_EDIT);
    
    Extend_Outer_Window_Borders(400, 300, 200, 100);
    
    Init_Window(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)",
        1920, 1080, true, CENTER);  

    Init_Window(L"Test_Window!",
        400, 400, true, POS_TOP_LEFT);
    
    Process_Lists();

    Window window[2];

    window[0].Address = Return_Window_Adress(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)");
    window[1].Address = Return_Window_Adress(L"Test_Window!");

    cout << "\n" << window[0].Address << "\n"
        << window[1].Address << "\n";

    while(System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();

    return 0;
}
