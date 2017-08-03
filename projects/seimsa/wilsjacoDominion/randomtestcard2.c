/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Random test for Village card. The program loops through a number
*  of random test scenarios. It determines how many tests failed or passed,
*  which tests failed, and prints out the results.
* References: the testDrawCard.c file as provided by the instructor
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
* Name: checkVillageCard()
* Input: five integers and gamestate struct
* Output: one integer
* Description: The function contains two gamestates that it uses to
*  check that various conditions are equal. It counts up the number
*  of tests that have failed, and returns that value to main.
*/
int checkVillageCard(int p, struct gameState *post, int *test1, int *test2, int *test3, int *test4) {
	// variables for tracking values
	struct gameState pre;
	int testStatus = 0;
	int handBefore, handAfter, deckBefore, deckAfter, actionsBefore, actionsAfter;
	int r;

	// copy the previous gamestate
	memcpy(&pre, post, sizeof(struct gameState));

	// call the function in test
	r = cardEffect(village, 0, 0, 0, post, 0, 0);

	// assign before and after variables
	handBefore = pre.handCount[p];
	deckBefore = pre.deckCount[p];
	actionsBefore = pre.numActions;
	handAfter = post->handCount[p];
	deckAfter = post->deckCount[p];
	actionsAfter = post->numActions;

	// TEST 1: two cards have been added to hand
	if ((handBefore + 2) != handAfter) {
		testStatus += 1;
		*test1 = 1;
	}

	// TEST 2: three cards have been removed from deck
	if ((deckBefore - 3) != deckAfter) {
		testStatus += 1;
		*test2 = 1;
	}

	// TEST3: two actions have been added
	if ((actionsBefore + 2) != actionsAfter) {
		testStatus += 1;
		*test3 = 1;
	}

	// TEST4: a correct return value from function
	if (r != 0) {
		testStatus += 1;
		*test4 = 1;
	}

	return testStatus;
}

int main() {
	// variables for setting up game
	int numPlayers;
	int currentPlayer = 0;
	int r = 0;
	int h, i, j;
	struct gameState testGame;

	// variables for tracking test results
	int testFailed = 0;
	int numTestsFailed = 0;
	int test1 = 0;
	int test2 = 0;
	int test3 = 0;
	int test4 = 0;

	printf("-------- RANDOM Testing Village Card--------\n");

	// set up random generator
	SelectStream(2);
	PutSeed(3);

	// loop through multiple random test cases
	for (i = 0; i < 2000; i++) {
		// copy random values into struct (taken from example file)
		for (j = 0; j < sizeof(struct gameState); j++) {
			((char*)&testGame)[j] = floor(Random() * 256);
		}

		// set up random reasonable values
		testGame.whoseTurn = currentPlayer;
		testGame.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		testGame.discardCount[currentPlayer] = floor(Random() * MAX_DECK);
		testGame.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		testGame.playedCardCount = floor(Random() * (MAX_DECK - 1));
		testGame.numActions = floor(Random() * 10);

		// run the test
		r = checkVillageCard(currentPlayer, &testGame, &test1, &test2, &test3, &test4);

		// keep track of the total number of tests failed
		if (r > 0) {
			testFailed = 1;
			for (h = 0; h < r; h++) {
				numTestsFailed++;
			}
			r = 0;
		}
	}

	// print results
	if (testFailed) {
		printf("Village Result: FAILED TESTS\n");
		printf("Number of tests failed: %d out of %d\n", numTestsFailed, (i * 4));
		printf("Failing tests:\n");
		if (test1 == 1) {
			printf("- incorrect number of cards in hand\n");
		}
		if (test2 == 1) {
			printf("- incorrect number of cards in deck\n");
		}
		if (test3 == 1) {
			printf("- incorrect number of actions\n");
		}
		if (test4 == 1) {
			printf("- incorrect function return value\n");
		}
		printf("\n");
	} else {
		printf("Village Result: PASSED ALL TESTS!!\n\n");
	}

	return 0;
}