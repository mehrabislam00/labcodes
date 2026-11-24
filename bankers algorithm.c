#include <stdio.h>

int main() {
    int n, m;  // n = number of processes, m = number of resources
    int allocation[10][10], max[10][10], need[10][10], available[10];
    int finish[10] = {0}, safeSequence[10];
    int i, j, k, count = 0;

    // Input number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    // Input Max Matrix
    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    // Input Available Resources
    printf("Enter Available Resources (%d):\n", m);
    for (i = 0; i < m; i++)
        scanf("%d", &available[i]);

    // Calculate Need Matrix = Max - Allocation
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Banker's Algorithm
    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {  // If process not finished
                int canRun = 1;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canRun = 0;  // Not enough resources
                        break;
                    }
                }

                if (canRun) {
                    // Allocate resources (pretend)
                    for (k = 0; k < m; k++)
                        available[k] += allocation[i][k];

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("System is NOT in safe state.\n");
            return 0;
        }
    }

    // Print Safe Sequence
    printf("System is in SAFE state.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);

    printf("\n");
    return 0;
}
