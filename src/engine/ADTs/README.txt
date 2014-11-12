Input file format: text

    Group            ||||        Actual format	           ||||            Description

Simulation length:          (float)\n                               Length of the simulation in hours
Storms:                     (float) (float) (float)\n               Mean of storm occurence, length interval (i, f)
Airport:                    (int) (int) (float) (float)\n           Number of berths, number of taxiways, travel time, de/berthing time
Fixed planes:               (float) (float)\n                       Arrival time interval (i, f)
                            (float) (float)\n                       Loading time interval (i, f)
                            (float)\n                               Cat3 landing gear probability
External planes:            (int)\n                                 Number of sets of external planes
                                (int)\n                             Number of planes in the set
                                (float) (float)\n                   RTT interval (i, f)
                                (float) (float)\n                   Loading time interval (i, f)
                                (float)\n                           Cat3 landing gear probability


Explanation: indentation indicates repetition. Each indented line is repeated as many times
    as the previous line states, there is no indentation in the file.
