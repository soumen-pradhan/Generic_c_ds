#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Vector.h"

Vector *Vector_init_(size_t typeSize) {
    Vector *vector = malloc(sizeof(Vector));
    vector->elem = malloc(typeSize);
    vector->size = 0;
    vector->cap = 1;
    vector->type = typeSize;

    return vector;
}

void Vector_resize_(Vector *vector, size_t maxElem) {
    vector->elem = realloc(vector->elem, maxElem*vector->type);
    vector->cap = maxElem;
}

void Vector_free(Vector *vector) {
    free(vector->elem);
    free(vector);
}

void Vector_copy(Vector *dest, Vector *src) {
    Vector_resize_(dest, src->cap * src->type);
    memcpy(dest->elem, src->elem, src->size * src->type);
    dest->size = src->size;
}

void Vector_push_(Vector *vector, void *data) {
    if (vector->size + 1 >= vector->cap) {
        Vector_resize_(vector, vector->cap*2);
    }
    memcpy(vector->elem + vector->type * vector->size, data, vector->type);
    vector->size++;
}

void Vector_push_vector(Vector *vector, Vector *insert) {
    size_t ogSize = vector->size;
    if (vector->cap <= vector->size + insert->size) {
        Vector_resize_(vector, (vector->size + insert->size) * 2);
    }

    memcpy(vector->elem + vector->type * ogSize, insert->elem, insert->size * insert->type);
    vector->size += insert->size;
}

void Vector_pop_(Vector *vector, void *var) {
    if (vector->size == 0) {
        fprintf(stderr, "%s:\n%d:'%s': Vector Empty\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(var, vector->elem + vector->type * (vector->size - 1), vector->type);
    vector->size--;

    if (vector->size < vector->cap/2) {
        Vector_resize_(vector, vector->cap/2);
    }
}


void Vector_back_(Vector *vector, void *var) {
    if (vector->size == 0) {
        fprintf(stderr, "%s:\n%d:'%s': Vector Empty\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(var, vector->elem + vector->type * (vector->size - 1), vector->type);
}

void Vector_access_(Vector *vector, size_t index, void *var) {
    if (index < 0 || index >= vector->size) {
        fprintf(stderr, "%s:\n%d:'%s': Index out of Bounds\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(var, vector->elem + vector->type * index, vector->type);
}

void Vector_insert_(Vector *vector, size_t index, void *var) {
    if (index < 0 || index >= vector->size) {
        fprintf(stderr, "%s:\n%d:'%s': Index out of Bounds\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(vector->elem + vector->type * index, var, vector->type);
}

void Vector_remove_index(Vector *vector, size_t index) {
    if (index < 0 || index >= vector->size) {
        fprintf(stderr, "%s:\n%d:'%s': Index out of Bounds\n", __FILE__, __LINE__, __func__);
        return;
    }

    memcpy(vector->elem + index, vector->elem + index + 1, vector->type * (vector->size - index - 1));
    vector->size--;

    if (vector->size < vector->cap/2) {
        Vector_resize_(vector, vector->cap/2);
    }
}