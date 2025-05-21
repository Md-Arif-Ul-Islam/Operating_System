#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 10

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    int blocks[MAX_BLOCKS];
    for (int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (blocks[j] >= processSize[i]) {
                allocation[i] = j;
                blocks[j] -= processSize[i];
                break;
            }

    printf("\nFirst Fit Allocation:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    int blocks[MAX_BLOCKS];
    for (int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int best = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processSize[i]) {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }
        if (best != -1) {
            allocation[i] = best;
            blocks[best] -= processSize[i];
        }
    }

    printf("\nBest Fit Allocation:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES];
    int blocks[MAX_BLOCKS];
    for (int i = 0; i < m; i++) blocks[i] = blockSize[i];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worst = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processSize[i]) {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            allocation[i] = worst;
            blocks[worst] -= processSize[i];
        }
    }

    printf("\nWorst Fit Allocation:\nProcess\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tBlock %d\n", i + 1, processSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES];
    int m, n, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter sizes of %d blocks:\n", m);
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter sizes of %d processes:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    do {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit(blockSize, m, processSize, n);
                break;
            case 2:
                bestFit(blockSize, m, processSize, n);
                break;
            case 3:
                worstFit(blockSize, m, processSize, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
