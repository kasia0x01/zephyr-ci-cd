/* SPDX-License-Identifier: Apache-2.0 */
#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
	uint8_t *buf;
	size_t   capacity;
	size_t   head;
	size_t   tail;
	size_t   count;
} ring_buf_t;

void   rb_init(ring_buf_t *rb, uint8_t *buf, size_t capacity);
bool   rb_push(ring_buf_t *rb, uint8_t val);
bool   rb_pop(ring_buf_t *rb, uint8_t *val);
bool   rb_peek(const ring_buf_t *rb, uint8_t *val);
bool   rb_is_empty(const ring_buf_t *rb);
bool   rb_is_full(const ring_buf_t *rb);
size_t rb_count(const ring_buf_t *rb);

#endif /* RING_BUFFER_H */
