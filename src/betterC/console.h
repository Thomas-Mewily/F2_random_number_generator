#ifndef betterC_console
#define betterC_console
#include "betterC.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_FOREGROUND_RESET     "\x1b[37m"
#define COLOR_BACKGROUND_RESET     "\x1b[40m"

#define COLOR_FOREGROUND_BLACK     "\x1b[30m"
#define COLOR_FOREGROUND_RED       "\x1b[31m"
#define COLOR_FOREGROUND_GREEN     "\x1b[32m"
#define COLOR_FOREGROUND_YELLOW    "\x1b[33m"
#define COLOR_FOREGROUND_BLUE      "\x1b[34m"
#define COLOR_FOREGROUND_MAGENTA   "\x1b[35m"
#define COLOR_FOREGROUND_CYAN      "\x1b[36m"
#define COLOR_FOREGROUND_WHITE     "\x1b[37m"
#define COLOR_FOREGROUND_GREY      "\x1b[90m"

#define COLOR_DEBUG_ERROR          COLOR_FOREGROUND_RED
#define COLOR_DEBUG_CATEGORY       COLOR_FOREGROUND_MAGENTA
#define COLOR_DEBUG_DATA           COLOR_FOREGROUND_GREEN

#define COLOR_BACKGROUND_BLACK     "\x1b[40m"
#define COLOR_BACKGROUND_RED       "\x1b[41m"
#define COLOR_BACKGROUND_GREEN     "\x1b[42m"
#define COLOR_BACKGROUND_YELLOW    "\x1b[43m"
#define COLOR_BACKGROUND_BLUE      "\x1b[44m"
#define COLOR_BACKGROUND_MAGENTA   "\x1b[45m"
#define COLOR_BACKGROUND_CYAN      "\x1b[46m"
#define COLOR_BACKGROUND_WHITE     "\x1b[47m"
#define COLOR_BACKGROUND_GREY      "\x1b[100m"

#define print_size(type) { printf("%ssizeof%s(%-6s) = %zu\n", COLOR_FOREGROUND_MAGENTA, COLOR_FOREGROUND_WHITE, #type, sizeof(type)); }
#define new_line() { printf("\n"); }
void printf_title(char* title);

#endif