#!/bin/bash

# script for compiling the algorithm and running all the instances contained in
#   the algorithm/instances directory. Giving the script an input from 1 to 5
#   will select which set of instances directories to run, from the SET1
#   directories to the SET5 folders). With an input of 0, it runs all instances.

SOURCEDIR="algorithm-c"
INSTANCESDIR="instances"

COMPILER="gcc"
COMPILERFLAGS="-std=c11 -o"
COMPILER="$COMPILER $COMPILERFLAGS"

CRUN="./algorithm-c/out/main"

ITER_N="1000"
H_RCL_SIZE="3"
P_RCL_SIZE="3"
RAN="1"
DEBUG="0"

CRUNFLAGS="$ITER_N $H_RCL_SIZE $P_RCL_SIZE $RAN $DEBUG"

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

STARTTIME=$(date +%s%N)

# TODO: make so that this line is only executed if a "-c" flag is set.
echo "============================="
echo " + compiling..."
$COMPILER $SOURCEDIR/out/main $SOURCEDIR/src/*.c -lm

if [[ $1 = "1" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 1..."
    echo "============================="

    for f in $INSTANCESDIR/SET1_*/*
    do
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$RAN" "$DEBUG"
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
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$RAN" "$DEBUG"
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
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$RAN" "$DEBUG"
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
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$RAN" "$DEBUG"
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
        $CRUN "$f" "$(formatOutput "$f")" "$ITER_N" "$H_RCL_SIZE" "$P_RCL_SIZE" "$RAN" "$DEBUG"
        if [[ $2 = "1" ]]
        then
            $PRUN "$(formatPython "$f")" $PMODE
        fi
    done
fi
ENDTIME=$(date +%s%N)
TIMEMS=$((($ENDTIME - $STARTTIME)/1000000))
echo "============================="
echo "total execution time: $TIMEMS [ms]."
echo "============================="
