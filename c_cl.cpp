/**
 * @file    c_cl.cpp
 *       
 * @author  John Glatts
 * @brief   CPP library to compile and then run C\CPP programs in one-go!  
 * @version 0.1
 * @date    2023-03-20
 * 
 * @copyright Copyright (c) 2023
 */
#include "c_cl.h"
#include <cstdlib>
#include <windows.h>
#include <cassert>
#include <stdio.h>
#include <string.h>
#include <tchar.h>

/**
 * @brief Construct a new CL::CL object
 * 
 * @param count 
 * @param vec 
 */
CL::CL(int count, char* vec[]):
    argc{count} {
    assert(count <= MAX_ARGS);
    for (int i = 0; i < count; i++) {
        argv[i] = vec[i];
    }
}

/**
 * @brief Begin the compile and run process
 *        First step is to launch a process and compile the code 
 *        Second setep is to run the newly compiled code
 * 
 * @return true if process creation is sucessfull 
 * @return false if process creation is not sucessfull 
 */
bool CL::run() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    // Compile the source files in argv
    init_process_info(&si, &pi);
    printf("\n\nCompiling Source Files...\n\n");
    if(!create_process_cl(&si, &pi)) {
        printf("CreateProcess failed (%d)\n", GetLastError());
        return false;
    }    
    WaitForSingleObject(pi.hProcess, INFINITE);
    
    // Run the compiled code from above 
    printf("\n\nRunning %s\n\n", argv[1]);
    init_process_info(&si, &pi);
    if(!create_process_run(&si, &pi)) {
        printf("CreateProcess failed (%d)\n", GetLastError());
        return false;
    }    
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread );

    return true;
}

/**
 * @brief Init the windows process structures
 * 
 * @param si pointer to STARTUPINFO object 
 * @param pi pointer to PROCESS_INFORMATION object 
 */
void CL::init_process_info(STARTUPINFO* si, PROCESS_INFORMATION* pi) {
    ZeroMemory(si, sizeof(*si));
    si->cb = sizeof(si);
    ZeroMemory(pi, sizeof(*pi));    
}

/**
 * @brief 
 * 
 * @param si pointer to STARTUPINFO object 
 * @param pi pointer to PROCESS_INFORMATION object 
 * @return true if process creation is sucessfull 
 * @return false if process creation is not sucessfull 
 */
bool CL::create_process_cl(STARTUPINFO* si, PROCESS_INFORMATION* pi) {
    char* cl_path = "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.34.31933\\bin\\Hostx86\\x86\\cl.exe";
    
    // convert array of strings to single string
    char all_paths[1024];
    int i = 0;
    for (int count = 1; count < argc; count++) {
        all_paths[i++] = ' ';
        for (int j = 0; j < strlen(argv[count]); j++, i++) {
            all_paths[i] = argv[count][j];
        }
    }
    all_paths[i] = '\0';

    return CreateProcess(
            cl_path,        // Module name
            all_paths,      // Module arguments
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            si,             // Pointer to STARTUPINFO structure
            pi              // Pointer to PROCESS_INFORMATOIN structure 
    );
}   

/**
 * @brief Create the process to run the new exe
 * 
 * @param si pointer to STARTUPINFO object 
 * @param pi pointer to PROCESS_INFORMATION object  
 * @return true if process creation is sucessfull 
 * @return false if process creation is not sucessfull 
 */
bool CL::create_process_run(STARTUPINFO* si, PROCESS_INFORMATION* pi) {
    char path[1024];
    int i;

    // remove the . extensions
    // could be prolly use a strstr to find first occurence
    // then write '\0' there to eet rid of it 
    for (i = 0; i < strlen(argv[1]) && argv[1][i] != '.'; i++) {
        path[i] = argv[1][i];
    }
    path[i] = '\0';

    return CreateProcess(
            NULL,           // Module name
            path,           // Module arguments
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            si,             // Pointer to STARTUPINFO structure
            pi              // Pointer to PROCESS_INFORMATOIN structure 
    );
}

/**
 * @brief Driver Code
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Error\nUsage:  c_cl source_file.c");
        return 1;
    }
    CL cl(argc, argv);
    cl.run();
    return 0;
}


