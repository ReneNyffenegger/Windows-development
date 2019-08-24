// cl /LD dll.c user32.lib /Fesome.dll /link /def:dll.def

#include <windows.h>


void CALLBACK func_1 (HWND hWnd, HINSTANCE hInst, LPSTR  lpszCmdLine, int nCmdShow) {
  MessageBoxA(0, lpszCmdLine, "func_1", 0);
}

void CALLBACK func_1W(HWND hWnd, HINSTANCE hInst, LPWSTR lpszCmdLine, int nCmdShow) {
  MessageBoxW(0, lpszCmdLine, L"func_1W", 0);
}

void CALLBACK func_2 (HWND hWnd, HINSTANCE hInst, LPSTR  lpszCmdLine, int nCmdShow) {
  MessageBoxA(0, lpszCmdLine, "func_2", 0);
}
