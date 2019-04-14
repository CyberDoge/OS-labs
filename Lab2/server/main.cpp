#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <algorithm>

using namespace std;

bool inLoop = true;
bool connected = false;
string *formula;

const char *myfifo = "/tmp/myfifo";
const vector<string> commands{"", "exit", "clear", "count"};

int expression();

const char *parseInput(char *input, int type);

int validateAndParse(char *input);

void send(const string *outputStr) {
    int fd = open(myfifo, O_WRONLY);
    write(fd, outputStr->c_str(), outputStr->length() + 1);
    close(fd);
};

char *read() {
    char *inputStr = new char[80];
    int fd = open(myfifo, O_RDONLY);
    if(!connected){
        cout<<"user connected"<<endl;
        connected = true;
    }
    read(fd, inputStr, 80);
    if (strlen(inputStr))
        printf("User: %s\n", inputStr);
    close(fd);
    return inputStr;
}

void circle() {
    remove(myfifo);

    if (mkfifo(myfifo, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH) < 0) {
        throw new runtime_error("cannot create pipe");
    }
    if (formula != nullptr) {
        formula->clear();
    }
    formula = new string();
    while (inLoop) {
        char *inputStr = read();
        int type = validateAndParse(inputStr);
        if (type == -2) {
            cout << "user disconnect" << endl;
            connected = false;
            circle();
        }
        string *message = new string(parseInput(inputStr, type));
        send(message);
        message->clear();
        delete[] inputStr;
    }
}

int main() {
    circle();
    return 0;
}

const char *parseInput(char *input, int type) {
    switch (type) {
        case 1:
            if (input == commands[1]) {
                connected = false;
                return "disconnect";
            } else if (input == commands[2]) {
                formula->clear();
                return "cleared";

            } else if (input == commands[3]) {
                return to_string(expression()).c_str();
            }
        case 0:
            return formula->append(input).c_str();
        case -1:
            return "bad input";
        default:
            throw runtime_error("unknown error");
    }
}

int validateAndParse(char *input) {
    if (!strcmp(input, "")) return -2;
    if ((formula->length() != 0 && strlen(input) < 2) || !strcmp(input, "\0")) {
        return -1;
    }
    if (find(commands.begin(), commands.end(), input) != commands.end()) {
        return 1;
    }

    if (formula->length() != 0 && (input[0] != '-' && input[0] != '+' && input[0] != '*' && input[0] != '/')) {
        return -1;
    }

    for (int i = 1; i < strlen(input); ++i) {
        if (input[i] > 57 || input[i] < 48) {
            return -1;
        }
    }

    return 0;
}

unsigned long f_i;

char peek() {
    return formula->at(f_i);
}

char get() {
    return formula->at(f_i++);
}


int number() {
    int result = get() - '0';
    while (f_i < formula->length() && peek() >= '0' && peek() <= '9') {
        result = 10 * result + get() - '0';
    }
    return result;
}

int factor() {
    if (f_i < formula->length() && peek() >= '0' && peek() <= '9')
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
    while (f_i < formula->length() && (peek() == '*' || peek() == '/')) {
        if (get() == '*')
            result *= factor();
        else
            result /= factor();
    }
    return result;
}

int expression() {
    f_i = 0;
    int result = term();
    while (f_i < formula->length() && (peek() == '+' || peek() == '-')) {
        if (get() == '+')
            result += term();
        else
            result -= term();
    }
    return result;
}