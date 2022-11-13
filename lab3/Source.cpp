#include <iostream> 
#include <fstream>
#include <list>


using namespace std;


void insertSort(int numbers[], int size) {

	for (int i = 1; i < size; i++)
		for (int j = i; j > 0 && numbers[j - 1] > numbers[j]; j--) 
			swap(numbers[j - 1], numbers[j]);

	return;
} 


void selectSort(int numbers[], int size) {

	int min = 0; 
	int buf = 0; 

	
	for (int i = 0; i < size; i++)
	{
		min = i; 
		for (int j = i + 1; j < size; j++)
			min = (numbers[j] < numbers[min]) ? j : min;
		
		if (i != min)
		{
			buf = numbers[i];
			numbers[i] = numbers[min];
			numbers[min] = buf;
		}
	}

	return;
}

void bubbleSort(int numbers[], int size) {

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size-1; j++) {
			if (numbers[j] > numbers[j + 1]) {
				swap(numbers[j + 1], numbers[j]);
			}
		}
	}

	return;

}


void mergeSort(int numbers[], int size)
{
if (size < 2)return;

mergeSort(numbers, size / 2);
mergeSort(&numbers[size / 2], size - (size / 2));

int* buf = new int[size];
int idbuf = 0, idl = 0, idr = size / 2;

while ((idl < size / 2) && (idr < size))
	if (numbers[idl] < numbers[idr])
		buf[idbuf++] = numbers[idl++];
	else
		buf[idbuf++] = numbers[idr++];

while (idl < size / 2) buf[idbuf++] = numbers[idl++];

while (idr < size) buf[idbuf++] = numbers[idr++];

for (idl = 0; idl < size; idl++)numbers[idl] = buf[idl];


delete[]buf;
}


void ShellSort(int numbers[],int size)
{
int i, j, step;
int tmp;
for (step = size / 2; step > 0; step /= 2)
for (i = step; i < size; i++)
{
tmp = numbers[i];
for (j = i; j >= step; j -= step)
{
if (tmp < numbers[j - step])
numbers[j] = numbers[j - step];
else
break;
}
numbers[j] = tmp;
}
}

void quickSort(int numbers[], int size) {
int i = 0;
int j = size - 1;

int mid = numbers[size / 2];

do {
while (numbers[i] < mid) {
	i++;
}
while (numbers[j] > mid) {
	j--;
}

		
if (i <= j) {
	int tmp = numbers[i];
	numbers[i] = numbers[j];
	numbers[j] = tmp;

	i++;
	j--;
}
} while (i <= j);


if (j > 0) {
quickSort(numbers, j + 1);
}
if (i < size) {
quickSort(&numbers[i], size - i);
}
}


void printMassive(int numbers[], int size) {

	for (int i = 0; i < size; i++) cout << numbers[i] << " ";
	cout << endl;
}


int main() {


	int startTime = clock();
	const int size = 200;
	int numbers[size];
	// «аполнение массива случайными числами
	for (int i = 0; i < size; i++)
		numbers[i] = rand() % 50 - 10;


	printMassive(numbers, size);
	cout << endl;

	quickSort(numbers, size);
	printMassive(numbers, size);

	int endTime = clock();

	cout << "work time: " << endTime - startTime << endl;

	return 0;
}