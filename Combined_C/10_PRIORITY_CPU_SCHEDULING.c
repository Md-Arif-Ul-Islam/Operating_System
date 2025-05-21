#include <stdio.h>

int main() {
    int n, i, j;
    int bt[20], p[20], pr[20], wt[20], tat[20], temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times and priorities:\n");
    for (i = 0; i < n; i++) {
        printf("P%d BT: ", i + 1);
        scanf("%d", &bt[i]);
        printf("P%d Priority (lower number = higher priority): ", i + 1);
        scanf("%d", &pr[i]);
        p[i] = i + 1;
    }
 
    // Sort based on priority
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (pr[i] > pr[j]) {
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("Process\tPriority\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t%d\t%d\n", p[i], pr[i], bt[i], wt[i], tat[i]);
    }

    printf("Average WT = %.2f\n", avg_wt / n);
    printf("Average TAT = %.2f\n", avg_tat / n);
    return 0;
}
