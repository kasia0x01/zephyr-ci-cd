/* SPDX-License-Identifier: Apache-2.0 */
#include <zephyr/ztest.h>
#include <stdlib.h>
#include "ring_buffer.h"

#define BUF_SIZE 4

static ring_buf_t rb;
static uint8_t    storage[BUF_SIZE];

static void setup(void *unused)
{
	rb_init(&rb, storage, BUF_SIZE);
}

ZTEST_SUITE(ring_buffer, NULL, NULL, setup, NULL, NULL);

ZTEST(ring_buffer, test_initial_state)
{
	zassert_true(rb_is_empty(&rb));
	zassert_false(rb_is_full(&rb));
	zassert_equal(rb_count(&rb), 0);
}

ZTEST(ring_buffer, test_push_and_pop_single)
{
	uint8_t out;

	zassert_true(rb_push(&rb, 42));
	zassert_equal(rb_count(&rb), 1);
	zassert_false(rb_is_empty(&rb));

	zassert_true(rb_pop(&rb, &out));
	zassert_equal(out, 42);
	zassert_true(rb_is_empty(&rb));
}

ZTEST(ring_buffer, test_fifo_order)
{
	uint8_t out;

	rb_push(&rb, 1);
	rb_push(&rb, 2);
	rb_push(&rb, 3);

	rb_pop(&rb, &out);
	zassert_equal(out, 1);
	rb_pop(&rb, &out);
	zassert_equal(out, 2);
	rb_pop(&rb, &out);
	zassert_equal(out, 3);
}

ZTEST(ring_buffer, test_push_when_full)
{
	for (int i = 0; i < BUF_SIZE; i++) {
		zassert_true(rb_push(&rb, i));
	}
	zassert_true(rb_is_full(&rb));
	zassert_false(rb_push(&rb, 99), "push into full buffer must return false");
	zassert_equal(rb_count(&rb), BUF_SIZE);
}

ZTEST(ring_buffer, test_pop_when_empty)
{
	uint8_t out = 0xAB;

	zassert_false(rb_pop(&rb, &out), "pop from empty buffer must return false");
	zassert_equal(out, 0xAB, "output must not be modified on failed pop");
}

ZTEST(ring_buffer, test_peek_does_not_consume)
{
	uint8_t peeked, popped;

	rb_push(&rb, 7);
	zassert_true(rb_peek(&rb, &peeked));
	zassert_equal(peeked, 7);
	zassert_equal(rb_count(&rb), 1, "peek must not consume the element");

	zassert_true(rb_pop(&rb, &popped));
	zassert_equal(popped, 7);
}

ZTEST(ring_buffer, test_wrap_around)
{
	uint8_t out;

	/* Fill completely */
	for (uint8_t i = 0; i < BUF_SIZE; i++) {
		rb_push(&rb, i);
	}
	/* Drain half */
	for (int i = 0; i < BUF_SIZE / 2; i++) {
		rb_pop(&rb, &out);
	}
	/* Refill — head wraps past end of storage array */
	for (uint8_t i = 10; i < 10 + BUF_SIZE / 2; i++) {
		zassert_true(rb_push(&rb, i));
	}
	/* Verify FIFO order across wrap */
	for (uint8_t i = BUF_SIZE / 2; i < BUF_SIZE; i++) {
		rb_pop(&rb, &out);
		zassert_equal(out, i);
	}
	for (uint8_t i = 10; i < 10 + BUF_SIZE / 2; i++) {
		rb_pop(&rb, &out);
		zassert_equal(out, i);
	}
	zassert_true(rb_is_empty(&rb));
}

/* Proof that asan job is working - uncomment to trigger failure */
// ZTEST(ring_buffer, test_asan_is_working)
// {
// 	int *p = malloc(sizeof(int));
// 	free(p);
// 	*p = 42;
// }
