CC = gcc -Wall -pedantic -O3
EXEC = takuzu
SRC = src
TEST = test



# executables
all: $(EXEC)

takuzu: takuzu.o regle1.o regle2.o regle3.o stack_t.o
	$(CC) $^ -o takuzu



# .o
# takuzu.o
takuzu.o: $(SRC)/takuzu.c
	$(CC) -c $(SRC)/takuzu.c

# regle1.o
regle1.o: $(SRC)/regle1.c $(SRC)/regle1.h $(SRC)/stack_t.h
	$(CC) -c $(SRC)/regle1.c

# regle2.o
regle2.o: $(SRC)/regle2.c $(SRC)/regle2.h
	$(CC) -c $(SRC)/regle2.c

# regle3.o
regle3.o: $(SRC)/regle3.c $(SRC)/regle3.h
	$(CC) -c $(SRC)/regle3.c

# stack_t.o
stack_t.o: $(SRC)/stack_t.c $(SRC)/stack_t.h
	$(CC) -c $(SRC)/stack_t.c



# clean
clean:
	rm -rf *.o $(EXEC)
