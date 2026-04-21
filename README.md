# zephyr-ci-cd

[![codecov](https://codecov.io/gh/kasia0x01/zephyr-ci-cd/branch/main/graph/badge.svg)](https://codecov.io/gh/kasia0x01/zephyr-ci-cd)

A practical guide to automated testing for Zephyr RTOS projects or libraries. Each technique is demonstrated with working code and a CI job that runs it on every push.

## What's in here

```
hello_world/          Sample app that invokes library
lib/ring_buffer/      A portable C library with no Zephyr dependencies
tests/ring_buffer/    Unit tests for ring_buffer using ztest
.github/workflows/    CI pipeline
zephyr-docker/        Docker image used by CI
```

## Techniques covered

### 1. Running an app on QEMU

`hello_world` builds for `qemu_cortex_m3` and checks that the expected string appears on the serial output.

The CI file shows two ways to do this:

- **`build-and-run-qemu`** — the naive approach: background process + `sleep` + `pkill`. Works, but fragile and slower.
- **`build-and-run-qemu-twister`** — the right way: Twister handles launch, output parsing, and timeout automatically.

### 2. Unit tests with ztest

`lib/ring_buffer` is a plain C ring buffer. Its tests live in `tests/ring_buffer/` and use Zephyr's built-in test framework, [ztest](https://docs.zephyrproject.org/latest/develop/test/ztest.html).

Tests run on `native_sim` — a Linux process (posix-like). Linux-like simulation is good enough for testing portable libraries that don't depend on Zephyr APIs, and it's much faster than QEMU.

The CI file shows two ways to do this:
- `unit-tests` — the naive approach: build with `west build -t run`.
- `twister-tests` — the right way: Twister discovers and runs tests, and produces a structured report.

[Twister](https://docs.zephyrproject.org/latest/develop/test/twister.html) discovers tests automatically using `testcase.yaml` files, runs them, and produces a structured report.

```bash
/workspace/zephyr/scripts/twister \
  --testsuite-root tests/ \
  --platform native_sim \
  --inline-logs
```

Each test suite declares which platforms it supports in `testcase.yaml`. Twister enforces this and skips tests that don't apply to the selected platform.

### 3. Sanitizers (ASAN + UBSan)

The `sanitizers` CI job builds the tests with `CONFIG_ASAN=y` and `CONFIG_UBSAN=y`. These are compiler-level tools that catch:

- Buffer overflows and out-of-bounds reads
- Use-after-free
- Undefined behavior (integer overflow, misaligned access, etc.)

### 4. Coverage

The `coverage` job builds with `CONFIG_COVERAGE=y`, runs the tests, and uses `gcovr` to produce an HTML report and a Cobertura XML file. The XML is uploaded to [Codecov](https://codecov.io), which tracks coverage over time and posts results to pull requests.
It produces a badge that shows the current coverage percentage, which is displayed in the README.

## Docker image

See `zephyr-docker/` for how the image is built.

## What this repo does not cover

- Thread-safe libraries and mocking Zephyr kernel APIs with [FFF](https://github.com/meekrosoft/fff)
- Hardware-in-the-loop testing
- Testing on real hardware via Twister's `hardware` runner
