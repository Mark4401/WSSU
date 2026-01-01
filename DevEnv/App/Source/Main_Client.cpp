#include <Engine.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    // Multi window demo
    Monitor_Information();

    CLIENT Primary = { };

    Primary.Width = 400;
    Primary.Height = 400;
    Primary.Title = L"Hello World! - 12/17/2025";
    Primary.Active_black_title_bar = true;

    int32_s Primary_Window = Create_Client_Window(Primary);

    CLIENT Secondary = { };

    Secondary.Width = 400;
    Secondary.Height = 1400;
    Secondary.Title = L"Hello World! - 12/17/2025__";
    Secondary.Active_black_title_bar = true;

    int32_s Secondary_Window = Create_Client_Window(Secondary);

    CLIENT theird = { };

    theird.Width = 1400;
    theird.Height = 600;
    theird.Title = L"Hello World! - 12/17/2025__ KML";
    theird.Active_black_title_bar = true;

    int32_s theird_Window = Create_Client_Window(theird);

    cout << "\nClient created!\n";
    
    bool primary_active = true;
    bool secondary_active = true;
    bool theird_active = true;

    while (theird_active || secondary_active || primary_active)
    {
        if (primary_active)
            primary_active = Queue(Primary_Window, primary_active);

        if (secondary_active)
            secondary_active = Queue(Secondary_Window, secondary_active);

        if (theird_active)
            theird_active = Queue(theird_Window, theird_active);
    }


    cout << "\nClient destroyed!\n";

    Clean_Up();

    return 0;
}
