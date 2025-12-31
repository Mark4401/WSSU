#include <Engine.h>
#include <iostream>

using namespace std;

int main(int argv, char* argc[])
{
    Monitor_Information();

    CLIENT* Primary = new CLIENT{ };

    Primary->Width = 700;
    Primary->Height = 1080;
    Primary->Title = L"Hello World! - 12/17/2025";
    Primary->Active_black_title_bar = true;

    Create_Client_Window(Primary);

    cout << "\nClient created!\n";

    while (Queue(Primary))
    {

    }

    cout << "\nClient destroyed!\n";

    Destroy_Client_Window(Primary);

    return 0;
}
