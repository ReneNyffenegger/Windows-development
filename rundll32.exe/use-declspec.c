#include <windows.h>

extern __declspec (dllexport) void CALLBACK func (
   HWND      hwnd,         // handle to owner window
   HINSTANCE hinst,        // instance handle for the DLL
   LPTSTR    lpCmdLine,    // string the DLL will parse
   int       nCmdShow      // show state
)
{
   MessageBox(0, lpCmdLine, "func", 0);
}
