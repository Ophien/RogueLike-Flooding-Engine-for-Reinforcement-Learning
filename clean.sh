#!/bin/bash
echo cleaning environment...

library_files="./build/*.a"
binary_files="./build/*.out"
obj_files="./obj/*.o"

count=`ls -1 $library_files 2>/dev/null | wc -l`
if [ $count != 0 ]
then
    echo cleaning .a files
	rm $library_files
fi

count=`ls -1 $binary_files 2>/dev/null | wc -l`
if [ $count != 0 ]
then
    echo cleaning .out files
	rm $binary_files
fi

count=`ls -1 $obj_files 2>/dev/null | wc -l`
if [ $count != 0 ]
then
    echo cleaning .o files
	rm $obj_files
fi

echo environment cleared!