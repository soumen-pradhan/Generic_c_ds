#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Interface for functions

typedef struct _baseVector {
    void *_elements;
    size_t _size;
    size_t _capacity;
} BaseVector;

#define Vector(type)\
    struct {\
        type *_elements;\
        size_t _size;\
        size_t _capacity;\
    } *


// Allocation functions

void *_vector_init(size_t element_size) {
    BaseVector *vector = malloc( sizeof(BaseVector) );
    vector->_elements = malloc(element_size);
    vector->_size = 0;
    vector->_capacity = 1;

    void *vec_return = vector;
    return vec_return;
}

void _vector_resize(void *vector, size_t new_size) {
    BaseVector *bVector = vector;
    bVector->_elements = realloc(bVector->_elements, new_size);
    bVector->_capacity = new_size;
}

void _vector_free(void *vector) {
    BaseVector *bVector = vector;
    free(bVector->_elements);
    free(bVector);
}

// Declare a Vector

#define new_Vector(type) _vector_init( sizeof(type) )

// Copy a vector contents to another. (Shallow Copy)

#define Vector_copy(dest, src) \
    do {\
        _vector_resize(dest, src->_capacity*sizeof( *(dest->_elements) ) );\
        memcpy( dest->_elements, src->_elements, src->_size*sizeof( *(dest->_elements) ) );\
        dest->_size = src->_size;\
    } while (false)

// Push a value at the end

#define Vector_push(vector, data) \
    do {\
        if (vector->_size + 1 >= vector->_capacity) {\
            _vector_resize(vector, vector->_capacity*2);\
        }\
        vector->_elements[vector->_size] = data;\
        vector->_size++;\
    } while (false)

// Push an entire vector at the end

#define Vector_push_vector(vector, push_vector) \
    do {\
        size_t _prev_size = vector->_size;\
        if (vector->_capacity <= push_vector->_size ) {\
            _vector_resize(vector, (vector->_size + push_vector->_size)*2);\
        }\
        memcpy( vector->_elements+_prev_size, push_vector->_elements, push_vector->_size*sizeof( *(vector->_elements) ) );\
        vector->_size += push_vector->_size;\
    } while (false)

// Remove and store the last element

#define Vector_pop(vector, var) \
    do {\
        if (vector->_size == 0) {\
            fprintf(stderr, "Stack Empty");\
        }\
        else {\
            var = vector->_elements[ vector->_size-1 ];\
            vector->_size--;\
            if (vector->_size < vector->_capacity/2) {\
                _vector_resize(vector, vector->_capacity/2);\
            }\
        }\
    } while (false)

// Store the last element

#define Vector_back(vector, var) \
    do {\
        if (stack->size == 0) {\
            fprintf(stderr, "Stack Empty\n");\
        }\
        else {\
            var = vector->_elements[ vector->_size-1 ];\
        }\
    } while (false)

// Random access at any index and store it

#define Vector_access(vector, index, var) \
    do {\
        if (index < 0 || index >= vector->_size) {\
            fprintf(stderr, "Index out of Bounds\n");\
        }\
        else {\
            var = vector->_elements[index];\
        }\
    } while (false)

// Remove any index and sift the elements up

#define Vector_remove_index(vector, index) \
    do {\
        if (index < 0 || index >= vector->_size) {\
            fprintf(stderr, "Index out of Bounds\n");\
        }\
        else {\
            memcpy( vector->_elements+index, vector->_elements+index+1, (vector->_size - index - 1)*sizeof( *(vector->_elements) ) );\
            vector->_size--;\
            if (vector->_size < vector->_capacity/2) {\
                _vector_resize(vector, vector->_capacity/2);\
            }\
        }\
    } while (false)

// Deallocate

#define Vector_free(vector) _vector_free(vector)


// Utility func. Has to be user defined.
void print_vec(void *vec) {
    BaseVector *v = vec;
    char *arr = v->_elements;

    for (int i = 0; i < v->_size; i++) printf("%c ", arr[i]);
    putchar('\n');
}

int main(int argc, char const *argv[]) {
    Vector(char) a = new_Vector(char);

    Vector_push(a, 'b');
    Vector_push(a, 'o');
    Vector_push(a, 'i');
    Vector_push(a, 'i');

    print_vec(a);

    Vector_remove_index(a, 0);

    print_vec(a);

    Vector(char) b = new_Vector(char);
    Vector_push(b, 'g');
    Vector_push(b, 'u');
    Vector_push(b, 'r');
    Vector_push(b, 'l');
    Vector_copy(a, b);

    Vector_push_vector(a, a);
    print_vec(a);

    Vector_free(a);
    Vector_free(b);
}