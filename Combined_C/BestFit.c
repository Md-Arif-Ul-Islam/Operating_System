#include <stdio.h>

int main() {
    int block[] = {100, 500, 200, 300, 600};
    int process[] = {212, 417, 112, 426};
    int m = 5, n = 4, alloc[4], i, j;

    for (i = 0; i < n; i++) {
        int best = -1;
        alloc[i] = -1;
        for (j = 0; j < m; j++) {
            if (block[j] >= process[i]) {
                if (best == -1 || block[j] < block[best])
                    best = j;
            }
        }
        if (best != -1) {
            alloc[i] = best;
            block[best] -= process[i];
        }
    }

    printf("Best Fit Allocation:\nProcess\tSize\tBlock\n");
    for (i = 0; i < n; i++) {
        if (alloc[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, process[i], alloc[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, process[i]);
    }

    return 0;
}
