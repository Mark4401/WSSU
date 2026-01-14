# WSML - Introduction

## Project Overview
**WSML (Windowing & State Management Library)** is an lightweight low level library inspired by libraries such as [Raylib](https://www.raylib.com/) and [GLFW](https://www.glfw.org/).
Mainly focusing in windows systems using win32. Support for Linux will be at a later point in development but not right now.


The tools/dependencies:
- [Cmake](https://cmake.org/)
- [Visual Studio 2026 - Community Edition](https://visualstudio.microsoft.com/free-developer-offers/)   
- [Win32](https://learn.microsoft.com/en-us/windows/win32/desktop-app-technologies) Sections:
	- [Desktop app user interface](https://learn.microsoft.com/en-us/windows/win32/desktop-app-technologies)
	- [Graphics and gaming](https://learn.microsoft.com/en-us/windows/win32/graphics-and-multimedia)
- **Git** and **Github**. Hope if u are reading this U are familiar With both.If not then [Freecodecamp - YouTube Channel](https://www.youtube.com/freecodecamp)  
has great resources for both. 

### **Design & Structure Summary**

**Language/s**
- **C and C++ 17/23 standards**:
	- **Why?** Well `C` gives me the ability of cross-compatibility between other library if I implement it correctly.
	`C++` on the other hand gives me quality of life tools that C just doesn't have. 	 
- **Lua**: I have heard that Lua has been the best choice for scripting. But at later stages in development.
- **Cmake**	  
	u can go to my [Cmake template project](https://github.com/Mark4401/Cmake-Starter-template).
which goes in way more in-depth description of it's design & use-case.
- **Coding Style**
	A blend majorly closers to C. snake_case style & Upper Case_naming:
```cpp
    WSML_API void Retrieve_All_Active_Window_instances();

    WSML_API void Init_Window(const wchar_t* title, int Width, int Height, bool Black_title_bar, enum Window_Position Position);

    WSML_API void Process_Lists();
```

At the moment I haven't yet come to an choice of either designing the main loop to be an **Pulling** or **Callback** system.
I will follow the documentation design of Win32 API with some deviations  


Archived Wiki files are located [Here](Wiki/Archived/v0.2.1_readme.md).

## Get Started 

API [Overview](Wiki/Docs/WSML_Doc_Overview.md)