#ifndef MEMORY_H
#define MEMORY_H
#include "betterC.h"

//#define calloc(nbBytes) ((calloc)(1,nbBytes))

#define make(type) (type*)malloc(sizeof(type))
#define make_array(type, nb) (type*)malloc(nb*sizeof(type))

#define TRACK_MEMORY

#ifdef TRACK_MEMORY
#define malloc(nbBytes) memory_malloc(nbBytes)
#define calloc(count, size) memory_calloc(count, size)
#define realloc(ptr, nbBytes) memory_realloc(ptr, nbBytes)
#define free(ptr) memory_free(ptr)

void* memory_malloc(size_t nb_byte);
void* memory_calloc(size_t count_, size_t size);
void* memory_realloc(void* ptr, size_t nb_byte);
void  memory_free(void* ptr);
#endif

void memory_printf_rel(nuint less);
void memory_printf();
void memory_printf_final();
nuint  memory_get_nb_alloc();
void memory_check_0_alloc();

//void* operator new(nuint nb_bytes);
//void operator delete(void* ptr) noexcept;

#endif