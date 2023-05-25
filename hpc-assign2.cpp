#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void merge(std::vector<int>& arr, int left, int mid, int right) {
 int i, j, k;
 int n1 = mid - left + 1;
 int n2 = right - mid;
 std::vector<int> leftArr(n1), rightArr(n2);
 for (i = 0; i < n1; i++)
 leftArr[i] = arr[left + i];
 for (j = 0; j < n2; j++)
 rightArr[j] = arr[mid + 1 + j];
 i = 0;
 j = 0;
 k = left;
 while (i < n1 && j < n2) {
 if (leftArr[i] <= rightArr[j]) {
 arr[k] = leftArr[i];
 i++;
 } else {
 arr[k] = rightArr[j];
 j++;
 }
 k++;
 }
 while (i < n1) {
 arr[k] = leftArr[i];
 i++;
 k++;
 }
 while (j < n2) {
 arr[k] = rightArr[j];
 j++;
 k++;
 }
}
void parallelMergeSort(std::vector<int>& arr, int left, int right) {
 if (left < right) {
 int mid = left + (right - left) / 2;
 #pragma omp parallel sections
 {
 #pragma omp section
 {
 parallelMergeSort(arr, left, mid);
 }
 #pragma omp section
 {
 parallelMergeSort(arr, mid + 1, right);
 }
 }
 merge(arr, left, mid, right);
 }
}
void parallelbubblesort(std::vector<int>& arr) {
 int n = arr.size();
 bool swapped;
 #pragma omp parallel
 {
 do {
 swapped = false;
 #pragma omp for
 for (int i = 0; i < n - 1; i++) {
 if (arr[i] > arr[i + 1]) {
 std::swap(arr[i], arr[i + 1]);
 swapped = true;
 }
 }
 } while (swapped);
 }
}
int main() {
 std::vector<int> numbers = {5, 2, 8, 12, 3};
 std::cout << "Before sorting: ";
 for (int num : numbers) {
 std::cout << num << " ";
 }
 std::cout << std::endl;
 parallelMergeSort(numbers, 0, numbers.size() - 1);
 std::cout << "After sorting: ";
 for (int num : numbers) {
 std::cout << num << " ";
 }
 std::cout << std::endl;
 std::vector<int> numbers1 = {5, 2, 8, 12, 3};
 std::cout << "Before sorting: ";
 for (int num : numbers1) {
 std::cout << num << " ";
 }
 parallelbubblesort(numbers1);
  std::cout << "After sorting: ";
 for (int num : numbers1) {
 std::cout << num << " ";
 }
 return 0;
}