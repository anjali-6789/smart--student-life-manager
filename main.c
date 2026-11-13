
#include <stdio.h>

int main()
{
    int choice;

    printf("\n====================================\n");
    printf("   SMART STUDENT LIFE MANAGER\n");
    printf("====================================\n");

    printf("\n1. Add Task");
    printf("\n2. View Tasks");
    printf("\n3. Mark Task as Completed");
    printf("\n4. Delete Task");
    printf("\n5. Exit");

    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    printf("\nYou selected option: %d\n", choice);

    return 0;
}
