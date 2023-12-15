#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


bool isOne(char *line, int cursor) {
    if (strlen(line) < 3) {
        return false;
    }
    return line[cursor] == 'o' && line[cursor + 1] == 'n' && line[cursor + 2] == 'e';
}

bool isTwo(char *line, int cursor) {
    if (strlen(line) < 3) {
        return false;
    }
    return line[cursor] == 't' && line[cursor + 1] == 'w' && line[cursor + 2] == 'o';
}

bool isThree(char *line, int cursor) {
    if (strlen(line) < 5) {
        return false;
    }
    return line[cursor] == 't' && line[cursor + 1] == 'h' && line[cursor + 2] == 'r' && line[cursor + 3] == 'e' &&
           line[cursor + 4] == 'e';
}

bool isFour(char *line, int cursor) {
    if (strlen(line) < 4) {
        return false;
    }
    return line[cursor] == 'f' && line[cursor + 1] == 'o' && line[cursor + 2] == 'u' && line[cursor + 3] == 'r';
}

bool isFive(char *line, int cursor) {
    if (strlen(line) < 4) {
        return false;
    }
    return line[cursor] == 'f' && line[cursor + 1] == 'i' && line[cursor + 2] == 'v' && line[cursor + 3] == 'e';
}

bool isSix(char *line, int cursor) {
    if (strlen(line) < 3) {
        return false;
    }
    return line[cursor] == 's' && line[cursor + 1] == 'i' && line[cursor + 2] == 'x';
}

bool isSeven(char *line, int cursor) {
    if (strlen(line) < 5) {
        return false;
    }
    return line[cursor] == 's' && line[cursor + 1] == 'e' && line[cursor + 2] == 'v' && line[cursor + 3] == 'e' &&
           line[cursor + 4] == 'n';
}

bool isEight(char *line, int cursor) {
    if (strlen(line) < 5) {
        return false;
    }
    return line[cursor] == 'e' && line[cursor + 1] == 'i' && line[cursor + 2] == 'g' && line[cursor + 3] == 'h' &&
           line[cursor + 4] == 't';
}

bool isNine(char *line, int cursor) {
    if (strlen(line) < 4) {
        return false;
    }
    return line[cursor] == 'n' && line[cursor + 1] == 'i' && line[cursor + 2] == 'n' && line[cursor + 3] == 'e';
}

int main(void) {
    char line[1000];
    int total = 0;
    while (fgets(line, 1000, stdin) != NULL) {
        int result = 0;
        int lastSeen = 0;
        int cursor = 0;
        while (cursor < strlen(line)) {
            if (isdigit(line[cursor])) {
                char copy = line[cursor];
                lastSeen = atoi(&copy);
            } else if (isOne(line, cursor)) {
                lastSeen = 1;
            } else if (isTwo(line, cursor)) {
                lastSeen = 2;
            } else if (isThree(line, cursor)) {
                lastSeen = 3;
            } else if (isFour(line, cursor)) {
                lastSeen = 4;
            } else if (isFive(line, cursor)) {
                lastSeen = 5;
            } else if (isSix(line, cursor)) {
                lastSeen = 6;
            } else if (isSeven(line, cursor)) {
                lastSeen = 7;
            } else if (isEight(line, cursor)) {
                lastSeen = 8;
            } else if (isNine(line, cursor)) {
                lastSeen = 9;
            }
            cursor++;

            if (result == 0 && lastSeen != 0)
                result = lastSeen * 10;
        }
        result += lastSeen;
        printf("line: %s %d\n", line, result);
        total += result;
    }
    printf("result: %d\n", total);
}