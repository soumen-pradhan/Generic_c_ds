#ifndef STACK_H
#define STACK_H

typedef struct _Stack {
    void *elem;
    size_t size, cap;
    size_t type;
} Stack;

// Stack Memory Allocations

Stack *Stack_init_(size_t typeSize);
#define Stack_init(type) Stack_init_(sizeof(type))

void Stack_resize_(Stack *stack, size_t maxElem);
void Stack_free(Stack *stack);

// Stack Operations

void Stack_push_(Stack *stack, void *data);
#define Stack_push(stack, data) Stack_push_(stack, &data)

void Stack_pop_(Stack *stack, void *var);
#define Stack_pop(stack, var) Stack_pop_(stack, &var)

void Stack_top_(Stack *stack, void *var);
#define Stack_top(stack, var) Stack_top_(stack, &var)

#endif

