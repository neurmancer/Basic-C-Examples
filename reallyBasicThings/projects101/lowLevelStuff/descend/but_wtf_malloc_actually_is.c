/*


    'Sup? You know the tea but if I must vocalize (or textualize if that's a word) today's low-level fuckery is implementing malloc using the
    ancient scrolls of sbrk insted of mmap. 
        
        This is the second time I am attempting to implement this because the first implementation respectfully got corrupted by ADHD with meaningless defines and 
        lost the actual point...Hence, We're doing it from scratch


        Shit to know:
            0- I'll use doubly linked lists so...go take a peek wtf it is
            1- Know how the pointers work at least fundementally
            2- Well...know how to use malloc and free at least

        and here is the source I am using implement malloc: https://levelup.gitconnected.com/malloc-is-not-magic-implementing-my-own-memory-allocator-e0354e914402
        So...let's fucking get the keyboard moving before I need to eventually use pyt*n for the android client for the TODO server
        and as always this is here as a template...
        
*/


//So let's start with headers...

#include <assert.h>

#include <malloc.h>
#include <stdlib.h> //This file is here to ditch you bruh just come and watch your funeral from a better seat
#include <stdbool.h> 
#include <stdint.h> //For data types such as uint32_t
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#ifndef PAGE_SIZE 
    #define PAGE_SIZE getpagesize() //Yeah instead of hardcoding 4096 I'll call a function again and again...That's hill I am willing to die on
#endif

struct free_block{
    uint8_t marker;
    struct free_block *prev;
    bool in_use;
    uint32_t len;
    struct free_block *next;
    //The header data
};

struct data{

    int dope_bytes;
    bool lock;
    uint32_t amount_of_blocks;
    uint16_t amount_of_pages;
};

const int DOPE_BYES = 0x13;
const int BLOCK_MARKER = 0x53;
const int FIRST_BLOCK_OFFSET = sizeof(struct free_block);

char *heap_begins = NULL;   //Yeah the batman begins joke remains...




void debug_print(const char *msg);

void reduce_heap_size_if_possible();

struct free_block *find_last_block(void);
struct free_block *find_fisrt_block(void);
struct free_block *find_previous_used_block(struct free_block *ptr);

struct data *get_allocator_header(void);


int main(void)
{


    return(0);
}


void debug_print(const char *msg)
{
    write(1, msg, strlen(msg));
}



struct data *get_allocator_header(void)
{
    assert(heap_begins != NULL);
    struct data *allocator_header = (struct data *)heap_begins;

    assert(allocator_header->dope_bytes == DOPE_BYES);
    return(allocator_header);
}

struct free_block *find_previous_used_block(struct free_block *ptr)
{
    struct free_block *iter = ptr;
    while (iter->prev != NULL) {
        iter = iter->prev;
        if (iter->in_use == true) {
            return(iter);
        }
    }
    return(NULL);
}

struct free_block *find_fisrt_block(void)
{
    struct data *allocator_header = get_allocator_header();
    return((struct free_block *)(char *)allocator_header + sizeof(struct data));    //Lol welcome to the low level pointer fuckery
}


void reduce_heap_size_if_possible()
{
    struct free_block *last_block = find_last_block();
    struct free_block *prev_block = find_previous_used_block(last_block);
    
    if (prev_block == NULL) {
        if (last_block->len > PAGE_SIZE) { last_block->len = PAGE_SIZE; }
        prev_block = last_block;
    }
    void *new_end = (void *)prev_block + sizeof(struct free_block) + prev_block->len;

    void *heap_end = sbrk(0);
    while (new_end < heap_end - PAGE_SIZE) {
        sbrk(-PAGE_SIZE);
        heap_end = sbrk(0);
        struct data *allocator_header = get_allocator_header();
        allocator_header->amount_of_pages -= 1;
    }
    //New block init sequence type shit...where the doubly pointers come in handy
    if (heap_end - new_end > sizeof(struct free_block)+1) {
        struct free_block *new_not_used_block = (struct free_block *)new_end;
        new_not_used_block->marker = BLOCK_MARKER;
        new_not_used_block->in_use = false;
        new_not_used_block->prev = prev_block;
        new_not_used_block->next = NULL;
        new_not_used_block->len = heap_end - new_end - sizeof(struct free_block);
    
        prev_block->next = new_not_used_block;
    }

}