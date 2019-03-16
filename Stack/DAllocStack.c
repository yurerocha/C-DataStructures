/*
 * @author: yurerocha
 * @date: 02/17/19
 * 
 * Dynamically allocated stack for primitive 
 * data types implementation file
 */

#include "DAllocStack.h"

void StackInitializer (stack_t *stackPtr, size_t width) 
{
    stackPtr->val = NULL;
    stackPtr->top = STACK_INIT_TOP;
    stackPtr->size = 0;
    stackPtr->width = width;
}

void StackPush (stack_t *stackPtr, void *value, void (*CopyFunction)(void *destPtr, const void *srcPtr, int quant))
{
    unsigned char *bytePtr;

    // Allocates memory
    if (stackPtr->size == 0) {
        stackPtr->val = malloc (stackPtr->width);
        stackPtr->size++;
    } else if (stackPtr->top >= ((int) stackPtr->size) - 1) {
        void *temp = stackPtr->val;
        stackPtr->size *= 2;
        stackPtr->val = malloc (stackPtr->size * stackPtr->width);

        CopyFunction(stackPtr->val, temp, stackPtr->top + 1);
        /*
         * Why not to make a generic memcpy? Because it would waste too much time copying
         * large arrays. The better option is to make a pointer based copy function for each
         * data type;
         */
        free (temp);
    }

    // The char *bytePtr is necessary because of its one byte pointer arithmetic 
    bytePtr = stackPtr->val;
    stackPtr->top++;
    memcpy ((void *) (bytePtr + (stackPtr->top * stackPtr->width)), value, stackPtr->width);
}

bool_t StackPop (stack_t *stackPtr)
{
    if (StackEmpty (stackPtr)) {
        puts ("(!)stack underflow(!)");
        return FALSE;
    }
    else {
        stackPtr->top--;
        return TRUE;
    }
}

void *StackTop (stack_t *stackPtr)
{
    unsigned char *bytePtr = stackPtr->val;

    if (StackEmpty (stackPtr)) {
        puts ("(!)empty stack(!)");
        return NULL;
    } else
        return (bytePtr + (stackPtr->top * stackPtr->width));
}

bool_t StackEmpty (stack_t *stackPtr)
{
    return (stackPtr->top == STACK_INIT_TOP);
}

void StackDeallocateDataVal (stack_t *stackPtr)
{
    if (stackPtr->val)
        free (stackPtr->val);
}

void StackCopyInteger (void *destPtr, const void *srcPtr, int quant)
{
    int *toPtr, *fromPtr;

    fromPtr = (int *)srcPtr;
    toPtr = (int *)destPtr;

    for (int i = 0; i < quant; i++)
        *(toPtr++) = *(fromPtr++);

}

void StackCopyChar (void *destPtr, const void *srcPtr, int quant)
{
    char *toPtr, *fromPtr;

    fromPtr = (char *)srcPtr;
    toPtr = (char *)destPtr;

    for (int i = 0; i < quant; i++)
        *(toPtr++) = *(fromPtr++);

}

void StackCopyDouble (void *destPtr, const void *srcPtr, int quant)
{
    double *toPtr, *fromPtr;

    fromPtr = (double *)srcPtr;
    toPtr = (double *)destPtr;

    for (int i = 0; i < quant; i++)
        *(toPtr++) = *(fromPtr++);

}