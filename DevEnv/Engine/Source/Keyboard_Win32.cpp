#include "Keyboard_Win32.h"

#define BIT_LENGTH_8    0xFF
#define BIT_LENGTH_16   0xFFFF

int16_u Virtual_Key_Code = 0;
int16_u Key_Flags = 0;
int16_u Scan_Code = 0;
int16_u Repeat_Count = 0;
bool Key_extended_Data = false;
bool Key_Pressed = false;
bool Key_Released = false;

using namespace std;

void Keyboard_Data(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	Virtual_Key_Code = static_cast<int16_u>(WParam);
	Key_Flags = static_cast<int16_u>((LParam >> 16) & BIT_LENGTH_16);
	Scan_Code = static_cast<int8_u>((Key_Flags)&BIT_LENGTH_8);

	Key_extended_Data = (Key_Flags & KF_EXTENDED) == KF_EXTENDED;

	if (Key_extended_Data) { Scan_Code = MAKEWORD(Scan_Code, 0xE0); };

	Repeat_Count = static_cast<int16_u>(LParam & BIT_LENGTH_16);

	Key_Pressed = (Key_Flags & KF_REPEAT) == KF_REPEAT;
	Key_Released = (Key_Flags & KF_UP) == KF_UP;

	switch (Virtual_Key_Code)
	{
	case VK_SHIFT:
	case VK_CONTROL:
	case VK_MENU:
		Virtual_Key_Code = LOWORD(MapVirtualKeyW(Scan_Code, MAPVK_VSC_TO_VK_EX));
		break;
	}
}

int16_u Return_Virtual_Code() { return Virtual_Key_Code; }
int16_u Return_Key_Flags() { return Key_Flags; }
int16_u Return_Scan_Code() { return Scan_Code; }