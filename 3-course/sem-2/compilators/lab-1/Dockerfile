FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y \
    clang-3.9 \
    g++-3.9 \
    zsh \
    && apt-get clean

WORKDIR /project

COPY ./dragon-tiger /project/dragon-tiger
COPY ./scripts /project/scripts

RUN find /project/scripts -name "*.sh" -exec chmod +x {} \;

CMD ["/bin/bash"]

