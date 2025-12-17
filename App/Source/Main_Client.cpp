#include <iostream>
#include<Engine.h>

using namespace std;


int main(int argv, char* argc[])
//int WinMain()
{

	CLIENT* Primary = new CLIENT{ };

	Primary->Width = 1200;
	Primary->Height = 800;
	Primary->Title = L"Hello World! - 12/17/2025";
	Primary->Active_black_title_bar = true;

	Create_Client_Window(Primary);

	cout << "\Client created!\n";

	while (Queue(Primary))
	{

	}

	cout << "\nClient destroyed!\n";

	Destroy_Client_Window(Primary);

	return 0;
}