#include <unistd.h>
#include <stdio.h>

int main() {
    int i = 0, pid;

    printf("\nReady for fork\n");
    pid = fork();

    if (pid == 0) {
        printf("\nChild process started\n");
        sleep(4);
        for (i = 0; i < 10; i++) {
            printf("\n%d", i);
        }
        printf("\nChild process ends\n");
    } else {
        printf("\nI am the parent\n");
        printf("\nParent process ends\n");
    }

    return 0;
}
