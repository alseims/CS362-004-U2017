/*
* Name: Jacob Wilson
* Course: CS362_400 Summer 2017
* Description: Unit test for Adventurer card. The program
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
}

int main() {
	// variables to determine expected outcome
	int gainCards = 0, discard = 0;
	int numCoins = 0, gainCoins = 0;
	int test1 = 0, test2 = 0, test3 = 0;
	int wasPlayed = 0;
	int i;

	// variables to set up the game state
	int currentPlayer = 0, handPos = 0;
	int seed = 100;
	int numPlayers = 2;
	struct gameState runGame, testGame;				// two game states for comparison
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &runGame);
	memcpy(&testGame, &runGame, sizeof(struct gameState));

	// put cards into test hand
	testGame.hand[currentPlayer][handPos] = adventurer;
	testGame.hand[currentPlayer][handPos + 1] = copper;
	testGame.hand[currentPlayer][handPos + 2] = copper;

	// play the card
	wasPlayed = cardEffect(adventurer, 0, 0, 0, &testGame, handPos, 0);

	gainCards = 2;
	discard = 1;

	printf("******* Testing Adventurer Card *******\n\n");

	// TEST that player gained two cards in hand
	printf("Player should gain two cards:\n");
	printf("hand count = %d, expected = %d\n", testGame.handCount[currentPlayer], (runGame.handCount[currentPlayer] + gainCards - discard));
	printf("Hand count result: ");
	test1 = assertTrue(testGame.handCount[currentPlayer] == (runGame.handCount[currentPlayer] + gainCards - discard));

	// TEST that player gained coins
	// count coins before playing card
	for (i = 0; i < runGame.handCount[currentPlayer]; i++) {
		if (isTreasureCard(runGame.hand[currentPlayer][i])) {
			numCoins += coinValue(runGame.hand[currentPlayer][i]);
		}
	}

	// count coins after playing card
	for (i = 0; i < testGame.handCount[currentPlayer]; i++) {
		if (isTreasureCard(testGame.hand[currentPlayer][i])) {
			gainCoins += coinValue(testGame.hand[currentPlayer][i]);
		}
	}

	printf("Player should gain some coins:\n");
	printf("coin count = %d, expected = %d\n", numCoins, gainCoins);
	printf("Coin count result: ");
	test2 = assertTrue(numCoins < gainCoins);

	// TEST the the card was played
	printf("cardEffect should return 0:\n");
	printf("return = %d, expected = 0\n", wasPlayed);
	printf("Play card result: ");
	test3 = assertTrue(wasPlayed >= 0);


	// check for any failed tests
	if (test1 && test2 && test3) {
		printf("All tests PASSED!!\n\n");
	} else {
		printf("At least one test has FAILED\n\n");
	}

	return 0;
}