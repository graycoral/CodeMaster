#!/bin/sh
clear
VERBOSE=""
CONFIG="config.json"
OUTFILE="result.json"
TESTMODE="-m single"

# --------------------------------------------------------------------------
# Command line usag
#

usage() {
    local MSG=$1
    echo >&2
    if [ "$MSG" != "" ]
    then
        echo "ERROR: $MSG" >&2
    fi
    cat >&2 << UsageEnd
Usage:
    ---------------------------------------------------------------------------------------------------
    [options]
    LARA COM Test Suites arguments

    -h, --help            Print this help and exit.
    -o, --out             save outfile name for COM Test Result.
    -c                    configuration file for COM Test Manger.
    -a, --all             Execute All Test case

    Ex) source ComTestRun.sh -c config.json -o result.json
    ----------------------------------------------------------------------------------------------------

UsageEnd
    if [ "$HELP" = "true" ]
    then
        return 0
    fi
    echo "Please check Test Configuration"
    return 0
}

# ---------------------------------------------------------------------------
# Parsing of command line arguments

parseArguments() {
    SHORTOPTS=":hG:j:t:acsovm"

    echo "parsing arguments: $@"
    echo "---------------------------------------------------------------------------"
    #if the script failed, force Execute this Line
    #set +e

    ARGS=$(getopt $SHORTOPTS "$@" )
    #Check script SUCCESS or FAIL and then return 0 or 1
    GETOPT_EXIT=$?

    # Option parsing error?
    if [ $GETOPT_EXIT -ne 0 ]
    then
        usage
        return 0
    fi

    # Set as positional parameters
    eval set -- "$ARGS"
    # echo "parseArguments loop"
    while true
    do
        case $1 in
            -v)
                VERBOSE="-v"
                echo "Using VERBOSE $VERBOSE"
                ;;
            -c)
                shift
                CONFIG="$1"
                echo "Using CONFIG PATH $CONFIG"
                ;;
            -o|--out)
                shift
                OUTFILE="-o $1"
                echo "Save File Path for Test Result is $OUTFILE"
                ;;
            -s|--singtest)
                shift
                TESTMODE="-m single"
                echo "Single Test Mode"
                ;;
            -a|--all)
                shift
                TESTMODE="-m all"
                echo "Execute All Test cases"
                ;;
            -h|--help)
                HELP="true"
                echo "Using HELP configuration"
                usage
                ;;
            --)
                shift
                break
                ;;
            *)
                shift
                break
                ;;
        esac
        shift
    done
}

parseArguments $@
/usr/local/bin/python3.5 main.py $TESTMODE
