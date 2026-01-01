#include <Engine.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    Monitor_Information();

    CLIENT Primary = { };

    Primary.Width = 400;
    Primary.Height = 400;
    Primary.Title = L"Hello World! - 12/17/2025";
    Primary.Active_black_title_bar = true;
    Primary.Active_state = true;

    int32_s Primary_Window = Create_Client_Window(Primary);

    CLIENT Secondary = { };

    Secondary.Width = 400;
    Secondary.Height = 1400;
    Secondary.Title = L"Hello World! - 12/17/2025";
    Secondary.Active_black_title_bar = true;
    Secondary.Active_state = true;

    int32_s Secondary_Window = Create_Client_Window(Secondary);

    cout << "\nClient created!\n";

    while (Queue(Primary_Window, Primary.Active_state) && Queue(Secondary_Window, Secondary.Active_state))
    {

    }

    cout << "\nClient destroyed!\n";

    Clean_Up();

    return 0;
}
