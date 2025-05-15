// 6 - Page Replacement Algorithms (FIFO, LRU, Optimal)

FIFO 

#include <stdio.h>

int main() {
    int frames, pages, i, j, k, page_faults = 0;
    int ref[100], mem[10], pos = 0, flag;

    printf("Enter number of pages: ");
    scanf("%d", &pages);
    printf("Enter reference string: ");
    for(i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++) mem[i] = -1;

    printf("\nFIFO Page Replacement:\n");

    for(i = 0; i < pages; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(mem[j] == ref[i]) {
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            mem[pos] = ref[i];
            pos = (pos + 1) % frames;
            page_faults++;
        }

        printf("Frame content: ");
        for(k = 0; k < frames; k++)
            printf("%d ", mem[k]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", page_faults);
    return 0;
}








LRU 

#include <stdio.h>

int findLRU(int time[], int n) {
    int i, min = time[0], pos = 0;
    for(i = 1; i < n; i++) {
        if(time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int frames, pages, i, j, k, time[10], counter = 0, page_faults = 0, pos;
    int mem[10], ref[100], flag;

    printf("Enter number of pages: ");
    scanf("%d", &pages);
    printf("Enter reference string: ");
    for(i = 0; i < pages; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for(i = 0; i < frames; i++) {
        mem[i] = -1;
        time[i] = 0;
    }

    printf("\nLRU Page Replacement:\n");

    for(i = 0; i < pages; i++) {
        flag = 0;
        for(j = 0; j < frames; j++) {
            if(mem[j] == ref[i]) {
                flag = 1;
                time[j] = ++counter;
                break;
            }
        }
        if(flag == 0) {
            if(i < frames) {
                mem[i] = ref[i];
                time[i] = ++counter;
            } else {
                pos = findLRU(time, frames);
                mem[pos] = ref[i];
                time[pos] = ++counter;
            }
            page_faults++;
        }

        printf("Frame content: ");
        for(k = 0; k < frames; k++)
            printf("%d ", mem[k]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", page_faults);
    return 0;
}







Optimal 

#include <stdio.h>

int search(int key, int frame[], int frames) {
    for(int i = 0; i < frames; i++)
        if(frame[i] == key)
            return 1;
    return 0;
}

int predict(int ref[], int frame[], int index, int n, int frames) {
    int res = -1, farthest = index;
    for(int i = 0; i < frames; i++) {
        int j;
        for(j = index; j < n; j++) {
            if(frame[i] == ref[j]) {
                if(j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if(j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int n, frames;
    int ref[100], frame[10], page_faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for(int i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    int filled = 0;

    printf("\nOptimal Page Replacement:\n");

    for(int i = 0; i < n; i++) {
        if(search(ref[i], frame, filled)) {
            // hit
        } else {
            if(filled < frames)
                frame[filled++] = ref[i];
            else {
                int pos = predict(ref, frame, i + 1, n, frames);
                frame[pos] = ref[i];
            }
            page_faults++;
        }

        printf("Frame content: ");
        for(int j = 0; j < filled; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", page_faults);
    return 0;
}