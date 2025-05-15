8 - Bankers algorithm 

#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m; // n = number of processes, m = number of resources
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];
    int i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Maximum Requirement Matrix:\n");
    for(i = 0; i < n; i++) {
        printf("P[%d]: ", i);
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j]; // Calculate need matrix
        }
    }

    printf("Enter Available Resources: ");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    bool finish[MAX_PROCESSES] = {false};
    int safeSeq[MAX_PROCESSES];
    int count = 0;

    while(count < n) {
        bool found = false;
        for(i = 0; i < n; i++) {
            if(!finish[i]) {
                bool canAllocate = true;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if(canAllocate) {
                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k]; // Release resources
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if(!found) {
            printf("\nSystem is NOT in a safe state.\n");
            return 1;
        }
    }

    // If here, system is in a safe state
    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for(i = 0; i < n; i++) {
        printf("P[%d]", safeSeq[i]);
        if(i != n-1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}
