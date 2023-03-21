/**
 * @file    c_cl.h

 * @author  John Glatts
 * @brief   CPP library to compile and then run C\CPP programs in one-go!  
 * @version 0.1
 * @date    2023-03-20
 * 
 * @copyright Copyright (c) 2023
 */
#ifndef __C__CL__H__
#define __C__CL__H__

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

/**
 * @brief Library definitons
 */
#define MAX_ARGS 10

/**
 * @brief CL structure to perfom the compile\run operatios
 */
struct CL {
public:    
    CL(int, char**);
    bool run();
private:
    int argc;
    char* argv[MAX_ARGS];
    void init_process_info(STARTUPINFO*, PROCESS_INFORMATION*);
    bool create_process_cl(STARTUPINFO*, PROCESS_INFORMATION*);
    bool create_process_run(STARTUPINFO*, PROCESS_INFORMATION*);
};

#endif