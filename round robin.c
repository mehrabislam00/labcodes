#include <stdio.h>

int main() {
    int n, tq;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    int queue[100], front = 0, rear = 0;
    int time = 0, completed = 0;
    int i, j;
    int visited[10] = {0};
    int done[10] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    // Find first arrival time
    int min_at = at[0], first = 0;
    for (i = 1; i < n; i++) {
        if (at[i] < min_at) {
            min_at = at[i];
            first = i;
        }
    }

    time = at[first];
    queue[rear++] = first;
    visited[first] = 1;

    printf("\nGantt Chart:\n|");

    while (completed < n) {
        if (front == rear) {
            // No process in ready queue. So, its needed to avoid the infinite loop of CPU
            for (i = 0; i < n; i++) {
                if (done[i] == 0) {
                    queue[rear++] = i;
                    visited[i] = 1;
                    time = at[i];     //jump time to its arrival(Suppose, at of P1 and P2 is 0,5 and BT of p1 and P2 is 2, 3)
                    break;
                }
            }
        }

        i = queue[front++]; // get process index //Dequeue the process

        if (rt[i] > tq) {
            printf(" P%d |", i + 1);
            time += tq;
            rt[i]= rt[i]-tq;
        } else if (rt[i] > 0) {
            printf(" P%d |", i + 1);
            time += rt[i];
            ct[i] = time;
            tat[i] = ct[i] - at[i];
            wt[i] = tat[i] - bt[i];
            rt[i] = 0;
            done[i] = 1;
            completed++;
        }

        // Enqueue newly arrived process
        for (j = 0; j < n; j++) {
            if (at[j] <= time && rt[j] > 0 && visited[j] == 0) {
                queue[rear++] = j;
                visited[j] = 1;
            }
        }

        // Re-enqueue current process(if not finished)
        if (rt[i] > 0) {
            queue[rear++] = i;
        }
    }

    // Output
    float avgWT = 0, avgTAT = 0;
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
