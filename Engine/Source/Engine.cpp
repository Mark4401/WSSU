#include "Engine.h"
#include"Runtime_variables.h"
#include"Win32_properties.h"

using namespace std;

bool Actively_running = true;

//static CLIENT* CLient_Adds_Reference = nullptr;

static WIN32_CLIENT* Main_Window_Adds_Reference = nullptr;

int Create_Client_Window(CLIENT* Client_reference)
{
    WIN32_CLIENT* Temp_ref = Create_Window_Properties(
        Client_reference->Height, Client_reference->Width,
        Client_reference->Title, Client_reference->Active_black_title_bar
        );

    Main_Window_Adds_Reference = Temp_ref;

    return 10;
}


bool Queue(CLIENT* Client_reference)
{
    if ( !Client_reference )
    {
        Win32_Event_Queue(false);
        Delete_Win32_Window_Porperties(Main_Window_Adds_Reference);
        
        cout << "HI";
        return false;
    }

    Win32_Event_Queue(true);

    return true;
}


void Destroy_Client_Window(CLIENT* Client_reference)
{
    if (!Client_reference)
    {
        return;
    }

    cout << "\nWin32 Window properties & memory deleted --> User Event!\n";

    delete Client_reference;
}

