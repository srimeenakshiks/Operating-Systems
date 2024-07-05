#include <stdio.h>

#define PAGE_SIZE 1024

void simulatePaging(int processSize[], int processes, int totalMemory) {
  int numPages[processes];

  // Calculate number of pages required by each process
  for (int i = 0; i < processes; i++) {
    numPages[i] = (processSize[i] + PAGE_SIZE - 1) / PAGE_SIZE;
  }

  int totalFrames = totalMemory / PAGE_SIZE;

  printf("Process Allocation Table:\n");
  printf("   Process ID   Process Size   Number of Pages\n");

  for (int i = 0; i < processes; i++) {
    printf("     %d                 %d                 %d\n", i + 1, processSize[i], numPages[i]);
  }
}

int main() {
  int processes;
  printf("Enter the number of processes: ");
  scanf("%d", &processes);

  int processSize[processes];
  printf("Enter the size of each process (space separated): ");
  for (int i = 0; i < processes; i++) {
    scanf("%d", &processSize[i]);
  }

  int totalMemory;
  printf("Enter the total memory size (multiple of page size): ");
  scanf("%d", &totalMemory);

  simulatePaging(processSize, processes, totalMemory);

  return 0;
}

