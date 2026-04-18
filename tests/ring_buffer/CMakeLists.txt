# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(test_ring_buffer)

add_subdirectory(../../lib/ring_buffer ring_buffer)

target_sources(app PRIVATE main.c)
