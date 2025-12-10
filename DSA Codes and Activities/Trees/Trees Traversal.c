// Iterative Traversal of a Binary Search Tree (BST) in C

// Iterative inorder traversal
void inorderTraversal(BST tree) {
    Stack *stack = createStack();
    BST current = tree;
    
    while (current != NULL || !isEmpty(stack)) {
        // Reach the leftmost node of the current node
        while (current != NULL) {
            push(stack, current);
            current = current->LC;
        }
        
        // Current must be NULL at this point
        current = pop(stack);
        printf("\"%s\" ", current->key);
        
        // Visit the right subtree
        current = current->RC;
    }
}

// Iterative preorder traversal
void preorderTraversal(BST tree) {
    if (tree == NULL) return;
    
    Stack *stack = createStack();
    push(stack, tree);
    
    while (!isEmpty(stack)) {
        BST current = pop(stack);
        printf("\"%s\" ", current->key);
        
        // Push right child first so left child is processed first (LIFO)
        if (current->RC != NULL) {
            push(stack, current->RC);
        }
        if (current->LC != NULL) {
            push(stack, current->LC);
        }
    }
}

// Iterative postorder traversal (using two stacks)
void postorderTraversal(BST tree) {
    if (tree == NULL) return;
    
    Stack *stack1 = createStack();
    Stack *stack2 = createStack();
    
    push(stack1, tree);
    
    while (!isEmpty(stack1)) {
        BST current = pop(stack1);
        push(stack2, current);
        
        if (current->LC != NULL) {
            push(stack1, current->LC);
        }
        if (current->RC != NULL) {
            push(stack1, current->RC);
        }
    }
    
    // Print all nodes from stack2
    while (!isEmpty(stack2)) {
        BST current = pop(stack2);
        printf("\"%s\" ", current->key);
    }
}

// Alternative postorder traversal (using one stack)
void postorderTraversalOneStack(BST tree) {
    if (tree == NULL) return;
    
    Stack *stack = createStack();
    BST current = tree;
    BST lastVisited = NULL;
    
    while (!isEmpty(stack) || current != NULL) {
        if (current != NULL) {
            push(stack, current);
            current = current->LC;
        } else {
            BST peekNode = peek(stack); // Look at top without popping
            
            // If right child exists and hasn't been visited yet
            if (peekNode->RC != NULL && lastVisited != peekNode->RC) {
                current = peekNode->RC;
            } else {
                printf("\"%s\" ", peekNode->key);
                lastVisited = pop(stack);
            }
        }
    }
}