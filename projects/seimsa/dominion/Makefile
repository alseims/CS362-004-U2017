CC = gcc-7.1
CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	$(CC) -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	$(CC) -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	$(CC) -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	$(CC)  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	$(CC) -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	$(CC) -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testGainCard: unittest1.c dominion.o rngs.o
	$(CC) -o testGainCard -g unittest1.c dominion.o rngs.o $(CFLAGS)

testDiscardCard: unittest2.c dominion.o rngs.o
	$(CC) -o testDiscardCard -g unittest2.c dominion.o rngs.o $(CFLAGS)

testSmithyCard: cardtest1.c dominion.o rngs.o
	$(CC) -o testSmithyCard -g cardtest1.c dominion.o rngs.o $(CFLAGS)

testSmithyCard_R: randomtestcard1.c dominion.o rngs.o
	$(CC) -o testSmithyCard_R -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)

testAdventurerCard: cardtest2.c dominion.o rngs.o
	$(CC) -o testAdventurerCard -g cardtest2.c dominion.o rngs.o $(CFLAGS)

testAdventurerCard_R: randomtestadventurer.c dominion.o rngs.o
	$(CC) -o testAdventurerCard_R -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

testCutpurseCard: cardtest3.c dominion.o rngs.o
	$(CC) -o testCutpurseCard -g cardtest3.c dominion.o rngs.o $(CFLAGS)

testCutpurseCard_R: randomtestcard2.c dominion.o rngs.o
	$(CC) -o testCutpurseCard_R -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)

testSea_HagCard: cardtest4.c dominion.o rngs.o
	$(CC) -o testSea_HagCard -g cardtest4.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	$(CC) -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	$(CC) -c interface.c -g  $(CFLAGS)

runtests: 
	./testGainCard >> unittestresult.out
	./testDiscardCard >> unittestresult.out
	./testSmithyCard >> unittestresult.out
	./testAdventurerCard >> unittestresult.out
	./testCutpurseCard >> unittestresult.out
	./testSea_HagCard >> unittestresult.out
	gcov-7.1 -b -c  dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

runtests2: 
	./testSmithyCard_R >> unittestresult.out
	./testAdventurerCard_R >> unittestresult.out
	./testCutpurseCard_R >> unittestresult.out
	gcov-7.1 -b -c  dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	$(CC) -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testGainCard testDiscardCard testSmithyCard testSmithyCard_R testAdventurerCard testAdventurerCard_R testCutpurseCard testCutpurseCard_R testSea_HagCard 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.gcov *.gcda *.gcno *.so *.out testGainCard testGainCard.exe testDiscardCard testDiscardCard.exe testSmithyCard testSmithyCard.exe testAdventurerCard testAdventurerCard.exe testCutpurseCard testCutpurseCard.exe testSea_HagCard testSea_HagCard.exe testSmithyCard_R testSmithyCard_R.exe testAdventurerCard_R testAdventurerCard_R.exe testCutpurseCard_R testCutpurseCard_R.exe
