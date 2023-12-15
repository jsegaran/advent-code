#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

enum HandType {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

struct Hand {
    char cards[5];
    enum HandType type;
    int point;
};

int handCharToInt(char i);

int compareHands(struct Hand *handA, struct Hand *handB) {
    if (handA->type != handB->type) {
        return handA->type - handB->type;
    }

    for (int i = 0; i < 5; i++) {
        if (handCharToInt(handA->cards[i]) != handCharToInt(handB->cards[i])) {
            return handCharToInt(handA->cards[i]) - handCharToInt(handB->cards[i]);
        }
    }

    return 0;
}

int handCharToInt(char card) {
    int cardIndex = 0;
    switch (card) {
        case 'J':
            cardIndex = 0;
            break;
        case '2':
            cardIndex = 1;
            break;
        case '3':
            cardIndex = 2;
            break;
        case '4':
            cardIndex = 3;
            break;
        case '5':
            cardIndex = 4;
            break;
        case '6':
            cardIndex = 5;
            break;
        case '7':
            cardIndex = 6;
            break;
        case '8':
            cardIndex = 7;
            break;
        case '9':
            cardIndex = 8;
            break;
        case 'T':
            cardIndex = 9;
            break;
        case 'Q':
            cardIndex = 10;
            break;
        case 'K':
            cardIndex = 11;
            break;
        case 'A':
            cardIndex = 12;
            break;
        default:
            exit(1);
    }
    return cardIndex;
}

enum HandType getHandType(char* hand) {
    int cardCounts[13] = {0};

    for (int i = 0; i < 5; i++) {
        cardCounts[handCharToInt(hand[i])]++;
    }

    enum HandType type = HIGH_CARD;
    for (int i = 0; i < 13; i++) {
        int maxCardCount = i != 0 ? cardCounts[0] + cardCounts[i] : cardCounts[0];

        if (maxCardCount == 5) {
            type = FIVE_OF_A_KIND;
        }

        if (maxCardCount == 4) {
            type = max(type, FOUR_OF_A_KIND);
        }

        if (maxCardCount == 3) {
            for (int j = 1; j < 13; j++) {
                if (cardCounts[j] == 2 && j != i) {
                    type = max(type, FULL_HOUSE);
                }
            }
            type = max(type, THREE_OF_A_KIND);
        }

        if (maxCardCount == 2) {
            for (int j = 1; j < 13; j++) {
                if (cardCounts[j] == 2 && j != i) {
                    type = max(type, TWO_PAIR);
                }
                if (cardCounts[j] == 3) {
                    type = max(type, FULL_HOUSE);
                }
            }
            type = max(type, ONE_PAIR);
        }
    }
    return type;
}

int main(void) {
    struct Hand hands[1001];
    int handsIndex = 0;

    char line[1000] = {0};
    int64_t total = 0;

    while (fgets(line, 1000, stdin) != NULL) {
        strncpy(hands[handsIndex].cards, line, 5);

        hands[handsIndex].point = strtol(&line[5], NULL, 10);
        hands[handsIndex].type = getHandType(hands[handsIndex].cards);
        handsIndex++;
    }
    qsort(hands, handsIndex, sizeof(struct Hand), (int (*)(const void *, const void *)) compareHands);
    for (int i = 0; i < handsIndex; i++) {
        total += hands[i].point * (i + 1);
//        printf("%d: %d %s %d\n", i, hands[i].type, hands[i].cards, hands[i].point);
    }
    printf("result: %lld\n", total);
}