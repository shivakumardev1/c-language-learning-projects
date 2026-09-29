#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int rollNo;
    char name[50];
    char course[50];
    int totalClasses;
    int presentClasses;
};

/* Function declarations */
void addStudent();
void displayStudents();
void searchStudent();
void markAttendance();
void attendanceReport();
void updateStudent();
void deleteStudent();

int studentExists(int rollNo);

/* Main Menu */
int main() {
    int choice;

    while (1) {
        printf("\n========================================\n");
        printf("      COLLEGE ATTENDANCE SYSTEM\n");
        printf("========================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Mark Attendance\n");
        printf("5. Attendance Report\n");
        printf("6. Update Student\n");
        printf("7. Delete Student\n");
        printf("8. Exit\n");
        printf("========================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                markAttendance();
                break;

            case 5:
                attendanceReport();
                break;

            case 6:
                updateStudent();
                break;

            case 7:
                deleteStudent();
                break;

            case 8:
                printf("\nThank you for using the system!\n");
                exit(0);

            default:
                printf("\nInvalid choice!\n");
        }
    }

    return 0;
}

/* Check whether roll number already exists */
int studentExists(int rollNo) {

    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL)
        return 0;

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.rollNo == rollNo) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* Add Student */
void addStudent() {

    FILE *fp;
    struct Student s;

    printf("\n========== ADD STUDENT ==========\n");

    printf("Enter Roll Number: ");
    scanf("%d", &s.rollNo);

    if (studentExists(s.rollNo)) {
        printf("\nStudent with this Roll Number already exists!\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);

    s.totalClasses = 0;
    s.presentClasses = 0;

    fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

/* Display all students */
void displayStudents() {

    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n================ ALL STUDENTS ================\n");

    printf("%-10s %-25s %-20s\n",
           "Roll No", "Name", "Course");

    printf("-----------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {

        printf("%-10d %-25s %-20s\n",
               s.rollNo,
               s.name,
               s.course);
    }

    fclose(fp);
}

/* Search student */
void searchStudent() {

    FILE *fp;
    struct Student s;
    int rollNo;
    int found = 0;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &rollNo);

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.rollNo == rollNo) {

            float percentage = 0;

            if (s.totalClasses > 0) {
                percentage =
                    ((float)s.presentClasses /
                     s.totalClasses) * 100;
            }

            printf("\n========== STUDENT DETAILS ==========\n");
            printf("Roll Number     : %d\n", s.rollNo);
            printf("Name            : %s\n", s.name);
            printf("Course          : %s\n", s.course);
            printf("Total Classes   : %d\n", s.totalClasses);
            printf("Present         : %d\n", s.presentClasses);
            printf("Absent          : %d\n",
                   s.totalClasses - s.presentClasses);
            printf("Attendance      : %.2f%%\n", percentage);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent not found!\n");
    }
}

/* Mark Attendance */
void markAttendance() {

    FILE *fp;
    struct Student s;
    int rollNo;
    char status;
    int found = 0;

    printf("\n========== MARK ATTENDANCE ==========\n");

    printf("Enter Roll Number: ");
    scanf("%d", &rollNo);

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo student records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.rollNo == rollNo) {

            printf("Student Name: %s\n", s.name);

            printf("Present or Absent? (P/A): ");
            scanf(" %c", &status);

            s.totalClasses++;

            if (status == 'P' || status == 'p') {
                s.presentClasses++;
                printf("\nAttendance marked PRESENT.\n");
            }
            else if (status == 'A' || status == 'a') {
                printf("\nAttendance marked ABSENT.\n");
            }
            else {
                s.totalClasses--;
                printf("\nInvalid attendance status!\n");
                fclose(fp);
                return;
            }

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent not found!\n");
    }
}

/* Attendance Report */
void attendanceReport() {

    FILE *fp;
    struct Student s;
    float percentage;

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo attendance records found!\n");
        return;
    }

    printf("\n================ ATTENDANCE REPORT ================\n");

    printf("%-8s %-20s %-10s %-10s %-10s\n",
           "Roll", "Name", "Total", "Present", "Percent");

    printf("------------------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {

        percentage = 0;

        if (s.totalClasses > 0) {
            percentage =
                ((float)s.presentClasses /
                 s.totalClasses) * 100;
        }

        printf("%-8d %-20s %-10d %-10d %.2f%%\n",
               s.rollNo,
               s.name,
               s.totalClasses,
               s.presentClasses,
               percentage);
    }

    fclose(fp);
}

/* Update Student */
void updateStudent() {

    FILE *fp;
    struct Student s;

    int rollNo;
    int found = 0;

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &rollNo);

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.rollNo == rollNo) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Course: ");
            scanf(" %[^\n]", s.course);

            fseek(fp, -sizeof(s), SEEK_CUR);

            fwrite(&s, sizeof(s), 1, fp);

            printf("\nStudent updated successfully!\n");

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nStudent not found!\n");
    }
}

/* Delete Student */
void deleteStudent() {

    FILE *fp;
    FILE *temp;

    struct Student s;

    int rollNo;
    int found = 0;

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &rollNo);

    fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.rollNo == rollNo) {
            found = 1;
        }
        else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("\nStudent deleted successfully!\n");
    }
    else {
        printf("\nStudent not found!\n");
    }
}