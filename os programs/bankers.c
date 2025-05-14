#include <stdio.h>
#include <stdbool.h>

#define P 5  // Number of processes
#define R 3  // Number of resource types

int available[R];              // Available resources
int max[P][R];                 // Maximum demand of each process
int allocation[P][R];          // Resources currently allocated
int need[P][R];                // Remaining needs of each process

void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - allocation[i][j];
}

bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int k = 0; k < R; k++)
                        work[k] += allocation[i][k];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");
    return true;
}

bool requestResources(int process_id, int request[]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }

        if (request[i] > available[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Pretend to allocate
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (isSafe()) {
        printf("Request can be granted.\n");
        return true;
    } else {
        // Rollback
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        printf("Request leads to unsafe state. Denied.\n");
        return false;
    }
}

int main() {
    // Example initialization
    int i, j;

    printf("Enter allocation matrix (%d x %d):\n", P, R);
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter max matrix (%d x %d):\n", P, R);
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &max[i][j]);

    printf("Enter available resources (%d):\n", R);
    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);

    calculateNeed();

    if (!isSafe())
        return 1;

    // Optional: test a resource request
    int req[P][R], pid;
    printf("Enter process number (0-%d) to request resources: ", P - 1);
    scanf("%d", &pid);
    printf("Enter request for P%d (%d resources):\n", pid, R);
    for (i = 0; i < R; i++)
        scanf("%d", &req[pid][i]);

    requestResources(pid, req[pid]);

    return 0;
}


// input
// Enter allocation matrix (5 x 3):
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2

// Enter max matrix (5 x 3):
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3

// Enter available resources (3):
// 3 3 2

// Enter process number (0-4) to request resources: 1
// Enter request for P1 (3 resources):
// 1 0 2
