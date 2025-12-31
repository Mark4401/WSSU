#include "Engine.h"
#include"Runtime_variables.h"
#include"Win32_properties.h"
#include"Win32_Phys_Monitor_Properties.h"

using namespace std;

bool Actively_running = true;

static WIN32_CLIENT* Main_Window_Adds_Reference = nullptr;

void Monitor_Information()
{
    Start_Up_Hardware_info();
}

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
   if ( !Client_reference || Main_Window_Adds_Reference->Currently_Running == false)
    {
        Win32_Event_Queue(false);
        Delete_Win32_Window_Porperties(Main_Window_Adds_Reference);
        
        //cout << "\nHI\n";
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

    cout << "\nRuntime properties & memory deleted --> System Event!\n";

    delete Client_reference;
}

