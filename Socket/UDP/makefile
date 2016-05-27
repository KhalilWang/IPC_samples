ROOT=$(shell pwd)
SRC=$(ROOT)/src
BIN=$(ROOT)/bin


all: ser cli

ser: ser
	gcc $(SRC)/ser.c -o $(BIN)/ser

cli: cli
	gcc $(SRC)/cli.c -o $(BIN)/cli

.PHONY:clean

clean:
	rm $(BIN)/* -i
