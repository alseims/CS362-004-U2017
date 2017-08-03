/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for Smithy card function. The program
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
	int gainCards = 0, discard = 0;
	int test1 = 0, test2 = 0;

	// variables to set up the game state
	int handPos = 0, currentPlayer = 0;
	int seed = 100;
	int numPlayers = 2;
	struct gameState runGame, testGame;				// two game states for comparison
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &runGame);
	memcpy(&testGame, &runGame, sizeof(struct gameState));

	// put card into test hand
	testGame.hand[currentPlayer][handPos] = smithy;

	// play the card
	cardEffect(smithy, 0, 0, 0, &testGame, handPos, 0);

	printf("******* Testing Smithy Card *******\n\n");

	// set up variables to compare expected results
	gainCards = 3;
	discard = 1;

	// TEST that player gained three cards in hand
	printf("Player gains three new cards:\n");
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], (runGame.handCount[currentPlayer] + gainCards - discard));
	printf("Hand count result: ");
	test1 = assertTrue(testGame.handCount[currentPlayer] == (runGame.handCount[currentPlayer] + gainCards - discard));

	// TEST that player deck decreases by three
	printf("Player deck should decrease by three:\n");
	printf("deck count = %d, expected = %d\n", testGame.deckCount[currentPlayer], (runGame.deckCount[currentPlayer] - gainCards));
	printf("Deck count result: ");
	test2 = assertTrue(testGame.deckCount[currentPlayer] == (runGame.deckCount[currentPlayer] - gainCards));

	// check for any failed tests
	if (test1 && test2) {
		printf("All tests PASSED!!\n\n");
	} else {
		printf("At least one test has FAILED\n\n");
	}

	return 0;
}