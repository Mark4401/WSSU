#include<WSSU/WSSU.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Default_Systen_info();

    Init_Window(L"One", 2000, 1460, true, CENTER, DEAFULT);

    Process_Lists();

    while (System_Queue())
    {
        //return true;
    };

    //Retrieve_All_Active_Window_instances();

    return 0;
}
