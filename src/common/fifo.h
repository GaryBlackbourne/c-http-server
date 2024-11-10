#ifndef _BALU_FIFO_H
#define _BALU_FIFO_H

#include <stdint.h>

typedef struct {
    void* data;
    uint16_t data_size;
} FifoElement;

typedef struct {
    FifoElement* list;
    uint32_t length;
    uint32_t index;
    uint32_t items_num;
} Fifo;

int init_fifo(Fifo* fifo, uint32_t length);

int destroy_fifo(Fifo* fifo);

int fifo_push(Fifo* fifo, void* data, uint32_t data_size);

int fifo_pop(Fifo* fifo, void* data, uint32_t* size);

#endif
