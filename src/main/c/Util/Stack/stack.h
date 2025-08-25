/**
 * Struct that represents a stack
 * 
 * @note Only use this stack to store data that has the same size as specified.
 * @note Only store one data type in each stack to be safe.
 */
typedef struct Stack Stack;

/**
 * Function that allocated memory for a stack struct
 * 
 * @param size the size of the elements that will be stored in the stack
 * @param copyElement pointer to a function that deep copies an element, pass NULL for elements, where a shallow copy is sufficient
 * @param freeElement pointer to a function that deep frees an element, pass NULL for elements, where a shallow free is sufficient
 * 
 * @return Success: Pointer to the created stack | Failure: NULL
 */
Stack *stackCreate(int size, void *(*copyElement)(void *), void(*freeElement)(void *));

/**
 * Function that adds an element to the stack
 * 
 * @param pStack the pointer to the stack
 * @param value the pointer to the element
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note The passed value does not have to be allocated on the heap.
 * The function creates a deep copy of the value before adding it to the list.
 */
int stackPush(Stack *pStack, void *value);

/**
 * Function that removes an element from the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the pointer to the removed element | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *stackPop(Stack *pStack);

/**
 * Function that retrieves the top element from the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the pointer to top element | Failure: NULL
 * 
 * @note The returned pointer is a deep copy and thus, has to be freed by the caller
 */
void *stackPeek(Stack *pStack);

/**
 * Function used to create a deep copy of a stack
 *
 * @param pStack the pointer to the stack
 *
 * @return Success: the copy of the stack | Failure: NULL
 *
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void *stackCopy(void *pStack);

/**
 * Function that returns the length of the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the length of the stack | Failure: -1
 */
int stackLength(Stack *pStack);

/**
 * Function that returns the size of the data that is stored in the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the size | Failure: -1
 */
int stackContentSize(Stack *pStack);

/**
 * Function that returns the size of a stack struct
 * 
 * @return Success: the size
 */
int stackSize();

/**
 * Function used to free the passed stack
 * 
 * @param pList the pointer to the stack
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this struct and thus function pointers
 *      with void datatype are needed
 */
void stackFree(void *pStack);
