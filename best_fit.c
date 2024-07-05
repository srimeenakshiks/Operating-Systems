#include <stdio.h>
#include <limits.h>

void allocateBestFit(int blockSize[], int blocks, int processSize[], int processes) {
  int allocation[processes];

  for (int i = 0; i < processes; i++) {
    allocation[i] = -1;
  }

  printf("Process Allocation Table:\n");
  printf("   Process ID   Process Size   Partition ID\n");

  for (int i = 0; i < processes; i++) {
    int bestIdx = -1;  
    int minDiff = INT_MAX;  

    for (int j = 0; j < blocks; j++) {
      if (blockSize[j] >= processSize[i]) {
        int diff = blockSize[j] - processSize[i];
        if (diff < minDiff) {
          minDiff = diff;
          bestIdx = j;
        }
      }
    }

    if (bestIdx != -1) {
      allocation[i] = bestIdx;
      blockSize[bestIdx] -= processSize[i];

      printf("     %d                 %d                %d\n", i + 1, processSize[i], bestIdx + 1);
    } else {
      printf("     %d                 %d          Not Allocated\n", i + 1, processSize[i]);
    }
  }
}

int main() {
  int blocks, processes;

  printf("Enter the number of partitions: ");
  scanf("%d", &blocks);

  int blockSize[blocks];
  printf("Enter the size of each partition (space separated): ");
  for (int i = 0; i < blocks; i++) {
    scanf("%d", &blockSize[i]);
  }

  printf("Enter the number of processes: ");
  scanf("%d", &processes);

  int processSize[processes];
  printf("Enter the size of each process (space separated): ");
  for (int i = 0; i < processes; i++) {
    scanf("%d", &processSize[i]);
  }

  allocateBestFit(blockSize, blocks, processSize, processes);

  return 0;
}
