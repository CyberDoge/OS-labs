//
// Created by cyberdoge on 3/15/19.
//
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>

using namespace std;

int main() {
    char *myfifo = "/tmp/myfifo";

    int fd;
    char inputStr[80], outputStr[80];
    do {
        fd = open(myfifo, O_WRONLY);
        fgets(outputStr, 80, stdin);
        outputStr[strlen(outputStr) - 1] = '\0';
        write(fd, outputStr, strlen(outputStr) + 1);
        close(fd);

        fd = open(myfifo, O_RDONLY);

        read(fd, inputStr, sizeof(inputStr));

        printf("server: %s\n", inputStr);
        close(fd);
    } while (strcmp(inputStr, "disconnect"));
    cout << "exit" << endl;
    return 0;
}