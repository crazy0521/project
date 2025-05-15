// form sorting, no. of vowels, 

2 - Fork sorting

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
  
void sort_desc(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void print_array(const char* label, int arr[], int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {5, 2, 8, 4, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        sort_desc(arr, n);
        print_array("Child sorted array", arr, n);
    } else {
        wait(NULL);  // Wait for child to complete
        sort_desc(arr, n);
        print_array("Parent sorted array", arr, n);
    }
    return 0;
}






3 - vfork() : no. of vowels in a sentence

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main() {
    char sentence[100];

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);

    int count = 0;
    pid_t pid = vfork();  // Use vfork() instead of fork()

    if (pid < 0) {
        perror("vfork failed");
        return 1;
    } else if (pid == 0) {
        // Child process
        for (int i = 0; sentence[i] != '\0'; i++) {
            char ch = tolower(sentence[i]);
            if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u') {
                count++;
            }
        }
        printf("Child: Number of vowels = %d\n", count);
        _exit(0);  // Must use _exit() with vfork
    } else {
        wait(NULL);
        printf("Parent: Child completed vowel counting.\n");
    }

    return 0;
}