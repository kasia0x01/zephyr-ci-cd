#include <stdio.h>
#include "ring_buffer.h"

#define BUF_CAPACITY 8

static uint8_t storage[BUF_CAPACITY];

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	ring_buf_t rb;
	rb_init(&rb, storage, BUF_CAPACITY);

	for (uint8_t i = 1; i <= 5; i++) {
		rb_push(&rb, i * 10);
	}

	uint8_t val;
	size_t popped = 0;
	while (rb_pop(&rb, &val)) {
		printf("  popped: %u\n", val);
		popped++;
	}

	printf("Popped %zu elements\n", popped);

	return 0;
}
