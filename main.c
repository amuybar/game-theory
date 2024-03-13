#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 50  

char getPlayerAResponse(char playerBResponses[], int currentTry) {
    if (currentTry <= 5)
        return 'C';  // Start with 5 consecutive 'C's
    else if (currentTry <= 7)
        return 'D';  // Defect twice
    else {
        int consecutiveC = 0;
        for (int i = currentTry - 1; i >= currentTry - 2; --i) {
            if (playerBResponses[i] == 'C')
                consecutiveC++;
        }
        return (consecutiveC >= 2) ? 'C' : 'D';  // Return 'C' if the previous two responses of B are 'C'
    }
}

char getPlayerBResponse(char playerAResponses[], int currentTry) {
    if (currentTry % 3 == 0)
        return 'D';  // Give 'D' after every 3rd try
    else if (currentTry <= 2 || currentTry == 5)
        return 'D';  // Defect twice initially and once again on the fifth try
    else
        return (currentTry - 2) % 2 == 0 ? 'C' : 'D';  // Alternate between 'C' and 'D'
}

void calculatePoints(char playerAResponse, char playerBResponse, int *playerAPoints, int *playerBPoints) {
    if (playerAResponse == 'C' && playerBResponse == 'C') {
        *playerAPoints += 10;
        *playerBPoints += 10;
    } else if (playerAResponse == 'D' && playerBResponse == 'D') {
        *playerAPoints += 1;
        *playerBPoints += 1;
    } else if (playerAResponse == 'D' && playerBResponse == 'C') {
        *playerAPoints += 20;
    } else if (playerAResponse == 'C' && playerBResponse == 'D') {
        *playerBPoints += 20;
    }
}

int main() {
    srand(time(NULL)); 

    int playerAPoints = 0;
    int playerBPoints = 0;
    char playerAResponses[MAX_TRIES] = {0}; 
    char playerBResponses[MAX_TRIES] = {0}; 

    int totalTries = 20;  

    for (int try = 1; try <= totalTries; ++try) {
        char playerAResponse = getPlayerAResponse(playerBResponses, try);
        char playerBResponse = getPlayerBResponse(playerAResponses, try);

        calculatePoints(playerAResponse, playerBResponse, &playerAPoints, &playerBPoints);
        playerAResponses[try - 1] = playerAResponse;
        playerBResponses[try - 1] = playerBResponse;

        printf("Try %d: Player A's response: %c, Player B's response: %c\n",
               try, playerAResponse, playerBResponse);
    }

    printf("Player A's total points: %d\n", playerAPoints);
    printf("Player B's total points: %d\n", playerBPoints);

    return 0;
}
