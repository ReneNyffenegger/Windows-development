#include <windows.h>

typedef void (WINAPI *funcPtr) (
   HWND      hwndParent,
   HINSTANCE unusedHinstance,
   LPCSTR    commandLine,
   int       unusedInt
);

#pragma warning(push)
#pragma warning(disable: 4100)
int WINAPI WinMain(
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR     lpCmdLine,
   int       nShowCmd
) {
#pragma warning(pop)

   HMODULE hShell32 = LoadLibraryA("shell32.dll");

   if (! hShell32) {
      MessageBoxA(0, "Could not load shell32.dll", "Error", MB_OK | MB_ICONSTOP);
      ExitProcess(1);
   }

   funcPtr func = (funcPtr) GetProcAddress(hShell32, "SHHelpShortcuts_RunDLL");

   if (! func) {
      MessageBoxA(0, "Could not get pointer to SHHelpShortcuts_RunDLL", "Error", MB_OK | MB_ICONSTOP);
      ExitProcess(1);
   }

// func(0, 0, "AddPrinter"    , 0);
// func(0, 0, "PrintersFolder", 0);
// func(0, 0, "FontsFolder"   , 0);
   func(0, 0, "Connect"       , 0); // Map Network Drive

// func(0, 0, "Disconnect"    , 0); // Does not seem to work in Windows 10 anymore
}
