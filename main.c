
#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100
#define SIZE 200

struct Task
{
    char name[SIZE];
    int completed;
};

struct Task tasks[MAX_TASKS];
int count = 0;

void addTask()
{
    if (count >= MAX_TASKS)
    {
        printf("\nTask list is full!\n");
        return;
    }

    getchar();

    printf("\nEnter your task: ");
    fgets(tasks[count].name, SIZE, stdin);

    tasks[count].name[strcspn(tasks[count].name, "\n")] = '\0';

    if (strlen(tasks[count].name) == 0)
    {
        printf("Task cannot be empty!\n");
        return;
    }

    tasks[count].completed = 0;
    count++;

    printf("Task added successfully!\n");
}

void viewTasks()
{
    int i;

    printf("\n========== YOUR TASKS ==========\n");

    if (count == 0)
    {
        printf("No tasks available!\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        printf("%d. %s [%s]\n",
               i + 1,
               tasks[i].name,
               tasks[i].completed ? "Completed" : "Pending");
    }
}

void completeTask()
{
    int num;

    viewTasks();

    if (count == 0)
        return;

    printf("\nEnter task number to complete: ");

    if (scanf("%d", &num) != 1)
    {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    if (num < 1 || num > count)
    {
        printf("Invalid task number!\n");
        return;
    }

    tasks[num - 1].completed = 1;

    printf("Task marked as completed successfully!\n");
}

void deleteTask()
{
    int num, i;

    viewTasks();

    if (count == 0)
        return;

    printf("\nEnter task number to delete: ");

    if (scanf("%d", &num) != 1)
    {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    if (num < 1 || num > count)
    {
        printf("Invalid task number!\n");
        return;
    }

    for (i = num - 1; i < count - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }

    count--;

    printf("Task deleted successfully!\n");
}

int main()
{
    int choice;

    printf("\n====================================\n");
    printf("     SMART STUDENT LIFE MANAGER\n");
    printf("====================================\n");

    while (1)
    {
        printf("\n1. Add Task");
        printf("\n2. View Tasks");
        printf("\n3. Mark Task as Completed");
        printf("\n4. Delete Task");
        printf("\n5. Exit");

        printf("\n\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Please enter a valid number!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                completeTask();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                printf("\nThank you for using Smart Student Life Manager!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}
