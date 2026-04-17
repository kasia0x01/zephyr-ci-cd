FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake ninja-build gperf ccache \
    python3 python3-pip python3-setuptools python3-wheel \
    wget xz-utils file make \
    clang clang-tidy cppcheck \
    qemu-system-arm \
    && rm -rf /var/lib/apt/lists/*

RUN pip3 install --no-cache-dir \
    west \
    pyelftools \
    cmake

# Zephyr SDK – only ARM toolchain, minimal installation
ARG ZEPHYR_SDK_VERSION=0.16.8
RUN wget -q \
    https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v${ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && tar xf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz -C /opt \
    && rm zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && /opt/zephyr-sdk-${ZEPHYR_SDK_VERSION}/setup.sh -t arm-zephyr-eabi -h -c

ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-${ZEPHYR_SDK_VERSION}
ENV PATH="/opt/zephyr-sdk-${ZEPHYR_SDK_VERSION}/arm-zephyr-eabi/bin:${PATH}"

WORKDIR /workspace