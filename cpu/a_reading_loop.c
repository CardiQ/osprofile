#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
//#define LOOP

// uint64_t rdtsc() // linux
// {
//     unsigned int lo, hi;
//     __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
//     return ((uint64_t)hi << 32) | lo;
// }
uint64_t rdtscp() // linux
{
    unsigned int lo, hi;
    __asm__ volatile("rdtscp" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main()
{

#ifdef LOOP
    printf("loop mode is enabled.\n");
    uint64_t start, end;

    start = rdtscp();
    for (int i = 0; i < 1000; i++)
        ;
    end = rdtscp();

    uint64_t overhead = end - start;
    overhead -= 72;
    uint64_t overhead_each = overhead / 1000;

    printf("loops overhead CPU cycles: %lu\n", overhead);
    printf("each loop overhead CPU cycles: %lu\n", overhead_each);
    return 0;
#else
    // cycle time
    uint64_t start, end, ave;
    for(int i=0;i<1000;i++){
        start = rdtscp();
        // nothing for reading overhead, without any additions
        end = rdtscp();

        printf("reading overhead CPU cycles: %llu\n", end - start);
        ave+= end-start;
    }
    ave/=1000;
    printf("avg reading overhead CPU cycles: %llu\n", ave);
    return 0;
#endif
}
