#include "sort.hpp"

void swap(int *a, int *b)
{
  int temp = (*a);
  (*a) = (*b);
  (*b) = temp;
}

void selectionSort(int *arr, int num)
{
  // Implement here
  int i, j;
  for (i=0; i<num-1; i++){
    int min =i;
    for (j=i+1; j<num; j++){
      if (arr[j] < arr[min]){
        min = j;
      }
    }
    // arr에 중복된 두 값이 있을 경우 -> 두 값을 swap (불필요한 수행임)
    swap(&arr[i], &arr[min]);
  }
}

void bubbleSort(int *arr, int num)
{
  // Implement here
  int i, j;
  for (i=num-1; i>0; i--){
    for (j=0; j<i; j++){
      if(arr[j] > arr[j+1]){
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}


void mergeSort(int* arr, int left, int right, int num) 
{
  // Implement here
  if (left < right) {
    // mid는 arr이 나누어지는 지점
    int mid = (left + right) / 2;

    mergeSort(arr, left, mid, num);
    mergeSort(arr, mid+1, right, num);

    // 정렬된 subarray를 Merge
    merge(arr, left, mid, right, num);
  }
}

void merge(int *arr, int left, int mid, int right, int num)
{
  // 나눠진 subarray들의 element 수 계산
  int n1 = mid - left + 1;
  int n2 = right - mid;

  // 하나의 array를 두개의 subarrays로 나눔 (array[left] ~ array[mid], array[mid+1] ~ array[right])
  int L[n1], M[n2];

  for (int i=0; i < n1; i++){
    L[i] = arr[left+i];
  }
 
  for (int j=0; j < n2; j++){
    M[j] = arr[mid+1+j];
  }

  // 현재의 ubarrays and 메인 array 인덱스 유지
  int i, j, k;
  i = 0;
  j = 0;
  k = left;

  // L 또는 M 의 마지막 element에 도달할 때까지, 더 큰 수를 선택하여 알맞은 곳에 정렬시킴
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  // L 또는 M의 element를 모두 정렬했으면, 남은 element들을 original array 뒤에 붙여줌
  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

