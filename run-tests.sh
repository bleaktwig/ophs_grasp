#!/bin/bash

# script for compiling the algorithm and running it with a given set of instances.
# usage: ./run-tests.sh N M
#   N: represents the SET to run. Possible values:
#      0: run all sets from 1 to 5, or under SET*/*.ophs
#      1: run all sets under SET1_*/*.ophs
#      2: run all sets under SET2_*/*.ophs
#      3: run all sets under SET3_*/*.ophs
#      4: run all sets under SET4/*.ophs
#      5: run all sets under SET5*/*.ophs
#   M: tells the program if it should plot or not a picture of the solution
#      found by using the "visualize.py" script, 1 meaning yes and 0 meaning no.

SOURCEDIR="algorithm"
INSTANCESDIR="instances"

CRUN="./algorithm/bin/ophs_grasp.out"

ITER_N="5000"
H_RCL_SIZE="8"
P_RCL_SIZE="5"
LS_ITER_N="15"
RAN="1"
TUNE="0"

PRUN="python3 visualize.py"
PMODE=1

function formatPython () {
    y="${1%.ophs}"
    y="${y#instances/}"
    echo $y
    return 0
}

function formatOutput () {
    y="${1%.ophs}.ophsout"
    y="out/${y#instances/}"
    echo $y
    return 0
}

echo "============================="
echo " + compiling..."
cd algorithm
make
cd ..

STARTTIME=$(date +%s%N)

if [[ $1 = "1" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 1..."
    echo "============================="

    for f in $INSTANCESDIR/SET1_*/*
    do
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$LS_ITER_N" "$RAN" "$TUNE"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi

if [[ $1 = "2" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 2..."
    echo "============================="
    for f in $INSTANCESDIR/SET2_*/*
    do
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$LS_ITER_N" "$RAN" "$TUNE"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi

if [[ $1 = "3" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 3..."
    echo "============================="
    for f in $INSTANCESDIR/SET3_*/*
    do
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$LS_ITER_N" "$RAN" "$TUNE"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi

if [[ $1 = "4" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 4..."
    echo "============================="
    for f in $INSTANCESDIR/SET4/*
    do
        valgrind --leak-check=full $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$LS_ITER_N" "$RAN" "$TUNE"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi

if [[ $1 = "5" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 5..."
    echo "============================="
    for f in $INSTANCESDIR/SET5_*/*
    do
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$LS_ITER_N" "$RAN" "$TUNE"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi

cd algorithm
make clean
cd ..

ENDTIME=$(date +%s%N)
TIMEMS=$((($ENDTIME - $STARTTIME)/1000000))
echo "============================="
echo "total execution time: $TIMEMS [ms]."
echo "============================="
