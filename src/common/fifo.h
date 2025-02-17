#ifndef _BALU_FIFO_H
#define _BALU_FIFO_H

#include <stdint.h>

/**
 * @brief Fifo element struct to contain data stored in a fifo.
 *
 * This struct contains a void pointer pointing at a given data and contains a
 * size indicating the size of the data object. This struct is used to contain
 * data in a fifo instance.
 */
typedef struct {
    void*    data;
    uint16_t data_size;
} FifoElement;

/**
 * @brief General purpose fifo struct.
 *
 * The Fifo struct represents a general purpose fifo. Containing a FifoElement,
 * which contains the data in the fifo. The maximum size is given during
 * initialization, and the fifo is implemented as a ring buffer. The 'length'
 * member represents the size of the fifo. 'index' member is used to calculate
 * the current head, and items num containing the current amount of the
 * contained elements.
 */
typedef struct {
    FifoElement* list;
    uint32_t     length;
    uint32_t     index;
    uint32_t     items_num;
} Fifo;

/**
 * @brief Initialize fifo instance.
 *
 * The function initializes a fifo instance. The maximum amount of data is
 * set by the second parameter.
 *
 * @param fifo - Fifo* pointer to the fifo instance.
 * @param length - uint32_t maximum size of the fifo.
 *
 * @return int indicating error or success. Upon success, returns 0.
 */
int init_fifo(Fifo* fifo, uint32_t length);

/**
 * @brief Destroy fifo instance.
 *
 * The function destroys a fifo instance.
 *
 * @param fifo - Fifo* pointer to the fifo instance.
 *
 * @return int indicating error or success. Upon success, returns 0.
 */
int destroy_fifo(Fifo* fifo);

/**
 * @brief Push data to fifo.
 *
 * @param fifo - Fifo* pointer to the fifo instance.
 * @param data - void* pointer to data which should be copied into the fifo
 * @param data_size - uint32_t size of the data pointed by 'data'
 *
 * @return int indicating error or success. Upon success, returns 0.
 */
int fifo_push(Fifo* fifo, void* data, uint32_t data_size);

/**
 * @brief Destroy fifo instance.
 *
 * @param fifo - Fifo* pointer to the fifo instance.
 * @param data - void* pointer to a buffer given by the user for the fifo data.
 * @param data_size - uint32_t size of the data pointed by 'data'
 *
 * @return int indicating error or success. Upon success, returns 0.
 */
int fifo_pop(Fifo* fifo, void* data, uint32_t* size);

#endif
