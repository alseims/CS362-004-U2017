/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for fullDeckCount() function. The program
*  sets up a game environment and performs a controlled test of
*  the function in question. It determines tests failed or passed
*  and prints out the results.
* References: the example file as provided by the instructor
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
	int handCards = 0;
	int deckCards = 0;
	int discardCards = 0;
	int maxHandCards = 5;
	int testFail = 0;
	int test1 = 0, test2 = 0, test3 = 0;
	int i, j;
	int gardenCards[MAX_HAND];
	int numGardens = 0;

	// variables to set up the game state
	int seed = 100;
	int numPlayers = 2;
	struct gameState testGame;				
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	// set all cards to garden
	for (i = 0; i < MAX_HAND; i++) {
		gardenCards[i] = gardens;
	}

	printf("******* Testing fullDeckCount() *******\n\n");

	// loop through each player setting hand cards to garden
	for (j = 0; j < numPlayers; j++) {
		for (handCards = 1; handCards <= maxHandCards; handCards++) {
			test1 = 0, test2 = 0, test3 = 0;
			printf("Player %d has %d garden cards.\n", (j + 1), handCards);

			// set up test game
			memset(&testGame, 23, sizeof(struct gameState));
			initializeGame(numPlayers, k, seed, &testGame);

			// add garden cards to hand
			testGame.handCount[j] = handCards;
			memcpy(testGame.hand[j], gardenCards, sizeof(int) *handCards);

			// TEST for number of garden cards in hand
			numGardens = fullDeckCount(j, gardens, &testGame);
			printf("Garden cards = %d, expected = %d\n", numGardens, handCards);
			printf("Result: ");
			test1 = assertTrue(numGardens == handCards);

			// add garden cards to deck
			testGame.deckCount[j] = deckCards;
			memcpy(testGame.deck[j], gardenCards, sizeof(int) *deckCards);

			// TEST for number of garden cards in deck
			numGardens = fullDeckCount(j, gardens, &testGame);
			printf("Garden cards = %d, expected = %d\n", numGardens, (deckCards + handCards));
			printf("Result: ");
			test2 = assertTrue(numGardens == (deckCards + handCards));

			// add garden cards to discard
			testGame.discardCount[j] = discardCards;
			memcpy(testGame.discard[j], gardenCards, sizeof(int) *discardCards);

			// TEST for number of garden cards in deck
			numGardens = fullDeckCount(j, gardens, &testGame);
			printf("Garden cards = %d, expected = %d\n", numGardens, (discardCards + deckCards + handCards));
			printf("Result: ");
			test3 = assertTrue(numGardens == (discardCards + deckCards + handCards));

			// track any failed tests
			if (!test1 || !test2 || !test3) {
				testFail = 1;
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