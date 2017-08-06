/******************************************************************************************************
 *
 * Alan Seims
 * CS 362
 * Unit test for playCutpurse()
 *
 * The following line is including in the makefile:
 * testCutpurseCard: cardtest3.c dominion.o rngs.o
 *       $(CC) -o testCutpurseCard -g cardtest3.c dominion.o rngs.o $(CFLAGS)
 *
 *
 *  void playCutpurse(int currentPlayer, struct gameState *state, int handPos)
 *  {
 *      int i, j, k;
 *
 *      updateCoins(currentPlayer, state, 3);
 *      for (i = 0; i < state->numPlayers; i++)
 *      {
 *          if (i != currentPlayer)
 *          {
 *              for (j = 0; j < state->handCount[i]; j++)
 *              {
 *                  if (state->hand[i][j] == copper)
 *                  {
 *                      discardCard(i, j, state, 0);
 *                      break;
 *                  }
 *                  if (j == state->handCount[i])
 *                  {
 *                      for (k = 0; k < state->handCount[i]; k++)
 *                      {
 *                          if (DEBUG)
 *                              printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
 *                      }
 *                      break;
 *                  }
 *              }
 *
 *          }
 *
 *      }
 *
 *      //discard played card from hand
 *      discardCard(handPos, currentPlayer, state, 0);
 *
 *      return;
 *  }
 *
 ******************************************************************************************************/


#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#define TESTCARD "Cutpurse"

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
    
    initializeGame(numPlayers, k, seed, &G); //Initialize a new game
    
    printf("------------------------------TESTING Card: %s -----------------------------------\n", TESTCARD);
    printf("TEST1: Player gains +2 coins and all other players discard the coppers in there hands.\n");
    
    //copy the game state to  test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    cardEffect(cutpurse, choice1, choice2, choice3, &testG, handpos, &bonus);
    
    xtraCoins = 2;
    
    //Check the state for the player that played the Smithy card
    assertTrue(&G, &testG, thisPlayer, 0, newCards, discarded, shuffleCards, xtraCoins);
    assertTrue(&G, &testG, thisPlayer, 1, newCards, discarded, shuffleCards, xtraCoins);
    assertTrue(&G, &testG, thisPlayer, 2, newCards, discarded, shuffleCards, xtraCoins);
    
    
    //Ensure that the state for the other players did not change
    xtraCoins = 0;
    for(p = 1; p < numPlayers; p++)
    {
        printf("**Checking the state of player %d to see if the Cutpurse card played by player 0 changed the other players' state.**\n\n", p);
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

