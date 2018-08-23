# OPHS - GRASP
A GRASP algorithm to solve the Orienteering Problem with Hotel Selection

### Orienteering Problem with Hotel Selection
The Orienteering Problem with Hotel Selection (OPHS) is a problem proposed by [Divsalar et. al. (2013)](https://www.researchgate.net/publication/257192309_A_Variable_Neighborhood_Search_Method_for_the_Orienteering_Problem_with_Hotel_Selection), which expands on the original Orienteering Problem by also adding the selection of Hotels where the traveler must rest while visiting the Points of Interest.

### Greedy Randomized Adaptive Search Procedure
A Greedy Randomized Adaptive Search Procedure (GRASP) is a metaheuristic algorithm that consists of several iterations made up from successive constructions of a greedy randomized solution and subsequent iterative improvements of it through a local search.

### Instances
The instances are inside the `instances/` directory, along with a format description. They were downloaded from [KU Leuven](https://www.mech.kuleuven.be/en/cib/op#section-14).

### Running:
The C code is inside the `algorithm/src/` directory and its compiled output is stored in the `algorithm/bin/` as `ophs_grasp.out`. The parameters given to it are:
* `const char* infile`: the input file.
* `const char* outfile`: the output file.
* `unsigned int iter_n`: number of iterations to be ran.
* `unsigned int h_rcl`: size of the hotel RCL for the tour GRC.
* `unsigned int p_rcl`: size of the POIs RCL for the trip GRC.
* `unsigned int ls_iter_n`: number of iterations for the local search.
* `bool random`: set to 1, it tells the algorithm to run with a random seed.
* `bool tune`: set to 1, it tells the algorithm to only print tuning-related data.

An output file for each instance is already in the `out/` directory, organized in the same manner as the `instances/` folder for ease of access, with the difference that the extension of each file is `.ophsout`. An example output would be the following:

    0 15 20 40 32 31 25 5
    5 44 43 35 55 49 2
    2 50 61 62 66 1

Simply put, every number in this list represents a different vertex visited in the solution, each line represents a trip and therefore the whole file represents the entire tour. It is easy to see that the first and last vertices indexes for each trip are always hotels, due to the constraints of the problem.

### Extra Stuff:
There's a python script inside the main directory named `visualize.py` which can be ran to plot each vertex in a given instance and the solution tour constructed by the algorithm and store them alongside the output files. It's usage is as follows:
* `fileName`: string telling the filename of the file that is to be accessed. Taking advantage of the naming convention, only one filename is provided to access both the instance file and the output file.
* `save`: a bool simply stating if the output picture should be stored (`1`) or if it should be shown and deleted (`0`). By default, the pictures are stored alongside the output files.

To run the algorithm and the visualization script in a fast manner for all or a subset of the instances, there is a shell script in the main directory named `run-tests.sh`. It's usage is simple:
* `$1`: an integer from `0` to `5` that tells the script what set of instances to run, where `1` to `5` correlate directly to a set of instances (SET1 through SET5), and `0` tells the script to simply run on all the given instances for simplicity.
* `$2`: an integer that can be either `0` or `1`, where `0` tells the script to only run the algorithm while `1` points it to also run the visualization script.
