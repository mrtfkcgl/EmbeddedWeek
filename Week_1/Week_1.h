//
// Created by casper on 16.12.2021.
//

#ifndef WEEK1_DAY_1_WEEK_1_H
#define WEEK1_DAY_1_WEEK_1_H
#include<stdint.h>
/*FIFO buffer*/
#include "stdio.h"
#include "assert.h"
#include <stdlib.h>

typedef struct circular_buffer_type circular_buffer_type;
typedef circular_buffer_type* circular_buffer_handle_t;

circular_buffer_handle_t circular_buffer_init(uint8_t* buffer,size_t size);
void circular_buffer_free(circular_buffer_handle_t circular_buffer);
void circular_buffer_reset(circular_buffer_handle_t circular_buffer);
void circular_buffer_put(circular_buffer_handle_t circular_buffer,uint8_t data);
int circular_buffer_put2(circular_buffer_handle_t circular_buffer, uint8_t data);
int circular_buffer_get(circular_buffer_handle_t circular_buffer,uint8_t data);
_Bool circular_buffer_empty(circular_buffer_handle_t circular_buffer);
_Bool circular_buffer_full(circular_buffer_handle_t circular_buffer);






// User provides struct

/*
 * void circular_buf_init(circular_buffer_type* cbuf, uint8_t* buffer,
                       size_t size);
// Return a concrete struct
circular_buffer_type circular_buf_init(uint8_t* buffer, size_t size);

// Return a pointer to a struct instance - preferred approach
circular_buffer_handle_t circular_buf_init(uint8_t* buffer, size_t size);

*/






/*
 * for thread safe aproach we use full flag
 * */
size_t circular_buffer_capacity(circular_buffer_handle_t circular_buffer);
size_t circular_buffer_size(circular_buffer_handle_t circular_buffer);


#endif //WEEK1_DAY_1_WEEK_1_H
