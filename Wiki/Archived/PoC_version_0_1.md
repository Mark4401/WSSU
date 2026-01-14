# CMAKE overview

Root file:

Contains global variables / presets;

```cmake

set(global_build_dir		"${CMAKE_CURRENT_SOURCE_DIR}/Builds")
set(external_dependencies	"${CMAKE_CURRENT_SOURCE_DIR}/Dependencies")

...

cfg_path_type(Client_Path		"${global_build_dir}/Client")
cfg_path_type(Library_Path		"${global_build_dir}/Engine")

```

`cfg_path_type` function comes from /cmake folder - [config-type](../cmake/Build_Destination_type.cmake).
contain technical information on its use. U can go to my [Cmake template project](https://github.com/Mark4401/Cmake-Starter-template).
With far more in-depth description to learn more.


## Client Application & library back-end

Name -> `Altera_Odyssey` given its the game name.
My own SDK library (lack of an better name) -> `AL_OD_Runtime` containing both static & dynamic library types.

The current version being **0.2.1**. it being a Proof of concept for now. 


# Code Documentation

## Application source files

- Main_Client.cpp

```cpp

#include <iostream>
#include<Engine.h>

using namespace std;


int main(int argv, char* argc[])
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
```