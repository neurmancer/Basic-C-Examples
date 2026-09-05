/*
*
*
*
*       'Sup? What's today's low-level fuckery? wriitng malloc using ancient scrolls (sbrk) before building a VM and understand virtual memory to do the same shit using 
*       mmap() 
*
*       This is a template for now and this shit has prerequiests(or how tf u spell it)
*
*       So here are shits to know:
*
*       0-Wtf are pointers
*       1-Basic struct usage
*       2-And esentials of DSA for doubly linked lists (I guess...haven't started writing a single line of code yet) 
*
*       Here we descend...
*       
*       Sources are: this blog: https://levelup.gitconnected.com/malloc-is-not-magic-implementing-my-own-memory-allocator-e0354e914402
*       And ofc for syscalls man pages as always
* */


#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> //This file is to ditch you out bro sorry... but you're here to watch your funeral 
#include <string.h>
#include <unistd.h>

/* If we go full low level we'll GO FULL LOW LEVEL 
  use cc -dM -E - < /dev/null to see compiler defined macros btw...all the types that I'll use can be found in <stdint.h>
*/

//Yeah this is for my rig if you're on a fucking toaster that may differ go use fucking stdint.h headers exist for a reason(to annoy me)
#ifdef __UINT8_TYPE__ 
  #define uint8_t unsigned char 
#endif

#ifdef __UINT16_TYPE__
  #define uint16_t unsigned short
#endif

#ifdef __UINT32_TYPE__
  #define uint32_t unsigned int
#endif

#ifdef __INT64_TYPE__
  #define int64_t long int 
#endif

#ifdef __INT8_TYPE__
  #define int8_t char
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ > 201710L
#elif !defined(__cplusplus)
#define bool _Bool
#define true 1
#define false 0
#elif defined(__GNUC__) && !defined(__STRICT_ANSI__)
#define _Bool bool
#endif

#ifndef NULL
  #define NULL (void *)0
#endif 

struct free_sectors {
    uint8_t marker;
    struct free_sectors *prev;  //As I said you need to have a rough understanding of doubly linked lists
    bool in_use; 
    uint32_t length;
    struct free_sectors *next;
};

//Btw I won't use typedef on those structs...cuz yk...we're going low-low-low-level so we're following Linus's convetion about those structs


struct stats{
    int dope_bytes; //4 bytes
    uint32_t block_amount;  //4 bytes
    uint16_t page_amount; //2 bytes
    bool lock;  //1 byte 
    
};

//You know shit's getting seriouser when your shit invokes magical bytes  -John Carmack (Quake type shit)
const int DOPE_BYTES = 0x13; //Hex for 19 (decimal)
const int BLOCK_MARKER = 0x53; //Hex for 83 (decimal)
const int FIRST_BLOCK_OFFSET = sizeof(struct free_sectors); //So we don't free program I guess
const int PAGE_SIZE = 4096; //FUCKING FINALLY I'VE USED 4096 FOR REALLY PAGE RELATED REASONS 

int8_t *heap_begins = NULL;

//Debug tools
void debug_log(const char *msg);

struct free_sectors *find_last_block();
struct free_sectors *find_previous_used_block(struct free_sectors *ptr);
struct stats *get_malloc_header(void);
int *so_this_is_malloc(ssize_t size); //doesn't malloc return (void *) implement first, question next ig...

int main(void)
{



    return(0);
}

void debug_log(const char *msg)
{
    write(STDOUT_FILENO, msg, strlen(msg));
}


struct stats *get_malloc_header(void)
{

    assert(heap_begins != NULL);  //Prints shit to stderr then calls abort()
    struct stats *malloc_header = (struct stats *)heap_begins;
    
    assert(malloc_header->dope_bytes == DOPE_BYTES);
    return(malloc_header);
}


struct free_sectors *find_previous_used_block(struct free_sectors *ptr)
{
    struct free_sectors *mov_ptr = ptr;

    while (mov_ptr->prev != NULL) {
        mov_ptr = mov_ptr->prev;
        if (mov_ptr->in_use) {
            return(mov_ptr);
        }
    }
    return(NULL);
}

struct free_sectors *find_first_block(void)
{
    struct stats *malloc_header = get_malloc_header();
    return((struct free_sectors *)((int8_t *)malloc_header + sizeof(struct stats)));
}

int *so_this_is_malloc(ssize_t size)
{
    if (heap_begins == NULL)
    {
        heap_begins = sbrk(0);
        if (heap_begins == (void *)-1) {
        perror("Yup...sbrk throwing a tantrum rn...");
        }

        if (sbrk(PAGE_SIZE) == (void *)-1) {
        perror("Bruh you won't believe me but this time sbrk really said NOPE!");
        }
    }

    int8_t *heap_end = sbrk(0);
    if (heap_end == (void *)-1) {
        perror("Sbrk...");
    }

    int64_t len = heap_end - heap_begins;

    if ((*heap_begins) != DOPE_BYTES) {
        (*heap_begins) = DOPE_BYTES;
        //Yeah I'm calling it a night it's almsot 00AM again...
    }
}