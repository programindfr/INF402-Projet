CC = gcc -Wall -pedantic -O3
EXEC = takuzu
SRC = src
TEST = test
BUILD = build
VENV = $(BUILD)/venv
INCLUDE = $(SRC)/include
CCFLAGS = -I $(INCLUDE)



all: mkbuild $(EXEC)

release: all venv

takuzu: $(addprefix $(BUILD)/, takuzu.o regle1.o regle2.o regle3.o stack_t.o)
	$(CC) $^ -o takuzu

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
	rm -rf *.dimacs *.takuzu $(EXEC) $(BUILD)

mkbuild:
	@mkdir -p $(BUILD)

venv:
	python3 -m venv $(VENV)
	python3 -m venv --upgrade --upgrade-deps $(VENV)
	./$(VENV)/bin/python3 -m pip install tk

run:
	./$(VENV)/bin/python3 $(SRC)/takuzu_gui.py
