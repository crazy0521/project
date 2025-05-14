// This code demonstrates how to open a file for writing, write data into the file, and then close the file using system calls in C.

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>


int main(){


int fd;

char data[] = "First Line\n Second Line\n Third Line\n";
fd = open("name1.txt",O_WRONLY|O_CREAT,0666);
write(fd,data,sizeof(data));
close(fd);
return 0;
}
