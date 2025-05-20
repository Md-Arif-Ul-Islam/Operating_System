#include <stdio.h>
int main() {
    int n, bt[20], p[20], wt = 0, tat = 0, i, j, temp;
    float avg_wt = 0, avg_tat = 0;
    printf("No. of processes: "); 
    scanf("%d", &n);
    for (i = 0; i < n; i++) { 
        printf("BT P%d: ", i + 1); 
        scanf("%d", &bt[i]);
         p[i] = i + 1; 
    }

    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (bt[i] > bt[j]) { 
                temp = bt[i];
                 bt[i] = bt[j];
                  bt[j] = temp;
                   temp = p[i];
                    p[i] = p[j];
                     p[j] = temp; 
                    }

    printf("P\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt, wt + bt[i]);
        avg_wt += wt; tat = wt + bt[i]; 
        avg_tat += tat; 
        wt += bt[i];
    }
    printf("Avg WT=%.2f, TAT=%.2f\n", avg_wt / n, avg_tat / n);
    return 0;
}
