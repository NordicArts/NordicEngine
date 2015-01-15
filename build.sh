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
    -p  Pull, pulls the latest code and all its gitmodules
    -t  Test Build, once built run the unit tests    
    -o  Option, can be 'build', 'rebuild', 'full' or 'os' [default: build]
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
    make > /dev/null
}
makeTestVerbose()
{
    echo "Make Test Verbose"

    cmake -C CMakeConfigs/Test.txt .
    make
}
makeTestQuiet() 
{
    echo "Make Test Quiet"
    
    cmake -C CMakeConfigs/Test.txt . > /dev/null
    make > /dev/null
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
PULL=false

while getopts ":o:?hvt" OPTION 
do
    case $OPTION in
        o)
            OPT=$OPTARG
            ;;
        t)
            TEST=1
            ;;
        p)
            PULL=1
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

# Build Standard
if [[ $OPT == "build" ]] 
then
    ./cleaner.sh -t build

    if [[ $VERBOSE == 1 ]] 
    then
        if [[ $PULL == 1 ]] 
        then
            pullVerbose
        fi

        if [[ $TEST == 1 ]]
        then
            makeTestVerbose
        else
            makeVerbose
        fi
    else
        if [[ $PULL == 1 ]] 
        then
            pullQuiet
        fi

        if [[ $TEST == 1 ]]
        then
            makeTestQuiet
        else
            makeQuiet
        fi
    fi

    ./cleaner.sh -t cmake
fi

# Rebuild
if [[ $OPT == "rebuild" ]] 
then
    ./cleaner.sh -t all

    if [[ $VERBOSE == 1 ]] 
    then
        makeVerbose
    else
        makeQuiet
    fi

    ./cleaner.sh -t cmake
fi

# Build OS 
if [[ $OPT == "os" ]] 
then
    ./cleaner.sh -t all

    if [[ $VERBOSE == 1 ]] 
    then
        if [[ $PULL == 1 ]] 
        then
            pullVerbose
        fi

        if [[ $TEST == 1 ]] 
        then
            makeTestOSVerbose
        else
            makeOSVerbose
        fi
    else
        if [[ $PULL == 1 ]] 
        then
            pullQuiet
        fi

        if [[ $TEST == 1 ]] 
        then
            makeTestOSQuiet
        else
            makeOSQuiet
        fi
    fi

    ./cleaner.sh -t cmake
fi

# Build Full
if [[ $OPT == "full" ]] 
    then
    ./cleaner.sh -t all

    if [[ $VERBOSE == 1 ]] 
    then
        if [[ $PULL == 1 ]] 
        then
            pullVerbose
        fi

        if [[ $TEST == 1 ]] 
        then
            makeTestFullVerbose
        else
            makeFullVerbose
        fi
    else
        if [[ $PULL == 1 ]] 
        then
            pullQuiet
        fi

        if [[ $TEST == 1 ]] 
        then
            makeTestFullQuiet
        else
            makeFullQuiet
        fi
    fi

    ./cleaner.sh -t cmake
fi

# Run the tests if its supposed to
if [[ $TEST == 1 ]] 
then
    ./UnitTests.app
fi

# Set Compiler Back
export CC=$CC
export CXX=$CXX

