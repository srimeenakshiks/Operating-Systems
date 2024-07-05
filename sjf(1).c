#include <stdio.h>
#include <limits.h>


struct Process {
    int pid;  
    int burst_time;
    int arrival_time;
};


int compare_processes(const void *a, const void *b) {
    const struct Process *p1 = (const struct Process *)a;
    const struct Process *p2 = (const struct Process *)b;


    return p1->burst_time - p2->burst_time;
}


void find_times(struct Process proc[], int n, int st[], int ft[], int wt[]) {
    int current_time = 0;
    st[0] = 0;
    ft[0] = st[0] + proc[0].burst_time;
    wt[0] = 0;


    for (int i = 1; i < n; i++) {
        // Start time for the current process is the finish time of the previous process
        st[i] = ft[i - 1];
        ft[i] = st[i] + proc[i].burst_time; // Finish time = start time + burst time
        wt[i] = st[i] - proc[i].arrival_time - proc[i].burst_time;


        if (wt[i] < 0) {
            wt[i] = 0;
        }


    }
}


void find_turnaround_time(struct Process proc[], int n, int wt[], int tat[], int st[]) {
    // Turnaround time = finish time - arrival time
    for (int i = 0; i < n; i++) {
        tat[i] = st[i] + proc[i].burst_time - proc[i].arrival_time;
    }
}


void find_avg_time(struct Process proc[], int n) {
    int wt[n], st[n], tat[n], ft[n];  


    find_times(proc, n, st, ft, wt);
    find_turnaround_time(proc, n, wt, tat, st);


    // Display processes along with start times, run times (burst times), and finish times
    printf("Process\t Burst Time\t Arrival Time\t Start Time\t Finish Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t %d\t\t %d\t\t %d\t\t %d\n", proc[i].pid, proc[i].burst_time, proc[i].arrival_time, st[i], ft[i]);
    }


    float avg_wt = 0, avg_tat = 0;
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
    }


    // Display average waiting time and average turnaround time    
    avg_wt /= (float)n;
    avg_tat /= (float)n;
    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);


    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        printf("Enter arrival time for process %d (default 0): ", i + 1);
        scanf("%d", &proc[i].arrival_time);
        if (proc[i].arrival_time < 0) {
            printf("Invalid arrival time. Setting to 0.\n");
            proc[i].arrival_time = 0;
        }
        proc[i].pid = i + 1;
    }


    find_avg_time(proc, n);


    return 0;
}
