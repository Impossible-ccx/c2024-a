#include<stdio.h>
#include<stdbool.h>
int myArray[100];
int* bubbleSort(int* target, int fIndex, int bIndex) {
	bool end = false;
	int track;
	while (!end) {
		end = true;
		for (int p = fIndex; p < bIndex; p++) {
			if (myArray[p] > myArray[p + 1]) {
				track = myArray[p];
				myArray[p] = myArray[p+1];
				myArray[p + 1] = track;
				end = false;
			}
		}
	}
}
int main() {
	for (int i = 100; i > 0; i--) {
		myArray[100 - i] = i;
	}
	bubbleSort(myArray, 0, 99);
	for (int i = 0; i < 100; i++)
	{
		printf("%d\n", myArray[i]);
	}
	return 0;
}