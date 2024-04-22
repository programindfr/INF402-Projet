#CC = gcc -Wall -pedantic -O3
CC = gcc -Wall -pedantic -g
EXEC = takuzu
SRC = src
TEST = test
BUILD = build
VENV = $(BUILD)/venv



all: mkbuild $(EXEC)

release: all venv

takuzu: $(BUILD)/takuzu.o $(BUILD)/regle1.o $(BUILD)/regle2.o $(BUILD)/regle3.o $(BUILD)/stack_t.o
	$(CC) $^ -o takuzu

%/takuzu.o: $(SRC)/takuzu.c
	$(CC) -c $< -o $@

%/regle1.o: $(SRC)/regle1.c $(SRC)/regle1.h $(SRC)/stack_t.h
	$(CC) -c $< -o $@

%/regle2.o: $(SRC)/regle2.c $(SRC)/regle2.h
	$(CC) -c $< -o $@

%/regle3.o: $(SRC)/regle3.c $(SRC)/regle3.h
	$(CC) -c $< -o $@

%/stack_t.o: $(SRC)/stack_t.c $(SRC)/stack_t.h
	$(CC) -c $< -o $@



clean:
	rm -rf *.dimacs *.takuzu $(EXEC) $(BUILD)

mkbuild:
	mkdir -p $(BUILD)

venv:
	python3 -m venv $(VENV)
	python3 -m venv --upgrade --upgrade-deps $(VENV)
	./$(VENV)/bin/python3 -m pip install tk

run:
	./$(VENV)/bin/python3 $(SRC)/takuzu_gui.py
