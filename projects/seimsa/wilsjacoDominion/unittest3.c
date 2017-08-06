/******************************************************************************************************
 *
 * Alan Seims
 * CS 362
 * Unit test for discardCard()
 *
 * The following line is including in the makefile:
 * testDiscardCard: unittest2.c dominion.o rngs.o
 *       $(CC) -o testDiscardCard -g unittest2.c dominion.o rngs.o $(CFLAGS)
 *
 *
 *  int getCost(int cardNumber)
 *  {
 *      switch( cardNumber )
 *      {
 *          case curse:
 *              return 0;
 *          case estate:
 *              return 2;
 *          case duchy:
 *              return 5;
 *          case province:
 *              return 8;
 *          case copper:
 *              return 0;
 *          case silver:
 *              return 3;
 *          case gold:
 *              return 6;
 *          case adventurer:
 *              return 6;
 *          case council_room:
 *              return 5;
 *          case feast:
 *              return 4;
 *          case gardens:
 *              return 4;
 *          case mine:
 *              return 5;
 *          case remodel:
 *              return 4;
 *          case smithy:
 *              return 4;
 *          case village:
 *              return 3;
 *          case baron:
 *              return 4;
 *          case great_hall:
 *              return 3;
 *          case minion:
 *              return 5;
 *          case steward:
 *              return 3;
 *          case tribute:
 *              return 5;
 *          case ambassador:
 *              return 3;
 *          case cutpurse:
 *              return 4;
 *          case embargo:
 *              return 2;
 *          case outpost:
 *              return 5;
 *          case salvager:
 *              return 4;
 *          case sea_hag:
 *              return 4;
 *          case treasure_map:
 *              return 4;
 *      }
 *
 *      return -1;
 *  }
 *
 ******************************************************************************************************/


#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

void assertTrue(int handCount, int player, struct gameState *state, int handPos, int testType);

int main()
{
    int i, it, j, l, m, p, r, t, handCount;
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    int testType = 0;
    
    printf("-------------------TESTING DISCARDCARD()---------------------\n\n");
    for(p = 0; p < numPlayer; p++)
    {
        for(handCount = 1; handCount <= maxHandCount; handCount++)
        {
            memset(&G, 23, sizeof(struct gameState)); //Clear the game state
            initializeGame(numPlayer, k, seed, &G); //Initialize a new game
            
            if(p > 0)
            {
                G.whoseTurn = p;
                for (it = 0; it < 5; it++){
                    drawCard(p, &G);
                }
            }
            printf("Test player %d with %d cards to discard.\n", p, handCount);
            for(j = 1; j <= handCount; j++)
            {
                discardCard(j, p, &G, 0);
                for(t = 0; t < 1; t++)
                {
                    assertTrue(handCount, p, &G, j, t);
                }
            }
            
            
            
        }
    }
    
    return 0;
}

void assertTrue(int handCount, int player, struct gameState *state, int handPos, int testType)
{
    int i;
    int discardTest = 0;
    int deckTest = 0;
    int handTest = 0;
    
    if(testType == 0)
    {
        printf("state->hand[player][handPos]: %d, state->playedCards[state->playedCardCount]: %d\n", state->hand[player][handPos], state->playedCards[state->playedCardCount]);
        if(state->playedCards[state->playedCardCount] != state->hand[player][handPos])
        {
            printf("Test failed!! Discard card did not get added to played pile for player %d!\n\n", player);
            return;
        }
        
        if(state->hand[player][handPos] != -1)
        {
            printf("Test failed!! Played card position did not get set to -1 for player %d!\n\n", player);
            return;
        }
        
    }
}
