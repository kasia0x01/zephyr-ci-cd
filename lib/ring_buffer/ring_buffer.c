/* SPDX-License-Identifier: Apache-2.0 */
#include "ring_buffer.h"

void rb_init(ring_buf_t *rb, uint8_t *buf, size_t capacity)
{
	rb->buf      = buf;
	rb->capacity = capacity;
	rb->head     = 0;
	rb->tail     = 0;
	rb->count    = 0;
}

bool rb_push(ring_buf_t *rb, uint8_t val)
{
	if (rb->count == rb->capacity) {
		return false;
	}
	rb->buf[rb->head] = val;
	rb->head = (rb->head + 1) % rb->capacity;
	rb->count++;
	return true;
}

bool rb_pop(ring_buf_t *rb, uint8_t *val)
{
	if (rb->count == 0) {
		return false;
	}
	*val = rb->buf[rb->tail];
	rb->tail = (rb->tail + 1) % rb->capacity;
	rb->count--;
	return true;
}

bool rb_peek(const ring_buf_t *rb, uint8_t *val)
{
	if (rb->count == 0) {
		return false;
	}
	*val = rb->buf[rb->tail];
	return true;
}

bool rb_is_empty(const ring_buf_t *rb)
{
	return rb->count == 0;
}

bool rb_is_full(const ring_buf_t *rb)
{
	return rb->count == rb->capacity;
}

size_t rb_count(const ring_buf_t *rb)
{
	return rb->count;
}
