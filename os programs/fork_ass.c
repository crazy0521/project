// Program 1: Sorting Array in Ascending and Descending Order using fork()

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void sort_asc(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sort_desc(int arr[], int n) {
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {12, 5, 3, 9, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    pid_t pid = fork();

    if(pid < 0) {
        printf("Fork failed.\n");
        return 1;
    }
    else if(pid == 0) {
        // Child process
        sort_asc(arr, n);
        printf("Child: Ascending order: ");
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }
    else {
        // Parent process
        wait(NULL); // Wait for child to complete
        sort_desc(arr, n);
        printf("Parent: Descending order: ");
        for(int i=0; i<n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    return 0;
}
