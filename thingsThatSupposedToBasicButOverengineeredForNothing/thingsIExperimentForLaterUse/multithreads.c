/*
    'sup? actual POSIX thread fuckery this time.
    Four workers split the sum of 1 through 1000000 between themselves.


    Create ALL workers before joining them. Joining immediately after each
    creation would make main wait before it even starts the next worker.
    The scheduler decides when they run multiple cores can run them in parallel
    This tiny example demonstrates dividing work, not a fucking guaranteed speedup
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>     // EXIT_SUCCESS / EXIT_FAILURE
#include <string.h>     // strerror: pthread functions return error codes directly

#define THREAD_COUNT 4
#define NUMBER_COUNT 1000000ULL

typedef struct {
    unsigned int id;
    unsigned long long first;
    unsigned long long last;
    unsigned long long sum;
} Worker;

static void *sum_range(void *arg);

int main(void)
{
    pthread_t threads[THREAD_COUNT];
    
    Worker workers[THREAD_COUNT] = { 0 };
    
    unsigned int created = 0;
    unsigned long long total = 0;
    
    const unsigned long long expected = NUMBER_COUNT * (NUMBER_COUNT + 1) / 2;
    
    int ret_value = EXIT_SUCCESS;

    for (unsigned int i = 0; i < THREAD_COUNT; ++i) {
        
        workers[i].id = i + 1;
        workers[i].first = NUMBER_COUNT * i / THREAD_COUNT + 1;
        workers[i].last = NUMBER_COUNT * (i + 1) / THREAD_COUNT;

        int error = pthread_create(&threads[i], NULL, sum_range, &workers[i]);
        
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            ret_value = EXIT_FAILURE;
            break;
        }
        ++created;
    }

    // Even if creation failed partway through join the workers already started
    for (unsigned int i = 0; i < created; ++i) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            // Terminate the process
            exit(EXIT_FAILURE);
        }

        // Joining guarantees this worker finished writing its result
        total += workers[i].sum;
    }

    if (ret_value != EXIT_SUCCESS)
        return(ret_value);

    printf("Total: %llu | Expected: %llu\n", total, expected);
    return(total == expected ? EXIT_SUCCESS : EXIT_FAILURE);
}

static void *sum_range(void *arg)
{
    Worker *worker = arg;
    unsigned long long sum = 0;

    printf("Worker %u: summing %llu throhg %llu\n", worker->id, worker->first, worker->last);

    for (unsigned long long number = worker->first; number <= worker->last; ++number){
        sum += number;
    }
    // Each worker owns a different result so no mutex is needed here
    // A shared total += number inside the loop WOULD need synchronization
    worker->sum = sum;
    printf("Worker %u: done, sum = %llu\n", worker->id, sum);
    return(NULL);
}
