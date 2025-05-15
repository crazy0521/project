DB="student_db.txt"

while true
do
    echo "-------- Student Database Menu --------"
    echo "a) Create Database"
    echo "b) View Database"
    echo "c) Insert a Record"
    echo "d) Delete a Record"
    echo "e) Modify a Record"
    echo "f) Result of a Particular Student"
    echo "g) Exit"
    read -p "Enter your choice: " choice

    case $choice in
        a)
            > $DB
            echo "Database created."
            ;;
        b)
            if [ -s $DB ]; then
                column -t -s "," $DB
            else
                echo "Database is empty."
            fi
            ;;
        c)
            read -p "Enter Roll No: " roll
            read -p "Enter Name: " name
            read -p "Enter Marks: " marks
            echo "$roll,$name,$marks" >> $DB
            echo "Record inserted."
            ;;
        d)
            read -p "Enter Roll No to delete: " roll
            grep -v "^$roll," $DB > temp && mv temp $DB
            echo "Record deleted if existed."
            ;;
        e)
            read -p "Enter Roll No to modify: " roll
            grep -v "^$roll," $DB > temp && mv temp $DB
            read -p "Enter New Name: " name
            read -p "Enter New Marks: " marks
            echo "$roll,$name,$marks" >> $DB
            echo "Record modified."
            ;;
        f)
            read -p "Enter Roll No: " roll
            grep "^$roll," $DB
            ;;
        g)
            echo "Exiting..."
            break
            ;;
        *)
            echo "Invalid option!"
            ;;
    esac
done



using functions
