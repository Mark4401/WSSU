#include<WSML/WSML.h>
#include <iostream>
#include"cuda_functions.h"

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";


    //CUDA_demo();

    Init_Program(DPI_AWARENESS_FALSE, DISABLE_DWM_EDIT);

    Init_Window(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)",
        1280, 720, true, CENTER_RIGHT);

    Process_Lists();

    Window window[1];

    window[0].Address = Return_Window_Adress(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)");

    cout << "\n\nTest_Window! ;P | WSML i.e (WIndowing & State Management Library) | Window Address: " 
         << window[0].Address << "\n";


    while (System_Queue())
    {
        //return true;
    };

    //Cuda_call_from_lib();

    cuda_test_func();

    return 0;
}

// Telemetry