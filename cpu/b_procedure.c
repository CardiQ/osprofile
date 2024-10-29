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

void func0()
{
}
void func1(int a)
{
}
void func2(int a, int b)
{
}
void func3(int a, int b, int c)
{
}
void func4(int a, int b, int c, int d)
{
}
void func5(int a, int b, int c, int d, int e)
{
}
void func6(int a, int b, int c, int d, int e, int f)
{
}
void func7(int a, int b, int c, int d, int e, int f, int g)
{
}

int main()
{
    FILE *file;
    const char *filename = "b_output.txt";
    file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // cycle time @ 2.30GHz
    uint64_t start, end;
    uint64_t ave = 0;
    int args = 0; // manually change
    int var = 0xfff;

    // typedef void (*func_ptr)();
    // func_ptr func_use;

    switch (args)
    {
    case 0:
        
        for (int i = 0; i < 10; i++)
        {

            
            start = rdtscp();
            // incremental overhead over number of arguments 0-7
            func0();
            end = rdtscp();
            fprintf(file, "0 CPU cycles: %ld\n", end - start);
            ave += end - start;
            
        }
        
        
        break;
    case 1:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func1(var);

            end = rdtscp();

            fprintf(file, "1 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 2:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func2(var, var);

            end = rdtscp();

            fprintf(file, "2 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 3:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func3(var, var, var);

            end = rdtscp();

            fprintf(file, "3 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 4:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func4(var, var, var, var);

            end = rdtscp();

            fprintf(file, "4 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 5:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func5(var, var, var, var, var);

            end = rdtscp();

            fprintf(file, "5 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 6:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func6(var, var, var, var, var, var);

            end = rdtscp();

            fprintf(file, "6 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    case 7:
        for (int i = 0; i < 10; i++)
        {

            start = rdtscp();

            // incremental overhead over number of arguments 0-7
            func7(var, var, var, var, var, var, var);

            end = rdtscp();

            fprintf(file, "7 CPU cycles: %ld\n", end - start);
            ave += end - start;
        }
        break;
    default:
        break;
    }

    ave /= 10;
    uint64_t overhead_r = 45;
    //uint64_t overhead_l = 6;
    fprintf(file, "average CPU cycles: %ld\n, samples: 10", ave-overhead_r);

    fclose(file);

    return 0;
}
