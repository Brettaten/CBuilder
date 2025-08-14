#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef struct List
{
    void **data;
    int size;
    int buffer;
    int length;
} List;

/**
 * Function used determine whether an index is in bounds
 *
 * @param pList pointer to the list
 * @param index position in the list
 *
 * @return true or false
 */
bool isIndexInBoundsList(List *pList, int index);

List *listCreate(int size)
{
    List *pList = (List *)malloc(sizeof(List));
    if (pList == NULL)
    {
        printf("[ERROR] : Memory allocation failed | listCreate \n");
        return NULL;
    }

    pList->data = (void **)malloc(sizeof(void *) * 8);
    if (pList->data == NULL)
    {
        free(pList);
        printf("[ERROR] : Memory allocation failed | listCreate \n");
        return NULL;
    }

    pList->buffer = 8;
    pList->length = 0;
    pList->size = size;

    return pList;
}

void *listGet(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listGet \n");
        return NULL;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listGet \n");
        return NULL;
    }

    void *value = pList->data[index];
    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | listGet \n");
        return NULL;
    }

    memcpy_s(cp, pList->size, value, pList->size);

    return cp;
}

int listSet(List *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listSet \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listSet \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listSet \n");
        return -1;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | listSet \n");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    void *lp = pList->data[index];

    free(lp);
    lp = NULL;

    pList->data[index] = cp;

    return 0;
}

int listAdd(List *pList, void *value)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listAdd \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listAdd \n");
        return -1;
    }

    if (pList->length == pList->buffer)
    {
        pList->data = (void **)realloc(pList->data, sizeof(void *) * pList->buffer * 2);
        if (pList->data == NULL)
        {
            printf("[ERROR] : Memory allocation failed | listAdd \n");
            return -1;
        }

        pList->buffer = pList->buffer * 2;
    }

    void *cp = (void *)malloc(pList->size);

    if (cp == NULL)
    {
        printf("[ERROR] : Memory allocation failed | listAdd \n");
        return -1;
    }
    memcpy_s(cp, pList->size, value, pList->size);

    pList->data[pList->length] = cp;
    pList->length++;

    return 0;
}

int listAddIndex(List *pList, void *value, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listAddIndex \n");
        return -1;
    }

    if (value == NULL)
    {
        printf("[WARN] : Pointer to value is NULL | listAddIndex \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listAddIndex \n");
        return -1;
    }

    void *p1 = pList->data[pList->length - 1];

    int st1 = listAdd(pList, p1);

    if (st1 == -1)
    {
        printf("[ERROR] : Function listAdd failed | listAddIndex \n");
        return -1;
    }

    for (int i = pList->length - 2; i > index; i--)
    {
        int st2 = listSwap(pList, i - 1, i);

        if (st2 == -1)
        {
            printf("[ERROR] : Function listSwap failed | listAddIndex \n");
            return -1;
        }
    }

    int st3 = listSet(pList, value, index);

    if (st3 == -1)
    {
        printf("[ERROR] : Function listSet failed | listAddIndex \n");
        return -1;
    }
    else
    {
        return 0;
    }
}

int listSwap(List *pList, int index1, int index2)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listSwap \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index1) || !isIndexInBoundsList(pList, index2))
    {
        printf("[INFO] : Index out of bounds | listSwap \n");
        return -1;
    }

    void *temp = pList->data[index1];
    pList->data[index1] = pList->data[index2];
    pList->data[index2] = temp;

    return 0;
}

List *listCopy(List *pList)
{
    if(pList == NULL){
        printf("[WARN] : Pointer to list is NULL | listCopy \n");
        return NULL;
    }

    List *listCpy = listCreate(pList->size);

    if(listCopy == NULL){
        printf("[ERROR] : Function listCreate failed | listCopy \n");
        return NULL;
    }

    for(int i = 0; i < pList->length; i++){
        void *temp;
        temp = listGet(pList, i);

        if(temp == NULL){
            printf("[ERROR] : Function listGet failed | listCopy \n");
            return NULL;
        }

        int st1 = listAdd(listCpy, temp);

        if(st1 == -1){
            printf("[ERROR] : Function listAdd failed | listCopy \n");
            return NULL;
        }

        free(temp);
    }
    
    return listCpy;
}

int listRemove(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listRemove \n");
        return -1;
    }

    if (!isIndexInBoundsList(pList, index))
    {
        printf("[INFO] : Index out of bounds | listRemove \n");
        return -1;
    }

    if (pList->length == 0)
    {
        printf("[INFO] : List is empty | listRemove");
        return -1;
    }

    for (int i = index + 1; i < pList->length; i++)
    {
        int st1 = listSwap(pList, i, i - 1);

        if (st1 == -1)
        {
            printf("[ERROR] : Function listSwap failed | listRemove \n");
            return -1;
        }
    }

    void *lastP = pList->data[pList->length - 1];

    free(lastP);
    lastP = NULL;
    pList->length--;

    return 0;
}

void listFree(List *pList)
{
    if (pList == NULL)
    {
        printf("[INFO] : Pointer to list is NULL | listFree \n");
        return;
    }

    for (int i = 0; i < pList->length; i++)
    {
        free(pList->data[i]);
    }

    free(pList->data);
    free(pList);
}

int listLength(List *pList)
{
    if (pList == NULL)
    {
        printf("[WARN] : Pointer to list is NULL | listLength \n");
        return -1;
    }

    return pList->length;
}

int listSize(List *pList)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | listSize \n");
        return -1;
    }

    return pList->size;
}

bool isIndexInBoundsList(List *pList, int index)
{
    if (pList == NULL)
    {
        printf("[ERROR] : Pointer to list is NULL | isIndexInBoundsList \n");
        return -1;
    }

    if (index < 0 || index >= pList->length)
    {
        return false;
    }
    return true;
}
