FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y cmake
RUN apt-get install -y g++
RUN apt-get install -y libsdl2-2.0
RUN apt-get install -y libsdl2-dev

RUN mkdir -p /fh
COPY . fh
WORKDIR /fh

RUN make
RUN ./frogHopper.exe