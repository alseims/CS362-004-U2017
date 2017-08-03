/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for numHandCards() function. The program
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
	int numCards = 0;
	int i;
	int test1 = 0, test2 = 0;

	// variables to set up the game state
	int seed = 100;
	int numPlayers = 2;
	struct gameState testGame;				
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	printf("******* Testing numHandCards() *******\n\n");

	// set up test game
	memset(&testGame, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &testGame);

	// TEST players have zero cards
	for (i = 0; i < numPlayers; i++) {
		testGame.handCount[i] = 0;
	}
	numCards = numHandCards(&testGame);
	printf("Test empty hands:\n");
	printf("Number of cards = %d, expected = 0\n", numCards);
	printf("Result: ");
	test1 = assertTrue(numCards == 0);

	// TEST players have max cards
	for (i = 0; i < numPlayers; i++) {
		testGame.handCount[i] = 5;
	}
	numCards = numHandCards(&testGame);
	printf("Test five cards in hand:\n");
	printf("Number of cards = %d, expected = 5\n", numCards);
	printf("Result: ");
	test2 = assertTrue(numCards == 5);

	// check for any failed tests
	if (test1 && test2) {
		printf("All tests PASSED!!\n\n");
	} else {
		printf("At least one test has FAILED\n\n");
	}

	return 0;
}