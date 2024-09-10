#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int lowestGuesses;
    int highestScore;
} Player;

typedef struct {
    Player** players;
    int playerCount;
    int capacity;
    char* fileName;
} PlayerDatabase;

void writePlayersToFile(PlayerDatabase* db, int isMultiplayer);

Player* createPlayer(char* name, int attempts) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->name = strdup(name);
    player->lowestGuesses = attempts;
    player->highestScore = attempts;
    return player;
}

PlayerDatabase* createPlayerDatabase(char* fileName) {
    PlayerDatabase* db = (PlayerDatabase*)malloc(sizeof(PlayerDatabase));
    db->players = (Player**)malloc(10 * sizeof(Player*));  // Start with capacity of 10
    db->playerCount = 0;
    db->capacity = 10;
    db->fileName = strdup(fileName);
    return db;
}

void addOrUpdatePlayer(PlayerDatabase* db, char* name, int attempts) {
    for (int i = 0; i < db->playerCount; i++) {
        if (strcmp(db->players[i]->name, name) == 0) {
            db->players[i]->lowestGuesses = (db->players[i]->lowestGuesses < attempts) ? db->players[i]->lowestGuesses : attempts;
            writePlayersToFile(db, 0);  // false for overwrite
            return;
        }
    }
    if (db->playerCount == db->capacity) {
        db->capacity *= 2;
        db->players = (Player**)realloc(db->players, db->capacity * sizeof(Player*));
    }
    db->players[db->playerCount++] = createPlayer(name, attempts);
    writePlayersToFile(db, 1);  // false for overwrite
}

void addOrUpdatePlayer2(PlayerDatabase* db, char* name, int scores) {
    for (int i = 0; i < db->playerCount; i++) {
        if (strcmp(db->players[i]->name, name) == 0) {
            db->players[i]->highestScore += scores;
            writePlayersToFile(db, 1);  // true for multiplayer
            return;
        }
    }
    if (db->playerCount == db->capacity) {
        db->capacity *= 2;
        db->players = (Player**)realloc(db->players, db->capacity * sizeof(Player*));
    }
    db->players[db->playerCount++] = createPlayer(name, scores);
    writePlayersToFile(db, 1);  // true for multiplayer
}

Player* getPlayer(PlayerDatabase* db, char* name) {
    for (int i = 0; i < db->playerCount; i++) {
        if (strcmp(db->players[i]->name, name) == 0) {
            return db->players[i];
        }
    }
    return NULL;
}

Player* readPlayersFromFile(PlayerDatabase* db) {
    Player* players = (Player*)calloc(db->playerCount, sizeof(Player));  // Use calloc to initialize memory to zero
    if (players == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    FILE* file = fopen(db->fileName, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", db->fileName);
        free(players);
        return NULL;
    }

    char line[256];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        // Remove potential newline character
        line[strcspn(line, "\n")] = 0;

        char* name = strtok(line, ",");
        int score = atoi(strtok(NULL, ","));

        // Debugging output
        printf("Name: %s, Score: %d\n", name, score);

        strcpy(players[index].name, name);
        players[index].lowestGuesses = score;  // Assuming you have a lowestGuesses field
        index++;
    }

    fclose(file);
    return players;
}

// Define a simple hash table structure for demonstration purposes
#define HASH_TABLE_SIZE 100
typedef struct HashTableEntry {
    char name[50];
    int highestScore;
    int lowestGuesses;
    struct HashTableEntry* next;
} HashTableEntry;

HashTableEntry* hashTable[HASH_TABLE_SIZE];

// Hash function to map a player's name to an index
unsigned int hash(const char* name) {
    unsigned int value = 0;
    for (; *name; ++name) {
        value = value * 37 + *name;
    }
    return value % HASH_TABLE_SIZE;
}

// Function to insert or update a player in the hash table
void insertOrUpdatePlayer(const char* name, int highestScore, int lowestGuesses, int isMultiplayer) {
    unsigned int index = hash(name);
    HashTableEntry* entry = hashTable[index];

    // Search for the player in the linked list
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            // Player found, update score
            if (isMultiplayer) {
                entry->highestScore = highestScore;
            } else {
                entry->lowestGuesses = lowestGuesses;
            }
            return;
        }
        entry = entry->next;
    }

    // Player not found, insert new entry
    entry = malloc(sizeof(HashTableEntry));
    if (entry == NULL) {
        printf("Failed to allocate memory for hash table entry.\n");
        return;
    }
    strcpy(entry->name, name);
    entry->highestScore = highestScore;
    entry->lowestGuesses = lowestGuesses;
    entry->next = hashTable[index];
    hashTable[index] = entry;
}

void writePlayersToFile(PlayerDatabase* db, int isMultiplayer) {
    // Initialize hash table
    memset(hashTable, 0, sizeof(hashTable));

    // Read existing players from the file and insert them into the hash table
    FILE* file = fopen(db->fileName, "r");
    if (file != NULL) {  // File exists
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char* name = strtok(line, ",");
            char* scoreStr = strtok(NULL, ",");
            if (name && scoreStr) {
                int score = atoi(scoreStr);
                insertOrUpdatePlayer(name, score, score, isMultiplayer);  // Insert with the same score for both fields
            }
        }
        fclose(file);
    }

    // Insert or update players from the database into the hash table
    for (int i = 0; i < db->playerCount; i++) {
        int highestScore = db->players[i]->highestScore;
        int lowestGuesses = db->players[i]->lowestGuesses;
        insertOrUpdatePlayer(db->players[i]->name, highestScore, lowestGuesses, isMultiplayer);
    }

    // Open the file for writing (this will clear the file and start fresh)
    file = fopen(db->fileName, "w");
    if (file == NULL) {
        printf("Could not open file %s for writing\n", db->fileName);
        return;
    }

    // Write the hash table contents to the file
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashTableEntry* entry = hashTable[i];
        while (entry != NULL) {
            if (isMultiplayer) {
                fprintf(file, "%s,%d\n", entry->name, entry->highestScore);
            } else {
                fprintf(file, "%s,%d\n", entry->name, entry->lowestGuesses);
            }
            entry = entry->next;
        }
    }

    // Clean up
    fclose(file);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        HashTableEntry* entry = hashTable[i];
        while (entry != NULL) {
            HashTableEntry* temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
}

// void writePlayersToFile(PlayerDatabase* db, int isMultiplayer) {
//     // Open the file in append mode
//     FILE* file = fopen(db->fileName, "a");
//     if (file == NULL) {
//         printf("Could not open file %s for appending\n", db->fileName);
//         return;
//     }

//     // Write each player's data to the file
//     for (int i = 0; i < db->playerCount; i++) {
//         if (isMultiplayer) {
//             fprintf(file, "%s,%d\n", db->players[i]->name, db->players[i]->highestScore);
//         } else {
//             fprintf(file, "%s,%d\n", db->players[i]->name, db->players[i]->lowestGuesses);
//         }
//     }

//     // Close the file
//     fclose(file);
// }

Player** getTopPlayers(PlayerDatabase* db, int count) {
    Player** topPlayers = (Player**)malloc(count * sizeof(Player*));
    for (int i = 0; i < count; i++) {
        topPlayers[i] = db->players[i];
    }
    return topPlayers;
}
