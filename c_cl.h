/**
 * @file    c_cl.h

 * @author  John Glatts
 * @brief   CPP library to compile and then run C\CPP programs in one-go!  
 *          CPP ver
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
#define PROCESS_FN_PARAMS(mod_name, mod_args, flags, si_ptr, pi_ptr)  \
        mod_name,      \
        mod_args,      \
        NULL,          \
        NULL,          \
        FALSE,         \
        flags,         \
        NULL,          \
        NULL,          \
        si_ptr,        \
        pi_ptr         

/**
 * @brief CL structure to perfom the compile\run operatios
 */
struct CL {
public:    
    CL(int, char**);
    bool run(void);
private:
    int argc;
    char* argv[MAX_ARGS];
    char* get_msvc_path(void);
    void init_process_info(STARTUPINFO*, PROCESS_INFORMATION*);
    bool create_process_cl(STARTUPINFO*, PROCESS_INFORMATION*);
    bool create_process_run(STARTUPINFO*, PROCESS_INFORMATION*);
};

#endif