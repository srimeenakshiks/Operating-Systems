#include <stdio.h>


int main() {
    int n, m, i, j, k;


    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);


    int alloc[n][m], max[n][m], need[n][m], avail[m], f[n], ans[n];
    for (k = 0; k < n; k++) {
        f[k] = 0;
    }


    printf("Enter the available resources: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }


    printf("Enter the Allocation Matrix (space separated):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }


    printf("Enter the Max Matrix (space separated):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }




    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }


    // Check for safe state using Banker's Algorithm with iterative approach
    int work[m];
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }
    int found = 0;


    for (int iter = 0; iter < n; iter++) { // Iterative loop to check for safe sequence
        int anyFinished = 0;
        for (i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }


                if (flag == 1) {
                    for (j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    f[i] = 1;
                    ans[found] = i;
                    found++;
                    anyFinished = 1;
                }
            }
        }
        if (anyFinished == 0) {
            break;
        }
    }


    if (found == n) {
        printf("System is in a safe state\n");
        printf("Safe sequence: ");
        for (i = 0; i < n; i++) {
            printf("P%d ", ans[i]);
        }
        printf("\n");
    } else {
        printf("System is in an unsafe state\n");
    }


    return 0;
}
