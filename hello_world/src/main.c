/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

const char* SECRET = "I am a secret string!";

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	printf("%s\n", SECRET);

	return 0;
}
