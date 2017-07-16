/******************************************************************************************************
*
* Alan Seims
* CS 362
* Unit test for gainCard()
*
* The following line is including in the makefile:
* testGainCard: unittest1.c dominion.o rngs.o
*       $(CC) -o testGainCard -g testGainCard.c dominion.o rngs.o $(CFLAGS)
*
*
* int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
* {
*   //Note: supplyPos is enum of chosen card
*
*   //check if supply pile is empty (0) or card is not used in game (-1)
*   if ( supplyCount(supplyPos, state) < 1 )
*   {
*       return -1;
*   }
*
*   //added card for [whoseTurn] current player:
*   // toFlag = 0 : add to discard
*   // toFlag = 1 : add to deck
*   // toFlag = 2 : add to hand
*
*   if (toFlag == 1)
*   {
*       state->deck[ player ][ state->deckCount[ player ] ] = supplyPos;
*       state->deckCount[ player ]++;
*   }
*   else if (toFlag == 2)
*   {
*       state->hand[ player ][ state->handCount[ player ] ] = supplyPos;
*       state->handCount[ player ]++;
*   }
*   else
*   {
*       state->discard[ player ][ state->discardCount[ player ] ] = supplyPos;
*       state->discardCount[ player ]++;
*   }
*
*   //decrease number in supply pile
*   state->supplyCount[ supplyPos ]--;
*
*   return 0;
* }
******************************************************************************************************/


#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

void assertTrue(int supplyPos, struct gameState *state, int player, int testType, int handCount);

int main()
{
    int i, it, j, l, m, p, r, handCount;
    int seed = 500;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    
    //Arrays of all adventurers, council_rooms, and feasts.
    int adventurers[MAX_HAND];
    int council_rooms[MAX_HAND];
    int feasts[MAX_HAND];
    for(i = 0; i < MAX_HAND; i++)
    {
        adventurers[i] = adventurer;
        council_rooms[i] = council_room;
        feasts[i] = feast;
    }
    
    printf("TESTING gainCard():\n");
    for(p = 0; p < numPlayer; p++)
    {
        for(handCount = 1; handCount <= maxHandCount; handCount++)
        {
            memset(&G, 23, sizeof(struct gameState)); //Clear the game state
            r = initializeGame(numPlayer, k, seed, &G); //Initialize a new game
            //G.handCount[p] = handCount; //Set the number of cards on hand
            //memcpy(G.hand[p], adventurers, sizeof(int) * handCount); //Set all the cards to adventurer
            if(p > 0)
            {
                G.whoseTurn = p;
                for (it = 0; it < 5; it++){
                    drawCard(p, &G);
                }
            }
            printf("Test player %d with %d cards to add to the player's discard pile.\n", p, handCount);
            for(j = 1; j <= handCount; j++)
            {
                gainCard(adventurer, &G, 0, p);
            }
            assertTrue(adventurer, &G, p, 0, handCount);
            
            printf("Test player %d with %d cards to add to the player's deck.\n", p, handCount);
            for(l = 1; l <= handCount; l++)
            {
                gainCard(council_room, &G, 1, p);
            }
            assertTrue(council_room, &G, p, 1, handCount);
            
            printf("Test player %d with %d cards to add to the player's hand.\n", p, handCount);
            for(m = 1; m <= handCount; m++)
            {
                gainCard(feast, &G, 2, p);
            }
            assertTrue(feast, &G, p, 2, handCount);
            
        }
    }
    
}

void assertTrue(int supplyPos, struct gameState *state, int player, int testType, int handCount)
{
    int i;
    int discardTest = 0;
    int deckTest = 0;
    int handTest = 0;

    if(testType == 0)
    {
        if(handCount != state->discardCount[player])
        {
            printf("Discard count is incorrect for player %d!\n\n", player);
            return;
        }
        
        for(i = 0; i < state->discardCount[player]; i++)
        {
            if(state->discard[ player ][ i ] != supplyPos)
                discardTest = 1;
        }
        
        if(discardTest != 0)
        {
            printf("Discard test failed for player %d!\n\n", player);
            return;
        }
        else
            printf("Discard test passed for player %d!\n\n", player);
        
        if(state->supplyCount[supplyPos] != (10 - handCount))
      {
            printf("Supply count is incorrect for %d after player %d's turn!\n\n", supplyPos, player);
            return;
        }
    }
    
    if(testType == 1)
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
    }
    
    return;
}
