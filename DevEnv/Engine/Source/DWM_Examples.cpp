#include "test_or_examples/DWM_Examples.h"

using namespace std;

int LEFTEXTENDWIDTH = 8, RIGHTEXTENDWIDTH = 8, BOTTOMEXTENDWIDTH = 50, TOPEXTENDWIDTH = 40, BIT_COUNT = 32, TMT_CAPTIONFONT = 802;

// Hit test the frame for resizing and moving.
static LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// Get the point coordinates for the hit test.
	POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	// Get the window rectangle.
	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	// Get the frame rectangle, adjusted for the style without a caption.
	RECT rcFrame = { 0 };
	AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

	// Determine if the hit test is for resizing. Default middle (1,1).
	USHORT uRow = 1;
	USHORT uCol = 1;
	bool fOnResizeBorder = false;

	// Determine if the point is at the top or bottom of the window.
	if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + TOPEXTENDWIDTH)
	{
		fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
		uRow = 0;
	}
	else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BOTTOMEXTENDWIDTH)
	{
		uRow = 2;
	}

	// Determine if the point is at the left or right of the window.
	if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + LEFTEXTENDWIDTH)
	{
		uCol = 0; // left side
	}
	else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - RIGHTEXTENDWIDTH)
	{
		uCol = 2; // right side
	}

	// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
	LRESULT hitTests[3][3] =
	{
		{ HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
		{ HTLEFT,       HTNOWHERE,     HTRIGHT },
		{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
	};

	return hitTests[uRow][uCol];
}
// Paint the title on the custom frame.
void PaintCustomCaption(HWND hWnd, HDC hdc)
{
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
	if (hTheme)
	{
		HDC hdcPaint = CreateCompatibleDC(hdc);
		if (hdcPaint)
		{

			int cx = (rcClient.right - rcClient.left);
			int cy = (rcClient.bottom - rcClient.top);

			// Define the BITMAPINFO structure used to draw text.
			// Note that biHeight is negative. This is done because
			// DrawThemeTextEx() needs the bitmap to be in top-to-bottom
			// order.
			BITMAPINFO dib = { };
			dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			dib.bmiHeader.biWidth = cx;
			dib.bmiHeader.biHeight = -cy;
			dib.bmiHeader.biPlanes = 1;
			dib.bmiHeader.biBitCount = BIT_COUNT;
			dib.bmiHeader.biCompression = BI_RGB;

			HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, NULL);
			if (hbm)
			{
				HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);

				// Setup the theme drawing options.
				DTTOPTS DttOpts = { sizeof(DTTOPTS) };
				DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
				DttOpts.iGlowSize = 15;

				// Select a font.
				LOGFONTW lgFont = { };
				HFONT hFontOld = NULL;
				if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
				{
					HFONT hFont = CreateFontIndirect(&lgFont);
					hFontOld = (HFONT)SelectObject(hdcPaint, hFont);
				}
				
				Wide_Char szTitle = L"Bit_Test";
				// Draw the title.
				RECT rcPaint = rcClient;
				rcPaint.top += 8;
				rcPaint.right -= 125;
				rcPaint.left += 8;
				rcPaint.bottom = 50;
				DrawThemeTextEx(hTheme,
					hdcPaint,
					0, 0,
					szTitle,
					-1,
					DT_LEFT | DT_WORD_ELLIPSIS,
					&rcPaint,
					&DttOpts);

				// Blit text to the frame.
				BitBlt(hdc, 0, 0, cx, cy, hdcPaint, 0, 0, SRCCOPY);

				SelectObject(hdcPaint, hbmOld);
				if (hFontOld)
				{
					SelectObject(hdcPaint, hFontOld);
				}
				DeleteObject(hbm);
			}
			DeleteDC(hdcPaint);
		}
		CloseThemeData(hTheme);
	}
}
static LRESULT Custom_Caption_Proc_1(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam, bool* Pointer_function_call_to_DWP)
{

	LRESULT L_Rssult = 0;
	HRESULT H_Result = S_OK;
	bool p_f_Call_DWP = true;

	p_f_Call_DWP = !DwmDefWindowProc(Window, Message, WParam, LParam, &L_Rssult);

	switch (Message)
	{
		case WM_CREATE:
		{
			RECT Rect_Client_Area;

			GetWindowRect(Window, &Rect_Client_Area);
			
			int Rect_CA_Width = Rect_Client_Area.right - Rect_Client_Area.left;
			int Rect_CA_Height = Rect_Client_Area.bottom - Rect_Client_Area.top;

			SetWindowPos(Window, NULL, Rect_Client_Area.left, 
				Rect_Client_Area.top, Rect_CA_Width, Rect_CA_Height, 
				SWP_FRAMECHANGED);
		
			p_f_Call_DWP = true;

			L_Rssult = 0;
			
			break;
		}
		case WM_ACTIVATE:
		{
			MARGINS Dwm_marggins;

			Dwm_marggins.cxLeftWidth = LEFTEXTENDWIDTH;      // 8
			Dwm_marggins.cxRightWidth = RIGHTEXTENDWIDTH;    // 8
			Dwm_marggins.cyBottomHeight = BOTTOMEXTENDWIDTH; // 20
			Dwm_marggins.cyTopHeight = TOPEXTENDWIDTH;       // 27

			H_Result = DwmExtendFrameIntoClientArea(Window, &Dwm_marggins);

			if ( !SUCCEEDED ( H_Result ) )
			{
				cerr << GetLastError() << "\n";
				exit(EXIT_FAILURE);
			}

			p_f_Call_DWP = true;

			L_Rssult = 0;

			break;
		}
		case WM_PAINT:
		{
			// Window painting at resize 
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(Window, &ps);

			// All painting occurs here, between BeginPaint and EndPaint.

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(Window, &ps);

			p_f_Call_DWP = true;

			L_Rssult = 0;

			break;
		}
		case WM_NCCALCSIZE:
		{
			if ( WParam == TRUE )
			{
				// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
				NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(LParam);

				pncsp->rgrc[0].left = pncsp->rgrc[0].left + 0;
				pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
				pncsp->rgrc[0].right = pncsp->rgrc[0].right - 0;
				pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;

				L_Rssult = 0;

				// No need to pass the message on to the DefWindowProc.
				p_f_Call_DWP = false;
			}
			break;
		}
		case WM_NCHITTEST:
		{
			if( L_Rssult == 0 )
			{
				L_Rssult = HitTestNCA(Window, WParam, LParam);

				if (L_Rssult != HTNOWHERE)
				{
					p_f_Call_DWP = false;
				}
			}
			break;
		}
	}

	*Pointer_function_call_to_DWP = p_f_Call_DWP;

	return L_Rssult;
}

