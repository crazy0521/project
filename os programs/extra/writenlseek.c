#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd;
    char data[] = "A Line1 of text1";
    char ch;
    fd = open("name1.txt", O_WRONLY | O_CREAT, 0666);
    write(fd, data, sizeof(data));
    close(fd);

    fd = open("name1.txt", O_RDONLY);
    // Move the file offset to the last 6 bytes from the end
    lseek(fd, -6, SEEK_END);
    while ((read(fd, &ch, sizeof(ch))) > 0)
    {
        printf("%c", ch);
        close(fd);
        printf("\n");
    }

    return 0;
}
