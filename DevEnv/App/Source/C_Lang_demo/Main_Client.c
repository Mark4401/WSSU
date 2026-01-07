#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<WSSU/WSSU.h>

int main(int argv, char* argc[])
//int WinMain()
{
	printf("DLL/LIB - Call From C! :P");

    Default_Systen_info();

    Init_Window(L"One", 2000, 1460, true, CENTER, DEAFULT);

    Process_Lists();

    while (System_Queue())
    {

    }

    Retrieve_All_Active_Window_instances();
    

	return 0;
}
