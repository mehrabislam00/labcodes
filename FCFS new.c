#include <stdio.h>

int main()
{
    int pid[50], bt[50], at[50];
    int st[50], ct[50], wt[50], tat[50];
    int n, i, j;

   printf("Enter the number of processes: ");
    scanf("%d",&n);

    printf("Enter process IDs:\n");
    for (i = 0; i < n; i++) scanf("%d", &pid[i]);

    printf("Enter burst times:\n");
    for (i = 0; i < n; i++) scanf("%d", &bt[i]);

    printf("Enter arrival times:\n");
    for (i = 0; i < n; i++) scanf("%d", &at[i]);

    /* Stable sort by arrival time (selection-like, but keep stability) */
    for (i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (at[j] < at[min_idx]) min_idx = j;
        }
        /* Move element at min_idx to position i shifting intermediate elements
           to preserve relative order (stable). */
        if (min_idx != i) {
            int tmp_at = at[min_idx];
            at[min_idx]=at[i];
            at[i] = tmp_at;

            int tmp_bt = bt[min_idx];
            bt[min_idx]=bt[i];
            bt[i] = tmp_bt;

            int tmp_pid = pid[min_idx];
            pid[min_idx]=pid[i];
            pid[i] = tmp_pid;
        }
    }

    /* Compute start, completion, waiting and turnaround times */
    /* First process: starts at its arrival time */
    st[0] = at[0];
    ct[0] = st[0] + bt[0];
    //wt[0] = st[0] - at[0];       /* normally 0 */
    tat[0] = ct[0] - at[0];
    wt[0]=tat[0]-bt[0];

    for (i = 1; i < n; i++) {
        /* If CPU is free till this process arrives, start at arrival time */
        if (ct[i-1] <= at[i]) {
            st[i] = at[i];
        } else {
            /* else start immediately after previous completion */
            st[i] = ct[i-1];
        }
        ct[i] = st[i] + bt[i];
        //wt[i] = st[i] - at[i];
        tat[i] = ct[i] - at[i];
        wt[i]=tat[i]-bt[i];
    }

    float total_wt = 0.0f, total_tat = 0.0f;
    printf("\nPID\tAT\tBT\tST\tCT\tWT\tTAT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], st[i], ct[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nAverage Waiting Time = %.2f\n", total_wt / n);
    printf("Average Turnaround Time = %.2f\n", total_tat / n);

    return 0;
}
