ROOT=$(shell pwd)
SRC=$(ROOT)/src
BIN=$(ROOT)/bin
HEAD=$(ROOT)/head

all: ser cli

ser: $(SRC)/ser.c
	gcc $(SRC)/ser.c -o $(BIN)/ser 

cli: $(SRC)/cli.c
	gcc $(SRC)/cli.c -o $(BIN)/cli

.PHONY:clean
clean:
	rm $(BIN)/* -i
