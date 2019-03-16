/*
 * @author: yurerocha
 * @date: 02/17/19
 * 
 * Dynamically allocated stack for primitive 
 * data types implementation header
 */

#ifndef D_ALLOC_STACK_H
#define D_ALLOC_STACK_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define STACK_INIT_TOP -1

    typedef enum Bool {
        FALSE = 0, TRUE
    } bool_t;

    typedef struct Stack {
        void *val;
        int top;
        size_t width;
        size_t size;
    } stack_t;

    /*
    * Before using the stack, it is necessary to properly initialize its variables. width is the
    * sizeof(dataType) you want to manipulate.
    */
    void StackInitializer (stack_t *stackPtr, size_t width);

    /*
    * Pushes a new value into the stack. It is necessary to implement a pointer based array copy function 
    * for each data type to be manipulated. It helps not to waste too much time copying large arrays.
    */
    void StackPush (stack_t *stackPtr, void *value, void (*CopyFunction)(void *destPtr, const void *srcPtr, int quant));

    /*
    * Pops the topmost element of the stack. Returns: TRUE, successfully popped; FALSE, stack underflow.
    */
    bool_t StackPop (stack_t *stackPtr);

    /*
    * Returns the address of the topmost element of the stack; NULL, if the stack is empty.
    */
    void *StackTop (stack_t *stackPtr);

    /*
    * Verify whether the stack is empty. Returns TRUE or FALSE.
    */
    bool_t StackEmpty (stack_t *stackPtr);

    /*
    * It deallocates the memory of the void *val and the void *val ONLY.
    */
    void StackDeallocateDataVal (stack_t *stackPtr);

    /*
    * Three pointer based array copy functions are already implemented.
    */
    void StackCopyInteger (void *destPtr, const void *srcPtr, int quant);
    void StackCopyChar (void *destPtr, const void *srcPtr, int quant);
    void StackCopyDouble (void *destPtr, const void *srcPtr, int quant);
#endif 