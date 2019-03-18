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

char *formula;

vector<string> commands{"clear", "count"};

int expression();

int main() {
    int fd1;

    char *myfifo = "/tmp/myfifo";


    mkfifo(myfifo, O_RDWR);

    fd1 = open(myfifo, O_RDWR);

    char inputStr[80];
    char *outputStr;

    cout << "started" << endl;
    while (true) {
        read(fd1, inputStr, 80);
        cout << fd1 << endl;
        if (!strcmp(inputStr, "exit")) {
            write(fd1, "disconnect", 10);
            break;
        }
        int type = validateAndParse(inputStr);
        if (type < 0) {
            cout<<inputStr<<"bad str, type = "<<type<<endl;
            write(fd1, "bad input", 9);
            continue;
        }

        outputStr = parseInput(inputStr, type);

        write(fd1, outputStr, strlen(outputStr) + 1);
    }
    close(fd1);
    return 0;
}

char *parseInput(char *input, int type) {
    switch (type) {
        case 1:
            strcat(formula, input);
            return formula;
        case 2:
            return "hopa";

        default:
            throw runtime_error("unknown error");
    }
}


int validateAndParse(char *input) {
    if (strlen(input) == 0 || !strcmp(input, "\0")) {
        return -1;
    }

    string tmp(input);
    if (find(commands.begin(), commands.end(), tmp) != commands.end()) {
        return 1;
    }

    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] < 58 && input[i] > 39) {
            return 2;
        }
    }
    return -1;
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