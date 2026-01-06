#include <WSSU.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    cout << "\ncalled from an C++ file! :p\n\n";

    Default_Systen_info();

    Init_Window(L"One", 1500, 1900, true);

    Process_Lists();

    while (Events())
    {
        //return true;
    };

    return 0;
}
