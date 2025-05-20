#include <stdio.h>

int main() {
    int frames[10], pages[30], i, j, k, n, f, index = 0, flag, faults = 0;

    printf("Enter no. of frames: ");
    scanf("%d", &f);
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    for(i = 0; i < f; i++)
        frames[i] = -1;

    for(i = 0; i < n; i++) {
        flag = 0;
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if(flag == 0) {
            frames[index] = pages[i];
            index = (index + 1) % f;
            faults++;
        }
    }

    printf("Total Page Faults = %d\n", faults);
    return 0;
}
