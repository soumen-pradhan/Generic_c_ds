#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"

Stack *Stack_init_(size_t typeSize) {
    Stack *stack = malloc(sizeof(Stack));
    stack->elem = malloc(typeSize);
    stack->size = 0;
    stack->cap = 1;
    stack->type = typeSize;

    return stack;
}

void Stack_resize_(Stack *stack, size_t maxElem) {
    stack->elem = realloc(stack->elem, stack->type * maxElem);
    stack->cap = maxElem;
}

void Stack_free(Stack *stack) {
    free(stack->elem);
    free(stack);
}

void Stack_push_(Stack *stack, void *data) {
    if (stack->size + 1 >= stack->cap) {
        Stack_resize_(stack, stack->cap*2);
    }

    memcpy(stack->elem + stack->type * stack->size, data, stack->type);
    stack->size++;
}

void Stack_pop_(Stack *stack, void *var) {
    if (stack->size == 0) {
        fprintf(stderr, "%s:\n%d:'%s': Stack Empty\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(var, stack->elem + stack->type * (stack->size - 1), stack->type);
    stack->size--;

    if (stack->size < stack->cap/2) {
        Stack_resize_(stack, stack->cap/2);
    }
}

void Stack_top_(Stack *stack, void *var) {
    if (stack->size == 0) {
        fprintf(stderr, "%s:\n%d:'%s': Stack Empty\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(var, stack->elem + stack->type * (stack->size - 1), stack->type);
}
