#student, calculations and string operations 

1 - Student Database 

#!/bin/bash

DB_FILE="student_db.txt"

# Function to create database (just clears or creates the file)
create_database() {
    > "$DB_FILE"
    echo "Database created (or cleared)."
}

# Function to view database
view_database() {
    if [[ -s "$DB_FILE" ]]; then
        echo -e "\n----- Student Database -----"
        column -t -s "," "$DB_FILE"
    else
        echo "Database is empty."
    fi
}

# Function to insert a record
insert_record() {
    echo "Enter Roll Number:"
    read roll
    echo "Enter Name:"
    read name
    echo "Enter Marks (out of 100):"
    read marks
    echo "$roll,$name,$marks" >> "$DB_FILE"
    echo "Record inserted."
}

# Function to delete a record
delete_record() {
    echo "Enter Roll Number to delete:"
    read roll
    grep -v "^$roll," "$DB_FILE" > temp && mv temp "$DB_FILE"
    echo "Record deleted (if it existed)."
}

# Function to modify a record
modify_record() {
    echo "Enter Roll Number to modify:"
    read roll
    grep -v "^$roll," "$DB_FILE" > temp && mv temp "$DB_FILE"
    echo "Enter new Name:"
    read name
    echo "Enter new Marks (out of 100):"
    read marks
    echo "$roll,$name,$marks" >> "$DB_FILE"
    echo "Record modified."
}

# Function to display result of a particular student
student_result() {
    echo "Enter Roll Number:"
    read roll
    record=$(grep "^$roll," "$DB_FILE")
    if [[ -n "$record" ]]; then
        IFS=',' read -r r name marks <<< "$record"
        echo "Roll Number: $r"
        echo "Name: $name"
        echo "Marks: $marks"
        if (( marks >= 40 )); then
            echo "Result: PASS"
        else
            echo "Result: FAIL"
        fi
    else
        echo "No record found for Roll Number $roll."
    fi
}

# Main menu loop
while true; do
    echo -e "\n---- Student Database Menu ----"
    echo "a) Create Database"
    echo "b) View Database"
    echo "c) Insert a Record"
    echo "d) Delete a Record"
    echo "e) Modify a Record"
    echo "f) Result of a Particular Student"
    echo "g) Exit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        a) create_database ;;
        b) view_database ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) student_result ;;
        g) echo "Exiting..."; break ;;
        *) echo "Invalid option. Try again." ;;
    esac
done








#!/bin/bash
# calculations

factorial() {
    echo -n "Enter a number: "
    read n
    fact=1
    for (( i=1; i<=n; i++ )); do
        fact=$((fact * i))
    done
    echo "Factorial of $n is $fact"
}

greatest_of_three() {
    echo "Enter three numbers:"
    read a b c
    if (( a >= b && a >= c )); then
        echo "$a is greatest"
    elif (( b >= c )); then
        echo "$b is greatest"
    else
        echo "$c is greatest"
    fi
}

is_prime() {
    echo -n "Enter a number: "
    read n
    if (( n <= 1 )); then
        echo "$n is not a prime number"
        return
    fi
    for (( i=2; i*i<=n; i++ )); do
        if (( n % i == 0 )); then
            echo "$n is not a prime number"
            return
        fi
    done
    echo "$n is a prime number"
}

number_palindrome() {
    echo -n "Enter a number: "
    read num
    rev=$(echo $num | rev)
    if [[ "$num" == "$rev" ]]; then
        echo "$num is a palindrome"
    else
        echo "$num is not a palindrome"
    fi
}

string_palindrome() {
    echo -n "Enter a string: "
    read str
    rev=$(echo "$str" | rev)
    if [[ "$str" == "$rev" ]]; then
        echo "\"$str\" is a palindrome"
    else
        echo "\"$str\" is not a palindrome"
    fi
}

while true; do
    echo -e "\n---- MENU ----"
    echo "a) Find factorial of a number"
    echo "b) Find greatest of three numbers"
    echo "c) Check prime number"
    echo "d) Check if a number is a palindrome"
    echo "e) Check if a string is a palindrome"
    echo "f) Exit"
    echo -n "Enter your choice: "
    read choice

    case $choice in
        a) factorial ;;
        b) greatest_of_three ;;
        c) is_prime ;;
        d) number_palindrome ;;
        e) string_palindrome ;;
        f) echo "Exiting..."; break ;;
        *) echo "Invalid option" ;;
    esac
done









# string operations
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
