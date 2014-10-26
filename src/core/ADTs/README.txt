Input file format: text

    Group            ||||        Actual format	          ||||            Description

Simulation length:          (float)\n                               Length of the simulation in hours
Storms:                     (float) (float) (float)\n               Mean of storm occurence, base length, variation length
Airport:                    (int) (int) (float)\n                   Number of berths, number of taxiways, travel time
Fixed planes:               (float) (float) (float)\n               Base plane arrival rate, variation rate
                            (int)\n                                 Number of planes of a type
                                (float) (float) (float)\n           Frequency, base loading time, variation in loading time
                                (float)\n                           Cat3 landing gear probability
External planes:            (int)\n                                 Number of sets of external planes
                                (int)\n                             Number of planes in the set
                                (float)\n                           Cat3 landing gear probability
                                (float) (float)\n                   Loading base time, variation time
                                (float) (float)\n                   Round trip base time, variation in RTT


Explanation: indentation indicates repetition. Each indented line is repeated as many times
    as the previous line states, there is no indentation in the file.
