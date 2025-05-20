#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent";
    char read_msg[100];

    pipe(fd);
    pid = fork();

    if (pid == 0) {
        close(fd[1]); // Close write
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child read: %s\n", read_msg);
    } else {
        close(fd[0]); // Close read
        write(fd[1], write_msg, strlen(write_msg) + 1);
    }

    return 0;
}
