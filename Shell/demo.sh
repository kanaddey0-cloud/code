#!/bin/bash

# echo "Hello Kanad"

# a=10; b=20
# sum=$((a+b))
# echo "Sum = ${sum}"

# result=$((5 + 3))
# echo $result
# 	result=$((10 - 4)); echo $result
# 	result=$((6 * 7)); echo $result
# 	result=$((20 / 4)); echo $result
# 	remainder=$((17 % 5)) echo $result
# 	result=$((2**3))
#     echo $result

# x=10
# echo $x
# ((x+=5)); echo $x
# ((x-=3)); echo $x
# ((x*=2)); echo $x
# ((x/=4)); echo $x
# ((x%=7))
# echo $x

## Array

# arr=(1 2 3 4)
# echo ${arr[@]}

## Conditional Statement

# x=5
# if [ $x -gt 5 ]
# then
#     echo "Greater"
# elif [ $x -eq 5 ]; then
#     echo "Equal"
# else
#     echo "Smaller"
# fi

# x=10
# if [[ $x -gt 5 ]]; then
#     echo "Greater"
# fi

# name="Kanad"
# if [ $name = "Kanad" ]; then
#     echo "Match"
# fi

# if ls; then
#     echo "Command Success"
# fi

# x=10
# if [ $x > 5 ]; then
#     echo "Meow"
# fi
# y=5; z=1
# if [ $(( x > y  == z )) ]; then
#     echo "Equal"
# fi

## Loopping Statement

# for i in 0 1 2 3; do
#     echo $i
# done

# arr=(10 20 30)
# echo ${arr[@]}
# for x in ${arr[@]}; do
#     echo $x
# done

# for ((i=4; i>0; i--)); do
#     echo $i
# done

# for i in {0..10..2}; do
#     echo $i
# done

# n=8
# seq 1 8
# seq 1 $n
# echo {1..$n}
# echo {1..8}

# arr=(10 20 30)
# for ((i=0; i<${#arr[@]}; i++)); do
#     echo "${arr[i]}"
# done

# for word in Hello How Are You; do
#     echo $word
# done

for file in $(ls); do
    echo $file
done

# for i in $(seq 1 5); do
#     echo $i
# done

