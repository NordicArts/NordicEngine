#!/bin/bash
oldCC=$CC
oldCXX=$CXX

# Set the compiler to clang
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

usage()
{
cat << EOF
usage: $0 options
    
This script can build, clean, and grab new versions,
    Rebuild = Clean and Build
    Pull = Clean, Pull Dependencies and Build

OPTIONS:
    -h  Show this message
    -v  Verbose
    -o  Option, can be 'rebuild' or 'pull'
EOF
}

makeVerbose()
{
    cmake .
    make
}
makeQuiet()
{
    cmake . > /dev/null
    make > /dev/null
}


OPT=
VERBOSE=

while getopts "ho:v" OPTION
do
    case $OPTION in
        t)
            OPT=$OPTARG
            ;;
        h)
            usage
            exit 1
            ;;
        v)
            VERBOSE=1
            ;;
        ?)
            usage
            exit
            ;;
    esac
done

if [[ -z "$OPT" ]]
then
    OPT=build
fi

# Run it
clear
if [[ $OPT == "build" ]]
then
    if [[ -z "$VERBOSE" ]]
    then
        makeQuiet
    else
        makeVerbose
    fi

    ./cleaner.sh -t cmake
fi
if [[ $OPT == "rebuild" ]] 
then
    ./cleaner.sh -t all

    if [[ -z "$VERBOSE" ]]
    then
        makeQuiet
    else
        makeVerbose
    fi

    ./cleaner.sh -t cmake
fi
if [[ $OPT == "pull" ]]
then
    ./cleaner.sh -t all

    if [[ -z "$VERBOSE" ]]
    then
        git submodule init
        git submodule update --recursive
        git submodule foreach git pull origin master --recurse-submodules
        makeVerbose
    else
        git submodule init >> /dev/null
        git submodule update --recursive >> /dev/null
        git submodule foreach git pull origin master --recurse-submodules >> /dev/null
        makeQuiet
    fi

    ./cleaner.sh -t cmake
fi

# Set Compiler Back
export CC=$CC
export CXX=$CXX

