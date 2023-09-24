#ifndef betterC_pointer
#define betterC_pointer

#if 0

#define it    /*Iterator. Don't own the memory*/
#define mut   /*Mutable.  Don't own the memory*/
#define ref   /*immutable.Don't own the memory*/
#endif

#define not_owned  /*Don't own the memory. Don't drop the value when your are done with the pointer*/
#define owned   /*Own the memory. Point at the beginning of the block. Drop the value when your are done with the pointer*/

#define maybe   /*Maybe the pointer is null*/

#define imut /*imutable data type*/

#endif