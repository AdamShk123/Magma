FROM debian:latest

RUN apt update && \
    apt install -y curl && \
    apt install -y zip && \
    apt install -y git && \
    apt install -y make && \
    apt install -y cmake && \
    apt install -y g++ && \
    apt install -y python3 && \
    apt install -y autoconf && \
    apt install -y automake && \
    apt install -y libtool && \
    apt install -y pkg-config

WORKDIR /home

RUN git clone https://github.com/microsoft/vcpkg.git && \
    ./vcpkg/bootstrap-vcpkg.sh && \
    export VCPKG_ROOT=/home/vcpkg && \
    export PATH=$VCPKG_ROOT:$PATH

ENV VCPKG_ROOT=/home/vcpkg
ENV PATH=$VCPKG_ROOT:$PATH