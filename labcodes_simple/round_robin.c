#include <stdio.h>

// global variable: নিচের function থেকেও ব্যবহার করা যাবে
int n, tq;
int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
int queue[1000], front = 0, rear = 0;       // Ready Queue
int inQueue[10] = {0};                      // একবার queue-তে ঢুকেছে কি না

// যারা এখন পর্যন্ত এসে গেছে এবং কাজ বাকি আছে, তাদের queue-তে ঢোকাও
void addArrived(int time) {
    int j;
    for (j = 0; j < n; j++) {
        if (at[j] <= time && rt[j] > 0 && inQueue[j] == 0) {
            queue[rear++] = j;
            inQueue[j] = 1;
        }
    }
}

int main() {
    int i, time = 0, completed = 0;
    float avgWT = 0, avgTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];                      // শুরুতে বাকি কাজ = পুরো Burst Time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        addArrived(time);                   // নতুন যারা এসেছে, queue-তে ঢোকাও

        if (front == rear) {                // queue খালি: কেউ আসেনি
            time++;                         // ঘড়ি এগোও (CPU idle)
            continue;
        }

        int p = queue[front++];             // সামনের প্রসেসকে বের করো

        int run = tq;                       // সাধারণত tq সময় চলবে
        if (rt[p] < tq) run = rt[p];        // কিন্তু কাজ কম বাকি থাকলে ততটুকুই

        printf(" P%d |", p + 1);            // Gantt Chart
        time += run;                        // ঘড়ি এগোও
        rt[p] -= run;                       // বাকি কাজ কমাও

        addArrived(time);                   // এই সময়ে যারা এসেছে, আগে তারা queue-তে

        if (rt[p] > 0) {
            queue[rear++] = p;              // কাজ বাকি: লাইনের শেষে ফেরত
        } else {
            ct[p] = time;                   // কাজ শেষ
            tat[p] = ct[p] - at[p];
            wt[p] = tat[p] - bt[p];
            completed++;
        }
    }

    printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        avgWT += wt[i];
        avgTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
    return 0;
}
