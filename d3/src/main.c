#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

struct Round {
    int blue;
    int green;
    int red;
};

struct RoundBound {
    int start;
    int end;
};

bool isSymbol(char *line, int i) {
    return (!(isalnum(line[i]) || line[i] == '.' || line[i] == 0));
}

bool containsSymbol(char *line, int startIndex, int endIndex) {
    for (int i = startIndex; i < endIndex; i++) {
        if (isSymbol(line, i))
            return true;
    }
    return false;
}

int step(char *lastLine, char *line, char *nextLine) {
    char *cursor = line;
    int result = 0;
    while (cursor < line + strlen(line)) {
        if (isdigit(*cursor)) {
            int startIndex = max(cursor - line - 1, 0);
            int curNumber = strtol(cursor, &cursor, 10);
            int endIndex = min(cursor - line + 1, strlen(line));

            bool isPart =
                    containsSymbol(lastLine, startIndex, endIndex) || containsSymbol(nextLine, startIndex, endIndex) ||
                    isSymbol(line, startIndex) || isSymbol(line, endIndex - 1);
            if (isPart) {
                result += curNumber;
            }
        } else {
            cursor++;
        }
    }
    strcpy(lastLine, line);
    strcpy(line, nextLine);
    return result;
}

int main(void) {
    char line[1000] = {0};
    char lastLine[1000] = {0};
    char nextLine[1000] = {0};
    int total = 0;

    while (fgets(nextLine, 1000, stdin) != NULL) {
        total += step(lastLine, line, nextLine);
    }
    strcpy(nextLine, "");
    total += step(lastLine, line, nextLine);
    printf("result: %d\n", total);
}