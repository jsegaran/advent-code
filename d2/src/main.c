#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Round {
    int blue;
    int green;
    int red;
};

struct RoundBound {
    int start;
    int end;
};

struct RoundBound findRound(char *line, int cursor) {
    struct RoundBound roundBound;
    roundBound.start = 0;
    roundBound.end = 0;

    // This is a bad if the first letter is 0, but that can never happen based on the inputs so its fine
    while (roundBound.start == 0 && cursor < strlen(line)) {
        if (line[cursor] == ';' || line[cursor] == ':') {
            roundBound.start = cursor;
        }
        cursor++;
    }

    while (roundBound.end == 0 && cursor < strlen(line)) {
        if (line[cursor] == ';' || line[cursor] == ':') {
            roundBound.end = cursor;
        }
        cursor++;
    }

    if (roundBound.start != 0 && roundBound.end == 0) {
        roundBound.end = cursor;
    }

    return roundBound;
}

struct Round extractRound(char *line, struct RoundBound roundBound) {
    struct Round round;
    round.blue = 0;
    round.green = 0;
    round.red = 0;

    int cursor = roundBound.start + 1;
    while (cursor < roundBound.end) {
        if (isdigit(line[cursor])) {
            int number = atoi(&line[cursor]);

            // Shift over to the space
            while (!isspace(line[cursor])) {
                cursor++;
            }

            if (line[cursor+1] == 'b') {
                round.blue = number;
            } else if (line[cursor + 1] == 'g') {
                round.green = number;
            } else if (line[cursor + 1] == 'r') {
                round.red = number;
            }
        }
        cursor++;
    }

    return round;
}

#define max(x,y) (((x) >= (y)) ? (x) : (y))

int main(void) {
    char line[1000];
    int total = 0;
    while (fgets(line, 1000, stdin) != NULL) {
        line[strcspn(line, "\n")] = 0;
        int id = atoi(&line[5]);
        int lastCursor = 5;
        struct Round minCubes;
        minCubes.blue = 0;
        minCubes.green = 0;
        minCubes.red = 0;
        do {
            struct RoundBound roundBound = findRound(line, lastCursor);
            lastCursor = roundBound.end;
            struct Round round = extractRound(line, roundBound);
            minCubes.red = max(minCubes.red, round.red);
            minCubes.blue = max(minCubes.blue, round.blue);
            minCubes.green = max(minCubes.green, round.green);
        } while (lastCursor < strlen(line));
        printf("%d: %d %d %d\n", id, minCubes.red, minCubes.green, minCubes.blue);
        total += minCubes.red * minCubes.green * minCubes.blue;
    }
    printf("result: %d\n", total);
}