FROM archlinux:latest
LABEL Name="Magma" Version="1.0.0"

WORKDIR /usr/local/app

RUN pacman -Syu && \
    pacman -S curl && \
    pacman -S zip && \
    pacman -S git && \
    pacman -S make && \
    pacman -S cmake && \
    git clone https://github.com/microsoft/vcpkg.git && \
    cd vcpkg && \
    ./bootstrap-vcpkg.sh && \
    export VCPKG_ROOT=$(pwd) && \
    export PATH=$VCPKG_ROOT:/bin

#COPY . .

CMD ["pwd", "echo 'lol'"]