#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <path> <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *path = argv[1];
    
    char fullpath[MAX_PATH];
    if (GetFullPathNameA(path, MAX_PATH, fullpath, NULL) == 0) {
        printf("Error: could not get full path of %s\n", path);
        return EXIT_FAILURE;
    }

    int target = atoi(argv[2]);
    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, target);
    if (handle == NULL) {
        printf("Error: could not open process %d\n", target);
        return EXIT_FAILURE;
    }

    HMODULE kernel32 = GetModuleHandleA("kernel32.dll");
    if (kernel32 == NULL) {
        printf("Error: could not get handle to kernel32.dll\n");
        return EXIT_FAILURE;
    }

    void *loadlibrarya = GetProcAddress(kernel32, "LoadLibraryA");
    if (loadlibrarya == NULL) {
        printf("Error: could not get address of LoadLibraryA\n");
        return EXIT_FAILURE;
    }

    size_t size = strlen(fullpath) + 1;
    void *remote =
        VirtualAllocEx(handle, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (remote == NULL) {
        printf("Error: could not allocate memory in target process\n");
        return EXIT_FAILURE;
    }

    if (WriteProcessMemory(handle, remote, fullpath, size, NULL) == 0) {
        printf("Error: could not write to target process\n");
        return EXIT_FAILURE;
    }

    HANDLE thread =
        CreateRemoteThread(handle, NULL, 0, loadlibrarya, remote, 0, NULL);
    if (thread == NULL) {
        printf("Error: could not create remote thread\n");
        return EXIT_FAILURE;
    }

    // print success message
    printf("Successfully loaded %s into process %d\n", argv[1], target);
    return EXIT_SUCCESS;
}
