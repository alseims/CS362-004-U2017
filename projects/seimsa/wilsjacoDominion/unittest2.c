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
 *  int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
 *  {
 *
 *      //if card is not trashed, added to Played pile
 *      if (trashFlag < 1)
 *      {
 *          //add card to played pile
 *          state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
 *          state->playedCardCount++;
 *      }
 *
 *      //set played card to -1
 *      state->hand[currentPlayer][handPos] = -1;
 *
 *      //remove card from player's hand
 *      if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
 *      {
 *          //reduce number of cards in hand
 *          state->handCount[currentPlayer]--;
 *      }
 *      else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
 *      {
 *          //reduce number of cards in hand
 *          state->handCount[currentPlayer]--;
 *      }
 *      else
 *      {
 *          //replace discarded card with last card in hand
 *          state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
 *          //set last card to -1
 *          state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
 *          //reduce number of cards in hand
 *          state->handCount[currentPlayer]--;
 *      }
 *
 *      return 0;
 *  }
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
    
    /*if(testType == 1)
    {
        //printf("Deck count is %d \n", state->deckCount[player]);
        if((handCount + 5) != state->deckCount[player])
        {
            printf("Deck count is incorrect for player %d!\n\n", player);
            return;
        }
        
        for(i = 5; i < state->deckCount[player]; i++)
        {
            if(state->deck[ player ][ i ] != supplyPos)
                deckTest = 1;
        }
        
        if(deckTest != 0)
        {
            printf("Deck test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Deck test passed for player %d!\n\n", player);
        
        if(state->supplyCount[supplyPos] != (10 - handCount))
        {
            printf("Supply count is incorrect for %d after player %d's turn!\n\n", supplyPos, player);
            return;
        }
    }
    
    if(testType == 2)
    {
        //printf("Hand count is %d \n", state->handCount[player]);
        if((handCount + 5) != state->handCount[player])
            //if((handCount) != state->handCount[player])
        {
            printf("Hand count is incorrect for player %d!\n\n", player);
            return;
        }
        
        for(i = 5; i < state->handCount[player]; i++)
            //for(i = 0; i < state->handCount[player]; i++)
        {
            if(state->hand[ player ][ i ] != supplyPos)
                handTest = 1;
        }
        
        if(handTest != 0)
        {
            printf("Hand test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Hand test passed for player %d!\n\n", player);
        
        if(state->supplyCount[supplyPos] != (10 - handCount))
        {
            printf("Supply count is incorrect for %d after player %d's turn!\n\n", supplyPos, player);
            return;
        }
    }*/
    
    return;
}
