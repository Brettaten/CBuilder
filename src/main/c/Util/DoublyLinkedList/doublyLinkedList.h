/**
 * Struct that represents a doubly linked list
 *
 * @note Only use this list to store data that has the same size as specified.
 * @note Only store one data type in each list to be safe.
 * @note When storing elements, that itself contain dynamic memory, make sure to free it
 * before freeing the element or the list.
 */
typedef struct DoublyLinkedList DoublyLinkedList;

/**
 * Struct that represents node of a singly linked list
 */
typedef struct DoublyLinkedListNode DoublyLinkedListNode;

/**
 * Function that allocated memory for a doubly linked list struct
 *
 * @param size the size of the elements that will be stored in the list
 *
 * @return Success: Pointer to the created list | Failure: NULL
 */
DoublyLinkedList *doublyLinkedListCreate(int size);

/**
 * Function that retrieves the element of the list at the passed index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: Pointer to the element at the passed index | Failure: NULL
 *
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *doublyLinkedListGet(DoublyLinkedList *pList, int index);

/**
 * Function that replaces the element of the list at the passed index with a new one
 *
 * @param pList pointer to the list
 * @param value pointer to the element that should replace the old element
 * @param index position in the list
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int doublyLinkedListSet(DoublyLinkedList *pList, void *value, int index);

/**
 * Function used to add the passed value to the end of the list
 *
 * @param pList pointer to the list
 * @param value pointer to a value
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int doublyLinkedListAdd(DoublyLinkedList *pList, void *value);

/**
 * Function used to add the passed value at a specific index
 *
 * @param pList pointer to the list
 * @param value pointer to a value
 * @param index position in the list
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int doublyLinkedListAddIndex(DoublyLinkedList *pList, void *value, int index);

/**
 * Function used to remove the data at the specified index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: 0 | Failure: -1
 *
 * @note This function only frees the pointer. If a struct is stored, that itself contains a pointer,
 * this pointer will not be freed.
 */
int doublyLinkedListRemove(DoublyLinkedList *pList, int index);

/**
 * Function used to return the length of the list
 *
 * @param pList pointer to the list
 *
 * @return Success: length | Failure: -1
 */
int doublyLinkedListLength(DoublyLinkedList *pList);

/**
 * Function used to return the size of the data that the list stores
 *
 * @param pList pointer to the list
 *
 * @return Success: size | Failure: -1
 */
int doublyLinkedListSize(DoublyLinkedList *pList);

/**
 * Function used to return the head of the list
 *
 * @param pList pointer to the list
 *
 * @return Success: pointer to the head of the list | Failure: NULL
 *
 * @note This function is used to get the head of the list. This is useful for traversing the list.
 */
DoublyLinkedListNode *doublyLinkedListGetHead(DoublyLinkedList *pList);

/**
 * Function used to return the tail of the list
 *
 * @param pList pointer to the list
 *
 * @return Success: pointer to the tail of the list | Failure: NULL
 *
 * @note This function is used to get the tail of the list. This is useful for traversing the list.
 */
DoublyLinkedListNode *doublyLinkedListGetTail(DoublyLinkedList *pList);

/**
 * Function used to get the next node
 *
 * @param pNode pointer to the node
 *
 * @return Success: pointer to the next node | Failure: NULL
 */
DoublyLinkedListNode *doublyLinkedListNodeNext(DoublyLinkedListNode *pNode);

/**
 * Function used to get the previous node
 *
 * @param pNode pointer to the node
 *
 * @return Success: pointer to the previous node | Failure: NULL
 */
DoublyLinkedListNode *doublyLinkedListNodePrev(DoublyLinkedListNode *pNode);

/**
 * Function used to get the value of a node
 *
 * @param pList pointer to the list
 * @param pNode pointer to the node
 *
 * @return Success: value of the node | Failure: NULL
 *
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *doublyLinkedListNodeGet(DoublyLinkedList *pList, DoublyLinkedListNode *pNode);

/**
 * Function used to set the value of a node directly
 *
 * @param pList pointer to the list
 * @param pNode pointer to the list
 * @param value ponter to the value
 *
 * @return Success: 0 | Failure: -1
 *
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int doublyLinkedListNodeSet(DoublyLinkedList *pList, DoublyLinkedListNode *pNode, void *value);

/**
 * Function used to free the passed list
 *
 * @param pList pointer to the list
 *
 * @return void
 *
 * @note This function frees the pointers of the stored data. If a struct is stored, that itself contains a pointer,
 * this pointer will not be freed.
 */
void doublyLinkedListFree(DoublyLinkedList *pList);