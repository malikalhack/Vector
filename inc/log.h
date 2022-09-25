/**
* @file    log.h
* @version 1.0.0
* @authors Anton Chernov
* @date    25/09/2022
*/

#ifndef LOG_H
#define LOG_H
/****************************** Included files ********************************/
#include <stdio.h>
#include <assert.h>
/******************************** Definition **********************************/
#define warning_print(fmt, ...) {\
        fprintf(\
            stdout,\
            "[WARNING] " fmt " in %s, Line %i\n",\
            __VA_ARGS__,\
            __FILE__,\
            __LINE__\
        );\
        fflush(stdout);\
    }
/*----------------------------------------------------------------------------*/
#define error_print(fmt, ...) {\
        fprintf(\
            stdout,\
            "[ERROR] " fmt " in %s, Line %i\n",\
            __VA_ARGS__,\
            __FILE__,\
            __LINE__\
        );\
        fflush(stdout);\
        assert(0);\
    }
/******************************************************************************/
#endif
