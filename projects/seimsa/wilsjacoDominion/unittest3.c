/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for isGameOver() function. The program
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
	int gameEnd = 0;
	int test1 = 0, test2 = 0, test3 = 0, test4 = 0;
	int i;

	// variables to set up the game state
	int seed = 100;
	int numPlayers = 2;
	struct gameState testGame;				
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};


	printf("******* Testing isGameOver() *******\n\n");

	// set up test game
	memset(&testGame, 23, sizeof(struct gameState));
	initializeGame(numPlayers, k, seed, &testGame);

	// TEST supply without any province cards present
	testGame.supplyCount[province] = 0;
	gameEnd = isGameOver(&testGame);
	printf("Test zero province cards in deck:\n");
	printf("Game end = %d, expected = 1\n", gameEnd);
	printf("Result: ");
	test1 = assertTrue(gameEnd == 1);

	// TEST supply with province cards present
	testGame.supplyCount[province] = 1;
	gameEnd = isGameOver(&testGame);
	printf("Test one province card in deck:\n");
	printf("Game end = %d, expected = 0\n", gameEnd);
	printf("Result: ");
	test2 = assertTrue(gameEnd == 0);

	// TEST supply card piles empty
	for (i = 0; i < 25; i++) {
		testGame.supplyCount[i] = 0;
	}
	gameEnd = isGameOver(&testGame);
	printf("Test empty supply piles:\n");
	printf("Game end = %d, expected = 1\n", gameEnd);
	printf("Result: ");
	test3 = assertTrue(gameEnd == 1);

	// TEST supply card piles non-empty	
	for (i = 0; i < 25; i++) {
		testGame.supplyCount[i] = 1;
	}
	gameEnd = isGameOver(&testGame);
	printf("Test empty supply piles:\n");
	printf("Game end = %d, expected = 0\n", gameEnd);
	printf("Result: ");
	test4 = assertTrue(gameEnd == 0);


	// check for any failed tests
	if (test1 && test2 && test3 && test4) {
		printf("All tests PASSED!!\n\n");
	} else {
		printf("At least one test has FAILED\n\n");
	}

	return 0;
}