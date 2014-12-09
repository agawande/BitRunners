CC = gcc
SRC = ADTs/berth.c ADTs/taxiway.c ADTs/plane.c parser.c simlib/simlib.c sim_io.c simulation.c gpct.c
KILLSRC = gpct_kill.c
LIBS = -lm
EXEC = gpct
KILLEXEC = gpct_kill

all:
	$(CC) $(SRC) -o $(EXEC) $(LIBS)
	$(CC) $(KILLSRC) -o $(EXEC)
	
clean:
	rm -rf $(EXEC) $(KILLEXEC) *~
