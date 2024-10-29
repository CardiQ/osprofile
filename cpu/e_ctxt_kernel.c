#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <stdint.h>
#include <unistd.h>

// #define KERNEL
// kernel creating: 22471 cycles on average

uint64_t start, end;
uint64_t ave = 0;
uint64_t overhead_r = 0;

uint64_t rdtscp() // linux
{
    unsigned int lo, hi;
    __asm__ volatile("rdtscp" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

void thread_function(){} // empty thread_func

int pipe_fd[2];

void* thread_function1(void* arg) {
    close(pipe_fd[1]);  // 关闭写端
    char buffer[10];
    printf("Thread 1 is waiting to read from the pipe...\n");
    read(pipe_fd[0], buffer, sizeof(buffer));
    //end = rdtscp();
    printf("Thread 1 received data: %s\n", buffer);
    close(pipe_fd[0]);
    return NULL;
}

void* thread_function2(void* arg) {
    close(pipe_fd[0]);  // 关闭读端
    sleep(2);           // 模拟延迟，确保线程1先阻塞
    printf("Thread 2 writing to the pipe...\n");
    write(pipe_fd[1], "World", 5);
    //start = rdtscp();
    close(pipe_fd[1]);
    return NULL;
}

int main() {
    // cycle time @ 2.30GHz


    pthread_t thread1, thread2;

    // 创建管道
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    // 创建线程1和线程2
    start = rdtscp();

    pthread_create(&thread1, NULL, thread_function1, NULL);
    pthread_create(&thread2, NULL, thread_function2, NULL);

    end = rdtscp();

    // 等待线程完成
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    

    printf("cycles: %ld", end-start-22471);
    return 0;
}
