CC = gcc -Wall -pedantic -O3
EXEC = regle1 regle2 regle3
SRC = src
TEST = test



# executables
all: $(EXEC)

regle1: regle1.o stack_t.o
	$(CC) $^ -o regle1

regle2: regle2.o
	$(CC) $^ -o regle2

regle3: regle3.o
	$(CC) $^ -o regle3



# .o
# regle1.o
regle1.o: $(SRC)/regle1.c $(SRC)/stack_t.h
	$(CC) -c $(SRC)/regle1.c

# regle2.o
regle2.o: $(SRC)/regle2.c
	$(CC) -c $(SRC)/regle2.c

# regle3.o
regle3.o: $(SRC)/regle3.c
	$(CC) -c $(SRC)/regle3.c

# stack_t.o
stack_t.o: $(SRC)/stack_t.c $(SRC)/stack_t.h
	$(CC) -c $(SRC)/stack_t.c



# clean
clean:
	rm -rf *.o $(EXEC)
