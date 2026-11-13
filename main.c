
#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100

struct Task {
    char title[100];
    int completed;
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;

void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL) {
        printf("Error saving tasks!\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(fp, "%d\n%s\n",
                tasks[i].completed, tasks[i].title);
    }

    fclose(fp);
}

void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");

    if (fp == NULL) return;

    while (taskCount < MAX_TASKS &&
           fscanf(fp, "%d\n", &tasks[taskCount].completed) == 1) {

        if (fgets(tasks[taskCount].title,
                  sizeof(tasks[taskCount].title), fp) == NULL) {
            break;
        }

        tasks[taskCount].title[
            strcspn(tasks[taskCount].title, "\n")] = '\0';

        taskCount++;
    }

    fclose(fp);
}

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("Enter task: ");
    fgets(tasks[taskCount].title,
          sizeof(tasks[taskCount].title), stdin);

    tasks[taskCount].title[
        strcspn(tasks[taskCount].title, "\n")] = '\0';

    if (strlen(tasks[taskCount].title) == 0) {
        printf("Task cannot be empty!\n");
        return;
    }

    tasks[taskCount].completed = 0;
    taskCount++;

    saveTasks();
    printf("Task added successfully!\n");
}

void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        printf("%d. %s [%s]\n",
               i + 1,
               tasks[i].title,
               tasks[i].completed ? "Completed" : "Pending");
    }
}

void completeTask() {
    int number;

    viewTasks();
    if (taskCount == 0) return;

    printf("Enter task number to complete: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (number < 1 || number > taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    tasks[number - 1].completed = 1;
    saveTasks();

    printf("Task marked as completed!\n");
}

void deleteTask() {
    int number;

    viewTasks();
    if (taskCount == 0) return;

    printf("Enter task number to delete: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (number < 1 || number > taskCount) {
        printf("Invalid task number!\n");
        return;
    }

    for (int i = number - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;
    saveTasks();

    printf("Task deleted successfully!\n");
}

int main() {
    int choice;

    loadTasks();

    do {
        printf("\n====================================\n");
        printf("   SMART STUDENT LIFE MANAGER\n");
        printf("====================================\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid number!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5: saveTasks(); printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
