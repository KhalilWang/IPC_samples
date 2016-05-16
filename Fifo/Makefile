all: ser cli
	

ser: ser.cpp
	g++ ser.cpp -o ser

cli: cli.cpp
	g++ cli.cpp -o cli

.PHONY: clean
clean:
	rm ser cli -rf
	rm read_fifo write_fifo -rf
