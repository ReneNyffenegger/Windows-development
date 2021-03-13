#include <windows.h>
#include <winternl.h>

void* get_gs_60();

HANDLE stdOut;


void* get_peb_address() {

   typedef NTSTATUS (NTAPI *ptrNtQueryInformationProcess)
   (
       HANDLE           ProcessHandle,
       PROCESSINFOCLASS ProcessInformationClass,
       PVOID            ProcessInformation,
       ULONG            ProcessInformationLength,
       PULONG           ReturnLength
    );

    ptrNtQueryInformationProcess qry = (ptrNtQueryInformationProcess) GetProcAddress(
       GetModuleHandleA("ntdll.dll"),
      "NtQueryInformationProcess"
    );

    HANDLE proc = GetCurrentProcess();
    PROCESS_BASIC_INFORMATION pbi;

    qry(proc, 0, &pbi, sizeof(pbi), NULL);
    return pbi.PebBaseAddress;
}


void printAddress(const char* text, void* addr) {

  char buf[200];

  int len = wsprintfA(buf, "%-20s: %p\n", text, addr);

  DWORD charsWritten;
  WriteConsoleA(stdOut, buf, len, &charsWritten, 0);

}


int __stdcall entryPoint(void* first_arg) {

    stdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    void* gs_60 = get_gs_60();
    void* PEB   = get_peb_address();

    printAddress("First argument", first_arg);
    printAddress("gs:[60h]"      , (void*) gs_60);
    printAddress("PEB"           , PEB);

    return 42;
}
