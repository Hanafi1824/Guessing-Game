#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Game.h"
#include "GuessNumberGame.h"
#include "Player.h"
#include "PlayerDatabase.h"
#include "utils.h"

// Main function
int main() {
    char start;
    char name[50];
    int command;
    int mode;
    int level;
    int board;
    PlayerDatabase database;
    // database.numPlayers = 0;
    // database.players = NULL;

    printf("       _________  __   __    _____     _____    ____\n");
    printf("      //   _____  ||   ||  //  ___|  //  ___|  //   \\\\ \n");
    printf("     ||   |____ | ||   || ||  ___|  ||  ___|  ||_____ \n");
    printf("     ||  ______|| ||   || ||  \\\\___ ||  \\\\___        || \n");
    printf("      \\\\_______//  \\\\__//  \\\\______| \\\\______| \\\\____// \n");

    printf(" __      __   __   __    __  ______     ______    _____ \n");
    printf("||\\\\  || ||   ||  ||\\\\  //| ||   _ \\   //  ___|  ||  _ \\ \n");
    printf("|| \\\\ || ||   ||  || \\\\//|| ||   __/  ||  ___|   || ____| \n");
    printf("||  \\\\|| ||   ||  ||     || ||   _ \\  ||  \\\\___   ||   \\\\ \n");
    printf("||   \\\\|  \\\\__//  ||     || ||_____/   \\\\_____|  ||    \\\\ \n");
    printf("        _________  ______   ___   __   ______ \n");
    printf("       //   _____  || _ || ||\\\\  //|  //  ___| \n");
    printf("      ||   |____ | ||___|| || \\\\//|| ||  ___| \n");
    printf("      ||  ______|| ||   || ||     || ||  \\\\___ \n");
    printf("       \\\\_______// ||   || ||     ||  \\\\______| \n");

    printf("\n[Reminder:]");
    printf("\n|Input all commands in the command section.");
    printf("\n|Type [y] or [n] for other prompts outside the game.");

    printf("\n\n>> Start? Enter [Y].");
    printf("\n<< Command: ");
    scanf(" %c", &start);
    start = toupper(start);

    while (start == 'Y') {
        printf("\033[H\033[2J");  // clear output

        printf("============ GUESS NUMBER GAME ================\n");
        printf("[0] Game rules.\n");
        printf("[1] Start the game.\n");
        printf("[2] View leaderboard.\n");
        printf("[3] Exit the game.\n");
        printf("\n<< Command: ");
        scanf("%d", &command);

        if (command == 0) {
            int rules;
            printf("\033[H\033[2J");  // clear output
            printf("Select LeaderBoard Type:\n");
            printf("[1] Solo Challenge: Face the computer.\n");
            printf("[2] Battle mode: Compete with friends.\n");
            printf("\n<< Command: ");
            scanf("%d", &rules);
            printf("\033[H\033[2J");  // clear output
            printf("============================== GAME RULES ====================================\n");

            if (rules == 1) {
                printf("<[                        Solo Challenge Rules                              ]>\n");
                printf("[1] Guess a number based on the difficulty mode.\n");
                printf("[2] Fewer attempts means a higher score.\n");
                printf("[3] Match the computer's number to win.\n");
                printf("[4] Follow the computer's hints to succeed.\n");
                printf("\n>> Continue?\n");
                printf("\n<< Command: ");
                scanf(" %c", &start);
                start = toupper(start);
            } else if (rules == 2) {
                printf("<[                          Battle Mode Rules                               ]>\n");
                printf("[1] Guess a number based on the chosen levels.\n");
                printf("[2] Earn points for guessing the target number before others.\n");
                printf("[3] Score increases with each correct guess.\n");
                printf("[4] Gain 10 points per round.\n");
                printf("\n>> Continue?\n");
                printf("\n<< Command: ");
                scanf(" %c", &start);
                start = toupper(start);
            }
        }

        if (command == 1) {
            Game* game;
            printf("Choose Your Gameplay:\n");
            printf("[1] Solo Challenge: Face the computer.\n");
            printf(
                "[2] Battle mode: Compete with friends.\
            \n\n<< Command: ");
            scanf("%d", &mode);

            // SOLO CHALLENGE:
            if (mode == 1) {
                printf("What's your name my friend?\n");
                printf("<< Name: ");
                scanf("%s", name);

                printf("\nSelect Gameplay Difficulty:\n");
                printf("[1] Easy mode: Guess between 1 and 50.\n");
                printf("[2] Normal mode: Guess between 1 and 100.\n");
                printf("[3] Extreme mode: Guess between 1 and 1000.\n");
                printf("\n<< Choose your level (1-3): ");
                scanf("%d", &level);

                if (level == 1) {
                    printf("\033[H\033[2J");  // clear output
                    printf("<[        Easy mode         ]>\n");
                    game = (Game*)createGuessNumberGame(1, 50);

                } else if (level == 2) {
                    printf("\033[H\033[2J");  // clear output
                    printf("<[        Normal mode         ]>\n");
                    game = (Game*)createGuessNumberGame(1, 100);
                } else if (level == 3) {
                    printf("\033[H\033[2J");  // clear output
                    printf("<[        Extreme mode         ]>\n");
                    game = (Game*)createGuessNumberGame(1, 1000);
                }
                printf("\nAre you ready? Good luck!\n");
                printf(">> Enter [Y] to continue.\n");
                printf(">> Enter [N] to exit.\n");
                printf("\n<< Command: ");
                scanf(" %c", &start);
                start = toupper(start);

                if (start == 'Y') {
                    printf("\033[H\033[2J");  // clear output
                    printf("\n============ GAME START!! ================\n");
                    // start the game
                    startGame(game);

                    PlayerDatabase* playerDatabase = createPlayerDatabase("SinglePlayerGame.txt");
                    if (playerDatabase == NULL) {
                        printf("Failed to create player database.\n");
                        return 1;  // Exit with an error code
                    }
                    addOrUpdatePlayer(playerDatabase, name, game->numberOfGuesses);

                    printf("\nPlayer name: %s\n", name);
                    printf("\nPlay again?\n");
                    printf(">> Enter [Y] to continue.\n");
                    printf(">> Enter [N] to exit.\n");
                    printf("\n<< Command: ");
                    scanf(" %c", &start);
                    start = toupper(start);
                    if (start != 'Y' && start != 'N') {
                        printf("Invalid command entered.\n");
                        // Handle the invalid input
                    }
                }
            }

            // multiplayer mode
            else if (mode == 2) {
                // define player 1 and player 2
                char player1[50];
                char player2[50];
                printf("Enter your name to begin your challenge!\n");
                printf("\nPlayer 1:\n");
                printf("<< Command: ");
                scanf("%s", player1);
                printf("\nPlayer 2:\n");
                printf("<< Command: ");
                scanf("%s", player2);

                printf("\nChoose your challenge level (number of rounds):\n");
                printf("\n<< Command: ");
                scanf("%d", &level);

                PlayerDatabase* multiplayerDatabase = createPlayerDatabase("MultiplayerGame.txt");
                printf("\033[H\033[2J");  // clear output
                char* winner = NULL;      // Declare winner outside the loop
                int score = 10;           // Points per win
                for (int i = 0; i < level; i++) {
                    printf("\n============ GAME START!! ================\n");
                    printf("          <[   Round %d    ]>\n", i + 1);
                    game = (Game*)createGuessNumberGame(1, 50);
                    winner = startGame2(game, player1, player2);  // Assign winner

                    if (winner != NULL) {
                        printf("\nCongratulations, %s!\n", winner);
                        addOrUpdatePlayer2(multiplayerDatabase, winner, score);  // Update score after each round
                    }
                }

                printf("\nPlay again?\n");
                printf(">> Enter [Y] to continue.\n");
                printf(">> Enter [N] to exit.\n");
                printf("\n<< Command: ");
                scanf(" %c", &start);
                start = toupper(start);
            }
        }

        if (command == 2) {
            int board;
            printf("Select LeaderBoard Type:\n");
            printf("[1] Solo Challenge: Face the computer.\n");
            printf("[2] Battle mode: Compete with friends.\n");
            printf("\n<< Command: ");
            scanf("%d", &board);
            printf("\033[H\033[2J");  // clear output
            printf("====================== LEADERBOARD ========================\n");

            // SINGLEPLAYER LEADERBOARD:
            if (board == 1) {
                FILE* file = fopen("SinglePlayerGame.txt", "r");
                if (file == NULL) {
                    printf("Failed to open the file.\n");
                    return 1;
                }

                Player players[100];  // Assuming there are no more than 100 players
                int playerCount = 0;
                char line[100];

                while (fgets(line, sizeof(line), file)) {
                    char* token = strtok(line, ",");
                    strcpy(players[playerCount].name, token);
                    token = strtok(NULL, ",");
                    players[playerCount].lowestGuesses = atoi(token);
                    playerCount++;
                }
                fclose(file);

                qsort(players, playerCount, sizeof(Player), compareLowestGuesses);

                printf("<[  Top 3 Players with Lowest Guesses in Solo Challenge  ]>\n");
                for (int i = 0; i < (playerCount < 3 ? playerCount : 3); i++) {
                    printf("%d. %s: %d\n", i + 1, players[i].name, players[i].lowestGuesses);
                }
            }

            // MULTIPLAYER LEADERBOARD:
            else if (board == 2) {
                FILE* file = fopen("MultiplayerGame.txt", "r");
                if (file == NULL) {
                    printf("Failed to open the file.\n");
                    return 1;
                }

                Player players[100];  // Assuming there are no more than 100 players
                int playerCount = 0;
                char line[100];

                while (fgets(line, sizeof(line), file)) {
                    char* token = strtok(line, ",");
                    strcpy(players[playerCount].name, token);
                    token = strtok(NULL, ",");
                    players[playerCount].highestScore = atoi(token);
                    playerCount++;
                }
                fclose(file);

                qsort(players, playerCount, sizeof(Player), compareHighestScore);
                printf("THIS WORK");


                printf("<[  Top 3 Players with Highest Score in Battlemode  ]>\n");
                for (int i = 0; i < (playerCount < 3 ? playerCount : 3); i++) {
                    printf("%d. %s: %d\n", i + 1, players[i].name, players[i].highestScore);
                }
            }
        }

        if (command == 3) {
            printf("\033[H\033[2J");  // clear output
            printf("Do you want to exit?\n");
            printf(">> Enter [Y] to continue.\n");
            printf(">> Enter [N] to exit.\n");
            printf("\n<< Command: ");
            scanf(" %c", &start);
            start = toupper(start);
        }

        printf("\033[H\033[2J");  // clear output
        printf("You are now leaving the game.\n");
        printf("Thanks for playing, see you again soon!\n");
    }

    return 0;
}