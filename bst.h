#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the BST
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* create_node(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to perform in-order traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Function to perform pre-order traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform post-order traversal
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Function to search for a node with a given key
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

// Function to find the node with the minimum value
struct Node* find_min(struct Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to find the node with the maximum value
struct Node* find_max(struct Node* root) {
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

// Function to delete a node with a given key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        struct Node* temp = find_min(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to calculate the height of the tree
int height(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    int left_height = height(root->left);
    int right_height = height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

// Function to calculate the size (number of nodes) of the tree
int size(struct Node* root) {
    if (root == NULL) {
        return 0;
    }

    return 1 + size(root->left) + size(root->right);
}

void display_leaf_nonleaf_count(struct Node *root, int *leafCount, int *nonLeafCount) {
    if (root == NULL) {
        return;
    }

    if (root->left == NULL && root->right == NULL) {
        // Leaf node
        (*leafCount)++;
    } else {
        // Non-leaf node
        (*nonLeafCount)++;
    }

    // Recursively check left and right subtrees
    display_leaf_nonleaf_count(root->left, leafCount, nonLeafCount);
    display_leaf_nonleaf_count(root->right, leafCount, nonLeafCount);
}

void level_order_traversal(struct Node *root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for level order traversal
    struct Node *queue[100];
    int front = -1, rear = -1;

    // Enqueue the root
    queue[++rear] = root;

    while (front <= rear) {
        // Dequeue a node
        struct Node *current = queue[++front];

        // Process the current node
        printf("%d ", current->data);

        // Enqueue left child
        if (current->left != NULL) {
            queue[++rear] = current->left;
        }

        // Enqueue right child
        if (current->right != NULL) {
            queue[++rear] = current->right;
        }
    }
}

// Function to visualize the BST (ASCII-based)
void visualize_tree(struct Node *root, int space) {
    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space += 10;

    // Process right child first
    visualize_tree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->data);

    // Process left child
    visualize_tree(root->left, space);
}

// Function to check if the tree is empty
int is_empty(struct Node* root) {
    return root == NULL;
}

// Function to clear the entire tree
struct Node* clear(struct Node* root) {
    if (root != NULL) {
        root->left = clear(root->left);
        root->right = clear(root->right);
        free(root);
    }
    return NULL;
}
