#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

uint64_t rdtscp() // linux
{
    unsigned int lo, hi;
    __asm__ volatile("rdtscp" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

// void mfence() // not accurate: reorder?
// {
//     __asm__ __volatile__("mfence" ::: "memory");
// }

int main()
{

    // cycle time @ 2.30GHz
    uint64_t start, end;
    uint64_t ave = 0;

    for (int i = 0; i < 10; i++)
    {
        start = rdtscp();
        sleep(10);
        // unsigned eax;
        // __asm__ __volatile__("cpuid" : "=a"(eax) : "a"(0x00));
        end = rdtscp();
        printf("CPU cycles: %ld\n", end - start);
        ave += end - start;
    }
    ave /= 10;
    printf("average CPU cycles: %ld\n, samples: 10", ave);

    return 0;
}
