# ophs_grasp
A GRASP algorithm to solve the Orienteering Problem with Hotel Selection

### Orienteering Problem with Hotel Selection
The Orienteering Problem with Hotel Selection (OPHS) is a problem proposed by (**TODO**: REFERENCE) Divsalar et. al., which expands on the original Orienteering Problem by also adding the selection of Hotels where the traveler must rest while visiting the Points of Interest.

### Greedy Randomized Adaptive Search Procedure
A Greedy Randomized Adaptive Search Procedure (GRASP) is a metaheuristic algorithm that consists of iterations made up from successive constructions of a greedy randomized solution and subsequent iterative improvements of it through a local search.

### GRASP applied on OPHS
* **TODO**

### Instances
The instances are inside the `instances/` directory, along with a format description in the same directory. They were downloaded from [KU Leuven](https://www.mech.kuleuven.be/en/cib/op#section-14).

### Running:
The C code is inside the `algorithm/src/` directory and its compiled output is stored in the `algorithm/bin/`. The parameters given to it are:
* **TODO**: Usage

An output file for each instance is already in the `out/` directory, and its format is as follows:
* **TODO**: explain the output files format

There's a python script inside the main directory named `visualize.py` which can be ran to plot each vertex in a given instance and the solution tour constructed by the algorithm and store them alongside the output files. It's usage is as follows:
* **TODO**: Usage

To run the algorithm and the visualization script in a fast manner for all the instances or a subset of them, there is a shell script in the main directory named `run-tests.sh`. It's usage is simple:
* `$1`: an integer from `0` to `5` that tells the script what set of instances to run, where `1` to `5` correlate directly to a set of instances (SET1 through SET5), and `0` tells the script to simply run on all the given instances.
* `$2`: an integer that can be either `0` or `1`, where `0` tells the script to only run the algorithm while `1` points it to also running the visualization script.
