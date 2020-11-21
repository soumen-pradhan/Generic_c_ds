#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// #define formatSpecifier(x) _Generic( (x), \
//     char: "%c", \
//     signed char: "%hhd", \
//     unsigned char: "%hhu", \
//     signed short: "%hd", \
//     unsigned short: "%hu", \
//     signed int: "%d", \
//     unsigned int: "%u", \
//     long int: "%ld", \
//     unsigned long int: "%lu", \
//     long long int: "%lld", \
//     unsigned long long int: "%llu", \
//     float: "%f", \
//     double: "%f", \
//     long double: "%Lf", \
//     char *: "%s", \
//     void *: "%p" )
// #define print(x) printf(formatSpecifier(x), x), putchar(' ')
// #define println(x) printf(formatSpecifier(x), x), putchar('\n')

// #define SWAP(type, x, y) { type __t = x; x = y; y = __t; }
// #define LESSER(x, y) ( (x<y) ? (1) : (0) )
// #define EQUAL(x, y) ( (x==y) ? (1) : (0) )

void print_array(int a[], int n) {
    for (int i = 0; i < n; ++i)
        print(a[i]);
    putchar('\n');
}

// Generic Stack

typedef struct _baseStack {
    void *elements;
    int size;
    int capacity;
} BaseStack;

#define Stack(type)\
    struct {\
        type *elements;\
        int size;\
        int capacity\
    } *

BaseStack *init_stack(size_t elementSize) {
    BaseStack *stack = malloc( sizeof(BaseStack) );
    stack->elements = malloc(elementSize);
    stack->size = 0;
    stack->capacity = 1;
    return stack;
}

void stack_resize(BaseStack *stack, size_t newSize) {
    stack->elements = realloc(stack->elements, newSize);
    stack->capacity = newSize;
}

void free_stack(BaseStack *stack) {
    free(stack->elements);
    free(stack);
}

#define newStack(type) ( Stack(type) ) init_stack(sizeof(type))

#define StackPush(stack, data) \
    if (stack->size + 1 >= stack->capacity) {\
        stack_resize(stack, stack->capacity*2);\
        stack->capacity *= 2;\
    }\
    stack->elements[stack->size] = data;\
    stack->size++;

#define StackPop(stack, var) \
    if (stack->size == 0) {\
        fprintf(stderr, "Stack Empty");\
    }\
    else {\
        var = stack->elements[ stack->size-1 ];\
        stack->size--;\
        if (stack->size < stack->capacity/2) {\
            stack_resize(stack, stack->capacity/2);\
            stack->capacity /= 2;\
        }\
    }

#define StackTop(stack, var) \
    if (stack->size == 0) {\
        fprintf(stderr, "Stack Empty");\
    }\
    else {\
        var = stack->elements[ stack->size-1 ];\
    }


// for initialization: Stack(data-type) {var-pointer} = mewStack(data-type); 

int main() {
    Stack(char) a = newStack(char);
    char pop;

    StackPush(a, 'b');
    StackPush(a, 'r');
    StackPush(a, 'u');

    StackTop(a, pop);
    printf("...pop: %c\n", pop);

    StackPop(a, pop);
    printf("__pop: %c\n", pop);
    StackPop(a, pop);
    printf("__pop: %c\n", pop);
    StackPop(a, pop);
    printf("__pop: %c\n", pop);
    StackPop(a, pop);
    printf("__pop: %c\n", pop);
    StackPop(a, pop);
    printf("__pop: %c\n", pop);
    
    StackPush(a, 'h');
    StackPop(a, pop);
    printf("__pop: %c\n", pop);

    free_stack(a);
}