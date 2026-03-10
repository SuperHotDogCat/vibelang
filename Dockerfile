FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    llvm-18-dev \
    clang-18 \
    flex \
    bison \
    make \
    g++ \
    git \
    && rm -rf /var/lib/apt/lists/*

RUN ln -s /usr/bin/llvm-config-18 /usr/bin/llvm-config && \
    ln -s /usr/bin/llc-18 /usr/bin/llc && \
    ln -s /usr/bin/clang-18 /usr/bin/clang && \
    ln -s /usr/bin/clang++-18 /usr/bin/clang++

WORKDIR /app
COPY . .

RUN make

CMD ["/bin/bash"]
