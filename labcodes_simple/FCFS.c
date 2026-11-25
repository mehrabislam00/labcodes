#include <stdio.h>

int main() {
    int n, i, j;
    int pid[50], at[50], bt[50];                // ID, Arrival Time, Burst Time
    int st[50], ct[50], wt[50], tat[50];        // Start, Completion, Waiting, Turnaround
    int time = 0;                               // এখনকার ঘড়ি
    float total_wt = 0, total_tat = 0;          // গড়ের জন্য যোগফল

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter process IDs:\n");
    for (i = 0; i < n; i++) scanf("%d", &pid[i]);

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) scanf("%d", &bt[i]);

    printf("Enter arrival times:\n");
    for (i = 0; i < n; i++) scanf("%d", &at[i]);

    // ---------- Arrival Time অনুযায়ী সাজানো (bubble sort) ----------
    // পাশাপাশি দুজনকে তুলনা করি; বাঁয়েরটার AT বড় হলে জায়গা বদলাই
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (at[j] > at[j + 1]) {
                int t;
                t = at[j];  at[j]  = at[j + 1];  at[j + 1]  = t;    // AT swap
                t = bt[j];  bt[j]  = bt[j + 1];  bt[j + 1]  = t;    // BT swap
                t = pid[j]; pid[j] = pid[j + 1]; pid[j + 1] = t;    // PID swap
            }
        }
    }

    // ---------- একটা লুপেই সব হিসাব ----------
    for (i = 0; i < n; i++) {
        if (time < at[i]) time = at[i];     // প্রসেস এখনো আসেনি? তার আসা পর্যন্ত অপেক্ষা
        st[i] = time;                       // শুরু = এখনকার ঘড়ি
        time += bt[i];                      // কাজ করলে ঘড়ি এগোবে
        ct[i] = time;                       // শেষ = এখনকার ঘড়ি
        tat[i] = ct[i] - at[i];             // Turnaround = Completion - Arrival
        wt[i] = tat[i] - bt[i];             // Waiting = Turnaround - Burst

        total_wt += wt[i];
        total_tat += tat[i];
    }

    // ---------- ফলাফল ----------
    printf("\nPID\tAT\tBT\tST\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], st[i], ct[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);
    return 0;
}
