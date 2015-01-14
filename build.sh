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
    echo "Make Verbose"

    cmake .
    make
}
makeQuiet()
{
    echo "Make Quiet"

    cmake . > /dev/null
    make > /dev/null
}

makeFullVerbose()
{
    echo "Make Full Verbose"

    cmake -C CMakeConfigs/Full.txt .
    make
}
makeFullQuiet()
{
    echo "Make Full Quiet"

    cmake -C CMakeConfigs/Full.txt . > /dev/null
    make > /dev/null
}
makeOSVerbose()
{
    echo "Make OS Verbose"

    cmake -C CMakeConfigs/OSOnly.txt .
    make
}
makeOSQuiet()
{
    echo "Make OS Quiet"

    cmake -C CMakeConfigs/OSOnly.txt . > /dev/null
    make > /dev/null
}
makeTestOSVerbose()
{
    echo "Make Test OS Verbose"

    cmake -C CMakeConfigs/TestOS.txt .
    make
}
makeTestOSQuiet()
{
    echo "Make Test OS Quiet"

    cmake -C CMakeConfigs/TestOS.txt . > /dev/null
    make > /dev/null
}
makeTestFullVerbose()
{
    echo "Make Full Verbose"

    cmake -C CMakeConfigs/TestFull.txt .
    make
}
makeTestFullQuiet()
{
    echo "Make Full Quiet"

    cmake -C CMakeConfigs/TestFull.txt . > /dev/null
    cmake > /dev/null
}

pullVerbose()
{
    echo "Pull Verbose"

    git submodule init
    git submodule update --recursive
    git submodule foreach git pull origin master --recurse-submodules
}
pullQuiet()
{
    echo "Pull Quiet"    

    git submodule init >> /dev/null
    git submodule update --recursive >> /dev/null
    git submodule foreach git pull origin master --recurse-submodules >> /dev/null
}


OPT='build'
VERBOSE=false
TEST=false

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

# Clear screen
clear

# Run it
if [[ $OPT == "build" ]] 
then
    if [[ -z "$VERBOSE" ]] 
    then
        if [[ -z "$TEST" ]]
        then
            makeFullVerbose
        else
            makeTestFullVerbose
        fi
    else
        if [[ -z "$TEST" ]]
        then
            makeFullQuiet
        else
            makeTestFullQuiet
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
            makeTestFullVerbose
        fi
    else
        pullQuiet

        if [[ -z "$TEST" ]]
        then
            makeQuiet
        else
            makeTestFullQuiet
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
            makeTestOSVerbose
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

