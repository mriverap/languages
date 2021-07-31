/* 
 - Creates a doubly linked list of integers
 - populates the list with 200 random values 
   between 0 and 49 (inclusive)
 - sorts the list using bubble sort
 - displays the list before and after sorting
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NODE_COUNT 200
#define MAX_NODE_VALUE 50

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;

/* Creates a struct node and populates 
its data with the parameter value */
node *createNode(int data)
{
    node *newNode = malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/* Appends a value 'data' to the linked list */
void appendToList(node *head, int data)
{
    node *currentPtr = head;
    while (currentPtr != NULL && currentPtr->next != NULL)
    {
        currentPtr = currentPtr->next;
    }

    currentPtr->next = createNode(data);
    currentPtr->next->prev = currentPtr;
}

/* Creates a linked list of nodes with 
the number of nodes passed in the parameter 
value nodeCount
*/
node *createRandomList(int nodeCount)
{
    time_t t;
    srand((unsigned)time(&t)); //seed the random function

    node *list = NULL;
    for (int i = 0; i < nodeCount; i++)
    {
        int data = rand() % MAX_NODE_VALUE;
        if (list == NULL)
            list = createNode(data);
        else
            appendToList(list, data);
    }

    return list;
}

/* Prints the list preceeded by a title */
void printList(char *title, node *head)
{
    printf("\n%s:\n", title);

    node *currentPtr = head;
    int k = 0;
    while (currentPtr != NULL)
    {
        printf("%2d  ", currentPtr->data);
        if (++k % 10 == 0)
            printf("\n");
        currentPtr = currentPtr->next != NULL ? currentPtr->next : NULL;
    }
}

/* Swap the values of two nodes */
void swapNodeValues(node *node1, node *node2)
{
    if (node1 == NULL || node2 == NULL)
        return;

    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

/* Sorts a list of nodes using bubble sort */
void sortList(node *head)
{
    int swaps = 0;           // keep track of the number of sorts done in a pass
    node *currentPtr = head; //create a pointer to the current node being examined

    //We use a do-while loop because we need to do at least one pass
    //this is the outer loop that continues until there are no more swaps
    do
    {
        swaps = 0;
        //the inner-while loop that swaps the values
        while (currentPtr->next != NULL)
        {
            if (currentPtr->data > currentPtr->next->data)
            {
                //if two consecutive nodes need to be swapped,
                //call the function and increment the swap counter
                swapNodeValues(currentPtr, currentPtr->next);
                swaps++;
            }

            //advance the current pointer to the next node
            currentPtr = currentPtr->next;
        }

        //when we are done with the inner loop, set the current
        //pointer to the first node again
        currentPtr = head;

    } while (swaps > 0);
}

void removeNode(node *node)
{
    if (node == NULL)
        return;

    //if the node is the first of the list,
    //set the second node's 'prev' value to NULL
    if(node->prev == NULL) {
        node->next->prev = NULL;
        return;
    }

    //if the node is the last of the list,
    //set the previous node's 'next' value to NULL
    if(node->next == NULL){
        node->prev->next = NULL;
        return;
    }

    //else, set previous node's next value to the 
    //node's next value and the next node's previous
    //to the previous node
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

/* Deduplicates the list passed as parameter
  by sorting first and then traversing the list
  and removing identical values
*/
void removeDuplicates(node *list)
{
    sortList(list);
    printList("Sorted list", list);

    node *currentPtr = list;

    while (currentPtr->next != NULL)
    {
        while (currentPtr->next != NULL && currentPtr->data == currentPtr->next->data)
        {
            removeNode(currentPtr->next);
        }

        currentPtr = currentPtr->next != NULL ? currentPtr->next : currentPtr;
    }
}

int main(void)
{
    const int SIZE = 200;
    node *list = createRandomList(NODE_COUNT);
    printList("Starting list", list);
    removeDuplicates(list);
    printList("Deduplicated list", list);

    return 0;
}