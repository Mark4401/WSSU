#include <Engine.h>
#include<iostream>
#include "3_Primary_WIndows.h"

using namespace std;

void Demo_Windows()
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

	while (Queue(Primary_Window, true))
	{

	}


	cout << "\nClient destroyed!\n";

	Clean_Up();
}
