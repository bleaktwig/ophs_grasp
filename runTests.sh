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
    for f in $INSTANCESDIR/SET1\ 1-2/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET1\ 2-3/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET1\ 3-4/*
    do
        $RUN "$f"
    done
fi

if [[ $1 = "2" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 2..."
    echo "============================="
    for f in $INSTANCESDIR/SET2\ 5-3/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET2\ 6-4/*
    do
        $RUN "$f"
    done
fi

if [[ $1 = "3" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 3..."
    echo "============================="
    for f in $INSTANCESDIR/SET3\ 10-4/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET3\ 12-5/*
    do
        $RUN "$f"
    done
fi

if [[ $1 = "4" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 4..."
    echo "============================="
    for f in $INSTANCESDIR/SET4/*
    do
        echo "$f"
        $RUN "$f"
    done
fi

if [[ $1 = "5" || $1 = "0" ]]
then
    echo "============================="
    echo " + executing SET 5..."
    echo "============================="
    for f in $INSTANCESDIR/SET5\ 10-5/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 10-6/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 12-4/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 12-6/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 15-4/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 15-5/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 15-6/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 15-8/*
    do
        $RUN "$f"
    done
    for f in $INSTANCESDIR/SET5\ 15-10/*
    do
        $RUN "$f"
    done
fi
ENDTIME=$(date +%s%N)
TIMES=$((($ENDTIME - $STARTTIME)/1000000000))
TIMEMS=$((($ENDTIME - $STARTTIME)/1000000))
echo "============================="
echo "total execution time: $TIMEMS [ms]."
echo "============================="
