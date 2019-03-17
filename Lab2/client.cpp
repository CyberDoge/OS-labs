//
// Created by cyberdoge on 3/15/19.
//
#include <iostream>
#include <sys/stat.h>
#include <bits/fcntl-linux.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main(){
    char* pipe_f = "/opt/my_pipe";
    mkfifo(pipe_f, 765);
    char arr1[80], arr2[80];
    int fd;
    while (1)
    {
        // Open FIFO for write only
        fd = open(pipe_f, O_WRONLY);

        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);

        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2)+1);
        close(fd);

        // Open FIFO for Read only
        fd = open(pipe_f, O_RDONLY);

        // Read from FIFO
        read(fd, arr1, sizeof(arr1));

        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
    }
}