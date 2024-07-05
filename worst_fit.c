#include <stdio.h>
#include <limits.h>

void allocateWorstFit(int blockSize[], int blocks, int processSize[], int processes) {
  int allocation[processes];

  for (int i = 0; i < processes; i++) {
    allocation[i] = -1;
  }

  printf("Process Allocation Table:\n");
  printf("   Process ID   Process Size   Partition ID\n");

  for (int i = 0; i < processes; i++) {
    int worstIdx = -1;
    int maxBlockSize = -INT_MAX;

    for (int j = 0; j < blocks; j++) {
      if (blockSize[j] >= processSize[i] && blockSize[j] > maxBlockSize) {
        maxBlockSize = blockSize[j];
        worstIdx = j;
      }
    }

    if (worstIdx != -1) {
      allocation[i] = worstIdx;
      blockSize[worstIdx] -= processSize[i];

      printf("     %d                 %d                %d\n", i + 1, processSize[i], worstIdx + 1);
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

  allocateWorstFit(blockSize, blocks, processSize, processes);

  return 0;
}

