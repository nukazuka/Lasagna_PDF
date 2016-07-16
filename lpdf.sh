#!/bin/bash

function usage()
{
    echo -e "Usage: `basename $0`  [OPTIONS] FILE1 FILE2 ..."
    echo -e "Options:"
    echo -e "  -a,    --all       : all pages will be processed"
    echo -e "  -e,    --end       : specify the end page"
    echo -e "  -h,    --help      : show this guide"
    echo -e "  -l,    --landscape : landscape mode"
    echo -e "  --nup, --matrix    : configuration of page, default is 1x1"
    echo -e "  -o,    --output    : A name of output file"
    echo -e "  -s,    --start     : specifiy the beginning page"
}

function GetNPDFPage()
{
    echo `python -c "import os;from CoreGraphics import *;print(CGPDFDocumentCreateWithProvider(CGDataProviderCreateWithFilename('$1')).getNumberOfPages())"`
}

# initialization
output="temp.pdf"
nup="1x1"

# arguments process
for OPT in "$@"
do
    case "$OPT" in
        '-h'|'--help' )
            usage
            exit 1
            ;;
        '-s' | '--start' )
            if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
                echo "$PROGNAME: option requires an argument -- $1" 1>&2
                exit 1
            fi
            start_page="$2"
            shift 2
            ;;
        '-e' | '--end' )
            if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
                echo "$PROGNAME: option requires an argument -- $1" 1>&2
                exit 1
            fi
            end_page="$2"
            shift 2
            ;;
        '--matrix' | '--nup' )
            if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
                echo "$PROGNAME: option requires an argument -- $1" 1>&2
                exit 1
            fi
            nup="$2"
            shift 2
	    ;;
        '--output' | '-o' )
            if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
                echo "$PROGNAME: option requires an argument -- $1" 1>&2
                exit 1
            fi
            output="$2"
            shift 2
            ;;
        '-a'|'--all' )
	    flag_all_page=1
            shift 1
            ;;
        '-l'|'--landscape' )
	    flag_landscape="--landscape"
            shift 1
            ;;
        '--'|'-' )
            shift 1
            param+=( "$@" )
            break
            ;;
        -*)
            echo "$PROGNAME: illegal option -- '$(echo $1 | sed 's/^-*//')'" 1>&2
            exit 1
            ;;
        *)
            if [[ ! -z "$1" ]] && [[ ! "$1" =~ ^-+ ]]; then
                param=( ${param[@]} "$1" )
                #param+=( "$1" )
                shift 1
            fi
            ;;
    esac
done

# if no file is specified, stop this script
if [ ${#param[@]} = 0 ]
then
    usage
    exit 1
fi

# check whether all files exist and have same number of page
page_num_prev=`GetNPDFPage ${param[0]}`
for file in ${param[@]}
do

    # if this file doesn't exist, stop the script
    if [ ! -e "${file}" ]
    then
	echo -e "${file} is not found"
	echo -e "Program is stopped"
	exit
    fi

    # if number of page are not same, show warning
    page_num=`GetNPDFPage ${file}`
    if [ "${page_num}" -ne "${page_num_prev}" ]
    then
	echo -e "==== WARNING ===="
	echo -e "Numbers of page are NOT same"
    fi
done

# if --start is not used, assign 1
if [ "${start_page}" = "" ]
then
    start_page=1
fi

# if --end is not used, assign $last_page
last_page=`GetNPDFPage ${param[0]}`
if [ "${end_page}" = "" ]
then
    end_page=${last_page}
fi

# if $end_page > $last_page, force to use $last_page
if [ "${end_page}" -gt "${last_page}" ]
then
    echo -e "--end ${end_page} is strange"
    echo -e "last page is ${last_page}"
    end_page=${last_page}
fi

# if $start_page > #end_page, stop the script
if [ "${start_page}" -gt "${end_page}" ]
then
    echo -e "--start : ${start_page}"
    echo -e "--end   : ${end_page}"
    echo -e "${start_page} > ${end_page}"
    echo -e "It's strange!!!"
    echo -e "Program is stopped"
    exit
fi

echo "---- configurations ---- "
echo "page: $start_page - $end_page"
echo "nup: $nup"

# make the statement to process page by page 
target=""
# loop over all pages to be processed
for num in `seq ${start_page} ${end_page}`
do

    # loop over all files
    for file in ${param[@]}
    do
	target+="${file} ${num} "
    done
done

pdfjam --nup ${nup} ${flag_landscape} --outfile ${output} $target


