import random
import math

########################################################################################################################
# NOTES: READ ME!!!
# THIS SCRIPT WILL GENERATE 10 DATASETS CONTAINING COORDINATES PAIRS (X,Y) OF INCREASING SIZE.
# IT MAY TAKE TIME TO RUN DEPENDING ON YOUR COMPUTER'S PROCESSING POWER.
#
# AS CONFIGURED NOW, IT WILL GENERATE 10 DATASETS (HULLS_TO_PRODUCE),
# STARTING WITH ONE OF 26 COORDINATE PAIRS AND ENDING WITH ONE OF ABOUT 1800 COORDINATE PAIRS.
#
# IT DOES SO BY MULTIPLYING THE NUMBER OF COORDINATE PAIRS FROM THE PREVIOUS DATASET BY A CONSTANT VALUE.
# CURRENTLY, THIS MULTIPLIER IS SET TO 1.6 (COORD_MULTIPLICATION_CONSTANT).
#
# THE MINIMUM X AND Y VALUE FOR A COORDINATE PAIR IS CURRENTLY SET AT -2000 (MIN_COORD_CONST).
# THE MAXIMUM X AND Y VALUE FOR A COORDINATE PAIR IS CURRENTLY SET AT 2000 (MAX_COORD_CONST).
#
# IF YOU DESIRE SMALLER DATASETS, IT IS RECOMMENDED TO CHANGE THE CONSTANT TO MAYBE 1.4 OR SMALLER.
########################################################################################################################

HULLS_TO_PRODUCE = 10 # NUMBER OF DATASETS PRODUCING
COORD_MULTIPLICATION_CONSTANT = 1.6
MIN_COORD_CONST = -2000 # LOWEST X AND Y VALUE
MAX_COORD_CONST = 2000 # HIGHEST X AND Y VALUE

# STARTING NUMBER OF COORDINATE PAIRS (WILL ACTUALLY BE 26 WITH 1.6 MULTIPLIER)
num_coords = 16

# GENERATE 10 CONVEX HULL DATASETS
for i in range(1, HULLS_TO_PRODUCE +1):
    num_coords = math.ceil(num_coords * COORD_MULTIPLICATION_CONSTANT) # EACH DATASET HAS 1.6 TIMES AS MANY COORDINATE PAIRS AS PREVIOUS
    coords = [(random.randint(MIN_COORD_CONST, MAX_COORD_CONST), random.randint(MIN_COORD_CONST, MAX_COORD_CONST)) for _ in range(num_coords)]
    print("Printing coords...")
    print(coords, "\n", "\n")

    coordList = list(coords)
    # WRITE TO A FILE TO CONTAIN THE DATASET
    fname = f'coordinatePairs_{i}.txt'
    with open(fname, "w") as graphFile:

        # WRITE NUMBER OF COORDINATE PAIRS
        graphFile.write("[" + str(num_coords) + "]" + "\n")

        # WRITE EACH COORDINATE PAIR ON A NEW LINE
        for coordPair in coordList:
            graphFile.write(str(coordPair[0]) + "," + str(coordPair[1]) + "\n")

