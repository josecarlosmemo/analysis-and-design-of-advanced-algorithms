#!/usr/bin/env bash

test_cases=(10 50 100 150 300 1000 5000 10000 20000 50000)

# Generating test cases
g++ -std=c++17 -o generate_numbers generate_numbers.cpp

for i in "${test_cases[@]}"; do
    ./generate_numbers $i >./test_cases/$i.txt
done

# Running the program
g++ -std=c++17 -o main main.cpp

for i in "${test_cases[@]}"; do
    ./main ./test_cases/$i.txt | tail -n 1 | sed 's/[^0-9]*//g' >>results.txt
done

# Cleaning up
rm generate_numbers
rm main
