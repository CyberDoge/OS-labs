#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;

char *parseInput(char *input, int type);

int validateAndParse(char *input);

char *formula = new char[0];

vector<string> commands{"clear", "count"};

int expression();

int main() {

    char *myfifo = "/tmp/myfifo";

    remove(myfifo);

    int fd = mkfifo(myfifo, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    cout << "pipe " << fd << endl;

    char inputStr[80];
    char *outputStr;

    cout << "started" << endl;
    while (true) {

        fd = open(myfifo, O_RDONLY);
        read(fd, inputStr, 80);
        // Print the read string and close
        printf("User1: %s\n", inputStr);
        close(fd);
        if (!strcmp(inputStr, "exit")) {
            write(fd, "disconnect", 10);
            break;
        }
        int type = validateAndParse(inputStr);
        if (type < 0) {
            cout << inputStr << " bad str, type = " << type << endl;
            outputStr = "bad input\n";
        }else {
            outputStr = parseInput(inputStr, type);
        }
        fd = open(myfifo, O_WRONLY);
        write(fd, outputStr, strlen(outputStr) + 1);
        close(fd);
    }
    return 0;
}

char *parseInput(char *input, int type) {
    switch (type) {
        case 1:
            return "hopa";
        case 2:
            strcat(formula, input);
            return formula;
        default:
            throw runtime_error("unknown error");
    }
}

int validateAndParse(char *input) {
    if (strlen(input) < 2 || !strcmp(input, "\0")) {
        return -1;
    }

    input[strlen(input) - 1] = '\0';
    string tmp(input);

    if (find(commands.begin(), commands.end(), tmp) != commands.end()) {
        return 1;
    }

    if (input[0] != '-' && input[0] != '+' && input[0] != '*' && input[0] != '/') {
        return -1;
    }

    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] > 57 || input[i] < 40) {
            return -1;
        }
    }

    return 2;
}


char peek() {
    return *formula;
}

char get() {
    return *formula++;
}


int number() {
    int result = get() - '0';
    while (peek() >= '0' && peek() <= '9') {
        result = 10 * result + get() - '0';
    }
    return result;
}

int factor() {
    if (peek() >= '0' && peek() <= '9')
        return number();
    else if (peek() == '(') {
        get(); // '('
        int result = expression();
        get(); // ')'
        return result;
    } else if (peek() == '-') {
        get();
        return -factor();
    }
    return 0; // error
}

int term() {
    int result = factor();
    while (peek() == '*' || peek() == '/')
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    return result;
}

int expression() {
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}