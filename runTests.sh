#!/bin/bash

# script for compiling the algorithm and running all the instances contained in
#   the algorithm/instances directory. Giving the script an input from 1 to 5
#   will select which set of instances directories to run, from the SET1
#   directories to the SET5 folders). With an input of 0, it runs all instances.

SOURCEDIR="algorithm"
INSTANCESDIR="instances"

COMPILER="g++"
COMPILERFLAGS="-Wall -g -o"
COMPILER="$COMPILER $COMPILERFLAGS"

RUN="./algorithm/output/main"
RUNFLAGS=
RUN="$RUN $RUNFLAGS"

function formatOutput () {
    y="${1%.ophs}.out"
    y="out/${y#instances/}"
    echo $y
    return 0
}

STARTTIME=$(date +%s%N)

# TODO: make so that this line is only executed if a "-c" flag is set.
echo "============================="
echo " + compiling..."
$COMPILER $SOURCEDIR/output/main $SOURCEDIR/*.cpp

if [[ $1 = "1" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 1..."
    echo "============================="

    for f in $INSTANCESDIR/SET1\ */*
    do
        $RUN "$f" "$(formatOutput "$f")"
    done
fi

if [[ $1 = "2" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 2..."
    echo "============================="
    for f in $INSTANCESDIR/SET2\ */*
    do
        $RUN "$f" "$(formatOutput "$f")"
    done
fi

if [[ $1 = "3" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 3..."
    echo "============================="
    for f in $INSTANCESDIR/SET3\ */*
    do
        $RUN "$f" "$(formatOutput "$f")"
    done
fi

if [[ $1 = "4" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 4..."
    echo "============================="
    for f in $INSTANCESDIR/SET4/*
    do
        $RUN "$f" "$(formatOutput "$f")"
    done
fi

if [[ $1 = "5" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 5..."
    echo "============================="
    for f in $INSTANCESDIR/SET5\ */*
    do
        $RUN "$f" "$(formatOutput "$f")"
    done
fi
ENDTIME=$(date +%s%N)
TIMES=$((($ENDTIME - $STARTTIME)/1000000000))
TIMEMS=$((($ENDTIME - $STARTTIME)/1000000))
echo "============================="
echo "total execution time: $TIMEMS [ms]."
echo "============================="
