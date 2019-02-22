#include <windows.h>
#include <tchar.h>
#include <strsafe.h>


#define macroToString(macro) expandMacro(macro)
#define expandMacro(macro) TEXT(#macro)

void msg(LPCTSTR calledFunction) {

   TCHAR buf[500];

   StringCbPrintf(buf, 500,
       TEXT("Called function: %s\nSize of TCHAR = %d\nMessageBox = %s"), 
       calledFunction,
       sizeof(TCHAR),
       macroToString(MessageBox));

   MessageBox(NULL,
       buf, 
       GetCommandLine(),
       0
   );

}


WINAPI _tWinMain (
     HINSTANCE hInstance    ,
     HINSTANCE hPrevInstance,
     LPTSTR    lpCmdLine    ,
     int       nShowCmd
) {

  msg(macroToString(_tWinMain));

  return 0;

}
