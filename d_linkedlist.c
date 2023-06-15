#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *pre;
    struct node *next;
} node_t;

typedef struct dlist
{
    node_t *head;
    node_t *tail;
} dlist_t;

node_t *makeNode(int data)
{
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->data = data;
    return newNode;
}

dlist_t *makeDlist()
{
    dlist_t *newSlist = (dlist_t *)malloc(sizeof(dlist_t));
    if (newSlist == NULL)
    {
        return NULL;
    }
    newSlist->head = NULL;
    newSlist->tail = NULL;
    return newSlist;
}

void freeNode(node_t *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node);
}

void printNode(node_t *node)
{
    node_t *cur = node;
    while (cur->next != NULL)
    {
        printf("%d <--> ", cur->data);
        cur = cur->next;
    }
    printf("%d\n", cur->data);
    printf("\n");
}

void printNodeReverse(node_t *node)
{
    node_t* cur = node;
    while (cur != NULL){
            printf("%d ", cur->data);
            cur = cur->pre;
    }
    printf("\n");

}

int searchPos(int ele, node_t *cur)
{
    if (cur == NULL)
    {
        printf("Empty linked list!\n");
        return -1;
    }
    node_t *temp = cur;
    int pos = 1;
    while (temp != NULL)
    {
        if (temp->data == ele)
        {
            return pos;
        }
        temp = temp->next;
        pos++;
    }
    return -1;
}

void insertHead(dlist_t *slist, int element)
{
    if (slist == NULL)
    {
        return;
    }
    node_t *newNode = makeNode(element);
    if (newNode == NULL)
    {
        return;
    }
    if (slist->head == NULL && slist->tail == NULL)
    {
        slist->head = newNode;
        slist->tail = newNode;
    }
    else
    {
        newNode->next = slist->head;
        slist->head->pre = newNode;
        slist->head = newNode;
    }
}

void insertTail(dlist_t *slist, int element)
{
    if (slist == NULL)
    {
        return;
    }
    node_t *newNode = makeNode(element);
    if (newNode == NULL)
    {
        return;
    }
    if (slist->head == NULL && slist->tail == NULL)
    {
        slist->head = newNode;
        slist->tail = newNode;
    }
    else
    {
        slist->tail->next = newNode;
        newNode->pre = slist->tail;
        slist->tail = newNode;
    }
}

void insertMid(node_t *headNode, int element, int pos)
{
    if (pos < 1 || headNode == NULL){
        return;
    }
    node_t *cur = headNode;
    node_t *newNode = makeNode(element);
    if (pos == 1){
        newNode->next = cur;
        cur->pre = newNode;
        return;
    }
    for (int i = 1; i < pos && cur != NULL; i++){
        cur = cur->next;
    }
    if (cur == NULL){
        printf("Invalid position!\n");
        return;
    }

    newNode->next = cur;
    newNode->pre = cur->pre;
    cur->pre->next = newNode;
    cur->pre = newNode;
}


void delHead(dlist_t *slist)
{
    if (slist == NULL || slist->head == NULL)
    {
        return;
    }
    node_t *curHead = slist->head;
    slist->head = curHead->next;
    curHead->next->pre = NULL;
    free(curHead);
}

void delTail(dlist_t *slist)
{
    if (slist == NULL || slist->tail == NULL)
    {
        return;
    }
    node_t *del = slist->tail;
    slist->tail = del->pre;
    slist->tail->next = NULL;
    free(del);
}

void delMid(dlist_t *dlist, int ele)
{
    if (dlist == NULL || dlist->head == NULL)
    {
        return;
    }
    node_t *cur = dlist->head;
    while (cur != NULL && cur->data != ele) 
    {
        cur = cur->next;
    }
    if (cur == NULL)
    {
        printf("Cannot find the element!\n");
        return;
    }

    if (cur == dlist->head) {
        delHead(dlist);
        return;
    }
    
    if (cur == dlist->tail) {
        delTail(dlist);
        return;
    }

    node_t* del = cur;
    cur->pre->next = cur->next;
    cur->next->pre = cur->pre;
    freeNode(del);
}

void freeAllNodeandList(dlist_t *slist)
{
    node_t *cur = slist->head;
    while (cur != NULL)
    {
        node_t *nextNode = cur->next;
        free(cur);
        cur = nextNode;
    }
    free(slist);
}

int main() {
    dlist_t *newList = makeDlist();

    int choice;
    int value;
    int position;

    while (1) {
        printf("1. Add head\n");
        printf("2. Add tail\n");
        printf("3. Add at position\n");
        printf("4. Delete head\n");
        printf("5. Delete tail\n");
        printf("6. Delete of same value\n");
        printf("7. Search position\n");
        printf("8. Print reversed linkedlist\n");
        printf("9. Quit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to add at head: ");
                scanf("%d", &value);
                insertHead(newList, value);
                printNode(newList->head);
                break;

            case 2:
                printf("Enter value to add at tail: ");
                scanf("%d", &value);
                insertTail(newList, value);
                printNode(newList->head);
                break;

            case 3:
                printf("Enter value to add: ");
                scanf("%d", &value);
                printf("Enter position to add at: ");
                scanf("%d", &position);
                insertMid(newList->head, value, position);
                printNode(newList->head);
                break;

            case 4:
                delHead(newList);
                printNode(newList->head);
                break;

            case 5:
                delTail(newList);
                printNode(newList->head);
                break;

            case 6:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                delMid(newList, value);
                printNode(newList->head);
                break;


            case 7:
                printf("Enter value to search position: ");
                scanf("%d", &value);
                printf("Position of %d: %d\n", value, searchPos(value, newList->head));
                break;

            case 8:
                printf("Print linkedlist element in the reversed oder:\n");
                printNodeReverse(newList->tail);
                break;

            case 9:
                freeAllNodeandList(newList);
                return 0;
            

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

