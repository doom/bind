/*
** Created by doom on 02/12/17.
*/

#include <stdio.h>
#include <string.h>
#include "bind.h"

typedef int (*pred_t)(const void *cur);

static void print_if(const void *const *data, size_t size, pred_t p)
{
    for (size_t i = 0; i < size; ++i) {
        if (p(data[i])) {
            puts(data[i]);
        }
    }
}

static int true_if_not_found(const void *data, const void *to_search)
{
    return strstr(data, to_search) == NULL;
}

static void print_some_ints(int i, int j, int k)
{
    printf("%d %d %d\n", i, j, k);
}

static void print_a_lot_of_ints(int a, int b, int c, int d, int e, int f)
{
    printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
}

int main(void)
{
    bind_t reject_lala = bind_new(&true_if_not_found, 1, "lala");
    bind_t print_lala = bind_new(&puts, 0, "lala");
    bind_t print_x23 = bind_new(&print_some_ints, 1, (void *)2, (void *)3);
    bind_t print_123 = bind_new(print_x23, 0, (void *)1);
    bind_t print_123456 = bind_new(&print_a_lot_of_ints, 0, (void *)1, (void *)2,
                                   (void *)3, (void *)4, (void *)5, (void *)6);

    if (!reject_lala || !print_lala || !print_x23 || !print_123 || !print_123456)
        return 1;

    print_if((const void *const[]){"This", "Is", "lalalala", "A", "Test"}, 5, reject_lala);

    ((void (*)(void))print_lala)();

    ((void (*)(int))print_x23)(42);
    ((void (*)(void))print_123)();

    ((void (*)(void))print_123456)();

    bind_delete(&reject_lala);
    bind_delete(&print_lala);
    bind_delete(&print_x23);
    bind_delete(&print_123);
    bind_delete(&print_123456);
    return 0;
}
