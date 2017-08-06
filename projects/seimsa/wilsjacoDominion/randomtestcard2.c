//Cutpurse
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"


int checkCutpurseCard(int player, struct gameState *post, int handPos);


int main()
{
    int i, j, n, r, p, handPos, numPlayers = 0;
    int numCoppers, copperPosition;
    struct gameState G;
    
    printf("Testing Cutpurse Card.\n");
    printf("RANDOM TESTS.\n");
    
    SelectStream(2);
    PutSeed(4);
    
    for(n = 0; n < 2000; n++)
    {
        printf("Test %d\n", n);
        for(i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        
        while(numPlayers < 2)
        {
            numPlayers = floor(Random() * MAX_PLAYERS);
        }
        G.numPlayers = numPlayers;
        p = floor(Random() * numPlayers);
        G.whoseTurn = p;
        for(i = 0; i <= numPlayers; i++)
        {
            G.deckCount[i] = floor(Random() * MAX_DECK);
        }
        for(i = 0; i <= numPlayers; i++)
        {
            G.discardCount[i] = floor(Random() * MAX_DECK);
        }
        
        for(i = 0; i <= numPlayers; i++)
        {
            G.handCount[i] = floor(Random() * MAX_HAND);
            if(i == p)
            {
                handPos = floor(Random() * G.handCount[i]);
                G.hand[i][handPos] = cutpurse;
                
                numCoppers = floor(Random() * G.handCount[i]);
                for(j = 0; j < numCoppers; j++)
                {
                    copperPosition = floor(Random() * G.handCount[i]);
                    if(G.hand[i][copperPosition] != copper)
                    {
                        G.hand[i][copperPosition] = copper;
                    }
                    else
                    {
                        do
                        {
                            copperPosition = floor(Random() * G.handCount[i]);
                            
                        }while(G.hand[i][copperPosition] == copper || G.hand[i][copperPosition] == cutpurse);
                        G.hand[i][copperPosition] = copper;
                    }
                }
            }
            if(i != p)
            {
                numCoppers = floor(Random() * G.handCount[i]);
                for(j = 0; j < numCoppers; j++)
                {
                    copperPosition = floor(Random() * G.handCount[i]);
                    if(G.hand[i][copperPosition] != copper)
                    {
                        G.hand[i][copperPosition] = copper;
                    }
                    else
                    {
                        do
                        {
                            copperPosition = floor(Random() * G.handCount[i]);
                            
                        }while(G.hand[i][copperPosition] == copper);
                        G.hand[i][copperPosition] = copper;
                    }
                }
            }
        }
        
        
        G.playedCardCount = floor(Random() * MAX_DECK);
        checkCutpurseCard(p, &G, handPos);
    }
}


int checkCutpurseCard(int player, struct gameState *post, int handPos)
{
    int i, j, r, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 2;
    int flag = 0, passedTestCounter = 0;
    struct gameState pre;
    
    
    memcpy(&pre, post, sizeof(struct gameState));
    
    r = cardEffect(cutpurse, choice1, choice2, choice3, post, handPos, &bonus);
    
    //Determine the current player's coin count with +2 bonus from Cutpurse.
    pre.coins = 0;
    for(i = 0; i < pre.handCount[player]; i++)
    {
        if(pre.hand[player][i] == copper)
        {
            pre.coins += 1;
        }
    }
    pre.coins += 2;
    
    //Have every other player discard a copper in there hand if one exists.
    for (i = 0; i < pre.numPlayers; i++)
    {
        if (i != player)
        {
            for (j = 0; j < pre.handCount[i]; j++)
            {
                if (pre.hand[i][j] == copper)
                {
                    //Put Cutpurse card onto the played cards pile.
                    pre.playedCards[pre.playedCardCount] = pre.hand[i][j];
                    pre.playedCardCount++;
                    
                    //Set the hand position that contained the Cutpurse card to -1
                    pre.hand[i][j] = -1;
                    
                    if ( j == (pre.handCount[i] - 1) ) 	//last card in hand array is played
                    {
                        //reduce number of cards in hand
                        pre.handCount[i]--;
                    }
                    else if ( pre.handCount[i] == 1 ) //only one card in hand
                    {
                        //reduce number of cards in hand
                        pre.handCount[i]--;
                    }
                    else
                    {
                        //replace discarded card with last card in hand
                        pre.hand[i][j] = pre.hand[i][(pre.handCount[i] - 1)];
                        //set last card to -1
                        pre.hand[i][pre.handCount[i] - 1] = -1;
                        //reduce number of cards in hand
                        pre.handCount[i]--;
                    }
                    break;
                }
            }
            
        }
        
    }
    
    //Have current player discard Cutpurse.
    //Put Cutpurse card onto the played cards pile.
    pre.playedCards[pre.playedCardCount] = pre.hand[player][handPos];
    pre.playedCardCount++;
    
    //Set the hand position that contained the Cutpurse card to -1
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
    
    
    if(r == 0)
        printf("TEST PASSED: Cutpurse card played\n");
    printf("----TEST RESULTS----\n");
    printf("----PRE--------POST----\n");
    //printf("Hand Pos: %d\n", handPos);
    
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
        printf("EMBARGO TOKENS TEST FAILED!\n");
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
    for(i = 0; i < pre.numPlayers; i++)
    {
        for(j = 0; j < post->handCount[i]; j++)
        {
            if(pre.hand[i][j] != post->hand[i][j])
            {
                printf("Hand[%d][%d]:  %d                %d\n", i, j, pre.hand[i][j], post->hand[i][j]);
                flag = 1;
            }
        }
    }
    if(flag == 1)
        printf("HAND TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < pre.numPlayers; i++)
    {
        if(pre.handCount[i] != post->handCount[i])
        {
            printf("HC[%d]:     %d                %d\n", i, pre.handCount[i], post->handCount[i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("HAND COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < pre.numPlayers; i++)
    {
        for(j = 0; j < post->deckCount[i]; j++)
        {
            if(pre.deck[i][j] != post->deck[i][j])
            {
                printf("deck[%d][%d]:  %d                %d\n", i, j, pre.deck[i][j], post->deck[i][j]);
                flag = 1;
            }
        }
    }
    if(flag == 1)
        printf("DECK TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < pre.numPlayers; i++)
    {
        if(pre.deckCount[i] != post->deckCount[i])
        {
            printf("DeckC:  %d                %d\n", pre.deckCount[i], post->deckCount[i]);
            flag = 1;
        }
    }
    if(flag == 1)
        printf("DECK COUNT TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i < pre.numPlayers; i++)
    {
        for(j = 0; j < post->discardCount[i]; j++)
        {
            if(pre.discard[i][j] != post->discard[i][j])
            {
                printf("Discard[%d][%d]:  %d                %d\n", i, j, pre.discard[i][j], post->discard[i][j]);
                flag = 1;
            }
        }
    }
    if(flag == 1)
        printf("DISCARD TEST FAILED!\n");
    else
        passedTestCounter++;
    
    flag = 0;
    for(i = 0; i <= pre.numPlayers; i++)
    {
        if(pre.discardCount[i] != post->discardCount[i])
        {
            printf("DiscC:  %d                %d\n", pre.discardCount[i], post->discardCount[i]);
            flag = 1;
        }
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
    
    
    return 0;
}


