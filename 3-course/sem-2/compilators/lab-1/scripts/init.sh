#!/bin/bash
set -e

docker buildx build --platform=linux/amd64 -t tiger-lab-1 .

docker run -it --rm tiger-lab-1

docker rmi tiger-lab-1
