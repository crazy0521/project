#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    char ch;
    int fd = open("name1.txt", O_RDONLY);
    if (fd == -1)
    {

        printf("file open error");

        exit(-1);
    }
    else
    {

        printf("File Open Success");
        while ((read(fd, &ch, 1) > 0))
        {

            printf("%c", ch);
        }
        close(fd);
    }

    return 0;
}
