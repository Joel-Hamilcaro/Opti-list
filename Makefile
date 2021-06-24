CC=gcc
CFLAGS=-g -Wall

launcher: alignement.o noeud.o tranche.o projet2019.o affichage.o tests.o classique.o main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c tests.h
	$(CC) $(CFLAGS) -c -o $@ $<

alignement.o: alignement.c alignement.h
	$(CC) $(CFLAGS) -c -o $@ $<

noeud.o: noeud.c noeud.h alignement.h
	$(CC) $(CFLAGS) -c -o $@ $<

tranche.o: tranche.c tranche.h
	$(CC) $(CFLAGS) -c -o $@ $<

projet2019.o: projet2019.c projet2019.h noeud.h tranche.h
	$(CC) $(CFLAGS) -c -o $@ $<

classique.o: classique.c classique.h alignement.h
	$(CC) $(CFLAGS) -c -o $@ $<

affichage.o: affichage.c affichage.h projet2019.h classique.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests.o: tests.c tests.h affichage.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *~ *.o launcher
