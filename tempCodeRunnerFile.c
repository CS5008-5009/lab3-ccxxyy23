// delete 12 which doesn't exist, shout be an alert'
    printf("%s\n", "delete 12:");
    delMid(newList, 12);
    printNode(newList->head);
    // delete 52 which doesn't exist, shout be '23 -> 19 -> 9'
    printf("%s\n", "delete 52:");
    delMid(newList, 52);
    printNode(newList->head);