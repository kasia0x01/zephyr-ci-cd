
## Building the image locally
From the `zephyr-docker` directory:
```bash
docker buildx build -t zephyr-ci-arm .
```

## Update remote after local changes
```bash
docker login ghcr.io -u GITHUB_LOGIN
docker tag zephyr-ci-arm ghcr.io/GITHUB_LOGIN/zephyr-ci-arm:latest
docker push ghcr.io/GITHUB_LOGIN/zephyr-ci-arm:latest
```
