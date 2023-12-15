#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

int compare (const void *a, const void *b)
{
    const int *ia = (const int *)a; // casting pointer types
    const int *ib = (const int *)b;
    return *ia  - *ib;
}


int main(void) {
    char line[1000] = {0};
    int total = 0;

    while (fgets(line, 1000, stdin) != NULL) {
        char* cursor = line;
        bool isWinningNumber = true;
        int winningNumberLen = 0;
        int winningNumbers[15] = {0};
        int myNumberLen = 0;
        int myNumbers[100]  = {0};
        while( cursor < line + strlen(line)) {
            if (isdigit(*cursor)) {
                int curNumber = strtol(cursor, &cursor, 10);
                if (isWinningNumber) {
                    winningNumbers[winningNumberLen] = curNumber;
                    winningNumberLen++;
                } else {
                    myNumbers[myNumberLen] = curNumber;
                    myNumberLen++;
                }
            } else if (*cursor == '|') {
                isWinningNumber = false;
                cursor++;
            } else {
                cursor++;
            }
        }
        qsort(winningNumbers, winningNumberLen, sizeof(int), (int (*)(const void *, const void *)) compare);
        qsort(myNumbers, myNumberLen, sizeof(int), (int (*)(const void *, const void *)) compare);
        printf("winning numbers: ");
        for (int i = 0; i < winningNumberLen; i++) {
            printf("%d ", winningNumbers[i]);
        }
        printf("\n");
        printf("my numbers: ");
        for (int i = 0; i < myNumberLen; i++) {
            printf("%d ", myNumbers[i]);
        }
        printf("\n");
        int points = 0;
        for (int i = 0; i < myNumberLen; i++) {
            for (int j = 0; j < winningNumberLen; j++) {
                if (myNumbers[i] == winningNumbers[j]) {
                    if (points == 0) {
                        points = 1;
                    } else {
                        points *= 2;
                    }
                    break;
                }
            }
        }
        total += points;
        printf("points: %d\n", points);
    }
    printf("result: %d\n", total);
}