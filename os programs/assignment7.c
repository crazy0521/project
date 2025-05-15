// IPC using Pipe (producer consumer)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    pid_t pid;
    char buffer[100];

    // Create pipe
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    // Create child process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // Consumer Process
        close(fd[1]);  // Close write end

        printf("Consumer: Waiting for data...\n");
        read(fd[0], buffer, sizeof(buffer));
        printf("Consumer: Received -> %s\n", buffer);

        close(fd[0]);  // Close read end
        exit(0);
    }

    else {
        // Producer Process
        close(fd[0]);  // Close read end

        char data[100];
        printf("Producer: Enter data to send: ");
        fgets(data, sizeof(data), stdin);

        write(fd[1], data, strlen(data) + 1);
        printf("Producer: Data sent to consumer.\n");

        close(fd[1]);  // Close write end
        wait(NULL);    // Wait for child to finish
    }

    return 0;
}
