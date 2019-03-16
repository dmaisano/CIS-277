#!/bin/bash

if [ -z $1 ]; then
  echo "missing arg"
  exit
fi

declare -a randomNumbers
declare -a sortedNumbers

for ((i = 1; i <= $1; i++)); do
  randomNumbers[$i]=$RANDOM
done

echo "Random Numbers"
for i in "${!randomNumbers[@]}"; do
  printf "${randomNumbers[$i]} "
  sortedNumbers["${randomNumbers[$i]}"]="${randomNumbers[$i]}" # the value serves as the index
done

echo "Sorted Numbers"
for i in "${!sortedNumbers[@]}"; do
  printf "${sortedNumbers[$i]} "
done

printf "\n"
