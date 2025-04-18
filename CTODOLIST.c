#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a task
typedef struct Task {
    char description[256];
    struct Task* next;
} Task;

// Function to create a new task
Task* createTask(const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(newTask->description, description);
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the list
void addTask(Task** head, const char* description) {
    Task* newTask = createTask(description);
    newTask->next = *head;
    *head = newTask;
    printf("Task added: %s\n", description);
}

// Function to display the tasks
void displayTasks(Task* head) {
    if (head == NULL) {
        printf("No tasks in the list.\n");
        return;
    }
    printf("To-Do List:\n");
    int index = 1;
    while (head != NULL) {
        printf("%d. %s\n", index++, head->description);
        head = head->next;
    }
}

// Function to delete a task by description
void deleteTask(Task** head, const char* description) {
    Task* current = *head;
    Task* previous = NULL;

    while (current != NULL && strcmp(current->description, description) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Task not found: %s\n", description);
        return;
    }

    if (previous == NULL) {
        *head = current->next; // The task to delete is the first task
    } else {
        previous->next = current->next; // Bypass the current task
    }

    free(current);
    printf("Task deleted: %s\n", description);
}

// Function to free the task list
void freeTasks(Task* head) {
    Task* current = head;
    Task* nextTask;

    while (current != NULL) {
        nextTask = current->next;
        free(current);
        current = nextTask;
    }
}

int main() {
    Task* todoList = NULL;
    int choice;
    char description[256];

    do {
        printf("\nTo-Do List Menu:\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline character
                addTask(&todoList, description);
                break;
            case 2:
                displayTasks(todoList);
                break;
            case 3:
                printf("Enter task description to delete: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = 0; // Remove newline character
                deleteTask(&todoList, description);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    freeTasks(todoList);
    return 0;
}
