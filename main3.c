#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void ChildProcessOne(void);
void ChildProcessTwo(void);
void ParentProcess(void);

int main(void) {
    pid_t pid, pid2, finished_pid;

    // First fork to create ChildProcessOne
    pid = fork();

    if (pid < 0) {
        perror("First fork failed\n");
    } else if (pid == 0) {
        ChildProcessOne();  // Child process 1
    } else {
        // Second fork to create ChildProcessTwo
        pid2 = fork();
        if (pid2 < 0) {
            perror("Second fork failed\n");
        } else if (pid2 == 0) {
            ChildProcessTwo();  // Child process 2
        }
        
        // Parent process waits for both child processes to complete
        finished_pid = wait(NULL);
        printf("Child Pid: %d has completed\n", finished_pid);
        finished_pid = wait(NULL);
        printf("Child Pid: %d has completed\n", finished_pid);
    }

    return 0;
}

void ChildProcessOne(void) {
    int max_loop, max_sleep;
    int i;
    
    // Seed random number generator with time and PID
    srandom(time(NULL) ^ getpid());

    // Generate random number of iterations and sleep time
    max_loop = random() % 30;
    max_sleep = random() % 10;

    for (i = 1; i <= max_loop; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(max_sleep);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n", getpid(), getppid());
    }

    exit(0);  // Terminate the child process
}

void ChildProcessTwo(void) {
    int max_loop, max_sleep;
    int i;

    // Seed random number generator with time and PID
    srandom(time(NULL) ^ getpid());

    // Generate random number of iterations and sleep time
    max_loop = random() % 30;
    max_sleep = random() % 10;

    for (i = 1; i <= max_loop; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep(max_sleep);
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d\n", getpid(), getppid());
    }

    exit(0);  // Terminate the child process
}
