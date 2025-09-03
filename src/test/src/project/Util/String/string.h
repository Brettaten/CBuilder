#include <stdbool.h>

/**
 * Function that allocated memory for a string struct
 * 
 * @param pString an initial string that can be null
 * 
 * @return Success: Pointer to the created string | Failure: NULL
 */
char *stringCreate(char *pString);

/**
 * Function that adds a char to the end of the string
 * 
 * @param pString the pointer to the string
 * @param value the pointer to the char
 * 
 * @return Success: the new String | Failure: NULL
 * 
 * @note pString has to live on the heap
 */
char *stringAdd(char *pString, char value);

/**
 * Function that adds a char at the passed index
 * 
 * @param pString the pointer to the string
 * @param value the pointer to the char
 * @param index the index
 * 
 * @return Success: the new String | Failure: NULL
 * 
 * @note pString has to live on the heap
 */
char *stringAddIndex(char *pString, char value, int index);

/**
 * Function that swaps two chars
 * 
 * @param pString the pointer to the string
 * @param index1 the first index
 * @param index2 the second index
 * 
 * @return Success: 0 | Failure: -1
 * 
 * @note pString has to live on the heap
 */
int stringSwap(char *pString, int index1, int index2);

/**
 * Function that creates a deep copy of a string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: the copy of the string | Failure: NULL
 * 
 * @note Void datatypes are used for this function because one might
 *      store this struct inside this another struct and thus function pointers
 *      with void datatype are needed
 */
void *stringCopy(void *pString);

/**
 * Function that concatenates the passed strings
 * 
 * @param pStringDest the pointer to the destination
 * @param pStringSrc the pointer to the source
 * 
 * @return Success: the new String | Failure: NULL
 */
char *stringCat(char *pStringDest, char *pStringSrc);

/**
 * Function that clears the passed string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: the new String | Failure: NULL
 *  
 * @note pString has to live on the heap
 */
char *stringClear(char *pString);

/**
 * Function that returns a substring of an existing string
 * 
 * @param pString the pointer to the string
 * @param beginning the starting index (inclusive)
 * @param end the ending index (inclusive)
 * 
 * @return Success: a substring | Failure: NULL
 * 
 * @note pString has to live on the heap
 */
char *stringSub(char *pString, int beginning, int end);

/**
 * Function that replaces every destination string inside a string with the source string
 * 
 * @param pString the pointer to the string
 * @param pStringDest the destination string
 * @param pStringSrc the source string
 * 
 * @return Success: the new String | Failure: NULL
 * 
 * @note pString has to live on the heap
 */
char *stringReplace(char *pString, char *pStringDest, char *pStringSrc);

/**
 * Function that removes the char at the passed index
 * 
 * @param pString the pointer to the string
 * @param index the index
 * 
 * @return Success: the new String | Failure: NULL
 *
 * @note pString has to live on the heap
 */
char *stringRemove(char *pString, int index);
