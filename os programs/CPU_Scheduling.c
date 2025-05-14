#include <stdio.h>

struct Process {
    int pid;
    int bt;      // Burst Time
    int at;      // Arrival Time
    int pt;      // Priority
    int wt;      // Waiting Time
    int tat;     // Turnaround Time
    int rt;      // Remaining Time (for Round Robin)
};

void fcfs(struct Process p[], int n) {
    int time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\n--- FCFS Scheduling ---\n");
    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", p[i].pid);

    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

void sjf(struct Process p[], int n) {
    struct Process temp;
    float total_wt = 0, total_tat = 0;

    // Sort by burst time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (p[j].bt > p[j+1].bt) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }

    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\n--- SJF (Non-preemptive) Scheduling ---\nGantt Chart: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", p[i].pid);

    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

void priorityScheduling(struct Process p[], int n) {
    struct Process temp;
    float total_wt = 0, total_tat = 0;

    // Sort by priority (lower number = higher priority)
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (p[j].pt > p[j+1].pt) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }

    p[0].wt = 0;
    p[0].tat = p[0].bt;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i - 1].wt + p[i - 1].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }

    printf("\n--- Priority Scheduling ---\nGantt Chart: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", p[i].pid);

    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

void roundRobin(struct Process p[], int n, int quantum) {
    int time = 0, remain = n;
    float total_wt = 0, total_tat = 0;
    int done;

    printf("\n--- Round Robin Scheduling (Time Quantum = %d) ---\nGantt Chart: ", quantum);

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (remain != 0) {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0) {
                done = 0;
                if (p[i].rt > quantum) {
                    printf("P%d ", p[i].pid);
                    time += quantum;
                    p[i].rt -= quantum;
                } else {
                    printf("P%d ", p[i].pid);
                    time += p[i].rt;
                    p[i].wt = time - p[i].bt;
                    p[i].tat = time;
                    p[i].rt = 0;
                    remain--;
                }
            }
        }
        if (done) break;
    }

    for (int i = 0; i < n; i++) {
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main() {
    int n, choice, quantum;
    struct Process p[10], temp[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &p[i].bt);
        printf("Enter Priority for P%d: ", i + 1);
        scanf("%d", &p[i].pt);
    }

    do {
        for (int i = 0; i < n; i++) temp[i] = p[i];  // Copy original data for reuse
        printf("\nSelect Scheduling Algorithm:\n");
        printf("1. FCFS\n2. SJF (Non-preemptive)\n3. Priority Scheduling\n4. Round Robin\n5. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fcfs(temp, n); break;
            case 2: sjf(temp, n); break;
            case 3: priorityScheduling(temp, n); break;
            case 4:
                printf("Enter Time Quantum: ");
                scanf("%d", &quantum);
                roundRobin(temp, n, quantum);
                break;
            case 5: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}
