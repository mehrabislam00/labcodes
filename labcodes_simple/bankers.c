#include <stdio.h>

int n, m;                                   // n = প্রসেস সংখ্যা, m = resource-এর ধরন
int allocation[10][10], max[10][10], need[10][10];
int available[10];

// প্রশ্ন: প্রসেস p কি এখন চলতে পারবে? (need <= available হলে হ্যাঁ)
int canRun(int p) {
    int j;
    for (j = 0; j < m; j++) {
        if (need[p][j] > available[j]) return 0;    // একটা resource কম পড়লেই না
    }
    return 1;                                       // সবগুলো যথেষ্ট, হ্যাঁ
}

int main() {
    int finish[10] = {0}, safeSequence[10];
    int i, j, count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max Matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources (%d):\n", m);
    for (j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Need = Max - Allocation
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    while (count < n) {
        int found = 0;                      // এই রাউন্ডে কেউ চলতে পেরেছে কি না

        for (i = 0; i < n; i++) {
            if (finish[i] == 1) continue;   // আগেই শেষ, বাদ
            if (!canRun(i)) continue;       // এখন চলতে পারবে না, বাদ

            // চলতে পারে: কাজ শেষ করে সব resource ফেরত দেবে
            for (j = 0; j < m; j++)
                available[j] += allocation[i][j];

            safeSequence[count++] = i;
            finish[i] = 1;
            found = 1;
        }

        if (found == 0) {                   // পুরো রাউন্ডে কেউই চলতে পারেনি
            printf("System is NOT in safe state.\n");
            return 0;
        }
    }

    printf("System is in SAFE state.\nSafe Sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", safeSequence[i]);
    printf("\n");
    return 0;
}
