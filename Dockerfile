FROM ubuntu

RUN apt update
RUN apt install -y cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib git python3 build-essential 

RUN mkdir /work
WORKDIR /work

RUN git clone https://github.com/raspberrypi/pico-sdk.git

RUN mkdir pico-gb
RUN mkdir pico-gb/build

WORKDIR /work/pico-gb/build

ENV PICO_SDK_PATH=/work/pico-sdk

ENTRYPOINT [ "cmake", ".." ]