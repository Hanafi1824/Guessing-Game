#ifndef GAME_H
#define GAME_H

typedef struct Game {
    int numberOfGuesses;
    int totalScore;
    int (*generateTargetNumber)(struct Game*);
    int (*guessNumber)(struct Game*);
    void (*startGame)(struct Game*);
    char* (*startGame2)(struct Game*, const char*, const char*);
} Game;

void startGame(Game* game);
char* startGame2(Game* game, const char* player1, const char* player2);

#endif  // GAME_H