static LRESULT Application_Window_Proc_1(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	int				Window_Massage_Id, Window_Massage_Event;
	PAINTSTRUCT		Paint_Source;
	HDC				Handle_Device_context;
	LRESULT			Long_Rssult;
	HRESULT			Handle_Result;

	switch (Message)
	{
		case WM_CREATE: 
		{}
		case WM_COMMAND:
		{
			Window_Massage_Id = LOWORD(WParam);
			Window_Massage_Event = HIWORD(WParam);

			switch (Window_Massage_Id)
			{
				default:
					return DefWindowProc(Window, Message, WParam, LParam);
			}
			break;
		}
		case WM_PAINT:
		{
			Handle_Device_context = BeginPaint(Window, &Paint_Source);
			PaintCustomCaption(Window, Handle_Device_context);

			// Add any drawing code here...

			EndPaint(Window, &Paint_Source);
		}
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(Window, Message, WParam, LParam);
	}
	return 0;
}


LRESULT DWM_Exmaple_1(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
	bool f_Call_DW_P = true;
	BOOL f_Dwm_Enabled = FALSE;
	LRESULT l_Result = 0;
	HRESULT Handle_Result = S_OK;

	Handle_Result = DwmIsCompositionEnabled(&f_Dwm_Enabled);

	if (SUCCEEDED(Handle_Result))
	{
		l_Result = Custom_Caption_Proc_1(Window, Message, WParam, LParam, &f_Call_DW_P);
	}

	if (f_Call_DW_P)
	{
		l_Result = Application_Window_Proc_1(Window, Message, WParam, LParam);
	}

	return l_Result;
}


