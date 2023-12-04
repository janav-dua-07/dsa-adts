#include <stdio.h>
#include <stdlib.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to print the linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Bubble Sort for Linked List
void bubbleSort(Node* head) {
    int swapped, temp;
    Node* current;
    Node* last = NULL;

    if (head == NULL)
        return;

    do {
        swapped = 0;
        current = head;

        while (current->next != last) {
            if (current->data > current->next->data) {
                // Swap the data
                temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Insertion Sort for Linked List
void insertionSort(Node** head_ref) {
    Node* sorted = NULL;
    Node* current = *head_ref;

    while (current != NULL) {
        Node* next = current->next;
        if (sorted == NULL || sorted->data >= current->data) {
            // Insert at the beginning
            current->next = sorted;
            sorted = current;
        } else {
            // Find the correct position to insert
            Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }

    *head_ref = sorted;
}

// Selection Sort for Linked List
void selectionSort(Node* head) {
    Node* current = head;

    while (current != NULL) {
        Node* min = current;
        Node* temp = current->next;

        while (temp != NULL) {
            if (temp->data < min->data) {
                min = temp;
            }
            temp = temp->next;
        }

        // Swap data
        int tempData = current->data;
        current->data = min->data;
        min->data = tempData;

        current = current->next;
    }
}

// Merge Sort for Linked List
Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    Node* result = NULL;

    if (left->data <= right->data) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }

    return result;
}

Node* getMiddle(Node* head) {
    if (head == NULL)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    Node* middle = getMiddle(head);
    Node* nextOfMiddle = middle->next;

    middle->next = NULL;

    Node* left = mergeSort(head);
    Node* right = mergeSort(nextOfMiddle);

    return merge(left, right);
}

// Bucket Sort for Linked List
void bucketSort(Node** head_ref, int numBuckets) {
    if (*head_ref == NULL)
        return;

    Node* buckets[numBuckets];
    for (int i = 0; i < numBuckets; ++i) {
        buckets[i] = NULL;
    }

    // Distribute elements into buckets
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next = current->next;
        int index = (current->data) % numBuckets;
        current->next = buckets[index];
        buckets[index] = current;
        current = next;
    }

    // Sort each bucket individually
    for (int i = 0; i < numBuckets; ++i) {
        insertionSort(&buckets[i]);
    }

    // Concatenate buckets
    *head_ref = NULL;
    Node* tail = NULL;
    for (int i = 0; i < numBuckets; ++i) {
        if (buckets[i] != NULL) {
            if (*head_ref == NULL) {
                *head_ref = buckets[i];
            } else {
                tail->next = buckets[i];
            }
            tail = buckets[i];
            while (tail->next != NULL) {
                tail = tail->next;
            }
        }
    }
}

// Function to free the linked list
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;  // Initialize an empty linked list

    // Example of using insertAtBeginning function
    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 8);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 5);

    printf("Original Linked List: ");
    printList(head);

    /* Example of using each sorting algorithm
    printf("\nSorting using Bubble Sort:\n");
    bubbleSort(head);
    printList(head); */

    /* Reset the linked list
    freeList(head);

    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 8);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 5);
    printf("\nSorting using Insertion Sort:\n");
    insertionSort(&head);
    printList(head); */

    /* Reset the linked list
    freeList(head);

    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 8);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 5);
    printf("\nSorting using Selection Sort:\n");
    selectionSort(head);
    printList(head); */

    /* Reset the linked list
    freeList(head);

    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 8);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 5);
    printf("\nSorting using Merge Sort:\n");
    head = mergeSort(head);
    printList(head); */

    /* Reset the linked list
    freeList(head);

    insertAtBeginning(&head, 7);
    insertAtBeginning(&head, 1);
    insertAtBeginning(&head, 8);
    insertAtBeginning(&head, 3);
    insertAtBeginning(&head, 5);
    printf("\nSorting using Bucket Sort:\n");
    bucketSort(&head, 5);
    printList(head); */

    // Free the memory allocated for the linked list
    freeList(head);

    return 0;
}