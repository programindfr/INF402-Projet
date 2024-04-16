CC = gcc -Wall -pedantic
EXEC = regle_2
SRC = src
TEST = test



all: $(EXEC)

regle_2: regle_2.o donnees.o logique.o
	$(CC) $^ -o regle_2



# .o
# regle_2.o
regle_2.o: $(TEST)/regle_2.c $(SRC)/donnees.h $(SRC)/logique.h
	$(CC) -c $(TEST)/regle_2.c

# donnees.o
donnees.o: $(SRC)/donnees.c $(SRC)/donnees.h
	$(CC) -c $(SRC)/donnees.c

# logique.o
logique.o: $(SRC)/logique.c $(SRC)/logique.h $(SRC)/donnees.h
	$(CC) -c $(SRC)/logique.c



#	clean	################################
clean:
	rm -rf *.o $(EXEC)
