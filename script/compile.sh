#!/bin/bash

pushd $(dirname $0) > /dev/null
SDIR=$(pwd)
popd > /dev/null
LLC=llc
OPT=opt
CC=gcc
CFLAGS=-std=gnu99
UUC=$SDIR/src/cc1/cc1
a=''
files=()

clean()
{
    rm  ${files[@]} -f
    rm $a $a.* -f
}

clean_die()
{
    clean
    exit 1
}

if [ $# -ge 1 ]; then
    for i in $@; do
	a=$(mktemp)
	echo "compiling $i"  
	# compile avec notre compilateur
	cpp -C -P $i > $a.1 || clean_die
	${UUC} < $a.1 > $a.2 || clean_die
	${OPT} -std-compile-opts -mem2reg $a.2 > $a.3 || clean_die
	${LLC} > $a.S < $a.3 || clean_die
	rm $a -f
	files+=($a.S)
    done
    if [[ ${#files} != "0" ]]; then
	echo "assemble and link ..."
	${CC} -o a.out ${files[@]} 
    	# assemble et link les .S
	clean
    else
	echo "nothing to be compiled :'("
	exit 1
    fi
    exit 0
    
else
    echo "no input files"
    exit 1
fi
