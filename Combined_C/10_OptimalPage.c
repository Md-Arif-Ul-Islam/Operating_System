#include <stdio.h>

int search(int key, int frame[], int n) {
    for(int i = 0; i < n; i++)
        if(frame[i] == key)
            return 1;
    return 0;
}

int predict(int pages[], int frame[], int n, int index, int pn) {
    int res = -1, farthest = index;
    for(int i = 0; i < n; i++) {
        int j;
        for(j = index; j < pn; j++) {
            if(frame[i] == pages[j]) {
                if(j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == pn)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int frames[10], pages[30], n, f, i, faults = 0;

    printf("Enter number of frames: ");
    scanf("%d", &f);
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    int filled = 0;
    for(i = 0; i < n; i++) {
        if(search(pages[i], frames, filled))
            continue;

        if(filled < f) {
            frames[filled++] = pages[i];
        } else {
            int j = predict(pages, frames, f, i + 1, n);
            frames[j] = pages[i];
        }
        faults++;
    }

    printf("Total Page Faults = %d\n", faults);
    return 0;
}
