#include <stdio.h>

int main() {
    int n, i;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], pr[n];
    int wt[n], tat[n], finished[n];

    for (i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d:\n", pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority (lower value = higher priority): ");
        scanf("%d", &pr[i]);

        finished[i] = 0;
    }

    int time = 0, done = 0;
    float total_wt = 0, total_tat = 0;

    while (done < n) {
        int idx = -1;                       // কাকে চালাব? এখনো ঠিক হয়নি

        for (i = 0; i < n; i++) {
            if (finished[i] == 1) continue;     // শেষ হয়ে গেছে, বাদ
            if (at[i] > time) continue;         // এখনো আসেনি, বাদ

            // i নম্বর প্রসেস কি এখনকার সেরার চেয়ে ভালো?
            int better = 0;
            if (idx == -1)
                better = 1;                             // প্রথম প্রার্থী, তাই ভালো
            else if (pr[i] < pr[idx])
                better = 1;                             // priority বেশি (সংখ্যা ছোট)
            else if (pr[i] == pr[idx] && at[i] < at[idx])
                better = 1;                             // priority সমান, কিন্তু আগে এসেছে

            if (better == 1) idx = i;
        }

        if (idx == -1) {                    // কেউ আসেনি
            time++;                         // CPU idle, ঘড়ি এগোও
            continue;
        }

        time += bt[idx];
        tat[idx] = time - at[idx];
        wt[idx] = tat[idx] - bt[idx];

        total_wt += wt[idx];
        total_tat += tat[idx];

        finished[idx] = 1;
        done++;
    }

    printf("\nPID\tAT\tBT\tPR\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], pr[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    return 0;
}
