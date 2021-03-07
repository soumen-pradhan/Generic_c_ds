#ifndef VECTOR_H
#define VECTOR_H

typedef struct _Vector {
    void *elem;
    size_t size, cap;
    size_t type;
} Vector;

// Memory Allocations

Vector *Vector_init_(size_t typeSize);
#define Vector_init(type) Vector_init_(sizeof(type))

void Vector_resize_(Vector *vector, size_t maxElem);
void Vector_free(Vector *vector);

// Copy a vector completely from dest to src
void Vector_copy(Vector *dest, Vector *src);

void Vector_push_(Vector *vector, void *data);
#define Vector_push(vec, data) Vector_push_(vec, &data)

// Push an entire vector at the end of another
void Vector_push_vector(Vector *vector, Vector *insert);

// Access last element and remove it
void Vector_pop_(Vector *vector, void *var);
#define Vector_pop(vec, var) Vector_pop_(vec, &var)

// Access last element
void Vector_back_(Vector *vector, void *var);
#define Vector_back(vec, var) Vector_back_(vec, &var)

// Access random element
void Vector_access_(Vector *vector, size_t index, void *var);
#define Vector_access(vec, idx, var) Vector_access_(vec, idx, &var)

// Modify element at random index
void Vector_insert_(Vector *vector, size_t index, void *data);
#define Vector_insert(vec, idx, data) Vector_insert_(vec, idx, &data)

// Remove element and shift elements at left
void Vector_remove_index(Vector *vector, size_t index);

#endif