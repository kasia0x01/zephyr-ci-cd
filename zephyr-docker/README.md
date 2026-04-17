
## Building the image locally
docker buildx build -t zephyr-ci-arm .

## Test
docker run --rm zephyr-ci-arm west --version
West version: v1.5.0

docker run --rm zephyr-ci-arm arm-zephyr-eabi-gcc --version
arm-zephyr-eabi-gcc (Zephyr SDK 0.16.8) 12.2.0

## Update remote after local changes
docker login ghcr.io -u GITHUB_LOGIN
docker tag zephyr-ci-arm ghcr.io/GITHUB_LOGIN/zephyr-ci-arm:latest
docker push ghcr.io/GITHUB_LOGIN/zephyr-ci-arm:latest