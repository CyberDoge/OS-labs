#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;

bool inLoop = true;
char *formula = new char[0];

const char *myfifo = "/tmp/myfifo";
const vector<string> commands{"exit", "clear", "count"};

int expression();

const char *parseInput(char *input, int type);

int validateAndParse(char *input);

void send(const char *outputStr) {
    int fd = open(myfifo, O_WRONLY);
    write(fd, outputStr, strlen(outputStr) + 1);
    close(fd);
};

char *read() {
    char *inputStr = new char[80];
    int fd = open(myfifo, O_RDONLY);
    read(fd, inputStr, 80);
    printf("User: %s\n", inputStr);
    close(fd);
    return inputStr;
}

int main() {
    remove(myfifo);

    if (mkfifo(myfifo, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH) < 0) {
        throw new runtime_error("cannot create pipe");
    }

    cout << "started" << endl;
    while (inLoop) {
        char *inputStr = read();

        int type = validateAndParse(inputStr);
        send(parseInput(inputStr, type));

    }
    return 0;
}

const char *parseInput(char *input, int type) {
    switch (type) {
        case 1:
            if (input == commands[0]) {
                inLoop = false;
                return "disconnect";
            } else if (input == commands[1]) {
                delete formula;
                return formula;

            } else if (input == commands[2]) {
                return to_string(expression()).c_str();
            }
        case 0:
            return strcat(formula, input);
        case -1:
            return "bad input";
        default:
            throw runtime_error("unknown error");
    }
}

int validateAndParse(char *input) {
    if (strlen(input) < 2 || !strcmp(input, "\0")) {
        return -1;
    }
    if (find(commands.begin(), commands.end(), input) != commands.end()) {
        return 1;
    }

    if (strlen(formula) != 0 && (input[0] != '-' && input[0] != '+' && input[0] != '*' && input[0] != '/')) {
        return -1;
    }

    for (int i = 0; i < strlen(input); ++i) {
        if (input[i] > 57 || input[i] < 42) {
            return -1;
        }
    }

    return 0;
}

int f_i;
char peek() {
    return formula[f_i];
}

char get() {
    return formula[f_i++];
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
    f_i = 0;
    int result = term();
    while (peek() == '+' || peek() == '-')
        if (get() == '+')
            result += term();
        else
            result -= term();
    return result;
}