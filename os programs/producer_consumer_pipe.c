#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 20 // Size of the buffer

void producer(int write_fd) {
    char *msg = "Data from producer\n";
    write(write_fd, msg, SIZE);
    printf("Producer: Data written to pipe\n");
}

void consumer(int read_fd) {
    char buf[SIZE];
    read(read_fd, buf, SIZE);
    printf("Consumer: Data read from pipe: %s\n", buf);
}

int main() {
    int fds[2];
    pid_t pid;

    if (pipe(fds) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Consumer process
        close(fds[1]);  // Close write end
        consumer(fds[0]);
    } else {  // Producer process
        close(fds[0]);  // Close read end
        producer(fds[1]);
        wait(NULL);  // Wait for child to finish
    }

    return 0;
}
