#!/bin/bash

#Usage: ./checker.sh <sorted|reverse|random> <numOfNodes> <filename> <AVL|BST> <perComparisonCost> <perParentChildUpdateCost>
#e.g:   ./checker.sh random 100 exp1 AVL 1 100

if [ "$#" != "6" ]; then
    echo "Incorrect number of arguments provided."
    echo "Usage: ./checker.sh <sorted|reverse|random> <numOfNodes> <filename> <AVL|BST> <perComparisonCost> <perParentChildUpdateCost>"
    exit 0
fi

g++ -g main.cpp -o AVLBSTTest

if [ $? != 0 ]; then
    echo "Compilation failed"
    exit 0
fi

if [ "$(python3 --version)" != "" ]; then
    python3 generateInput.py $1 $2 "$3.in" $4 $5 $6
    ./AVLBSTTest < "$3.in" > "$3.log"
    mv "$4.out" "$3.out"
    python3 plot.py "$3.out" "$3.png"
elif [ "$(python --version)" != "" ]; then
    python generateInput.py $1 $2 "$3.in" $4 $5 $6
    ./AVLBSTTest < "$3.in" > "$3.log"
    cp "$4.out" "$3.out"
    python plot.py "$3.out" "$3.png"
else
    echo "python not installed"
    exit 0
fi
