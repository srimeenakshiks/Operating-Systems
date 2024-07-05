#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>


struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
};


void findWaitingTime(struct Process proc[], int n, int wt[], int time_quantum) {
    int remaining = n;


    int queue[n];
    int front = 0, rear = 0;


    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
    }


    int current_time = 0;
    while (remaining > 0) {
        int process = queue[front];


        // If burst time is greater than time quantum
        if (proc[process].remaining_time > time_quantum) {
            proc[process].remaining_time -= time_quantum;
            current_time += time_quantum;
            queue[rear++] = process;
        } else {
            current_time += proc[process].remaining_time;
            wt[process] = current_time - proc[process].burst_time - proc[process].arrival_time;
            remaining--;
        }


        // If queue is empty
        if (front == rear) {
            int found = 0;
            for (int i = 0; i < n; i++) {
                if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {
                    queue[rear++] = i;
                    found = 1;
                    break;
                }
            }
            // If no new process arrives
            if (found == 0) {
                current_time++;
            }
        }


        front = (front + 1) % n;
    }
}


void findTurnAroundTime(struct Process proc[], int n, int tat[], int wt[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].burst_time + wt[i];
    }
}


void findAverageTime(struct Process proc[], int n) {
    int wt[n], tat[n];
    int time_quantum;


    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);


    findWaitingTime(proc, n, wt, time_quantum);
    findTurnAroundTime(proc, n, tat, wt);


    // Display processes along with waiting times and turnaround times
    printf("Process ID\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burst_time, wt[i], tat[i]);
    }


    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }


    float avg_wt = (float)total_wt / (float)n;
    float avg_tat = (float)total_tat / (float)n;


    printf("Average Waiting Time = %.2f\n", avg_wt);
    printf("Average Turnaround Time = %.2f\n", avg_tat);
}


int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);


    struct Process proc[n];


    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].pid = i + 1; // Assign process IDs
    }


    findAverageTime(proc, n);
    return 0;
}
