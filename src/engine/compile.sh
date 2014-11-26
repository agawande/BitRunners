#!/bin/bash

gcc ADTs/berth.c ADTs/taxiway.c ADTs/plane.c parser.c simlib/simlib.c simulation.c gpct.c -o gpct -lm
gcc gpct_kill.c -o gpct_kill
