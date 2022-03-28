FROM ubuntu:latest

# Install compilers
RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y nasm

# Set up shared volume
VOLUME [ "/env" ]
WORKDIR /root/env