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
        So...let's fucking get the keyboard moving before I need to eventually use pyt*n (or worse java) for the android client for the TODO server
        and as always this is here as a template...
    
        
        and since we're doing low-level fuckery I'll be using structs as they are no typedefing we're going with full Linus Doctrine


        Future shit:
            0- Check the return value of sbrk before proceeding (which returns (void *)-1 btw)
            1- Error handlig for sbrk
            2- implement sbrk() lol (yeah..that's a joke I am not writing my own syscalls just yet) 
*/


//So let's start with headers...

#include <assert.h>

#include <malloc.h>
// #include <setjmp.h>yet another cursed plan gets out
#include <stddef.h>
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

int *add_used_block(size_t size);
int *so_this_is_malloc(size_t size); //Original malloc returns (void *) so...should I do that instead?

struct free_block *find_last_block(void);
struct free_block *find_fisrt_block(void);
struct free_block *find_previous_used_block(struct free_block *ptr);

struct data *get_allocator_header(void);

bool free_shit(void *ptr);

//Test case prototypes
void call_test(void (*test_func)(), const char *msg);
void complex_set_of_malloc_and_free_calls();
void test_free();
void test_bigger_than_available_malloc();
void test_basic_malloc();


int main(void)
{

    call_test(test_basic_malloc, "Basic Malloc");
    call_test(test_bigger_than_available_malloc, "More ALLOCATION");
    call_test(test_free, "Free your shit");
    call_test(complex_set_of_malloc_and_free_calls, "Heap fuckery");
    
    debug_print("We're done ig?");
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
    return((struct free_block *)((char *)allocator_header + sizeof(struct data)));    //Lol welcome to the low level pointer fuckery
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
    if (heap_end == (void *)-1) {
        perror("Sbrk really said nope...");
        exit(EXIT_FAILURE); //Yup  I feel fancy this time
    }
    while (new_end < heap_end - PAGE_SIZE) {
        if( sbrk(-PAGE_SIZE) == (void *)-1){
            perror("Sbrk having a tantrum");
            exit(EXIT_FAILURE);
        } 
        heap_end = sbrk(0);
        if (heap_end == (void *)-1) {
            perror("Same story...");
            exit(EXIT_FAILURE);
        }

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


bool free_shit(void *ptr)
{
    struct data *allocator_header = get_allocator_header();
    while (allocator_header->lock) {
        sleep(1);
    }
    allocator_header->lock = true;

    struct free_block *block = ptr - sizeof(struct free_block);

    if (block->marker != BLOCK_MARKER) {
        //Basically this says. 'here's not a beginning of any allocated block pal'
        return(false);
    }
    
    else {
        block->in_use = false;

        memset(ptr,  0, block->len);
        if (block->next != NULL && (block->next)->in_use == false) {
            //next block isn't in use smash those together
            struct free_block *not_used_next_block = block->next;
            if (not_used_next_block != NULL) {
                block->next = not_used_next_block->next;

                if (not_used_next_block->next != NULL) {
                    not_used_next_block->next->prev = block;
                }
            }
            else {
                block->next = NULL;
            }

            block->len += sizeof(struct free_block) + not_used_next_block->len;
            
            memset((void *)not_used_next_block, 0, sizeof(struct free_block) + not_used_next_block->len);
            allocator_header->amount_of_blocks -= 1;
        }

        if (block->prev != NULL && (block->prev)->in_use == false) {
            struct free_block *to_delete_block = block;
            block = block->prev;
            //adding the extra size to the prev
            block->len += sizeof(struct free_block) + to_delete_block->len;
            block->next = to_delete_block;

            if (block->next != NULL) {
                block->next->prev = block;
            }
            allocator_header->amount_of_blocks -= 1;
        }
        reduce_heap_size_if_possible();
    }

    allocator_header->lock = false;
    return(true);
}



struct free_block *find_last_block(void)
{
    struct data *allocator_header = get_allocator_header();
    
    struct free_block *block = (struct free_block *)((char *)allocator_header + sizeof(struct data));

    while (block->next != NULL) {
        block = block->next;    //Forward list walk (conceptually same as the backwards walk)
    }
    return(block);
}


int *add_used_block(size_t size)
{

    struct data *allocator_header = get_allocator_header(); //Even this started to feel repetitive tho

    while (allocator_header->lock) {
        sleep(1);
    }

    allocator_header->lock = true;
    
    struct free_block *block = (struct free_block *)((char *)heap_begins + sizeof(struct data));
    struct free_block *smallest_block = NULL;
    struct free_block *last_block = block;

    while (block != NULL) {
        assert(block->marker == BLOCK_MARKER);
        if (block->len + sizeof(struct free_block) >= size && block->in_use == false) {
            if (smallest_block == NULL || smallest_block->len > block->len) {
                smallest_block = block;
            }    
        }
        
        last_block = block;
        block = block->next;
    }

    if (smallest_block == NULL) {
        struct free_block *last_block = find_last_block();
        
        while (last_block->len < size) {
            if(sbrk(PAGE_SIZE) == (void *)-1)
            {
                perror("Fuckk...");
                exit(EXIT_FAILURE);
            }

            last_block->len += PAGE_SIZE;
            allocator_header->amount_of_pages += 1;
        }

        smallest_block = last_block;
    }

    smallest_block->in_use = true;
    int must_size = smallest_block->len - size - sizeof(struct free_block) - 1;
    
    if (must_size <= 0 ) {
        if(sbrk(PAGE_SIZE) == (void *)-1)
        {
            perror("Fuckyty fuck...");
            exit(EXIT_FAILURE);

        }
        allocator_header->amount_of_pages += 1;
        last_block->len += PAGE_SIZE;

        must_size = smallest_block->len - size - sizeof(struct free_block) - 1;
    }

    int size_residue = must_size + 1;
    allocator_header->amount_of_blocks += 1;
    struct free_block *new_block = (struct free_block *)((char *)smallest_block + sizeof(struct free_block) + size);

    new_block->marker = BLOCK_MARKER;
    new_block->prev = smallest_block;
    new_block->next = smallest_block->next;

    if (new_block->next != NULL) {
        (new_block->next)->prev = new_block;
    }

    smallest_block->next = new_block;
    new_block->len = size_residue;
    smallest_block->len = size;
    allocator_header->lock = false;

    return((int *)((char *)smallest_block + sizeof(struct free_block)));
}

int *so_this_is_malloc(size_t size)
{
    if (heap_begins == NULL) {
        heap_begins = sbrk(0);
        if (heap_begins == (void *)-1 ) {
            perror("My error codes getting worse and worse...");
            exit(EXIT_FAILURE);
        }

        sbrk(PAGE_SIZE);
    }

    char *heap_end = sbrk(0);
    if (heap_end == (void *)-1) {
        perror("Heap end error in add_used_block and yeah this one says exactly what needs to be said...");
        exit(EXIT_FAILURE);
    }

    long int len = heap_end - heap_begins;

    if ((*heap_begins) != DOPE_BYES) {
        *(heap_begins) = DOPE_BYES;
        struct data *allocator_header = (struct data *)heap_begins;

        allocator_header->amount_of_blocks = 1;
        allocator_header->amount_of_pages = 1;

        struct free_block *first_block = (struct free_block *)((char *)heap_begins + sizeof(struct data));

        first_block->marker = BLOCK_MARKER;
        first_block->in_use = false;
        first_block->len = len - sizeof(struct data) - sizeof(struct free_block);
        first_block->prev = NULL;
        first_block->next = NULL;
    }
    return add_used_block(size);
}


void test_basic_malloc() {
  char *ptr = (char *)so_this_is_malloc(1);
  struct free_block *first_block = (void *)ptr - sizeof(struct free_block);
  assert(first_block->marker == BLOCK_MARKER);
  *ptr = 'C';
  assert(*ptr == 'C');
}

void test_bigger_than_available_malloc() {
    uint16_t *ptr = (uint16_t *)so_this_is_malloc(5000);
    struct free_block *first_block = (void *)ptr - sizeof(struct free_block);
    
    for (uint16_t i = 0; i <= 2499; i = i + 1) {
        *(ptr + i) = i;
    }

    assert(first_block->marker == BLOCK_MARKER);
    assert(*ptr == 0);
    assert(*(ptr + 2) == 2);
    assert(*(ptr + 2499) == 2499);
    
    assert(*((uint8_t *)ptr + 4999) == (2499 >> 8));
    assert(*((uint8_t *)ptr + 4998) == (2499 & 0xFF));
}

void test_free() {
    uint8_t *first = (uint8_t *)so_this_is_malloc(2048);
    
    struct free_block *first_block = (void *)first - sizeof(struct free_block);
    
    assert(first_block->next != NULL);
    assert(first_block->len == 2048);
    
    struct free_block *second_block = first_block->next;
    
    assert(second_block->marker == BLOCK_MARKER);
    assert(second_block->in_use == false);
    assert(second_block->next == NULL);
    assert(second_block->len == PAGE_SIZE - sizeof(struct data) - (2 * sizeof(struct free_block)) - first_block->len);
    
    free_shit(first);
    
    assert(first_block->marker == BLOCK_MARKER);
    assert(first_block->next == NULL);
    assert(first_block->len == PAGE_SIZE - sizeof(struct data) - sizeof(struct free_block));
}

void complex_set_of_malloc_and_free_calls() {
    
    uint8_t *first =
        (uint8_t *)so_this_is_malloc(2048);
    
    struct free_block *first_block = find_fisrt_block();
    
    assert(first_block->len == 2048);
    
    struct free_block *second_block = first_block->next;
    
    assert(second_block->len ==
            PAGE_SIZE - sizeof(struct data) - 2 * sizeof(struct free_block) - first_block->len);
    assert(second_block->next == NULL);
    assert(second_block->prev == first_block);
    
    uint8_t *second =
        (uint8_t *)so_this_is_malloc(10000);
    
        assert(second_block->len == 10000);
    assert(second_block->next != NULL);
    
    struct free_block *third_block = second_block->next;
    
    assert(third_block->len == 3 * PAGE_SIZE - sizeof(struct data) -
                                    3 * sizeof(struct free_block) - first_block->len -
                                    second_block->len);
                                    struct data *malloc_header = get_allocator_header();
  
    assert(malloc_header->amount_of_pages == 3);
    assert(malloc_header->amount_of_blocks == 3);
    
    free_shit(second);
    
    assert(malloc_header->amount_of_pages == 1);
    assert(malloc_header->amount_of_blocks == 2);
    
    void *sys_break = sbrk(0);
    if (sys_break == (void *)-1) {
        perror("Yet another sbrk nope");
        exit(EXIT_FAILURE);
    }

    int heap_size = sys_break  - (void *)heap_begins;
    
    assert(heap_size == PAGE_SIZE);
    
    // The second block is whatever is left from the first page
    assert(second_block->in_use == false);
    assert(first_block->len == 2048);
    assert(second_block->len ==
            PAGE_SIZE - sizeof(struct data) - 2 * sizeof(struct free_block) - first_block->len);
    
    assert(second_block->next == NULL);
    // test block unification, add three blocks, free the left, free the right,
    // and then free the middle
    
    uint8_t *third = (uint8_t *)so_this_is_malloc(1000);
    
    assert(malloc_header->amount_of_pages == 1);
    assert(malloc_header->amount_of_blocks == 3);
    // A third, empty block has been created
    
    struct free_block *third_block_new = second_block->next;
    
    assert(third_block_new->marker == BLOCK_MARKER);
    assert(third_block_new->in_use == false);
    assert(second_block->len == 1000);
    assert(third_block_new->len == PAGE_SIZE - sizeof(struct data) -
                                            3 * sizeof(struct free_block) - first_block->len -
                                            second_block->len);
    assert(third_block_new->next == NULL);
    
    uint8_t *fourth = (uint8_t *)so_this_is_malloc(5000);
    
    assert(third_block_new->len == 5000);
    assert(third_block_new->next != NULL);
    assert(third_block_new->in_use == true);
    assert(third_block_new->prev == second_block);
    assert(malloc_header->amount_of_pages ==
            3); // the 5000 needed a second page, and then another page was needed
                // to create a third block
    assert(malloc_header->amount_of_blocks == 4);
    
    uint8_t *fifth = (uint8_t *)so_this_is_malloc(1000);
    // a new block has been created
    
    struct free_block *fourth_block = third_block_new->next;
    
    assert(fourth_block->marker == BLOCK_MARKER);
    assert(third_block_new->len == 5000);
    assert(fourth_block->len == 1000);
    assert(fourth_block->in_use == true);
    assert(fourth_block->next != NULL);
    
    struct free_block *fifth_block = fourth_block->next;
    
    assert(fifth_block->marker == BLOCK_MARKER);
    assert(fifth_block->in_use == false);
    assert(fifth_block->next == NULL);
    assert(malloc_header->amount_of_pages == 3);
    assert(malloc_header->amount_of_blocks == 5); // fifth malloc made a new block
    
    uint8_t *sixth = (uint8_t *)so_this_is_malloc(
        1000); 
    
    assert(fifth_block->in_use == true);
    assert(fifth_block->len == 1000);
    assert(fifth_block->next != NULL);
    assert(fifth_block->prev == fourth_block);
    
    struct free_block *sixth_block = fifth_block->next;
    
    assert(sixth_block->marker == BLOCK_MARKER);
    assert(sixth_block->in_use == false);
    assert(sixth_block->next == NULL);
    assert(malloc_header->amount_of_pages == 3);
    assert(malloc_header->amount_of_blocks == 6);
    
    free_shit(third);
    
    assert(second_block->in_use == false);
    assert(second_block->len == 1000); // should be unchanged
    assert(malloc_header->amount_of_pages == 3);
    assert(malloc_header->amount_of_blocks == 6); // 'cuz we have a free block
    
    free_shit(fifth);
    
    assert(fourth_block->in_use == false);
    assert(malloc_header->amount_of_pages == 3);
    assert(malloc_header->amount_of_blocks == 6);
    
    free_shit(fourth);
    
    assert(third_block_new->in_use == false);
    assert(malloc_header->amount_of_pages == 3);  
    assert(malloc_header->amount_of_blocks == 4); 
}

void call_test(void (*test_func)(), const char *msg) {
    pid_t pid = fork();
    
    if (pid == 0) {
        test_func();
        exit(0);
    } 
    
    else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) { printf("%s crashed with signal %d\n", msg, WTERMSIG(status)); } 
        else { printf("%s passed\n", msg); }
    }
}


/*

==514891== HEAP SUMMARY:
==514891==     in use at exit: 0 bytes in 0 blocks
==514891==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==514891== 
==514891== All heap blocks were freed -- no leaks are possible
==514891== 
==514891== Use --track-origins=yes to see where uninitialised values come from
==514891== For lists of detected and suppressed errors, rerun with: -s
==514891== ERROR SUMMARY: 27 errors from 22 contexts (suppressed: 0 from 0)
Heap fuckery passed
We're done ig?==514870== 
==514870== HEAP SUMMARY:
==514870==     in use at exit: 0 bytes in 0 blocks
==514870==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==514870== 
==514870== All heap blocks were freed -- no leaks are possible
==514870== 
==514870== For lists of detected and suppressed errors, rerun with: -s
==514870== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


now it's better...
*/