#include "betterC.h"

code_position get_code_position(char* file_name, char* func_name, int line_number)
{
    code_position c;
    c.file_name = file_name;
    c.func_name = func_name;
    c.line_number = line_number;
    return c;
}