#!/bin/bash

echo "Compiling";
gcc ADTs/berth.c ADTs/taxiway.c ADTs/plane.c parser.c simlib/simlib.c sim_io.c simulation.c gpct.c -o gpct -lm -w
gcc gpct_kill.c -o gpct_kill -w
