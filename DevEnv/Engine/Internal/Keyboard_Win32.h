#ifndef KEYBOARD_WIN32_H
#define KEYBOARD_WIN32_H

#include"Runtime_variables.h"

void  Keyboard_Data(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam);

int16_u Return_Virtual_Code();
int16_u Return_Key_Flags();
int16_u Return_Scan_Code();

#endif // !KEYBOARD_WIN32_H
