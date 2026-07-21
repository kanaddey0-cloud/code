#!/bin/bash

echo "Hello Kanad"

a=10; b=20
sum=$((a+b))
echo "Sum = ${sum}"

result=$((5 + 3));     echo $result
result=$((10 - 4));    echo $result
result=$((6 * 7));     echo $result
result=$((20 / 4));    echo $result
remainder=$((17 % 5)); echo $result
result=$((2**3));      echo $result

printf "\n"
echo ----
x=10
echo $x
((x+=5)); echo $x
((x-=3)); echo $x
((x*=2)); echo $x
((x/=4)); echo $x
((x%=7))
echo $x


printf "\n----\n" ## Array

arr=(1 2 3 4)
echo ${arr[@]}
echo ${arr[0]}


printf "\n----\n" ## Conditional Statement

x=5
if [ $x -gt 5 ]
then
    echo "Greater"
elif [ $x -eq 5 ]; then
    echo "Equal"
else
    echo "Smaller"
fi

name="Kanad"
if [ $name = "Kanad" ]; then
    echo "Match"
fi

echo
if ls; then
    echo "Command Success"
fi

y=5; z=1
if (( x > y  == z )); then   # if [ $(( x > y  == z )) ]; then
    echo "Equal"
fi

printf "\n----\n" ## Loopping Statement

for i in 0 1 2 3; do
    echo $i
done

echo
arr=(10 20 30)
for x in ${arr[@]}; do
    echo $x
done

echo
for ((i=4; i>0; i--)); do
    echo $i
done

echo
for i in {0..10..2}; do
    echo $i
done


printf "\n----\n" 
n=8
seq 1 3; echo
seq 1 $n; echo
seq 2 2 8
echo $(seq 0 4 8)
echo {1..$n}
echo {1..7}


printf "\n----\n"
arr=(10 20 30)
for ((i=0; i<${#arr[@]}; i++)); do
    echo "${arr[i]}"
done

for word in Hello How Are You; do
    echo $word
done

printf "\n----\n"
for file in $(ls); do
    echo $file
done
echo
for i in $(seq 1 5); do
    echo $i
done


printf "\n---- ---\n" # Funtion

test() {
    x=10          # No print
    local y=20    # No print

    # $((x+1))      # No print

    echo x        # Print text x
    echo $x       # Print value of x
    echo $y       # Print value of y

    echo $((x+y)) # Print calculation result
}
rult=$(test) # Capture all output produced by test()
echo $rult   # Print the captured output in one line
echo "global x = $x  y = $y"
echo
test # if we don't capture function output then is wrok normally


printf "\n---- ---\n"
test() {
    local s=10
    echo $s
}
test
echo "Local s = $s" # s is the function local variable

printf "\n---- ---\n"
square() {
    echo $(($1 * $1))
}
square 5
result=$(square 5)
echo Square of 5 is $result

printf "\n---- ---\n"
check() {
    if ((0 == 0)); then
        return 7
    fi
    return 4
}
check
echo $?  # $? stores the exit status (return value) of the last command executed.


printf "\n---- ---- -\n" # bash demo.sh A B C
echo $0 $1 $2 $3
    # $0  Script name (demo.sh)
    # $1  First command-line argument (A)
    # $2  Second command-line argument (B)
    # $3  Third command-line argument (C)
    
echo $#   # Total number of command-line arguments (3)
echo $@   # All command-line arguments: A B C
echo $$   # Process ID (PID) of the current shell running the script
