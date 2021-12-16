#include <stdio.h>
#include "Week_1.h"
#define EXAMPLE_BUFFER_SIZE 25

int main() {
    uint8_t * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
    circular_buffer_handle_t circular_buffer = circular_buffer_init(buffer, EXAMPLE_BUFFER_SIZE);

    int full = circular_buffer_full(circular_buffer);
     int empty = circular_buffer_empty(circular_buffer);
    printf("Current buffer size: %zu\n", circular_buffer_size(circular_buffer));

    free(buffer);
    circular_buffer_free(circular_buffer);

    return 0;
}
