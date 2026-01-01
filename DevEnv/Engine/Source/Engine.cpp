#include "Engine.h"
#include"Runtime_variables.h"
#include"Win32_properties.h"
#include"Win32_Phys_Monitor_Properties.h"

using namespace std;

void Monitor_Information()
{
    Start_Up_Hardware_info();
}

#define MAXIMUM_TABLE_SIZE 10

static WIN32_CLIENT*    Client_Table_Registry[MAXIMUM_TABLE_SIZE]  = { };
static int32_s          Client_Table_index                         = 0;

int32_s Create_Client_Window(CLIENT Client_reference)
{
    WIN32_CLIENT* Client_Window = Create_Window_Properties(
            Client_reference.Height,
            Client_reference.Width,
        Client_reference.Title, 
        Client_reference.Active_black_title_bar
        );

    Client_Table_Registry[Client_Table_index] = Client_Window;

    return Client_Table_index++;
}



bool Queue(int32_s Client_Index, bool Active)
{

    if (Client_Index < 0 || Client_Index >= Client_Table_index) { return false; };

    WIN32_CLIENT& Client_Ref = *Client_Table_Registry[Client_Index];
    
    Active = Win32_Event_Queue(Active, Client_Ref);;
    
    if(!Active)
    {
        Delete_Win32_Window_Porperties(Client_Ref);

        Client_Table_Registry[Client_Table_index] = nullptr;
    }

    return Active;
}


void Clean_Up()
{
    cout << "\nRuntime properties & memory deleted --> System Event!\n";
}

