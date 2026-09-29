#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.txt"

struct Student {
    int roll;
    char name[50];
    int age;
    char course[50];
};

/* Function declarations */
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("       STUDENT DATABASE SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                viewStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you! Program closed.\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}


/* ================= ADD STUDENT ================= */

void addStudent() {
    struct Student s;
    FILE *file;

    file = fopen(FILE_NAME, "a");

    if (file == NULL) {
        printf("\nError: File open nahi hui!\n");
        return;
    }

    printf("\n---------- ADD STUDENT ----------\n");

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    fprintf(file, "%d|%s|%d|%s\n",
            s.roll,
            s.name,
            s.age,
            s.course);

    fclose(file);

    printf("\nStudent added successfully!\n");
}


/* ================= VIEW STUDENTS ================= */

void viewStudents() {
    struct Student s;
    FILE *file;
    char line[200];

    file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo student data found!\n");
        return;
    }

    printf("\n================ STUDENT LIST ================\n");

    printf("%-10s %-20s %-10s %-20s\n",
           "Roll", "Name", "Age", "Course");

    printf("------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {

        if (sscanf(line, "%d|%49[^|]|%d|%49[^\n]",
                   &s.roll,
                   s.name,
                   &s.age,
                   s.course) == 4) {

            printf("%-10d %-20s %-10d %-20s\n",
                   s.roll,
                   s.name,
                   s.age,
                   s.course);
        }
    }

    printf("============================================================\n");

    fclose(file);
}


/* ================= SEARCH STUDENT ================= */

void searchStudent() {
    struct Student s;
    FILE *file;
    char line[200];
    int roll;
    int found = 0;

    file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo student data found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), file)) {

        if (sscanf(line, "%d|%49[^|]|%d|%49[^\n]",
                   &s.roll,
                   s.name,
                   &s.age,
                   s.course) == 4) {

            if (s.roll == roll) {

                printf("\n---------- STUDENT FOUND ----------\n");
                printf("Roll Number : %d\n", s.roll);
                printf("Name        : %s\n", s.name);
                printf("Age         : %d\n", s.age);
                printf("Course      : %s\n", s.course);

                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("\nStudent not found!\n");
    }

    fclose(file);
}


/* ================= UPDATE STUDENT ================= */

void updateStudent() {
    struct Student s;
    FILE *file;
    FILE *temp;

    char line[200];
    int roll;
    int found = 0;

    file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo student data found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), file)) {

        if (sscanf(line, "%d|%49[^|]|%d|%49[^\n]",
                   &s.roll,
                   s.name,
                   &s.age,
                   s.course) == 4) {

            if (s.roll == roll) {

                printf("\nStudent found!\n");

                printf("Enter New Name: ");
                scanf(" %[^\n]", s.name);

                printf("Enter New Age: ");
                scanf("%d", &s.age);

                printf("Enter New Course: ");
                scanf(" %[^\n]", s.course);

                found = 1;
            }

            fprintf(temp, "%d|%s|%d|%s\n",
                    s.roll,
                    s.name,
                    s.age,
                    s.course);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("\nStudent updated successfully!\n");
    } else {
        printf("\nStudent not found!\n");
    }
}


/* ================= DELETE STUDENT ================= */

void deleteStudent() {
    struct Student s;
    FILE *file;
    FILE *temp;

    char line[200];
    int roll;
    int found = 0;

    file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        printf("\nNo student data found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL) {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fgets(line, sizeof(line), file)) {

        if (sscanf(line, "%d|%49[^|]|%d|%49[^\n]",
                   &s.roll,
                   s.name,
                   &s.age,
                   s.course) == 4) {

            if (s.roll == roll) {
                found = 1;
                continue;
            }

            fprintf(temp, "%d|%s|%d|%s\n",
                    s.roll,
                    s.name,
                    s.age,
                    s.course);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("\nStudent deleted successfully!\n");
    } else {
        printf("\nStudent not found!\n");
    }
}