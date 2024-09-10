#ifndef PLAYER_H
#define PLAYER_H

typedef struct Player {
    char name[50];
    int lowestGuesses;
    int highestScore;
    int score;
} Player;

char* getName(Player* player);
int getLowestGuesses(Player* player);
int getHighestScore(Player* player);
int getScore(Player* player);
void setScore(Player* player, int score);
void setLowestGuesses(Player* player, int lowestGuesses);
void setHighestScore(Player* player, int highestScore);
int compareHighestScore(const void* a, const void* b);
int compareLowestGuesses(const void* a, const void* b);


#endif  // PLAYER_H
