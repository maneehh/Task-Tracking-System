#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enumeration for representing task status
enum TaskStatus {
    NOT_STARTED,
    IN_PROGRESS,
    DONE
};

// Structure to represent a task
struct Task {
    int id;
    char title[100];
    char description[500];
    char priority; //'L' for Low, 'M' for Medium, etc.
    enum TaskStatus status;
};

// Node structure for the hash table
struct Node {
    struct Task task;
    struct Node* next;
};

// Hash table structure
struct HashTable {
    struct Node* table[100]; // Max 100 tasks
};

// Function to create a new task
struct Task createTask(int id) {
    struct Task newTask;
    newTask.id = id;

    printf("Enter task title: ");
    scanf(" %99[^\n]", newTask.title); // Read up to 99 characters

    printf("Enter task description: ");
    scanf(" %499[^\n]", newTask.description);

    printf("Enter task priority (L for Low, M for Medium, H for High, U for Urgent): ");
    scanf(" %c", &newTask.priority);

    newTask.status = NOT_STARTED; // Default status not started

    return newTask;
}

// Function to display a task
void displayTask(struct Task task) {
    printf("\nTask ID: %d\n", task.id);
    printf("Title: %s\n", task.title);
    printf("Description: %s\n", task.description);
    printf("Priority: %c\n", task.priority);
    printf("Status: ");
    switch (task.status) {
        case NOT_STARTED:
            printf("Not Started\n");
            break;
        case IN_PROGRESS:
            printf("In Progress\n");
            break;
        case DONE:
            printf("Done\n");
            break;
    }
}

// Initializing hash table
void initializeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < 100; ++i) {
        hashTable->table[i] = NULL;
    }
}

// Function for inserting a task in the hash table
void insertTask(struct HashTable* hashTable, struct Task task) {
    int key = task.id % 100; // I used the simplest hash function

    // Create a new node
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->task = task;
    newNode->next = hashTable->table[key];

    // Insert the node into the hash table
    hashTable->table[key] = newNode;

    // Display the ID of the added task
    printf("Task added successfully! Task ID: %d\n", task.id);
}

// Function to retrieve a task from the hash table using ID
struct Task* getTask(struct HashTable* hashTable, int taskId) {
    int key = taskId % 100;

    // Linked list at the specific index
    struct Node* currentNode = hashTable->table[key];
    while (currentNode != NULL) {
        if (currentNode->task.id == taskId) {
            return &(currentNode->task); // Task is found
        }
        currentNode = currentNode->next;
    }

    return NULL; // Task is not found
}


int main() {
    int choice;
    struct HashTable taskHashTable;
    initializeHashTable(&taskHashTable);
    int taskIdCounter = 1;

    do {
        printf("\nTask Tracking Menu:\n");
        printf("\n");
        printf("1. Add Task\n");
        printf("2. Update Task Status\n");
        printf("3. Display Tasks\n");
        printf("4. Exit\n");
        printf("\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (taskIdCounter <= 100) {
                    struct Task newTask = createTask(taskIdCounter);
                    insertTask(&taskHashTable, newTask);
                    taskIdCounter++;
                } else {
                    printf("No space for new tasks!\n");
                }
                break;

            case 2:
                printf("Enter the ID of the task to update status: ");
                int taskId;
                scanf("%d", &taskId);

                struct Task* taskToUpdate = getTask(&taskHashTable, taskId);
                if (taskToUpdate != NULL) {
                    printf("Update status for task \"%s\":\n", taskToUpdate->title);
                    printf("\n");
                    printf("1. Not Started\n");
                    printf("2. In Progress\n");
                    printf("3. Done\n");
                    printf("Enter your choice: ");

                    int statusChoice;
                    scanf("%d", &statusChoice);

                    switch (statusChoice) {
                        case 1:
                            taskToUpdate->status = NOT_STARTED;
                            printf("Task status updated to Not Started.\n");
                            break;
                        case 2:
                            taskToUpdate->status = IN_PROGRESS;
                            printf("Task status updated to In Progress.\n");
                            break;
                        case 3:
                            taskToUpdate->status = DONE;
                            printf("Task status updated to Done.\n");
                            break;
                        default:
                            printf("Invalid choice. Status not updated.\n");
                    }
                } else {
                    printf("Task ID not found. \n");
                }
                break;

            case 3:
                printf("\nTask List:\n");
                printf("\n");
                for (int i = 0; i < 100; ++i) {
                    struct Node* currentNode = taskHashTable.table[i];
                    while (currentNode != NULL) {
                        displayTask(currentNode->task);
                        currentNode = currentNode->next;
                    }
                }
                break;

            case 4:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    // Free allocated memory for nodes in the hash table
    for (int i = 0; i < 100; ++i) {
        struct Node* currentNode = taskHashTable.table[i];
        while (currentNode != NULL) {
            struct Node* nextNode = currentNode->next;
            free(currentNode);
            currentNode = nextNode;
        }
    }

    return 0;
}

