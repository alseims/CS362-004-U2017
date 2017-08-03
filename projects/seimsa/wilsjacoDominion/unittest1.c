/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for updateCoins() function. The program
*  sets up a game environment and performs a controlled test of
*  the function in question. It determines tests failed or passed
*  and prints out the results.
* References: the updateCoins.c file as provided by the instructor
*  was used as a template.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/*
* Name: assertTrue()
* Input: one integer
* Output: one integer
* Description: The function takes the result of a comparison
*  and prints a message depending on the result of the
*  comparison. This result indicates success or failure of
*  a given test.
*/

int assertTrue(int success) {
	if (success) {
		printf("PASSED\n\n");
		return 1;
	} else {
		printf("FAILED\n\n");
		return 0;
	}
}

int main() {
	// variables to determine expected outcome
	int handCards = 0, bonus = 0;
	int maxHandCards = 5;
	int maxBonus = 10;
	int testFail = 0;
	int i, j;
	int copperCards[MAX_HAND];
	int silverCards[MAX_HAND];
	int goldCards[MAX_HAND];

	// variables to set up the game state
	int seed = 100;
	int numPlayers = 2;
	struct gameState testGame;				
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// set all treasure cards
	for (i = 0; i < MAX_HAND; i++) {
		copperCards[i] = copper;
		silverCards[i] = silver;
		goldCards[i] = gold;
	}

	printf("******* Testing updateCoins() *******\n\n");

	// loop through each player setting various hand and bonus values
	for (j = 0; j < numPlayers; j++) {
		for (handCards = 0; handCards <= maxHandCards; handCards++) {
			for (bonus = 0; bonus <= maxBonus; bonus++) {
				int test1 = 0, test2 = 0, test3 = 0;

				// set up the game for each player-card-bonus combination
				printf("Player %d has %d treasure cards and %d bonus.\n", (j + 1), handCards, bonus);
				memset(&testGame, 23, sizeof(struct gameState));
				initializeGame(numPlayers, k, seed, &testGame);
				testGame.handCount[j] = handCards;

				// TEST for coppers in hand
				memcpy(testGame.hand[j], copperCards, sizeof(int)*handCards);
				updateCoins(j, &testGame, bonus);
				printf("Number of coins= %d, expected = %d\n", testGame.coins, handCards * 1 + bonus);
				printf("Copper result: ");
				test1 = assertTrue(testGame.coins == (handCards * 1 + bonus));

				// TEST for silvers in hand
				memcpy(testGame.hand[j], silverCards, sizeof(int)*handCards);
				updateCoins(j, &testGame, bonus);
				printf("Number of coins= %d, expected = %d\n", testGame.coins, handCards * 2 + bonus);
				printf("Silver result: ");
				test2 = assertTrue(testGame.coins == (handCards * 2 + bonus));

				// TEST for golds in hand
				memcpy(testGame.hand[j], goldCards, sizeof(int)*handCards);
				updateCoins(j, &testGame, bonus);
				printf("Number of coins= %d, expected = %d\n", testGame.coins, handCards * 3 + bonus);
				printf("Gold result: ");
				test3 = assertTrue(testGame.coins == (handCards * 3 + bonus));

				// track if any tests have failed
				if (!test1 || !test2 || !test3) {
					testFail = 1;
				}
			}
		}
	}

	// check for any failed tests
	if (!testFail) {
		printf("All tests PASSED!!\n\n");
	} else {
		printf("At least one test has FAILED\n\n");
	}

	return 0;
}