/*
** Created by doom on 02/12/17.
*/

#ifndef BIND_H
#define BIND_H

#include <stddef.h>

typedef void *bind_t;

#define __array_len(arr)        (sizeof(arr) / sizeof((arr)[0]))

#define bind_new(f, nb_before, ...)                                         \
    bind_new_(f, nb_before, (void *[]){__VA_ARGS__},                        \
    __array_len(((void *[]){__VA_ARGS__})))

bind_t bind_new_(void *func, size_t nbargs_before, void **args, size_t nb);

void bind_delete(bind_t *p_op);

#endif /* !BIND_H */
