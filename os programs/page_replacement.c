// 1. FIFO (First-In-First-Out) Algorithm

#include <stdio.h>

void fifo(int reference[], int n, int frames) {
    int page[frames];
    int page_faults = 0;
    int next_frame = 0;

    for (int i = 0; i < frames; i++) {
        page[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (page[j] == reference[i]) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            page[next_frame] = reference[i];
            next_frame = (next_frame + 1) % frames;
            page_faults++;
        }

        printf("Frame after reference %d: ", reference[i]);
        for (int k = 0; k < frames; k++) {
            if (page[k] != -1) {
                printf("%d ", page[k]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int reference[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames = 3; // Number of frames

    fifo(reference, n, frames);
    return 0;
}


// 2. Optimal Page Replacement Algorithm (OPT)

#include <stdio.h>
#include <limits.h>

int findOptimal(int reference[], int frame[], int n, int f, int curr) {
    int farthest = curr;
    int page = -1;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = curr; j < n; j++) {
            if (frame[i] == reference[j]) {
                if (j > farthest) {
                    farthest = j;
                    page = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }
    return page;
}

void optimal(int reference[], int n, int frames) {
    int page[frames];
    int page_faults = 0;

    for (int i = 0; i < frames; i++) {
        page[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (page[j] == reference[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pageToReplace = findOptimal(reference, page, n, frames, i + 1);
            page[pageToReplace] = reference[i];
            page_faults++;
        }

        printf("Frame after reference %d: ", reference[i]);
        for (int k = 0; k < frames; k++) {
            if (page[k] != -1) {
                printf("%d ", page[k]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int reference[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames = 3;

    optimal(reference, n, frames);
    return 0;
}


// 3. Least Recently Used (LRU) Page Replacement Algorithm


#include <stdio.h>
#include <stdbool.h>

void lru(int reference[], int n, int frames) {
    int page[frames];
    int page_faults = 0;
    int timestamps[frames];
    for (int i = 0; i < frames; i++) {
        page[i] = -1;
        timestamps[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (page[j] == reference[i]) {
                found = 1;
                timestamps[j] = i;
                break;
            }
        }

        if (!found) {
            int replace = 0;
            for (int j = 1; j < frames; j++) {
                if (timestamps[j] < timestamps[replace]) {
                    replace = j;
                }
            }
            page[replace] = reference[i];
            timestamps[replace] = i;
            page_faults++;
        }

        printf("Frame after reference %d: ", reference[i]);
        for (int k = 0; k < frames; k++) {
            if (page[k] != -1) {
                printf("%d ", page[k]);
            }
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
}

int main() {
    int reference[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = sizeof(reference) / sizeof(reference[0]);
    int frames = 3;

    lru(reference, n, frames);
    return 0;
}
