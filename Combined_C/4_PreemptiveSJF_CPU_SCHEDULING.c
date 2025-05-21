#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int bt[n], at[n], rt[n], wt[n], tat[n];
    printf("Enter arrival and burst times:\n");
    for(int i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    int complete = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;
    int check = 0;

    while(complete != n) {
        minm = INT_MAX;
        check = 0;
        for(int j = 0; j < n; j++) {
            if((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if(check == 0) {
            t++;
            continue;
        }

        rt[shortest]--;
        if(rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if(wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }

    for(int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    printf("Process\tBT\tAT\tWT\tTAT\n");
    for(int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, bt[i], at[i], wt[i], tat[i]);

    return 0;
}
