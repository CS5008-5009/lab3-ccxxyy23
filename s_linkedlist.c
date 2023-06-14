#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

typedef struct slist
{
    node_t *head;
    node_t *tail;
} slist_t;

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

slist_t *makeSlist()
{
    slist_t *newSlist = (slist_t *)malloc(sizeof(slist_t));
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
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("%d\n", cur->data);
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

void insertHead(slist_t *slist, int element)
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
        slist->head = newNode;
    }
}

void insertTail(slist_t *slist, int element)
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
        slist->tail = newNode;
    }
}

void insertMid(node_t *headNode, int element, int pos)
{
    if (pos < 2 || headNode == NULL)
    {
        return;
    }
    node_t *cur = headNode;
    for (int i = 1; i < (pos - 1); i++)
    {
        if (cur == NULL)
        {
            return;
        }
        cur = cur->next;
    }

    node_t *newNode = makeNode(element);
    newNode->next = cur->next;
    cur->next = newNode;
}

void delHead(slist_t *slist)
{
    if (slist == NULL || slist->head == NULL)
    {
        return;
    }
    node_t *curHead = slist->head;
    slist->head = curHead->next;
    free(curHead);
}

void delTail(slist_t *slist)
{
    if (slist == NULL || slist->tail == NULL)
    {
        return;
    }
    node_t *cur = slist->head;
    node_t *del = slist->tail;
    while (cur->next != slist->tail)
    {
        cur = cur->next;
    }
    cur->next = NULL;
    slist->tail = cur;
    free(del);
}

void delMid(slist_t *slist, int ele)
{
    if (slist == NULL || slist->head == NULL)
    {
        return;
    }
    node_t *cur = slist->head;
    node_t *prev = NULL;
    if (cur->data == ele)
    {
        delHead(slist);
        return;
    }
    while (cur != NULL && cur->data != ele)
    {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL)
    {
        printf("Cannot find the element!\n\n");
        return;
    }
    if (cur == slist->tail)
    {
        slist->tail = prev;
        slist->tail->next = NULL;
    }
    else
    {
        prev->next = cur->next;
    }

    free(cur);
}


void freeAllNodeandList(slist_t *slist)
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
    slist_t *newList = makeSlist();

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
        printf("8. Quit\n");
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
                freeAllNodeandList(newList);
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}


