#!/bin/bash

gcc ADTs/berth.c ADTs/taxiway.c ADTs/plane.c parser.c simlib/simlib.c simulation.c -o a -lm
