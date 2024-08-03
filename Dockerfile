FROM debian:latest
LABEL Name="Magma" Version="1.0.0"

WORKDIR /usr/local/app

RUN apt update && \
    apt install -y curl && \
    apt install -y zip && \
    apt install -y git && \
    apt install -y make && \
    apt install -y cmake && \
    git clone https://github.com/microsoft/vcpkg.git && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh && \
    export VCPKG_ROOT=$(pwd) && \
    export PATH=$VCPKG_ROOT:/bin

#COPY . .

CMD ["pwd", "echo 'lol'"]