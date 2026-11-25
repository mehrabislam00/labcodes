#include <stdio.h>

int main() {
    int n, i;
    int pid[20], at[20], bt[20], ct[20], tat[20], wt[20];
    int finished[20] = {0};                 // 0 = চলেনি, 1 = শেষ
    int done = 0, time = 0;                 // done = কয়টা শেষ, time = ঘড়ি
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Process IDs: ");
    for (i = 0; i < n; i++) scanf("%d", &pid[i]);

    printf("Enter Burst Times: ");
    for (i = 0; i < n; i++) scanf("%d", &bt[i]);

    printf("Enter Arrival Times: ");
    for (i = 0; i < n; i++) scanf("%d", &at[i]);

    while (done < n) {
        int pick = -1;                      // কাকে চালাব? এখনো ঠিক হয়নি

        // সবচেয়ে ছোট Burst Time-এর প্রসেস খোঁজা
        for (i = 0; i < n; i++) {
            if (finished[i] == 1) continue;     // আগেই শেষ হয়ে গেছে, বাদ
            if (at[i] > time) continue;         // এখনো আসেনি, বাদ

            if (pick == -1 || bt[i] < bt[pick]) // প্রথম প্রার্থী, অথবা আগেরজনের চেয়ে ছোট
                pick = i;
        }

        if (pick == -1) {                   // কেউই আসেনি
            time++;                         // ঘড়ি ১ এগোও
            continue;
        }

        // বাছাই করা প্রসেস চালাও
        time += bt[pick];
        ct[pick] = time;
        tat[pick] = ct[pick] - at[pick];
        wt[pick] = tat[pick] - bt[pick];

        finished[pick] = 1;
        done++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avgWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", avgTAT / n);
    return 0;
}
