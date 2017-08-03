/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Random test for Adventurer card. The program loops through a number
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
* Name: isTreasureCard()
* Input: one integer
* Output: one integer
* Description: The function takes a card as an argument
*  and determines if the card is a Treasure card (can be
*  either copper, silver, or gold). Returns 1 (True) if
*  the card is a Treasure.
*/
int isTreasureCard(int card) {
	if (card == copper || card == silver || card == gold) {
		return 1;
	} else {
		return 0;
	}
}

/*
* Name: coinValue()
* Input: one integer
* Output: one integer
* Description: The function takes a card as an argument
*  and determines value of the card. It then returns the
*  value of the card depending on if it's gold, silver,
*  or copper.
*/
int coinValue(int card) {
	if (card == gold) {
		return 3;
	} else if (card == silver) {
		return 2;
	} else if (card == copper) {
		return 1;
	}

	return 0;
}

/*
* Name: checkAdventurerCard()
* Input: four integers and gamestate struct
* Output: one integer
* Description: The function contains two gamestates that it uses to
*  check that various conditions are equal. It counts up the number
*  of tests that have failed, and returns that value to main.
*/
int checkAdventurerCard(int p, struct gameState *post, int *test1, int *test2, int *test3) {
	// variables for tracking values
	struct gameState pre;
	int testStatus = 0;
	int handBefore, handAfter;
	int numCoins = 0;
	int gainCoins = 0;
	int i;
	int r;

	// copy the previous gamestate
	memcpy(&pre, post, sizeof(struct gameState));

	// call the function in test
	r = cardEffect(adventurer, 0, 0, 0, post, 0, 0);

	// assign before and after variables
	handBefore = pre.handCount[p];
	handAfter = post->handCount[p];

	// TEST 1: two cards have been added to hand
	if ((handBefore + 2) != handAfter) {
		testStatus += 1;
		*test1 = 1;
	}

	// loop through players before and after hand counting coins
	for (i = 0; i < pre.handCount[p]; i++) {
		if (isTreasureCard(pre.hand[p][i])) {
			numCoins += coinValue(pre.hand[p][i]);
		}
	}

	for (i = 0; i < post->handCount[p]; i++) {
		if (isTreasureCard(post->hand[p][i])) {
			gainCoins += coinValue(post->hand[p][i]);
		}
	}

	// TEST 2: coins have been added to player
	if (numCoins > gainCoins) {
		testStatus += 1;
		*test2 = 1;
	}

	// TEST 3: correct return value from function
	if (r != 0) {
		testStatus += 1;
		*test3 = 1;
	}

	return testStatus;
}

int main() {
	// variables for setting up game
	int numPlayers;
	int currentPlayer = 0;
	int r = 0;

	// variables for tracking test results
	int testFailed = 0;
	int numTestsFailed = 0;
	int test1 = 0;
	int test2 = 0;
	int test3 = 0;
	int h, i, j;
	int seed = 100;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	struct gameState testGame;

	printf("-------- RANDOM Testing Adventurer Card--------\n");

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
		numPlayers = floor(Random() * 2);
		initializeGame(numPlayers, k, seed, &testGame);
		testGame.whoseTurn = currentPlayer;
		testGame.deckCount[currentPlayer] = floor(Random() * MAX_DECK);
		testGame.discardCount[currentPlayer] = floor(Random() * (MAX_DECK - testGame.deckCount[currentPlayer]));
		testGame.handCount[currentPlayer] = floor(Random() * MAX_HAND);
		testGame.playedCardCount = floor(Random() * (MAX_DECK - 1));

		// add necessary cards to hand and deck
		testGame.hand[currentPlayer][0] = adventurer;
		testGame.deck[currentPlayer][0] = copper;
		testGame.deck[currentPlayer][1] = copper;

		// run the test
		r = checkAdventurerCard(currentPlayer, &testGame, &test1, &test2, &test3);

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
		printf("Adventurer Result: FAILED TESTS\n");
		printf("Number of tests failed: %d out of %d\n", numTestsFailed, (i * 3));
		printf("Failing tests:\n");
		if (test1 == 1) {
			printf("- incorrect number of cards in hand\n");
		}
		if (test2 == 1) {
			printf("- incorrect number of coins gained\n");
		}
		if (test3 == 1) {
			printf("- incorrect function return value\n");
		}
		printf("\n");
	} else {
		printf("Adventurer Result: PASSED ALL TESTS!!\n\n");
	}

	return 0;
}