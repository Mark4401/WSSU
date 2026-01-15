#include<WSML/WSML.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Init_Program(DPI_AWARENESS_FALSE);
    
    Extend_Outer_Window_Borders(400, 300, 200, 100);
    
    Init_Window(L"Test_Window! ;P | WSML i.e (WIndowing & State Management Library)",
        1920, 1080, true, CENTER);  
    
    Process_Lists();

    while(System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();

    return 0;
}

/*
well my current inplementation gives an function to the user with 4 int vals. and within the function it just passes the
*/