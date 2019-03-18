//
// Created by cyberdoge on 3/15/19.
//
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
    int fd1;

    char *myfifo = "/tmp/myfifo";


    mkfifo(myfifo, 765);

    char inputStr[80], outputStr[80];
    fd1 = open(myfifo, O_RDWR);
    do {
        read(fd1, inputStr, 80);
        printf("server: %s\n", inputStr);
        fgets(outputStr, 80, stdin);
        write(fd1, outputStr, strlen(outputStr) + 1);
    }while(strcmp(outputStr, "exit"));
    close(fd1);
    return 0;
}