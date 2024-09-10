#include "Game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void startGame(Game* game) {
    int targetNumber = game->generateTargetNumber(game);
    while (1) {
        int guessedNumber = game->guessNumber(game);
        if (guessedNumber > targetNumber) {
            printf("COMPUTER: <Too high>\n");
        } else if (guessedNumber < targetNumber) {
            printf("COMPUTER: <Too low>\n");
        } else {
            printf("\033[H\033[2J");  // clear output
            printf("\n+++++++++++++ GAME COMPLETED! ++++++++++++++\n");
            printf("\nCongratulations, my friend!\n");
            break;
        }
        game->numberOfGuesses++;
    }
    printf("You guessed it in about %d attempts!\n", game->numberOfGuesses);
}

char* startGame2(Game* game, const char* player1, const char* player2) {
    int targetNumber = game->generateTargetNumber(game);
    char* winner = (char*)malloc(50 * sizeof(char));
    while (1) {
        int guessedNumber1, guessedNumber2;

        // PLAYER 1:
        printf("\n%s, guess the number: ", player1);
        scanf("%d", &guessedNumber1);
        if (guessedNumber1 > targetNumber) {
            printf("COMPUTER: <Too high>\n");
        } else if (guessedNumber1 < targetNumber) {
            printf("COMPUTER: <Too low>\n");
        } else {
            printf("\033[H\033[2J");  // clear output
            printf("\n+++++++++++++ GAME COMPLETED! ++++++++++++++\n");
            printf("\nCongratulations, %s!\n", player1);
            printf("<10 points for player 1!>\n");
            strcpy(winner, player1);
            return winner;
        }

        // PLAYER 2:
        printf("\n%s, guess the number: ", player2);
        scanf("%d", &guessedNumber2);
        if (guessedNumber2 > targetNumber) {
            printf("COMPUTER: <Too high>\n");
        } else if (guessedNumber2 < targetNumber) {
            printf("COMPUTER: <Too low>\n");
        } else {
            printf("\033[H\033[2J");  // clear output
            printf("\n+++++++++++++ GAME COMPLETED! ++++++++++++++\n");
            printf("\nCongratulations, %s!\n", player2);
            printf("<10 points for player 2!>\n");
            strcpy(winner, player2);
            return winner;
        }
    }
}
