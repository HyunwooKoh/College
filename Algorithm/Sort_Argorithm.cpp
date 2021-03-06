/******************************************
**********     Hyunwoo, KOH     ***********
**********  trghyunwoo@naver.com  *********
**********  Dankook UNIV , Jookjeon *******

********** 각 정렬 방식의 수행시간 차이를 확인하고, 이해하기 위해 작성한 프로그램 *******
*/

#include "pch.h"
#include <iostream>
#include <time.h>
using namespace std;

class Sort{
private:
	int List[60000]; // 정렬시에 사용할 정수형 배열
	int Sem_List[60000]; // 각 방식으로 정렬할 것이기 때문에, 동일한 배열을 다른 공간에 저장해 놓고, 이를 복사하여 사용
						 // 동일한 배열을 사용해야지, 비교가 더 수월함
	int len = 60000; // 정수형 배열의 길이
	int link[60000] = { 0, }; // 링크를 사용한 합병정렬에서 링크를 사용하기 위한 저장 공간
public:
	Sort() { for (int i = 0; i < len; i++) Sem_List[i] = List[i] = rand(); }
	void Reset_List(); // 각 정렬 방식전에, 리스트를 초기화
	void Insertion_sort(); //삽입정렬
	void Selection_sort(); //선택 정렬
	void Bubble_sort(); // 버블 정렬
	int partition(int left, int right); // 퀵 정렬에서 받은 배열을 부분으로 나눠 주는 함수
	void Quick_sort(int left, int right); // 퀵 정렬
	int Merge(int q, int r); // 합병정렬에서 합병하는 함수
	int Merge_sort(int low, int high); // 합병 정렬
};

void Sort::Reset_List()
{
	for (int i = 0; i < len; i++)
		List[i] = Sem_List[i];

	return;
}

void Sort::Insertion_sort()
{
	int i, j, key;

	for (i = 1; i < len; i++) {
		key = List[i];

		for (j = i - 1; j >= 0 && List[j] > key; j--)
			List[j + 1] = List[j];

		List[j + 1] = key;
	}
	return;
}

void Sort::Selection_sort()
{
	int temp, min = 0;

	for (int i = 1; i < len - 1; i++) {
		min = i;
		
		for (int j = i + 1; j < len; j++) {
			if (List[j] < List[min])	min = j;
		}
		
		if (i != min) {
			temp = List[min];
			List[min] = List[i];
			List[i] = temp;
		}
	}
	return;
}

void Sort::Bubble_sort()
{
	int temp;

	for (int i = len - 1; i > 0; i--) {
		
		for (int j = 0; j < i; j++) {
			
			if (List[j] < List[j + 1]) {
				temp = List[j];
				List[j] = List[j + 1];
				List[j + 1] = temp;
			}
		}
	}
	return;
}

int Sort::partition(int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = List[left];

	do {
		do {
			low++;
		} while (low <= right && List[low] < pivot);

		do {
			high--;
		} while (high >= left && List[high] > pivot );

		if (low < high) {
			temp = List[low];
			List[low] = List[high];
			List[high] = temp;
		}
	} while (low < high);

	temp = List[left];
	List[left] = List[high];
	List[high] = temp;

	return high;
}

void Sort::Quick_sort(int left, int right)
{
	if (left < right) {
		int q = partition( left, right );

		Quick_sort(left, q - 1);
		Quick_sort(q + 1, right);
	}
	return;
}

int Sort::Merge(int q, int r)
{
	int i = q, j = r, k = 0;

	while (i != 0 && j != 0) { // While both lists are nonempty do
		if (List[i] <= List[j]) { // Find the smaller key.
			link[k] = i; k = i; i = link[i]; // Add a new key to the list.
		}
		else {
			link[k] = j; k = j; j = link[j];
		}
	}

	if (i == 0) link[k] = j;
	else link[k] = i;
	return(link[0]);
}

int Sort::Merge_sort(int low, int high)
{
	List[0] = 0;
	if (!(low < high))
		return low;
	else {
		int mid = (low + high) / 2;
		int q = Merge_sort( low, mid );
		int r = Merge_sort( mid + 1, high );
		return( Merge(q, r) );
	}
}

/* merge sort : List[0] = 0 으로 초기화 해준 후, 처음 호출은 1,60000
 * Quick sort : 0, 60000 - 1으로 첫 호출
*/
int main()
{
	cout << "\t삽입정렬\t선택정렬\t버블정렬\t퀵정렬\t합병정렬\n";
	cout << "수행시간 : ";
	Sort arr = Sort();

	clock_t start, end;
	double result = 0.0f; //수행시간 측정을 위한 변수 선언

	start = clock();
	arr.Insertion_sort();
	end = clock();
	result = double(end - start) / 1000; // 삽입정렬의 수행 및 수행시간 측정

	cout << result << "\t";

	arr.Reset_List();
	start = clock();
	arr.Selection_sort();
	end = clock();
	result = double(end - start) / 1000; // 선택정렬의 수행 및 수행시간 측정

	cout << result << "\t\t";
	
	arr.Reset_List();
	start = clock();
	arr.Bubble_sort();
	end = clock();
	result = double(end - start)/1000; // 버블정렬의 수행 및 수행시간 측정

	cout << result << "\t\t";
	
	arr.Reset_List();
	start = clock();
	arr.Quick_sort(0,59999);
	end = clock();
	result = double(end - start) / 1000; // 퀵 정렬의 수행 및 수행시간 측정

	cout << result << "\t";

	arr.Reset_List();
	start = clock();
	arr.Merge_sort(1,60000);
	end = clock();
	result = double(end - start) / 1000; // 합병 정렬의 수행 및 수행시간 측정

	cout << result << "\t";

	return 0;
}
