//
//   cl .\EnumServiceStatusEx.c advapi32.lib
//

#include <windows.h>
#include <stdio.h>

int main() {

   SC_HANDLE scMgr = OpenSCManager(
      NULL,
      SERVICES_ACTIVE_DATABASE,
      SC_MANAGER_ALL_ACCESS
   );

   if (scMgr) {

      DWORD myPID = GetCurrentProcessId();

      DWORD additionalNeeded;
      DWORD cnt = 0;
      DWORD resume       = 0;

      ENUM_SERVICE_STATUS_PROCESS  services[1024];

      if (
         EnumServicesStatusEx(
            scMgr,
            SC_ENUM_PROCESS_INFO,        // Influences 5th parameter!
            SERVICE_WIN32_OWN_PROCESS,   // Service type (SERVICE_WIN32_OWN_PROCESS = services that run in their own process)
            SERVICE_STATE_ALL,           // Service state (ALL = active and inactive ones)
            services,
            sizeof(services),
           &additionalNeeded,
           &cnt,
           &resume,
            NULL                         // Group name
        ))
       {

          for (DWORD i = 0; i < cnt; i++) {

            printf("%-50s %5d\n", services[i].lpServiceName, services[i].ServiceStatusProcess.dwProcessId);

          }
       }
       CloseServiceHandle(scMgr);
   }
   else {
      printf("Could not open service manager.\n");
   }
}
