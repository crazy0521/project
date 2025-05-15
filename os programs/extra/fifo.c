#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

int main()
{
    int frames[MAX_FRAMES], pages[MAX_PAGES];
    int capacity, n, page_faults = 0, index = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &capacity);

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    for (int i = 0; i < capacity; i++)
    {
        frames[i] = -1;
    }

    printf("\nPage Replacement Process:\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int found = 0;

        for (int j = 0; j < capacity; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            frames[index] = page;
            index = (index + 1) % capacity;
            page_faults++;
            printf("Page %d -> ", page);
            for (int j = 0; j < capacity; j++)
            {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);
    return 0;
}

// input:
// Enter the number of frames: 3
// Enter the number of pages: 6
// Enter the reference string: 1 2 3 5 3 1
