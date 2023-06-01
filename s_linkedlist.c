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
    if (slist == NULL || slist->tail == NULL)
    {
        return;
    }
    node_t *cur = slist->head;
    if (cur->data == ele)
    {
        delHead(slist);
    }
    while (cur->next != NULL && cur->next->data != ele)
    {
        cur = cur->next;
    }
    if (cur->next == NULL)
    {
        printf("Cannot find the element!\n");
        printf("\n");
        return;
    }

    node_t *del = cur->next;
    cur->next = cur->next->next;
    freeNode(del);
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

int main()
{
    slist_t *newList = makeSlist();
    // insert 23 at head, output should be '23'
    printf("%s\n", "add head 23: ");
    insertHead(newList, 23);
    printNode(newList->head);
    // insert 52 at head, output should be '23 -> 52'
    printf("%s\n", "add tail 52: ");
    insertTail(newList, 52);
    printNode(newList->head);
    printf("%s\n", "add tail 9: ");
    insertTail(newList, 9);
    printNode(newList->head);
    // insert 19 at pos 3, output should be '23 -> 52 -> 19 -> 9'
    printf("%s\n", "add 19 at position 3: ");
    insertMid(newList->head, 19, 3);
    printNode(newList->head);
    printf("%s\n", "add 7 at head and add 100 at tail: ");
    insertHead(newList, 7);
    insertTail(newList, 100);
    printNode(newList->head);
    // find the pos of 52, should return 3
    printf("%s\n", "find positon of 52:");
    printf("%d\n", searchPos(52, newList->head));
    printf("\n");
    // delete head, output should be '23 -> 52 -> 19 -> 9 -> 100'
    printf("%s\n", "delete head:");
    delHead(newList);
    printNode(newList->head);
    // delete tail, output should be '23 -> 52 -> 19 -> 9'
    printf("%s\n", "delete tail:");
    delTail(newList);
    printNode(newList->head);
    // delete 12 which doesn't exist, shout be an alert'
    printf("%s\n", "delete 12:");
    delMid(newList, 12);
    printNode(newList->head);
    // delete 52 which doesn't exist, shout be '23 -> 19 -> 9'
    printf("%s\n", "delete 52:");
    delMid(newList, 52);
    printNode(newList->head);

    freeAllNodeandList(newList);
    return 0;
}
