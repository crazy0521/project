#!/bin/bash

while true
do
    echo "----- Menu -----"
    echo "a) Factorial"
    echo "b) Greatest of 3 numbers"
    echo "c) Prime Check"
    echo "d) Number Palindrome"
    echo "e) String Palindrome"
    echo "f) Exit"
    read -p "Choose an option: " opt

    case $opt in
        a)
            read -p "Enter number: " n
            fact=1
            for (( i=2; i<=n; i++ )); do
                fact=$((fact * i))
            done
            echo "Factorial: $fact"
            ;;
        b)
            read -p "Enter 3 numbers: " a b c
            if (( a > b && a > c )); then
                echo "$a is greatest"
            elif (( b > c )); then
                echo "$b is greatest"
            else
                echo "$c is greatest"
            fi
            ;;
        c)
            read -p "Enter number: " num
            prime=1
            for (( i=2; i<=num/2; i++ )); do
                if (( num % i == 0 )); then
                    prime=0
                    break
                fi
            done
            (( prime == 1 && num > 1 )) && echo "Prime" || echo "Not Prime"
            ;;
        d)
            read -p "Enter number: " num
            rev=$(echo $num | rev)
            [[ $rev == $num ]] && echo "Palindrome" || echo "Not Palindrome"
            ;;
        e)
            read -p "Enter string: " str
            rev=$(echo $str | rev)
            [[ $rev == $str ]] && echo "Palindrome" || echo "Not Palindrome"
            ;;
        f)
            echo "Exit"
            break
            ;;
        *)
            echo "Invalid choice!"
            ;;
    esac
done




# a. Biggest of Three Numbers
#!/bin/bash
a=$1
b=$2
c=$3

if (( a > b && a > c )); then
    echo "$a is biggest"
elif (( b > c )); then
    echo "$b is biggest"
else
    echo "$c is biggest"
fi
# To run : bash bigger.sh 12 43 35





# b. Reverse a Number
#!/bin/bash
num=$1
rev=$(echo $num | rev)
echo "Reversed Number: $rev"
# To run : bash reverse.sh 123456





# c. Print Word N Times
#!/bin/bash
n=$1
word=$2

for (( i=1; i<=n; i++ )); do
    echo "$word"
done
# to run: bash print.sh 5 muskan 





# d. Sum of Digits of a 4-digit Number
#!/bin/bash
num=$1
sum=0
while [ $num -gt 0 ]; do
    digit=$((num % 10))
    sum=$((sum + digit))
    num=$((num / 10))
done
echo "Sum of digits: $sum"
# to run:  bash sum.sh 1234
