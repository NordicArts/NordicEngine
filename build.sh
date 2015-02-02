#!/bin/bash
oldCC=$CC
oldCXX=$CXX

# Set the compiler to clang
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

usage()
{
cat << EOF
This script can build, clean, and grab new versions,

usage: $0 options

OPTIONS:
    -h  Show this message
    -v  Verbose
    -p  Pull, pulls the latest code and all its gitmodules
    -t  Test Build, once built run the unit tests
    -o  Option, can be 'build', 'full' or 'os' [default: build]
    -g  Generate build files, can be 'osx', 'windows' or 'linux' [default: linux]
    -n  No Clean
EOF
}

# Make the build
makeIt()
{
    beLoud=$1

    if [[ $beLoud == 1 ]]; then
        echo "Make Verbose"

        make
    else
        echo "Make Quiet"

        make >> /dev/null
    fi
}

# Pull the latest stuff
pullCode()
{
    beLoud=$1

    if [[ $beLoud == 1 ]]; then
        echo "Pull Verbose"

        git submodule init
        git submodule update --recursive
        git submodule foreach git pull origin master --recurse-submodules
    else
        echo "Pull Quiet"

        git submodule init >> /dev/null
        git submodule update --recursive >> /dev/null
        git submodule foreach git pull origin master --recurse-submodules >> /dev/null
    fi
}

# Full Engine
fullEngine()
{
    beLoud=$1
    testIt=$2
    doGenerate=$3

    endEcho="Full Engine"
    endResult="cmake -C CMakeConfigs/"

    # Test Build
    if [[ $testIt == 1 ]]; then
        endEcho+=", Test"
        endResult+="TestFull.txt"
    else
        endEcho+=", Non-Test"
        endResult+="Full.txt"
    fi

    # Generate IDE builds or Make
    if [[ $doGenerate == "osx" ]]; then
        endEcho+=", XCode Build"
        endResult+=" -G Xcode ."
    elif [[ $doGenerate == "windows" ]]; then
        endEcho+=", Ninja Build"
        endResult+=" -G Ninja ."
    else
        endEcho+=", MakeFiles Build"
        endResult+=" ."
    fi

    # Verbose
    if [[ $beLoud == 1 ]]; then
        endEcho+=", Verbose"
    else
        endEcho+=", Quiet"
        endResult+=" >> /dev/null"
    fi

    echo $endEcho
    eval $endResult
}

# OS Only
osOnly()
{
    beLoud=$1
    testIt=$2
    doGenerate=$3

    endEcho="OS Only"
    endResult="cmake -C CMakeConfigs/"

    # Test Build
    if [[ $testIt == 1 ]]; then
        endEcho+=", Test"
        endResult+="TestOS.txt"
    else
        endEcho+=", Non-Test"
        endResult+="OSOnly.txt"
    fi

    # Generate IDE builds or Make
    if [[ $doGenerate == "osx" ]]; then
        endEcho+=", XCode Build"
        endResult+=" -G Xcode ."
    elif [[ $doGenerate == "windows" ]]; then
        endEcho+=", Ninja Build"
        endResult+=" -G Ninja ."
    else
        endEcho+=", MakeFiles Build"
        endResult+=" ."
    fi

    # Verbose
    if [[ $beLoud == 1 ]]; then
        endEcho+=", Verbose"
    else
        endEcho+=", Quiet"
        endResult+=" >> /dev/null"
    fi

    echo $endEcho
    eval $endResult
}

# Build
builder()
{

    beLoud=$1
    testIt=$2

    endEcho="ReBuild"
    endResult=""

    # Testing
    if [[ $testIt == 1 ]]; then
        endEcho+=", Test"
        endResult+="cmake -C CMakeConfigs/Test.txt ."
    else
        endEcho+=", Non-Test"
        endResult+="cmake ."
    fi

    # Verbose
    if [[ $beLoud == 1 ]]; then
        endEcho+=", Verbose"
    else
        endEcho+=", Quiet"
        endResult+=" >> /dev/null"
    fi

    echo $endEcho
    eval $endResult

    makeIt $beLoud
}

# Build Number
buildNumber()
{    
    buildName=$1
    beLoud=$2

    # Text file
    if [[ $beLoud == 1 ]]; then
        echo "awk -F, '{$1=$1+1}1' OFS= buildNumber.txt > buildNumberNew.txt && mv buildNumberNew.txt buildNumber.txt"
    fi

    awk -F, '{$1=$1+1}1' OFS= buildNumber.txt > buildNumberNew.txt && mv buildNumberNew.txt buildNumber.txt    

    # Get the result
    buildNumber=$(cat buildNumber.txt)

    # Build the header
    l1="#ifndef NORDICARTS_"
    l1+=$buildName
    l1+="_BUILDNUMBER"

    l2="#define NORDICARTS_"  
    l2+=$buildName
    l2+="_BUILDNUMBER "
    l2+=$buildNumber

    l3="#endif"

    echo -e $l1 > $buildName/buildNumber.hpp
    echo -e $l2 >> $buildName/buildNumber.hpp
    echo -e $l3 >> $buildName/buildNumber.hpp

    if [[ $beLoud == 1 ]]; then
        echo $l2
    fi
}

# Variables
OPT='build'
GENERATE='linux'
VERBOSE=false
TEST=false
PULL=false
MAKER=false
CLEAN=1

# Go through the options
while getopts ":o:g:?phnvt" OPTION; do
    case $OPTION in
        o)
            OPT=$OPTARG
            ;;
        g)
            GENERATE=$OPTARG
            ;;
        t)
            TEST=1
            ;;
        p)
            PULL=1
            ;;
        n)
            CLEAN=false
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

# Pull
if [[ $PULL == 1 ]]; then
    pullCode $VERBOSE
fi

# Build Standard
if [[ $OPT == "build" ]]; then
    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t build
    fi

    buildNumber "NORDICENGINE" $VERBOSE
    builder $VERBOSE $TEST

    if [[ $CLEAN == true ]]; then
        ./cleaner.sh -t cmake
    fi
fi

# Build OS
if [[ $OPT == "os" ]]; then
    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t all
    fi

    buildNumber "NORDICENGINE" $VERBOSE
    osOnly $VERBOSE $TEST $GENERATE

    if [[ $GENERATE == "linux" ]]; then
        makeIt $VERBOSE
    fi

    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t cmake
    fi
fi

# Build Full
if [[ $OPT == "full" ]]; then
    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t all
    fi

    buildNumber "NORDICENGINE" $VERBOSE
    fullEngine $VERBOSE $TEST $GENERATE

    if [[ $GENERATE == "linux" ]]; then
        makeIt $VERBOSE
    fi

    if [[ $CLEAN == 1 ]]; then
        ./cleaner.sh -t cmake
    fi
fi

# Run the tests if its supposed to
if [[ $TEST == 1 ]]; then
    ./UnitTests.app
fi

# Set Compiler Back
export CC=$CC
export CXX=$CXX
