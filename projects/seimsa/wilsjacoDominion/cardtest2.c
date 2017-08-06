/******************************************************************************************************
 *
 * Alan Seims
 * CS 362
 * Unit test for playAdventurer()
 *
 * The following line is including in the makefile:
 * testAdventurerCard: cardtest2.c dominion.o rngs.o
 *       $(CC) -o testAdventurerCard -g testcard2.c dominion.o rngs.o $(CFLAGS)
 *
 *
 * void playAdventurer(int currentPlayer, struct gameState *state, int *temphand)
 * {
 *      int drawntreasure = 1;
 *      int z = 0;// this is the counter for the temp hand
 *      int cardDrawn;
 *
 *      while(drawntreasure<2){
 *          if (state->deckCount[currentPlayer] <1){    //if the deck is empty we need to shuffle discard and add to deck
 *              shuffle(currentPlayer, state);
 *          }
 *          drawCard(currentPlayer, state);
 *          cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];  //top card of hand is most recently drawn card.
 *          if (cardDrawn == copper || cardDrawn == silver)
 *              drawntreasure++;
 *          else{
 *              temphand[z]=cardDrawn;
 *              state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
 *              z++;
 *          }
 *      }
 *      while(z-1>=0){
 *          state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
 *          z=z-2;
 *      }
 *      return;
 * }
 ******************************************************************************************************/


#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#define TESTCARD "Adventurer"

void assertTrue(struct gameState *state, struct gameState *testState, int player, int testType, int newCards, int discarded, int shuffleCards, int xtraCoins);

int main()
{
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int shuffleCards = 0;
    
    int i, j, m, n, p;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    
    //Initialize a new game
    initializeGame(numPlayers, k, seed, &G);
    
    printf("------------------------------TESTING Card: %s -----------------------------------\n", TESTCARD);
    printf("TEST1: Player's deck is not empty.\n\n");
    
    //copy the game state to  test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    newCards = 2;
    
    //Check the state for the player that played the Adventurer card
    assertTrue(&G, &testG, thisPlayer, 0, newCards, discarded, shuffleCards, xtraCoins);
    assertTrue(&G, &testG, thisPlayer, 1, newCards, discarded, shuffleCards, xtraCoins);
    assertTrue(&G, &testG, thisPlayer, 2, newCards, discarded, shuffleCards, xtraCoins);
    
    
    //Ensure that the state for the other players did not change
    newCards = 0;
    discarded = 0;
    
    for(p = 1; p < numPlayers; p++)
    {
        printf("**Checking the state of player %d to ensure the Adventurer card played by player 0 did not change other player's state.**\n\n", p);
        for(n = 0; n < 3; n++)
        {
            assertTrue(&G, &testG, p, n, newCards, discarded, shuffleCards, xtraCoins);
        }
        
    }
    
    //Ensure that a state change did not occur for the victory and kingdom card piles.
    assertTrue(&G, &testG, thisPlayer, 3, newCards, discarded, shuffleCards, xtraCoins);
    
    printf("TEST2: Player's deck is empty and must be shuffled before drawing cards.\n\n");
    
    //Initialize a new game
    initializeGame(numPlayers, k, seed, &G);
    for(j = 0; j < 5; j++)
    {
        playCard(j, choice1, choice2, choice3, &G);
    }
    
    for(j = 0; j < 5; j++)
    {
        drawCard(thisPlayer, &G);
    }
    
    for(j = 0; j < 5; j++)
    {
        discardCard(j, thisPlayer, &G, 0);
    }
    
    printf("deck count: %d\n", G.deckCount[0]);
    
    //copy the game state to  test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    newCards = 2;
    
    //Check the state for the player that played the Adventurer card
    assertTrue(&G, &testG, thisPlayer, 0, newCards, discarded, shuffleCards, xtraCoins);
    //assertTrue(&G, &testG, thisPlayer, 1, newCards, discarded, shuffleCards, xtraCoins);
    assertTrue(&G, &testG, thisPlayer, 2, newCards, discarded, shuffleCards, xtraCoins);
    
    
    //Ensure that the state for the other players did not change
    newCards = 0;
    discarded = 0;
    
    for(p = 1; p < numPlayers; p++)
    {
        printf("**Checking the state of player %d to ensure the Smithy card played by player 0 did not change other player's state.**\n\n", p);
        for(n = 0; n < 3; n++)
        {
            assertTrue(&G, &testG, p, n, newCards, discarded, shuffleCards, xtraCoins);
        }
        
    }
    
    //Ensure that a state change did not occur for the victory and kingdom card piles.
    assertTrue(&G, &testG, thisPlayer, 3, newCards, discarded, shuffleCards, xtraCoins);
    
    printf("--------------------------------------------------------------------------------\n\n");
    
    return 0;
    
}

void assertTrue(struct gameState *state, struct gameState *testState, int player, int testType, int newCards, int discarded, int shuffleCards, int xtraCoins)
{
    int i;
    int coinTest = 0;
    int deckTest = 0;
    int handTest = 0;
    int kingVicTest = 0;
    int cards;
    if(testType == 0)
    {
        printf("Hand count = %d, Expected = %d\n", testState->handCount[player], state->handCount[player] + newCards - discarded);
        if(testState->handCount[player] != (state->handCount[player] + newCards - discarded))
        {
            printf("Hand count is incorrect for player %d.\n", player);
            handTest = 1;
        }
        if(handTest != 0)
        {
            printf("Hand count test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Hand count test passed for player %d!\n\n", player);
    }
    
    if(testType == 1)
    {
        printf("Deck count = %d, Expected = %d\n", testState->deckCount[player], state->deckCount[player] - newCards + shuffleCards);
        if(testState->deckCount[player] != (state->deckCount[player] - newCards + shuffleCards))
        {
            printf("Deck count is incorrect for player %d.\n", player);
            deckTest = 1;
        }
        if(deckTest != 0)
        {
            printf("Deck count test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Deck count test passed for player %d!\n\n", player);
    }
    
    if(testType == 2)
    {
        printf("Coins = %d, Expected = %d\n", testState->coins, state->coins + xtraCoins);
        if(testState->coins != (state->coins  + xtraCoins))
        {
            printf("Coin count is incorrect for player %d.\n", player);
            coinTest = 1;
        }
        if(coinTest != 0)
        {
            printf("Coin count test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Coin count test passed for player %d!\n\n", player);
    }
    
    if(testType == 3)
    {
        printf("Checking that Kingdom and Victory cards counts did not change due to Smithy card being played.\n");
        for(cards = 0; cards <= treasure_map; cards++)
        {
            if(testState->supplyCount[cards] != state->supplyCount[cards])
            {
                printf("Test failed! Kingdom and Victory card counts are incorrect.\n");
                return;
            }
            
        }
        printf("Kingdom and Victory card test passed!\n\n");
    }
    
    return;
}
