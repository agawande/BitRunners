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
	$(CC) $(SRC) -o $(EXEC) $(LIBS)
	
kill:
	$(CC) $(KILLSRC) -o $(KILLEXEC)
