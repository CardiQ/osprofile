#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <stdint.h>
#include <unistd.h>

// #define KERNEL

uint64_t rdtscp() // linux
{
    unsigned int lo, hi;
    __asm__ volatile("rdtscp" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

void thread_function(){} // empty thread_func

int main()
{

    // cycle time @ 2.30GHz
    uint64_t start, end;
    uint64_t ave = 0;
    uint64_t overhead_r = 0;

    #ifdef KERNEL

        for (int i = 0; i < 10; i++)
        {
            pthread_t thread_id;  // 用于保存新线程的 ID
            int arg = 42;         // 传递给线程的参数

            // 创建一个新线程
            start = rdtscp();

            if (pthread_create(&thread_id, NULL, thread_function, &arg) != 0) {
                perror("Failed to create thread");
                return 1;
            }

            end = rdtscp();

            // 等待新线程结束
            if (pthread_join(thread_id, NULL) != 0) {
                perror("Failed to join thread");
                return 1;
            }

            
            printf("process CPU cycles: %ld\n", end - start);
            ave += end - start;
        }

        ave /= 10;
        printf("average CPU cycles: %ld\n, samples: 10", ave-overhead_r);

    #else

        // for (int i = 0; i < 10; i++)
        // {
        start = rdtscp();

        pid_t pid = fork(); // 创建一个新进程

        end = rdtscp();

        if (pid < 0) {
            perror("fork failed");
            return 1;
        } else if (pid == 0) {
            // 子进程代码
            //printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        } else {
            // 父进程代码
            //printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
            wait(NULL); // 等待子进程结束
        }

            
        printf("kernel CPU cycles: %ld\n", end - start);
        ave += end - start;    
        // }
        //ave /= 10;
        printf("average CPU cycles: %ld\n, samples: 1", ave-overhead_r);

    #endif

    return 0;
}
