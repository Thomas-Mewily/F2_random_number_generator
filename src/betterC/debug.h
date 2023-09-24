#ifndef betterC_debug
#define betterC_debug
#include "betterC.h"

#define current_file __FILE__
#define current_line __LINE__
#define current_func __func__ 
#define current_time __TIME__ 

typedef struct
{
    char* file_name;
    char* func_name;
    int   line_number;
} code_position;

code_position get_code_position(char* file_name, char* func_name, int line_number);

#define GET_CODE_POS   get_code_position((char*)current_file, (char*)current_func, current_line)
#define EMPTY_CODE_POS get_code_position((char*)"", (char*)"", -1)

#define print_debug  { printf("function %s() : %s%s:%i%s\n", current_func, COLOR_DEBUG_DATA, current_file, (int)current_line, COLOR_RESET); }
#define debug        { printf("%sdebug%s at ", COLOR_DEBUG_CATEGORY, COLOR_RESET); print_debug; }

#define exit_program(error_code) { trigger_debugger(true); exit(error_code);}

#define crash_silent { printf("%scrash%s : \n", COLOR_DEBUG_CATEGORY, COLOR_RESET); print_debug; exit_program(EXIT_FAILURE); }
#define crash(msg)   { printf("%scrash%s : %s\n", COLOR_DEBUG_CATEGORY, COLOR_RESET, msg); print_debug; exit_program(EXIT_FAILURE); }

#define check(condTrue) if(!(condTrue)) { crash(#condTrue); }
#define check_msg(msg, condTrue) if(!(condTrue)) { crash(COLOR_DEBUG_ERROR msg COLOR_RESET " : " #condTrue); }

#define todo crash("todo")

#define trigger_debugger(cond) if(cond){ int a = 0; int b = 1; int c = b/a; unused(c); }

#define in_range(val, maxNotIncluded) (val < maxNotIncluded)
#define in_interval(val, minIncluded, maxExcluded) (val >= minIncluded && val < maxNotIncluded)

#define check_range(val, maxNotIncluded) check(in_range(val, maxNotIncluded))
#define check_interval(val, minIncluded, maxExcluded) check(in_interval(val, minIncluded, maxNotIncluded))

#endif
