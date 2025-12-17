#include <iostream>
#include<Engine.h>

using namespace std;


int main(int argv, char* argc[])
{

	CLIENT* Primary = new CLIENT{ };

	Primary->Width = 800;
	Primary->Height = 800;
	Primary->Title = L"Hello World!";
	Primary->Active_black_title_bar = true;

	Create_Client_Window(Primary);

	cout << "\nClient created!\n";

	while (Queue(Primary))
	{
		if ()
		{
			cout << "\nQueue Active!\n";

			;
		}
		cout << "\nnQueuw Shutdown!\n";

		return true;
	}

	cout << "Client destroyed!\n";

	Destroy_Client_Window(Primary);

	return 0;
}