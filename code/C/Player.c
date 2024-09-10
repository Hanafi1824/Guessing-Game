#include "Player.h"

#include <stdlib.h>
#include <string.h>

char* getName(Player* player) {
    return player->name;
}

int getLowestGuesses(Player* player) {
    return player->lowestGuesses;
}

int getHighestScore(Player* player) {
    return player->highestScore;
}

int getScore(Player* player) {
    return player->score;
}

void setScore(Player* player, int score) {
    player->score = score;
}

void setLowestGuesses(Player* player, int lowestGuesses) {
    player->lowestGuesses = lowestGuesses;
}

void setHighestScore(Player* player, int highestScore) {
    player->highestScore = highestScore;
}

int compareHighestScore(const void* a, const void* b) {
    Player* playerA = *(Player**)a;
    Player* playerB = *(Player**)b;
    return playerB->highestScore - playerA->highestScore;
}

int compareLowestGuesses(const void* a, const void* b) {
    Player* playerA = (Player*)a;
    Player* playerB = (Player*)b;
    return playerA->lowestGuesses - playerB->lowestGuesses;
}