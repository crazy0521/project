// File Handling System Calls  (create db, view, insert, delete, modify, search)

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int roll;
    char name[20];
    float marks;
};

#define FILENAME "student_db.dat"

void createDB() {
    int fd = open(FILENAME, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("Cannot create file");
        return;
    }

    int n;
    printf("Enter number of students: ");
    scanf("%d", &n);

    struct Student s;
    for (int i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %s %f", &s.roll, s.name, &s.marks);
        write(fd, &s, sizeof(s));
    }

    close(fd);
}

void viewDB() {
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) {
        perror("Cannot open file");
        return;
    }

    struct Student s;
    printf("\n%-5s %-20s %-5s\n", "Roll", "Name", "Marks");
    while (read(fd, &s, sizeof(s)) > 0) {
        printf("%-5d %-20s %-5.2f\n", s.roll, s.name, s.marks);
    }

    close(fd);
}

void insertRecord() {
    int fd = open(FILENAME, O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Cannot open file");
        return;
    }

    struct Student s;
    printf("Enter roll, name, marks: ");
    scanf("%d %s %f", &s.roll, s.name, &s.marks);
    write(fd, &s, sizeof(s));

    close(fd);
}

void deleteRecord() {
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) {
        perror("Cannot open file");
        return;
    }

    int tempfd = open("temp.dat", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (tempfd < 0) {
        perror("Cannot create temp file");
        close(fd);
        return;
    }

    int roll;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);

    struct Student s;
    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll != roll) {
            write(tempfd, &s, sizeof(s));
        }
    }

    close(fd);
    close(tempfd);

    remove(FILENAME);
    rename("temp.dat", FILENAME);
}

void modifyRecord() {
    int fd = open(FILENAME, O_RDWR);
    if (fd < 0) {
        perror("Cannot open file");
        return;
    }

    int roll;
    printf("Enter roll number to modify: ");
    scanf("%d", &roll);

    struct Student s;
    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll == roll) {
            printf("Enter new name and marks: ");
            scanf("%s %f", s.name, &s.marks);

            lseek(fd, -sizeof(s), SEEK_CUR);
            write(fd, &s, sizeof(s));
            printf("Record updated.\n");
            close(fd);
            return;
        }
    }

    printf("Record not found.\n");
    close(fd);
}

void searchResult() {
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0) {
        perror("Cannot open file");
        return;
    }

    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);

    struct Student s;
    while (read(fd, &s, sizeof(s)) > 0) {
        if (s.roll == roll) {
            printf("Name: %s, Marks: %.2f\n", s.name, s.marks);
            close(fd);
            return;
        }
    }

    printf("Student not found.\n");
    close(fd);
}

int main() {
    int choice;

    do {
        printf("\n--- Student Database Menu ---\n");
        printf("1. Create Database\n2. View Database\n3. Insert Record\n4. Delete Record\n5. Modify Record\n6. Student Result\n7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createDB(); break;
            case 2: viewDB(); break;
            case 3: insertRecord(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
            case 6: searchResult(); break;
            case 7: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 7);

    return 0;
}
