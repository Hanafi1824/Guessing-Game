#ifndef GUESSNUMBERGAME_H
#define GUESSNUMBERGAME_H

#include "Game.h"

typedef struct {
    Game game;
    int minNumber;
    int maxNumber;
} GuessNumberGame;

GuessNumberGame* createGuessNumberGame(int minNumber, int maxNumber);
int generateTargetNumber(Game* game);
int guessNumber(Game* game);

#endif  // GUESSNUMBERGAME_H
