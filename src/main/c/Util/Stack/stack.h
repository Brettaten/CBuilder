/**
 * Struct that represents a stack
 * 
 * @note Only use this stack to store data that has the same size as specified.
 * @note Only store one data type in each stack to be safe.
 * @note When storing elements, that itself contain dynamic memory, make sure to free it 
 * before freeing the element or the stack.
 */
typedef struct Stack Stack;

/**
 * Function that allocated memory for a stack struct
 * 
 * @param size the size of the elements that will be stored in the stack
 * 
 * @return Success: Pointer to the created stack | Failure: NULL
 */
Stack *stackCreate(int size);

/**
 * Function that adds an element to the stack
 * 
 * @param pStack the pointer to the stack
 * @param value the pointer to the element
 * 
 * @return Success: 0 | Failure: -1
 */
int stackPush(Stack *pStack, void *value);

/**
 * Function that removes an element from the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the pointer to the removed element | Failure: NULL
 */
void *stackPop(Stack *pStack);

/**
 * Function that retrieves the top element from the stack
 * 
 * @param pStack the pointer to the stack
 * 
 * @return Success: the pointer to top element | Failure: NULL
 */
void *stackPeek(Stack *pStack);

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
int stackSize(Stack *pStack);

/**
 * Function used to free the passed stack
 * 
 * @param pList the pointer to the stack
 * 
 * @note This function frees the pointers of the stored data. If a struct is stored, that itself contains a pointer, 
 * this pointer will not be freed.
 */
void stackFree(Stack *pStack);
