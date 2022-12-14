#!/bin/bash
g++ -std=c++11 -I../include ../src/kl.cpp -o kl.o
g++ kl.o kl_unittest.cpp -std=c++11 -I../google_test/include -I../include -L../google_test/lib -lgtest -o kl_unittest
if [[ $? -eq 0 ]];then
    ./test/kl_unittest
fi
