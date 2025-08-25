/**
 * Struct that represents a dynamic list
 *
 * @note Only use this list to store data that has the same size as specified.
 * @note Only store one data type in each list to be safe.
 * @note When storing elements, that itself contain dynamic memory, pass a pointer to
 *      a function that deep copies an element and to one that frees the element. Otherwise
 *      only shallow copies are stored in the list and the list is only freed shallowly, resulting
 *      undefined behaviour.
 */
typedef struct List List;

/**
 * Function that allocates memory for 8 void pointers
 *
 * @param size the size of the elements that will be stored in the list
 * @param copyElement pointer to a function that deep copies an element, pass NULL for elements, where a shallow copy is sufficient
 * @param freeElement pointer to a function that deep frees an element, pass NULL for elements, where a shallow free is sufficient
 *
 * @return Success: Pointer to the created list | Failure: NULL
 */
List *listCreate(int size, void *(*copyElement)(void *), void (*freeElement)(void *));

/**
 * Function used to retrieve the data stored in the list at the specified index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: Pointer to the data stored at the specified index | Failure: NULL
 *
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *listGet(List *pList, int index);

/**
 * Function used to replace the data at the specified index with a new value
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
int listSet(List *pList, void *value, int index);

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
 * @note When the allocated memory for the list is not large enough, the data gets reallocated
 * and is now able to hold twice as much memory.
 */
int listAdd(List *pList, void *value);

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
 * @note When using this function, the data that is located at the index or at a higher index
 * will be shifted to the next index to make room for the new value by swapping.
 */
int listAddIndex(List *pList, void *value, int index);

/**
 * Function used to swap two values
 *
 * @param pList pointer to the list
 * @param index1 first position in the list
 * @param index2 second position in the list
 *
 * @return Success: 0 | Failure: -1
 */
int listSwap(List *pList, int index1, int index2);

/**
 * Function used to create a deep copy of a list
 *
 * @param pList the pointer to the list
 *
 * @return Success: the copy of the list | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *listCopy(void *pList);

/**
 * Function used to remove the data at the specified index
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return Success: 0 | Failure: -1
 *
 * @note This function brings the value, that should be removed, to the end of the list by swapping
 * it with the next using swaps, before freeing it.
 */
int listRemove(List *pList, int index);

/**
 * Function used to return the length of the list
 *
 * @param pList pointer to the list
 *
 * @return Success: length | Failure: -1
 */
int listLength(List *pList);

/**
 * Function used to return the size of the data that the list stores
 *
 * @param pList pointer to the list
 *
 * @return Success: size | Failure: -1
 */
int listContentSize(List *pList);

/**
 * Function used to return the size of the a list struct
 *
 * @return Success: size
 */
int listSize();

/**
 * Function used to free the passed list
 *
 * @param pList pointer to the list
 *
 * @return void
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void listFree(void *pList);
