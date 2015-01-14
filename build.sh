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
    -t  Test Build
    -o  Option, can be 'build', 'rebuild', 'os' or 'pull' [default: build]
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
makeOSVerbose()
{
    cmake -C CMakeConfigs/OSOnly.txt .
    make
}
makeOSQuiet()
{
    cmake -C CMakeConfigs/OSOnly.txt . > /dev/null
    make > /dev/null
}
makeTestOSVerbose()
{
    cmake -C CMakeConfigs/TestOS.txt .
    make
}
makeTestOSQuiet()
{
    cmake -C CMakeConfigs/TestOS.txt . > /dev/null
    make > /dev/null
}
makeTestFullVerbose()
{
    cmake -C CMakeConfigs/TestFull.txt .
    make
}
makeTestFullQuiet()
{
    cmake -C CMakeConfigs/TestFull.txt . > /dev/null
    cmake > /dev/null
}

pullVerbose()
{
    git submodule init
    git submodule update --recursive
    git submodule foreach git pull origin master --recurse-submodules
}
pullQuiet()
{
    git submodule init >> /dev/null
    git submodule update --recursive >> /dev/null
    git submodule foreach git pull origin master --recurse-submodules >> /dev/null
}


OPT=
VERBOSE=
TEST=

while getopts ":o:?hvt" OPTION
do
    case $OPTION in
        o)
            OPT=$OPTARG
            ;;
        t)
            TEST=1
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

# Clear screen
clear

# Run it
if [[ $OPT == "build" ]] 
then
    if [[ -z "$VERBOSE" ]] 
    then
        if [[ -z "$TEST" ]]
        then
            makeVerbose
        else
            makeFullVerbose
        fi
    else
        if [[ -z "$TEST" ]]
        then
            makeQuiet
        else
            makeFullQuiet
        fi
    fi

    ./cleaner.sh -t cmake
fi
if [[ $OPT == "rebuild" ]] 
then
    ./cleaner.sh -t all

    if [[ -z "$VERBOSE" ]] 
    then
        makeVerbose
    else
        makeQuiet
    fi

    ./cleaner.sh -t cmake
fi
if [[ $OPT == "pull" ]] 
then
    ./cleaner.sh -t all

    if [[ -z "$VERBOSE" ]] 
    then
        pullVerbose

        if [[ -z "$TEST" ]]
        then
            makeVerbose
        else
            makeFullVerbose
        fi
    else
        pullQuiet

        if [[ -z "$TEST" ]]
        then
            makeQuiet
        else
            makeFullQuiet
        fi
    fi

    ./cleaner.sh -t cmake
fi
if [[ $OPT == "os" ]] 
then
    ./cleaner.sh -t all

    if [[ -z "$VERBOSE" ]] 
    then
        pullQuiet

        if [[ -z "$TEST" ]]
        then
            makeOSQuiet
        else
            makeTestOSQuiet
        fi
    else
        pullVerbose

        if [[ -z "$TEST" ]]
        then
            makeOSVerbose
        else
            makeOSTestVerbose
        fi
    fi

    ./cleaner.sh -t cmake
fi
if [[ "$TEST" ]] 
then
    ./UnitTests.app
fi

# Set Compiler Back
export CC=$CC
export CXX=$CXX

