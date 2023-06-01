void delMid(slist_t *slist, int ele)
{
    if (slist == NULL || slist->tail == NULL)
    {
        return;
    }
    node_t *cur = slist->head;
    while (cur->next != NULL && cur->next->data != ele) 
    {
        cur = cur->next;
    }
    if (cur->next == NULL)
    {
        printf("Cannot find the element!\n");
        return;
    }

    node_t* del = cur->next;
    cur->next = cur->next->next;
    freeNode(del);
}