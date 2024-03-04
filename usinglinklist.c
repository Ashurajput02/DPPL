#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a node in the linked list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Function to create a new node with the given data
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a digit at the beginning of the linked list
void insertAtBeginning(Node **head, int data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

// Function to free the memory allocated for the linked list
void freeList(Node *head)
{
    Node *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Function to print the linked list representing a big number
void printList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to add two big numbers represented as linked lists
Node *add(Node *num1, Node *num2)
{
    Node *result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry != 0)
    {
        int sum = carry;
        if (num1 != NULL)
        {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL)
        {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum %= 10;

        insertAtBeginning(&result, sum);
    }

    return result;
}

// Function to subtract two big numbers represented as linked lists (num1 - num2)
Node *subtract(Node *num1, Node *num2)
{
    Node *result = NULL;
    int borrow = 0;

    while (num1 != NULL)
    {
        int diff = borrow + num1->data;
        if (num2 != NULL)
        {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0)
        {
            diff += 10;
            borrow = -1;
        }
        else
        {
            borrow = 0;
        }

        insertAtBeginning(&result, diff);
        num1 = num1->next;
    }

    // Remove leading zeros
    while (result != NULL && result->data == 0)
    {
        Node *temp = result;
        result = result->next;
        free(temp);
    }

    return result;
}

Node *multiply(Node *num1, Node *num2)
{
    // If either of the numbers is zero, return zero
    if (num1 == NULL || num2 == NULL)
    {
        Node *zero = createNode(0);
        return zero;
    }

    // Initialize result to store the product
    Node *result = createNode(0);

    // Temporary variables to store intermediate results
    Node *temp1 = num1, *temp2;
    Node *tempResult, *prev = NULL;
    int carry = 0, tempProduct;

    while (temp1 != NULL)
    {
        int digit = temp1->data;
        temp2 = num2;
        tempResult = createNode(0);

        // Append zeros for place value
        if (prev != NULL)
        {
            prev->next = tempResult;
        }

        while (temp2 != NULL || carry != 0)
        {
            tempProduct = carry + (temp2 ? (temp1->data * temp2->data) : 0);
            carry = tempProduct / 10;
            tempResult->data = tempProduct % 10;

            if (temp2)
            {
                temp2 = temp2->next;
            }

            if (temp2 != NULL || carry != 0)
            {
                tempResult->next = createNode(0);
                prev = tempResult;
                tempResult = tempResult->next;
            }
        }

        // Add the intermediate result to the final result
        result = add(result, reverse(tempResult));
        temp1 = temp1->next;
        carry = 0;
    }

    return result;
}

int main()
{
    Node *num1 = NULL;
    Node *num2 = NULL;

    // Add numbers to the linked lists (example numbers)
    insertAtBeginning(&num1, 9);
    insertAtBeginning(&num1, 9);
    insertAtBeginning(&num1, 9);

    insertAtBeginning(&num2, 1);
    insertAtBeginning(&num2, 2);
    insertAtBeginning(&num2, 3);

    printf("Number 1: ");
    printList(num1);
    printf("Number 2: ");
    printList(num2);

    // Add the numbers and print the result
    Node *sum = add(num1, num2);
    printf("Sum: ");
    printList(sum);

    // Free the memory allocated for the linked lists
    Node *difference = subtract(num1, num2);
    printf("Difference: ");
    printList(difference);

    Node *multi = multiply(num1, num2);
    printf("Multiplication: ");
    printList(multiply);

    // Free the memory allocated for the linked lists
    freeList(num1);
    freeList(num2);
    freeList(difference);
    freeList(sum);

    return 0;
}