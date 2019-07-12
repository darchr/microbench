FROM ubuntu:18.04
RUN apt-get update && apt-get install -y build-essential gcc-arm-linux-gnueabihf 
CMD ls /usr/bin
