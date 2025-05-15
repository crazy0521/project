#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int do_parent(int num[], int sz)
{
    int max = num[0];
    for (int i = 1; i < sz; i++)
    {
        if (num[i] > max)
        {
            max = num[i];
        }
    }
    return max;
}

int do_child(int num[], int sz)
{
    int min = num[0];
    for (int i = 1; i < sz; i++)
    {
        if (num[i] < min)
        {
            min = num[i];
        }
    }
    return min;
}

int main()
{
    pid_t x;
    int num[50], sz, i, min, max;

    printf("Enter size:\n");
    scanf("%d", &sz);

    printf("Enter array elements:\n");
    for (i = 0; i < sz; i++)
    {
        scanf("%d", &num[i]);
    }

    printf("Before fork call\n");

    x = fork();

    if (x < 0) {
        perror("Fork failed");
        return 1;
    }

    if (x == 0)
    {
        printf("In child process x=%ld\n", (long)x);
        min = do_child(num, sz);
        printf("Min of array elements = %d\n", min);
    }
    else
    {
        wait(NULL);
        printf("In parent process x=%ld\n", (long)x);
        max = do_parent(num, sz);
        printf("Max of array elements = %d\n", max);
    }
    return 0;
}
