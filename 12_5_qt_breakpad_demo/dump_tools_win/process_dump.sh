#!/bin/bash

if [ $# != 2 ] ; then 
echo "USAGE: $0 EXE_NAME DMP_NAME" 
echo " e.g.: $0 test 3872B2CF-983B-4963-AFA9-C8534DFD4C44.dmp" 
exit 1; 
fi 

#get input param
exe_file_name=$1
dmp_file_name=$2

getSymbol() {
    echo "@getSymbol: start get symbol"
    input_file_name=$exe_file_name 
    pdb_file_name=${input_file_name%.*}
    ./dump\_syms ./$exe_file_name > $pdb_file_name'.sym'
}

getStackTrace() {
    echo "@getStackTrace: start get StackTrace"

    input_file_name=$exe_file_name 
    pdb_file_name=${input_file_name%.*}

    sym_file_name=$pdb_file_name'.sym'

    #get first line of $sym_file_name
    line1=`head -n1 $sym_file_name`
    #echo $line1

    #get version number form string of first line
    OIFS=$IFS; IFS=" "; set -- $line1; aa=$1;bb=$2;cc=$3;dd=$4; IFS=$OIFS 
    #echo $dd
    version_number=$dd

    #make standard dir and move *.sym in it
    mkdir -p ./symbols/$exe_file_name/$version_number
    mv $sym_file_name ./symbols/$exe_file_name/$version_number

    #print stack trace at std output
    ./minidump_stackwalk $dmp_file_name ./symbols 2> /dev/null 

    #print stack trace at a file
    #./minidump_stackwalk $dmp_file_name ./symbols 2>/dev/null >result.txt
}

main() {
    getSymbol 
    if [ $? == 0 ] 
    then 
        getStackTrace
    fi
}
# run main
main
