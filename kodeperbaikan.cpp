#include <stdio.h>
#include <stdlib.h>

#define SIZE 100


int minHeap[SIZE];
int minCount = 1;

int getParentIndex(int index) { return index / 2; }
int getLeftIndex(int index) { return index * 2; }
int getRightIndex(int index) { return index * 2 + 1; }

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void HeapUpMin(int index) {
	if (index <= 1) return;
	int parent = getParentIndex(index);
	if (minHeap[parent] > minHeap[index]) {
		swap(&minHeap[parent], &minHeap[index]);
		HeapUpMin(parent);
	}
}

void HeapDownMin(int index) {
	int smallest = index;
	int left = getLeftIndex(index);
	int right = getRightIndex(index);

	if (left < minCount && minHeap[left] < minHeap[smallest])
		smallest = left;
	if (right < minCount && minHeap[right] < minHeap[smallest])
		smallest = right;

	if (smallest != index) {
		swap(&minHeap[index], &minHeap[smallest]);
		HeapDownMin(smallest);
	}
}

void pushMin(int value) {
	minHeap[minCount] = value;
	HeapUpMin(minCount);
	minCount++;
}

int popMin() {
	if (minCount <= 1) return -1;
	int removed = minHeap[1];
	swap(&minHeap[1], &minHeap[minCount - 1]);
	minCount--;
	HeapDownMin(1);
	return removed;
}

void viewMinHeap() {
	if (minCount <= 1) {
		printf("MinHeap is empty.\n");
	} else {
		for (int i = 1; i < minCount; i++)
			printf("MinHeap[%2d] = %d\n", i, minHeap[i]);
	}
	puts("");
}


int maxHeap[SIZE];
int maxCount = 1;

void HeapUpMax(int index) {
	if (index <= 1) return;
	int parent = getParentIndex(index);
	if (maxHeap[parent] < maxHeap[index]) {
		swap(&maxHeap[parent], &maxHeap[index]);
		HeapUpMax(parent);
	}
}

void HeapDownMax(int index) {
	int largest = index;
	int left = getLeftIndex(index);
	int right = getRightIndex(index);

	if (left < maxCount && maxHeap[left] > maxHeap[largest])
		largest = left;
	if (right < maxCount && maxHeap[right] > maxHeap[largest])
		largest = right;

	if (largest != index) {
		swap(&maxHeap[index], &maxHeap[largest]);
		HeapDownMax(largest);
	}
}

void pushMax(int value) {
	maxHeap[maxCount] = value;
	HeapUpMax(maxCount);
	maxCount++;
}

int popMax() {
	if (maxCount <= 1) return -1;
	int removed = maxHeap[1];
	swap(&maxHeap[1], &maxHeap[maxCount - 1]);
	maxCount--;
	HeapDownMax(1);
	return removed;
}

void viewMaxHeap() {
	if (maxCount <= 1) {
		printf("MaxHeap is empty.\n");
	} else {
		for (int i = 1; i < maxCount; i++)
			printf("MaxHeap[%2d] = %d\n", i, maxHeap[i]);
	}
	puts("");
}


void showMenu() {
	puts("Choose Heap Type:");
	puts("1. MinHeap");
	puts("2. MaxHeap");
	puts("3. Exit");
}

void showHeapMenu() {
	puts("1. Insert");
	puts("2. Delete");
	puts("3. Back to Heap Type Menu");
}

int main() {
	int mainChoice = 0;

	while (mainChoice != 3) {
		showMenu();
		printf("Input your choice: ");
		scanf("%d", &mainChoice); getchar();

		if (mainChoice == 1 || mainChoice == 2) {
			int heapChoice = 0;
			while (heapChoice != 3) {
				printf("\nCurrent %s:\n", mainChoice == 1 ? "MinHeap" : "MaxHeap");
				if (mainChoice == 1) viewMinHeap();
				else viewMaxHeap();

				showHeapMenu();
				printf("Choose an option: ");
				scanf("%d", &heapChoice); getchar();

				if (heapChoice == 1) {
					int value;
					printf("Enter value to insert: ");
					scanf("%d", &value); getchar();
					if (mainChoice == 1) pushMin(value);
					else pushMax(value);
					printf("%d inserted into %s.\n\n", value, mainChoice == 1 ? "MinHeap" : "MaxHeap");
				}
				else if (heapChoice == 2) {
					int removed = (mainChoice == 1) ? popMin() : popMax();
					if (removed == -1)
						printf("%s is empty.\n\n", mainChoice == 1 ? "MinHeap" : "MaxHeap");
					else
						printf("%d removed from %s.\n\n", removed, mainChoice == 1 ? "MinHeap" : "MaxHeap");
				}
				else if (heapChoice != 3) {
					printf("Invalid option. Try again.\n");
				}
			}
		}
		else if (mainChoice != 3) {
			printf("Invalid heap type. Try again.\n");
		}
	}

	printf("Exiting program...\n");
	return 0;
}

