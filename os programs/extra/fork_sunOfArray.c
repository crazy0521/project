#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void do_parent(int num[], int sz)
{
    int s = 0;
    for (int i = 0; i < sz; i++)
    {
        s = s + num[i];
    }
    printf("Sum of array elements = %d\n", s);
}

void do_child(int num[], int sz)
{
    int m = 1;
    for (int i = 0; i < sz; i++)
    {
        m = m * num[i];
    }
    printf("Product of array elements = %d\n", m);
}

int main()
{
    pid_t x;
    int num[100], sz;

    printf("Enter size:\n");
    scanf("%d", &sz);

    printf("Enter array elements:\n");
    for (int i = 0; i < sz; i++)
    {
        scanf("%d", &num[i]);
    }

    printf("Before fork call\n");

    x = fork();

    if (x == 0)
    {
        printf("In child process x=%d\n", x);
        do_child(num, sz);
    }
    else
    {
        wait(NULL);
        printf("In parent process x=%d\n", x);
        do_parent(num, sz);
    }

    return 0;
}
