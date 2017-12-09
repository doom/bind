/*
** Created by doom on 02/12/17.
*/

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "bind.h"

static const unsigned char movs[6][2] = {
    {0x48, 0xbf},
    {0x48, 0xbe},
    {0x48, 0xba},
    {0x48, 0xb9},
    {0x49, 0xb8},
    {0x49, 0xb9},
};

static size_t set_args_instr(void *op, size_t nb_before, void **args, size_t nb_args)
{
    size_t written = 0;

    for (size_t i = 0; i < nb_args; ++i) {
        memcpy(op + written, movs[nb_before + i], sizeof(movs[0]));
        memcpy(op + written + sizeof(movs[0]), args + i, sizeof(void *));
        written += sizeof(void *) + sizeof(movs[0]);
    }
    return written;
}

static const unsigned char rax_mov[2] = {0x48, 0xb8};

static const unsigned char rax_jmp[2] = {0xff, 0xe0};

static void set_call_instr(void *op, void *func)
{
    memcpy(op, rax_mov, sizeof(rax_mov));
    memcpy((char *)op + sizeof(rax_mov), &func, sizeof(void *));
    memcpy((char *)op + sizeof(rax_mov) + sizeof(void *), rax_jmp, sizeof(rax_jmp));
}

bind_t bind_new_(void *func, size_t nbargs_before, void **args, size_t nb)
{
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    char *ret;
    size_t offset;

    ret = mmap(NULL, page_size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (ret == MAP_FAILED)
        return NULL;

    offset = set_args_instr(ret, nbargs_before, args, nb);
    set_call_instr(ret + offset, func);

    mprotect(ret, page_size, PROT_EXEC | PROT_READ);
    return ret;
}

void bind_delete(bind_t *p_op)
{
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    munmap(*p_op, page_size);
}
