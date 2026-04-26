# zephyr-ci-cd

[![codecov](https://codecov.io/gh/kasia0x01/zephyr-ci-cd/branch/main/graph/badge.svg)](https://codecov.io/gh/kasia0x01/zephyr-ci-cd)

Example of automated testing for Zephyr RTOS applications or libraries.

## Content

```
.github/workflows/    CI pipeline -- contains 3 different workflows that show different approaches
hello_world/          Sample application that invokes example library
lib/ring_buffer/      A portable C library `ring_buffer` with no Zephyr dependencies
tests/ring_buffer/    Unit tests for `ring_buffer` using ZTESTS
zephyr-docker/        Custom Docker image allowing to run Zephyr tests on CI
```

## Different approaches to run Zephyr tests on CI/CD

### Own Docker image and own logic

## Own Docker image and Twister tool

## Ready Zephyr actions and Twister tool