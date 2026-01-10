#include<WSSU/WSSU.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Init_Program(DPI_AWARENESS_FALSE);

    Init_Window(L"Test_Window! ;P", 3100,1900, true, POS_TOP_LEFT);
    //Init_Window(L"Test_Window! ;P", 400, 1800, false, CENTER);
    //Init_Window(L"Test_Window! ;P", 400, 1800, true , CENTER);

    Process_Lists();

    while (System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();

    return 0;
}
