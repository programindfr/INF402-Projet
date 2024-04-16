CC = gcc -Wall -pedantic
EXEC = main
SRC = src
BUILD = build

all: mkbuild $(EXEC)

mkbuild:
	mkdir -p $(BUILD)

#	main	################################
$(BUILD)/main.o: $(SRC)/main.h $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(BUILD)/main.o

main: $(BUILD)/main.o
	$(CC) $(BUILD)/main.o -o main

#	clean	################################
clean:
	rm -rf $(BUILD) $(EXEC)
