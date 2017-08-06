//Smithy
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

int checkSmithyCard(int handPos, int player, struct gameState *post);


int main()
{
    int i, n, r, p, handPos;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf("Testing Smithy Card.\n");
    printf("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(4);

    for(n = 0; n < 2000; n++)
    {
        for(i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        
        p = floor(Random() * 2);
        G.whoseTurn = p;
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        handPos = floor(Random() * G.handCount[p]);
        G.hand[p][handPos] = smithy;
        G.playedCardCount = floor(Random() * MAX_DECK);
        checkSmithyCard(handPos, p, &G);
    }
}


int checkSmithyCard(int handPos, int player,  struct gameState *post)
{
    int choice1 = 0, choice2 = 0, choice3 = 0;
    int bonus = 0, i, r;
    int handCounter, compareReturn, flag = 0, passedTestCounter = 0;
    struct gameState pre;
    
    //post->deckCount[player] = 2;
    memcpy(&pre, post, sizeof(struct gameState));
    
    r = cardEffect(smithy, choice1, choice2, choice3, post, handPos, &bonus);
    
    //No shuffle needed if deck count is 3 or greater.
    if(pre.deckCount[player] >= 3)
    {
        //Get hand count before cards are drawn and use as a counter.
        handCounter = pre.handCount[player];
        
        //Draw three cards from the deck.
        for(i = handCounter; i < (handCounter + 3) ; i++)
        {
            pre.hand[player][i] = pre.deck[player][pre.deckCount[player] - 1];
            pre.deckCount[player]--;
            pre.handCount[player]++;
        }
    
        //Put Smithy card onto the played cards pile.
        pre.playedCards[pre.playedCardCount] = pre.hand[player][handPos];
        pre.playedCardCount++;
        
        //Set the hand position that contained the Smithy card to -1
        pre.hand[player][handPos] = -1;
        
        if ( handPos == (pre.handCount[player] - 1) ) 	//last card in hand array is played
        {
            //reduce number of cards in hand
            pre.handCount[player]--;
        }
        else if ( pre.handCount[player] == 1 ) //only one card in hand
        {
            //reduce number of cards in hand
            pre.handCount[player]--;
        }
        else
        {
            //replace discarded card with last card in hand
            pre.hand[player][handPos] = pre.hand[player][(pre.handCount[player] - 1)];
            //set last card to -1
            pre.hand[player][pre.handCount[player] - 1] = -1;
            //reduce number of cards in hand
            pre.handCount[player]--;
        }
    }
    //Shuffle is needed. Ensure that the discard count is 3 or greater. Copy over the deck and discard
    //piles to avoid having to shuffle manually.
    else if(pre.discardCount[player] >= 3)
    {
        memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.discardCount[player]);
        memcpy(pre.discard[player], post->discard[player], sizeof(int)*pre.discardCount[player]);
        
        //Put Smithy card onto the played cards pile.
        pre.playedCards[pre.playedCardCount] = pre.hand[player][handPos];
        pre.playedCardCount++;
        
        //Copy the drawn card, from post, that was put into the Smithy card's hand position.
        pre.hand[player][handPos] = post->hand[player][handPos];
        
        //Get post hand count and use as a counter.
        handCounter = post->handCount[player];
        
        //Copy the last two remaing drawn cards from post hand to
        for(i = handCounter - 1; i >= (handCounter - 2); i--)
        {
            pre.hand[player][i] = post->hand[player][i];
            pre.handCount[player]++;
        }
        
        
        pre.deckCount[player] = pre.discardCount[player] - 1;
        pre.discardCount[player] = 0;
    }
    
    

    
    if(r == 0)
        printf("TEST PASSED: Smithy card played\n");
    printf("----TEST RESULTS----\n");
    
    if(pre.numPlayers != post->numPlayers)
    {
        printf("Num players: %d                %d\n", pre.numPlayers, post->numPlayers);
        flag = 1;
    }
    if(flag == 1)
        printf("NUMPLAYERS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i <= treasure_map; i++)
    {
        if(pre.supplyCount[i] != post->supplyCount[i])
        {
            printf("SuppC[%d]:  %d                %d\n", i, pre.supplyCount[i], post->supplyCount[i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("SUPPLYCOUNTS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i <= treasure_map; i++)
    {
        if(pre.embargoTokens[i] != post->embargoTokens[i])
        {
            printf("ET[%d]:  %d                %d\n", i, pre.embargoTokens[i], post->embargoTokens[i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("EMBARGOTOKENS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.outpostPlayed != post->outpostPlayed)
    {
        printf("Outpost Played:     %d                %d\n", pre.outpostPlayed, post->outpostPlayed);
        flag = 1;
    }
    if(flag == 1)
        printf("OUTPOST PLAYED TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.outpostTurn != post->outpostTurn)
    {
        printf("Outpost Turn:     %d                %d\n", pre.outpostTurn, post->outpostTurn);
        flag = 1;
    }
    if(flag == 1)
        printf("OUTPOST TURN TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.whoseTurn != post->whoseTurn)
    {
        printf("Whose Turn:     %d                %d\n", pre.whoseTurn, post->whoseTurn);
        flag = 1;
    }
    if(flag == 1)
        printf("WHOSE TURN TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.phase != post->phase)
    {
        printf("Phase:     %d                %d\n", pre.phase, post->phase);
        flag = 1;
    }
    if(flag == 1)
        printf("PHASE TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.numActions != post->numActions)
    {
        printf("Num Actions:     %d                %d\n", pre.numActions, post->numActions);
        flag = 1;
    }
    if(flag == 1)
        printf("NUM ACTIONS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.coins != post->coins)
    {
        printf("Coins:     %d                %d\n", pre.coins, post->coins);
        flag = 1;
    }
    if(flag == 1)
        printf("COINS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.numBuys != post->numBuys)
    {
        printf("Num Buys:     %d                %d\n", pre.numBuys, post->numBuys);
        flag = 1;
    }
    if(flag == 1)
        printf("NUM BUYS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < post->handCount[player]; i++)
    {
        if(pre.hand[player][i] != post->hand[player][i])
        {
            printf("Hand[%d]:  %d                %d\n", i, pre.hand[player][i], post->hand[player][i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("HAND TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.handCount[player] != post->handCount[player])
    {
        printf("HC:     %d                %d\n", pre.handCount[player], post->handCount[player]);
        flag = 1;
    }
    if(flag == 1)
        printf("HAND COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < post->deckCount[player]; i++)
    {
        if(pre.deck[player][i] != post->deck[player][i])
        {
            printf("deck[%d]:  %d                %d\n", i, pre.deck[player][i], post->deck[player][i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("DECK TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.deckCount[player] != post->deckCount[player])
    {
        printf("DeckC:  %d                %d\n", pre.deckCount[player], post->deckCount[player]);
        flag = 1;
    }
    if(flag == 1)
        printf("DECK COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < post->discardCount[player]; i++)
    {
        if(pre.discard[player][i] != post->discard[player][i])
        {
            printf("Discard[%d]:  %d                %d\n", i, pre.discard[player][i], post->discard[player][i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("DISCARD TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.discardCount[player] != post->discardCount[player])
    {
        printf("DiscC:  %d                %d\n", pre.discardCount[player], post->discardCount[player]);
        flag = 1;
    }
    if(flag == 1)
        printf("DISCARD COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < post->playedCardCount; i++)
    {
        if(pre.playedCards[i] != post->playedCards[i])
        {
            printf("Played Cards[%d]:  %d                %d\n", i, pre.playedCards[i], post->playedCards[i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("PLAYED CARDS TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    if(pre.playedCardCount != post->playedCardCount)
    {
        printf("PCC:  %d                %d\n", pre.playedCardCount, post->playedCardCount);
        flag = 1;
    }
    if(flag == 1)
        printf("PC COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    if(passedTestCounter == 18)
        printf("ALL TESTS PASSED!\n");
    
    /*compareReturn = memcmp(&pre, post, sizeof(struct gameState));
    
    printf("Compare return: %d\n", compareReturn);
    if(memcmp(&pre, post, sizeof(struct gameState)) == 0)
        printf("TEST PASSED: Oracle Complete\n");
    */
    return 0;
}
