#include <stdio.h>
#include <unistd.h>


int main() {
    execlp("ls", "ls", "-l", NULL);
    printf("This line won't be printed if execlp is successful\n");
    return 0;
}

