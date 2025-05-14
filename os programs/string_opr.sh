# 1) WAP to Implement String Operations
#!/bin/bash

echo "---- String Operations ----"
echo "Enter first string:"
read str1
echo "Enter second string:"
read str2

echo "Choose an operation:"
echo "1) Length of strings"
echo "2) Concatenate strings"
echo "3) Compare strings"
echo "4) Reverse strings"
read -p "Enter choice (1-4): " choice

case $choice in
  1)
    echo "Length of '$str1': ${#str1}"
    echo "Length of '$str2': ${#str2}"
    ;;
  2)
    concat="$str1$str2"
    echo "Concatenated string: $concat"
    ;;
  3)
    if [ "$str1" = "$str2" ]; then
      echo "Strings are equal"
    else
      echo "Strings are not equal"
    fi
    ;;
  4)
    rev1=$(echo "$str1" | rev)
    rev2=$(echo "$str2" | rev)
    echo "Reversed '$str1': $rev1"
    echo "Reversed '$str2': $rev2"
    ;;
  *)
    echo "Invalid choice"
    ;;
Esac

# 2) WAP for Sorting Numbers
#!/bin/bash

echo "Enter numbers separated by space:"
read -a numbers

echo "Sorted numbers:"
for num in "${numbers[@]}"
do
    echo $num
done | sort -n
