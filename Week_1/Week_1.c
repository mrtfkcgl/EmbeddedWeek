//
// Created by casper on 16.12.2021.
//

#include "Week_1.h"
#include "stdio.h"
#include "assert.h"
#include <stdlib.h>


#define false 0
#define FALSE false

struct circular_buffer_type
{
    uint8_t* buffer;
    size_t head;
    size_t tail;
    size_t max;
    _Bool full;
};
circular_buffer_handle_t circular_buffer_init(uint8_t* buffer,size_t size)
{
    assert(buffer && size);
    circular_buffer_handle_t circular_buffer = malloc(sizeof(circular_buffer_type));
    assert(circular_buffer);

    circular_buffer->buffer = buffer;
    circular_buffer->max = size;

    circular_buffer_reset(circular_buffer);
    assert(circular_buffer_empty(circular_buffer));

    return circular_buffer;
}

void circular_buffer_reset(circular_buffer_handle_t circular_buffer){
    assert(circular_buffer);

    circular_buffer->head = 0;
    circular_buffer->tail = 0;
    circular_buffer->full = false;
}

void circular_buffer_free(circular_buffer_handle_t circular_buffer)
{
    assert(circular_buffer);
    free(circular_buffer);
}

_Bool circular_buffer_full(const circular_buffer_handle_t const circular_buffer)
{
    assert(circular_buffer);
    return circular_buffer->full;
}
_Bool circular_buffer_empty(const circular_buffer_handle_t const circular_buffer)
{
    assert(circular_buffer);
    return (!circular_buffer->full && (circular_buffer->head == circular_buffer->tail));
}

size_t circular_buffer_capacity(const circular_buffer_handle_t const circular_buffer)
{
    assert(circular_buffer);
    return circular_buffer->max;
}
size_t circular_buffer_size(circular_buffer_handle_t circular_buffer)
{
    assert(circular_buffer);

    size_t size = circular_buffer->max;
    if(!circular_buffer->full)
    {
        if(circular_buffer->head >= circular_buffer->tail)
        {
            size = (circular_buffer->head - circular_buffer->tail);
        }
        else{
            size = (circular_buffer->max+circular_buffer-circular_buffer->tail);
        }
    }
    return size;
}


static inline size_t advance_headtail_value(size_t value, size_t max)
{
    return (value + 1) % max;
}

static void advance_head_pointer(circular_buffer_handle_t cbuf)
{
    assert(cbuf);

    if(circular_buffer_full(cbuf))
    {
        cbuf->tail = advance_headtail_value(cbuf->tail, cbuf->max);
    }

    cbuf->head = advance_headtail_value(cbuf->head, cbuf->max);
    cbuf->full = (cbuf->head == cbuf->tail);
}
/*expensice funciton */
/*
static void advance_pointer(circular_buffer_handle_t circular_buffer)
{
    assert(circular_buffer);

    if(circular_buffer->full)
    {
        circular_buffer->tail = (circular_buffer->tail +1 ) % circular_buffer->max;
    }
    circular_buffer->head = (circular_buffer->head + 1) % circular_buffer->max;
    circular_buffer->full = (circular_buffer->head == circular_buffer->tail);
}*/
static void advance_pointer(circular_buffer_handle_t circular_buffer)
{
    assert(circular_buffer);

    if(circular_buffer->full)
    {
        if (++(circular_buffer->tail) == circular_buffer->max)
        {
            circular_buffer->tail = 0;
        }
    }

    if (++(circular_buffer->head) == circular_buffer->max)
    {
        circular_buffer->head = 0;
    }
    circular_buffer->full = (circular_buffer->head == circular_buffer->tail);
}

void circular_buffer_put(circular_buffer_handle_t cbuf, uint8_t data)
{
    assert(cbuf && cbuf->buffer);

    cbuf->buffer[cbuf->head] = data;

    advance_head_pointer(cbuf);
}

int circular_buffer_try_put(circular_buffer_handle_t cbuf, uint8_t data)
{
    int r = -1;

    assert(cbuf && cbuf->buffer);

    if(!circular_buffer_full(cbuf))
    {
        cbuf->buffer[cbuf->head] = data;
        advance_head_pointer(cbuf);
        r = 0;
    }

    return r;
}

int circular_buf_get(circular_buffer_handle_t cbuf, uint8_t* data)
{
    assert(cbuf && data && cbuf->buffer);

    int r = -1;

    if(!circular_buffer_empty(cbuf))
    {
        *data = cbuf->buffer[cbuf->tail];
        cbuf->tail = advance_headtail_value(cbuf->tail, cbuf->max);
        cbuf->full = false;
        r = 0;
    }

    return r;
}




int circular_buf_peek(circular_buffer_handle_t cbuf, uint8_t* data, unsigned int look_ahead_counter)
{
    int r = -1;
    size_t pos;

    assert(cbuf && data && cbuf->buffer);

    // We can't look beyond the current buffer size
    if(circular_buffer_empty(cbuf) || look_ahead_counter > circular_buffer_size(cbuf))
    {
        return r;
    }

    pos = cbuf->tail;
    for(unsigned int i = 0; i < look_ahead_counter; i++)
    {
        data[i] = cbuf->buffer[pos];
        pos = advance_headtail_value(pos, cbuf->max);
    }

    return 0;
}