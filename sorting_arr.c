#include <stdio.h>

// Function to swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 1. Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

// 2. Insertion Sort
void insertionSort(int arr[], int n) {
    int key, j;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 3. Selection Sort
void selectionSort(int arr[], int n) {
    int minIndex;
    for (int i = 0; i < n-1; i++) {
        minIndex = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[minIndex])
                minIndex = j;

        swap(&arr[minIndex], &arr[i]);
    }
}

// 4. Merge Sort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

// 5. Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 6. Bucket Sort
void bucketSort(int arr[], int n) {
    // Find maximum and minimum values in the array
    int max_val = arr[0];
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
        if (arr[i] < min_val)
            min_val = arr[i];
    }

    // Create buckets
    int range = max_val - min_val + 1;
    int buckets[range];
    for (int i = 0; i < range; i++)
        buckets[i] = 0;

    // Fill buckets
    for (int i = 0; i < n; i++)
        buckets[arr[i] - min_val]++;

    // Reconstruct the array
    int index = 0;
    for (int i = 0; i < range; i++)
        while (buckets[i] > 0) {
            arr[index++] = i + min_val;
            buckets[i]--;
        }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    // Choose the sorting algorithm to test
    // Uncomment the desired sorting algorithm

    // 1. Bubble Sort
    bubbleSort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);

    // 2. Insertion Sort
    insertionSort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);

    // 3. Selection Sort
    selectionSort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);

    // 4. Merge Sort
    mergeSort(arr, 0, n-1);
    printf("Sorted array: ");
    printArray(arr, n);

    // 5. Quick Sort
    quickSort(arr, 0, n-1);
    printf("Sorted array: ");
    printArray(arr, n);

    // 6. Bucket Sort
    bucketSort(arr, n);
    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
