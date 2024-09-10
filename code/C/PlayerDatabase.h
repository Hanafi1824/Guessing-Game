#ifndef PLAYER_DATABASE_H
#define PLAYER_DATABASE_H

#include <stdbool.h>

#include "Player.h"

typedef struct PlayerDatabase {
    Player** players;
    int playerCount;
    char* fileName;
} PlayerDatabase;

PlayerDatabase* createPlayerDatabase(char* fileName);
void addOrUpdatePlayer(PlayerDatabase* db, char* name, int attempts);
void addOrUpdatePlayer2(PlayerDatabase* db, char* name, int scores);
Player* getPlayer(PlayerDatabase* db, char* name);
Player* readPlayersFromFile(PlayerDatabase* db);
void writePlayersToFile(PlayerDatabase* db);
Player** getTopPlayers(PlayerDatabase* db, int count);

#endif  // PLAYER_DATABASE_H
