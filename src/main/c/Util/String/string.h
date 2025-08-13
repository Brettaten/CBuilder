#include <stdbool.h>
/**
 * Struct that represents a string
 */
typedef struct String String;

/**
 * Function that allocated memory for a string struct
 * 
 * @param charArr an initial string that can be null
 * 
 * @return Success: Pointer to the created string | Failure: NULL
 */
String *stringCreate(char *charArr);

/**
 * Function that adds a char to the end of the string
 * 
 * @param pString the pointer to the string
 * @param value the pointer to the char
 * 
 * @return Success: 0 | Failure: -1
 */
int stringAdd(String *pString, char value);

/**
 * Function that adds a char at the passed index
 * 
 * @param pString the pointer to the string
 * @param value the pointer to the char
 * @param index the index
 * 
 * @return Success: 0 | Failure: -1
 */
int stringAddIndex(String *pString, char value, int index);

/**
 * Function that gets the char at the passed index
 * 
 * @param pString the pointer to the string
 * @param index the index
 * 
 * @return Success: the char | Failure: -1
 */
char stringGet(String *pString, int index);

/**
 * Function that sets the char at the passed index
 * 
 * @param pString the pointer to the string
 * @param value the pointer to the char
 * @param index the index
 * 
 * @return Success: 0 | Failure: -1
 */
int stringSet(String *pString, char value, int index);

/**
 * Function that swaps two chars
 * 
 * @param pString the pointer to the string
 * @param index1 the first index
 * @param index2 the second index
 * 
 * @return Success: 0 | Failure: -1
 */
int stringSwap(String *pString, int index1, int index2);

/**
 * Function that concatenates the passed strings
 * 
 * @param pStringDest the pointer to the destination
 * @param pStringSrc the pointer to the source
 * 
 * @return Success: 0 | Failure: -1
 */
int stringCat(String *pStringDest, String *pStringSrc);

/**
 * Function that creates a deep copy of a string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: the copy of the string | Failure: NULL
 */
String *stringCopy(String *pString);

/**
 * Function that clears the passed string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: 0 | Failure: -1
 */
int stringClear(String *pString);

/**
 * Function that returns a substring of an existing string
 * 
 * @param pString the pointer to the string
 * @param beginning the starting index (inclusive)
 * @param end the ending index (inclusive)
 * 
 * @return Success: a substring | Failure: NULL
 */
String *stringSub(String *pString, int beginning, int end);

/**
 * Function that replaces every destination string inside a string with the source string
 * 
 * @param pString the pointer to the string
 * @param pStringDest the destination string
 * @param pStringSrc the source string
 * 
 * @return Success: 0 | Failure: -1
 */
int stringReplace(String *pString, String *pStringDest, String *pStringSrc);

/**
 * Function that checks whether two strings are equal or not
 * 
 * @param pString1 the pointer to the first string
 * @param pString2 the pointer to the second string
 * 
 * @return Success: true | Failure: false
 */
bool stringEquals(String *pString1, String *pString2);

/**
 * Function that returns the corresponding char array of the passed string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: a pointer to the char array | Failure: NULL
 */
char *stringToArr(String *pString);

/**
 * Function that removes the char at the passed index
 * 
 * @param pString the pointer to the string
 * @param index the index
 * 
 * @return Success: 0 | Failure: -1
 */
int stringRemove(String *pString, int index);

/**
 * Function that returns the length of the string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: the length of the string | Failure: -1
 */
int stringLength(String *pString);

/**
 * Function that returns the size of the data that is stored in the string
 * 
 * @param pString the pointer to the string
 * 
 * @return Success: the size | Failure: -1
 */
int stringSize(String *pString);

/**
 * Function used to free the passed string
 * 
 * @param pList the pointer to the string
 */
void stringFree(String *pString);
