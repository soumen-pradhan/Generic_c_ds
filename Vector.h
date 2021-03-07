#ifndef VECTOR_H
#define VECTOR_H

typedef struct _Vector {
    void *elem;
    size_t size, cap;
    size_t type;
} Vector;

Vector *Vector_init_(size_t typeSize);
void Vector_resize_(Vector *vector, size_t maxElem);
void Vector_free(Vector *vector);

void Vector_copy(Vector *dest, Vector *src);

void Vector_push_(Vector *vector, void *data);
void Vector_push_vector(Vector *vector, Vector *insert);
void Vector_pop_(Vector *vector, void *var);

void Vector_back_(Vector *vector, void *var);
void Vector_access_(Vector *vector, size_t index, void *var);
void Vector_insert_(Vector *vector, size_t index, void *data);
void Vector_remove_index(Vector *vector, size_t index);

#define Vector_init(type) Vector_init_(sizeof(type))

#define Vector_push(vec, data) Vector_push_(vec, &data)
#define Vector_pop(vec, var) Vector_pop_(vec, &var)

#define Vector_back(vec, var) Vector_back_(vec, &var)
#define Vector_access(vec, idx, var) Vector_access_(vec, idx, &var)
#define Vector_insert(vec, idx, data) Vector_insert_(vec, idx, &data)

#endif