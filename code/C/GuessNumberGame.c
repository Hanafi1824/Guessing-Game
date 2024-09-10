#include "GuessNumberGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateTargetNumber(Game* game) {
    GuessNumberGame* guessNumberGame = (GuessNumberGame*)game;
    return (rand() %
            (guessNumberGame->maxNumber - guessNumberGame->minNumber + 1)) +
           guessNumberGame->minNumber;
}

int guessNumber(Game* game) {
    int guess;
    printf("\nGuess the number: ");
    scanf("%d", &guess);
    return guess;
}

GuessNumberGame* createGuessNumberGame(int minNumber, int maxNumber) {
    GuessNumberGame* game = (GuessNumberGame*)malloc(sizeof(GuessNumberGame));
    game->game.numberOfGuesses = 1;
    game->game.totalScore = 0;
    game->game.generateTargetNumber = generateTargetNumber;
    game->game.guessNumber = guessNumber;
    game->game.startGame = startGame;
    game->game.startGame2 = startGame2;
    game->minNumber = minNumber;
    game->maxNumber = maxNumber;

    return game;
}
