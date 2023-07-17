#define WIN32_LEAN_AND_MEAN
#include <windows.h>



BOOL WINAPI DllMain(HINSTANCE hinstDll, // handle to DLL module
                    DWORD fdwReason,    // reason for calling function
                    LPVOID lpReserved)  // reserved
{
  switch (fdwReason) {
  case DLL_PROCESS_ATTACH: {
     // wait for 5 seconds 

    MessageBoxA(NULL, "Hello from DLL!", "DLL Message", MB_OK | MB_ICONINFORMATION);

    break;
  }
  case DLL_PROCESS_DETACH: {
    break;
  }
  }

  return TRUE;
}
