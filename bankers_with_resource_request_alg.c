#include <stdio.h>

int main() {
    int n, m, i, j, k;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m];
    printf("Enter the allocation matrix for each process :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    printf("Enter the max matrix for each process :\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    printf("Enter the available resources: ");
    for (int k = 0; k < m; k++)
        scanf("%d", &avail[k]);

    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++)
        f[k] = 0;

    int need[n][m];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    int y = 0;

    // Safety check and resource request loop
    while (1) {
        int flag = 1;
        for (k = 0; k < n; k++)
            for (i = 0; i < n; i++)
                if (f[i] == 0) {
                    int flag2 = 0;
                    for (j = 0; j < m; j++)
                        if (need[i][j] > avail[j]) {
                            flag2 = 1;
                            break;
                        }
                    if (flag2 == 0) {
                        ans[ind++] = i;
                        for (y = 0; y < m; y++)
                            avail[y] += alloc[i][y];
                        f[i] = 1;
                    }
                }

        // Check if all processes are finished
        flag = 1;
        for (i = 0; i < n; i++)
            if (f[i] == 0) {
                flag = 0;
                break;
            }

        // Print safe sequence (if any)
        if (flag == 1) {
            printf("\nFollowing is the safe sequence:\n");
            for (i = 0; i < n - 1; i++)
                printf(" P%d ->", ans[i]);
            printf(" P%d\n", ans[n - 1]);
        }

        // Handle resource requests
        int req_process, req[m];
        printf("\nEnter process ID for resource request (-1 to exit): ");
        scanf("%d", &req_process);
        if (req_process == -1) {
            break; // Exit loop if user enters -1
        }

        printf("Enter resource request for process P%d (space separated):\n", req_process);
        for (i = 0; i < m; i++) {
            scanf("%d", &req[i]);
        }

        // Validate request
        int valid_req = 1;
        for (i = 0; i < m; i++) {
            if (req[i] > need[req_process][i] || req[i] > avail[i]) {
                valid_req = 0;
                break;
            }
        }

        if (valid_req) {
            // Simulate granting the request
            for (i = 0; i < m; i++) {
                avail[i] -= req[i];
                alloc[req_process][i] += req[i];
                need[req_process][i] -= req[i];
            }
            printf("Request granted for process P%d.\n", req_process);
            break;
        } else {
            printf("Invalid request or insufficient resources.\n");
            break;
        }
    }
}
