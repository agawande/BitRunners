CC = gcc
SRC = ADTs/berth.c ADTs/taxiway.c ADTs/plane.c parser.c simlib/simlib.c sim_io.c simulation.c gpct.c
KILLSRC = gpct_kill.c
LIBS = -lm
EXEC = gpct
KILLEXEC = gpct_kill

all: main kill

clean:
	rm -rf $(EXEC) $(KILLEXEC) *~

main:
	$(CC) -ggdb -o $(EXEC) $(LIBS) $(SRC)
	
kill:
	$(CC) -ggdb -o $(KILLEXEC) $(KILLSRC)
