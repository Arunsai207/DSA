
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 100

// Structure representing a student node
struct Student {
    int regNo;
    char name[NAME_LENGTH];
    float marks;
    struct Student *next;
};

struct Student *head = NULL;

// Search for a student by registration number
struct Student *searchStudent(int regNo) {
    struct Student *current = head;

    while (current != NULL) {
        if (current->regNo == regNo) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

// Add a new student record
void addStudent(void) {
    int regNo;
    struct Student *newNode;

    printf("Enter registration number: ");
    if (scanf("%d", &regNo) != 1 || regNo <= 0) {
        printf("Invalid registration number.\n");
        while (getchar() != '\n');
        return;
    }

    if (searchStudent(regNo) != NULL) {
        printf("Registration number already exists.\n");
        return;
    }

    newNode = malloc(sizeof(struct Student));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->regNo = regNo;

    printf("Enter student name: ");
    scanf(" %99[^\n]", newNode->name);

    printf("Enter marks (0-100): ");
    if (scanf("%f", &newNode->marks) != 1 ||
        newNode->marks < 0 || newNode->marks > 100) {
        printf("Invalid marks.\n");
        while (getchar() != '\n');
        free(newNode);
        return;
    }

    newNode->next = NULL;

    // Insert at the end of the list
    if (head == NULL) {
        head = newNode;
    } else {
        struct Student *current = head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newNode;
    }

    printf("Student record added successfully.\n");
}

// Search and display a student
void searchRecord(void) {
    int regNo;
    struct Student *student;

    printf("Enter registration number to search: ");
    if (scanf("%d", &regNo) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    student = searchStudent(regNo);

    if (student == NULL) {
        printf("Student record not found.\n");
    } else {
        printf("\nStudent found:\n");
        printf("Registration Number: %d\n", student->regNo);
        printf("Name: %s\n", student->name);
        printf("Marks: %.2f\n", student->marks);
    }
}

// Delete a student record
void deleteStudent(void) {
    int regNo;
    struct Student *current = head;
    struct Student *previous = NULL;

    printf("Enter registration number to delete: ");
    if (scanf("%d", &regNo) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    while (current != NULL && current->regNo != regNo) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student record not found.\n");
        return;
    }

    // If deleting the first node
    if (previous == NULL) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Student record deleted successfully.\n");
}

// Display all student records
void displayStudents(void) {
    struct Student *current = head;

    if (head == NULL) {
        printf("No student records available.\n");
        return;
    }

    printf("\n%-15s %-25s %-10s\n",
           "Reg. Number", "Name", "Marks");
    printf("--------------------------------------------------\n");

    while (current != NULL) {
        printf("%-15d %-25s %-10.2f\n",
               current->regNo,
               current->name,
               current->marks);

        current = current->next;
    }
}

// Release allocated memory
void freeList(void) {
    struct Student *current = head;

    while (current != NULL) {
        struct Student *temp = current;
        current = current->next;
        free(temp);
    }

    head = NULL;
}

int main(void) {
    int choice;

    while (1) {
        printf("\n===== STUDENT RECORD MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. Search Student\n");
        printf("3. Delete Student\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Enter a number from 1 to 5.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                searchRecord();
                break;

            case 3:
                deleteStudent();
                break;

            case 4:
                displayStudents();
                break;

            case 5:
                freeList();
                printf("Exiting application. Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Please select 1-5.\n");
        }
    }

    return 0;
}
