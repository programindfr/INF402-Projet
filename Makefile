CC = gcc -Wall -pedantic -O3
EXEC = takuzu
SRC = src
TEST = test
DIST = dist
VENV = $(DIST)/venv
INCLUDE = $(SRC)/include
CCFLAGS = -I $(INCLUDE)



all: mkdir $(EXEC)

build: all venv

takuzu: $(addprefix $(DIST)/, takuzu.o regle1.o regle2.o regle3.o stack_t.o)
	$(CC) $^ -o $(DIST)/takuzu

%/takuzu.o: $(SRC)/takuzu.c
	$(CC) -c $< -o $@ $(CCFLAGS)

%/regle1.o: $(SRC)/regle1.c $(INCLUDE)/regle1.h $(INCLUDE)/stack_t.h
	$(CC) -c $< -o $@ $(CCFLAGS)

%/regle2.o: $(SRC)/regle2.c $(INCLUDE)/regle2.h
	$(CC) -c $< -o $@ $(CCFLAGS)

%/regle3.o: $(SRC)/regle3.c $(INCLUDE)/regle3.h
	$(CC) -c $< -o $@ $(CCFLAGS)

%/stack_t.o: $(SRC)/stack_t.c $(INCLUDE)/stack_t.h
	$(CC) -c $< -o $@ $(CCFLAGS)



clean:
	rm -rf $(DIST)

mkdir:
	@mkdir -p $(DIST)

venv:
	@echo Setting up python virtual env ...
	@python3 -m venv $(VENV)
	@python3 -m venv --upgrade --upgrade-deps $(VENV)
	@./$(VENV)/bin/python3 -m pip install tk
	@echo Done

run:
	@./$(VENV)/bin/python3 $(SRC)/takuzu_gui.py
