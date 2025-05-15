// scheduling algorithms
// FCFS, SJF (preemptive), Round Robin Scheduling (preemptive), Priority Scheduling (not preemptive)



4 - FCFS 

#include <stdio.h>

int main() {
    int n, bt[20], wt[20], tat[20], i;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt/n);
    printf("Average Turnaround Time: %.2f\n", avg_tat/n);
    return 0;
}









5 - SJF - Preemptive

#include <stdio.h>

int main() {
    int n, i, j, smallest, time = 0, count = 0;
    int at[10], bt[10], rt[10], wt[10], tat[10];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time for each process:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d] Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("P[%d] Burst Time: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // Remaining time
    }

    int complete = 0;
    int minm = 9999;
    int finish_time;
    int shortest = 0;
    int check = 0;

    while (complete != n) {
        shortest = -1;
        minm = 9999;

        for (j = 0; j < n; j++) {
            if (at[j] <= time && rt[j] > 0 && rt[j] < minm) {
                minm = rt[j];
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            time++;
            continue;
        }

        rt[shortest]--;
        if (rt[shortest] == 0) {
            complete++;
            finish_time = time + 1;

            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        time++;
    }

    // Turnaround time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt / n);
    printf("Average Turnaround Time: %.2f\n", avg_tat / n);

    return 0;
}








6 - Round Robin - Preemptive

#include <stdio.h>

int main() {
    int n, i, qt, count = 0, temp, sq = 0;
    int bt[10], rt[10], wt[10] = {0}, tat[10] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i+1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &qt);

    while(1) {
        int done = 1;
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                done = 0;
                if(rt[i] > qt) {
                    sq += qt;
                    rt[i] -= qt;
                } else {
                    sq += rt[i];
                    wt[i] = sq - bt[i];
                    rt[i] = 0;
                }
            }
        }
        if(done) break;
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nProcess\tBT\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("P[%d]\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt/n);
    printf("Average Turnaround Time: %.2f\n", avg_tat/n);
    return 0;
}








7 - Priority Scheduling - Non Preemptive

#include <stdio.h>

int main() {
    int n, bt[20], p[20], pr[20], wt[20], tat[20], i, j, temp;
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter burst time and priority for P[%d]: ", i+1);
        scanf("%d %d", &bt[i], &pr[i]);
        p[i] = i+1;
    }

    // Sort by priority (lower number = higher priority)
    for(i = 0; i < n-1; i++) {
        for(j = i+1; j < n; j++) {
            if(pr[i] > pr[j]) {
                temp = pr[i]; pr[i] = pr[j]; pr[j] = temp;
                temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for(i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }

    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tBT\tPriority\tWT\tTAT\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]\t%d\t%d\t\t%d\t%d\n", p[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("Average Waiting Time: %.2f\n", avg_wt/n);
    printf("Average Turnaround Time: %.2f\n", avg_tat/n);
    return 0;
}