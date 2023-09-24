#include "betterC.h"

#ifdef TRACK_MEMORY
nuint memory_nb_malloc_actif = 0;

void* memory_malloc(size_t nb_byte)
{
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (malloc)(nb_byte);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void* memory_calloc(size_t count, size_t size)
{
    size_t nb_byte = count*size;
    if(nb_byte == 0) { return null;}
    void* ptr;
    do
    {
        ptr = (calloc)(count, size);
    }while(ptr == null);
    memory_nb_malloc_actif++;
    return ptr;
}

void memory_free(void* ptr)
{
    if(ptr == null) return;
    memory_nb_malloc_actif--;
    (free)(ptr);
}

void* memory_realloc(void* ptr, size_t nb_byte)
{
    if(ptr == null) { return malloc(nb_byte); }
    if(nb_byte == 0) { free(ptr); }
    return (realloc)(ptr, nb_byte);
}
#endif

void _memory_printf(nuint less, bool is_final)
{
    unused(less);
    unused(is_final);
    #ifdef TRACK_MEMORY
    if(is_final){less = 0;}
    printf("%smemory %s: %s%s%i malloc actif%s\n", COLOR_FOREGROUND_GREEN, COLOR_FOREGROUND_WHITE, (!is_final || memory_nb_malloc_actif == 0) ? COLOR_FOREGROUND_WHITE : COLOR_FOREGROUND_RED, less == 0 ? "": (COLOR_FOREGROUND_YELLOW "~ " COLOR_FOREGROUND_WHITE), (int)(memory_nb_malloc_actif-less), COLOR_RESET);
    #else
    printf("%smemory %s: not tracked\n", COLOR_FOREGROUND_GREEN, COLOR_FOREGROUND_WHITE);
    #endif
}

void memory_printf_rel(nuint less) { _memory_printf(less, false); }
void memory_printf_final() { _memory_printf(0, true); }
void memory_printf() { memory_printf_rel(0); }

void memory_check_0_alloc() 
{
    #ifdef TRACK_MEMORY
    if(memory_nb_malloc_actif != 0)
    {
        memory_printf_final();
        crash("expected 0 allocation");
    }
    #endif
}


nuint memory_get_nb_alloc()
{
    #ifdef TRACK_MEMORY
    return memory_nb_malloc_actif;
    #else
    return usize_error;
    #endif
}

/*
void* operator new(nuint nb_bytes)
{
    return malloc(nb_bytes);
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
}

void operator delete(void* ptr, nuint size) noexcept
{
    unused(size);
    free(ptr);
}*/