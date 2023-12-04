#include <stdio.h>
#include <stdlib.h>

// Node structure for a queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// Function to initialize an empty queue
void initializeQueue(Queue* q) {
    q->front = q->rear = NULL;
}

// Function to check if the queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Function to enqueue a new element
void enqueue(Queue* q, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Function to dequeue an element
int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1; // Return a sentinel value for an empty queue
    }

    Node* temp = q->front;
    int data = temp->data;

    q->front = temp->next;
    free(temp);

    if (q->front == NULL) {
        q->rear = NULL; // If the last element is dequeued, update rear
    }

    return data;
}

// Function to print the elements of the queue
void printQueue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Bubble sort on a given queue
void bubbleSort(Queue* q) {
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    // Check for empty or single-element queues
    if (isEmpty(q) || q->front == q->rear) {
        return;
    }

    do {
        swapped = 0;
        ptr1 = q->front;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                // Swap nodes if they are in the wrong order
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Insertion sort on a given queue
void insertionSort(Queue* q) {
    if (isEmpty(q) || q->front == q->rear) {
        return;
    }

    Queue sortedQueue;
    initializeQueue(&sortedQueue);

    while (!isEmpty(q)) {
        int current = dequeue(q);

        // Find the correct position in the sorted queue
        while (!isEmpty(&sortedQueue) && sortedQueue.rear->data < current) {
            enqueue(q, dequeue(&sortedQueue));
        }

        enqueue(&sortedQueue, current);
    }

    // Copy the sorted elements back to the original queue
    while (!isEmpty(&sortedQueue)) {
        enqueue(q, dequeue(&sortedQueue));
    }
}

// Selection sort on a given queue
void selectionSort(Queue* q) {
    Node* current = q->front;

    while (current != NULL) {
        Node* minNode = current;
        Node* temp = current->next;

        // Find the minimum element in the remaining unsorted part
        while (temp != NULL) {
            if (temp->data < minNode->data) {
                minNode = temp;
            }
            temp = temp->next;
        }

        // Swap the found minimum element with the current element
        int tempData = current->data;
        current->data = minNode->data;
        minNode->data = tempData;

        current = current->next;
    }
}

// Quick sort on a given queue
void quickSort(Queue* q) {
    if (isEmpty(q) || q->front == q->rear) {
        return; // Already sorted (or empty) queue
    }

    // Choose a pivot (for simplicity, let's use the front element)
    int pivot = dequeue(q);

    // Initialize two queues for elements less than the pivot and greater than the pivot
    Queue lessQueue, greaterQueue;
    initializeQueue(&lessQueue);
    initializeQueue(&greaterQueue);

    // Partition the queue into two sub-queues based on the pivot
    while (!isEmpty(q)) {
        int current = dequeue(q);
        if (current < pivot) {
            enqueue(&lessQueue, current);
        } else {
            enqueue(&greaterQueue, current);
        }
    }

    // Recursively sort the sub-queues
    quickSort(&lessQueue);
    quickSort(&greaterQueue);

    // Concatenate the sorted sub-queues and the pivot
    while (!isEmpty(&lessQueue)) {
        enqueue(q, dequeue(&lessQueue));
    }

    enqueue(q, pivot);

    while (!isEmpty(&greaterQueue)) {
        enqueue(q, dequeue(&greaterQueue));
    }
}

// Merge sort on a given queue
void mergeSort(Queue* q) {
    if (isEmpty(q) || q->front == q->rear) {
        return; // Already sorted (or empty) queue
    }

    // Divide the queue into two halves
    Queue leftQueue, rightQueue;
    initializeQueue(&leftQueue);
    initializeQueue(&rightQueue);

    int size = 0;
    Node* current = q->front;

    while (current != NULL) {
        size++;
        current = current->next;
    }

    int middle = size / 2;

    for (int i = 0; i < middle; i++) {
        enqueue(&leftQueue, dequeue(q));
    }

    while (!isEmpty(q)) {
        enqueue(&rightQueue, dequeue(q));
    }

    // Recursively sort the two halves
    mergeSort(&leftQueue);
    mergeSort(&rightQueue);

    // Merge the sorted halves
    while (!isEmpty(&leftQueue) && !isEmpty(&rightQueue)) {
        if (leftQueue.front->data < rightQueue.front->data) {
            enqueue(q, dequeue(&leftQueue));
        } else {
            enqueue(q, dequeue(&rightQueue));
        }
    }

    // Copy any remaining elements from the left queue
    while (!isEmpty(&leftQueue)) {
        enqueue(q, dequeue(&leftQueue));
    }

    // Copy any remaining elements from the right queue
    while (!isEmpty(&rightQueue)) {
        enqueue(q, dequeue(&rightQueue));
    }
}

// Bucket sort on a given queue
void bucketSort(Queue* q) {
    if (isEmpty(q) || q->front == q->rear) {
        return; // Already sorted (or empty) queue
    }

    // Find the maximum element in the queue
    int max = q->front->data;
    Node* current = q->front->next;

    while (current != NULL) {
        if (current->data > max) {
            max = current->data;
        }
        current = current->next;
    }

    // Create an array of queues (buckets)
    int bucketCount = max + 1;
    Queue buckets[bucketCount];

    for (int i = 0; i < bucketCount; i++) {
        initializeQueue(&buckets[i]);
    }

    // Distribute elements into buckets based on their value
    current = q->front;

    while (current != NULL) {
        enqueue(&buckets[current->data], current->data);
        current = current->next;
    }

    // Concatenate the elements from the buckets back into the original queue
    for (int i = 0; i < bucketCount; i++) {
        while (!isEmpty(&buckets[i])) {
            enqueue(q, dequeue(&buckets[i]));
        }
    }
}

int main() {
    Queue myQueue;
    initializeQueue(&myQueue);

    // Enqueue some elements to the queue
    enqueue(&myQueue, 5);
    enqueue(&myQueue, 2);
    enqueue(&myQueue, 8);
    enqueue(&myQueue, 1);
    enqueue(&myQueue, 6);

    printf("Original Queue: ");
    printQueue(&myQueue);

    // Call the sorting algorithms
    bubbleSort(&myQueue);
    printf("After Bubble Sort: ");
    printQueue(&myQueue);

    return 0;
}
