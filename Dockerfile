FROM ubuntu:18.04
RUN apt-get update \
    # Install gcc for x86 and ARM
    && apt-get install -y build-essential gcc-arm-linux-gnueabi gcc-arm-linux-gnueabihf git \
    curl gawk texinfo expat libexpat1-dev bison flex libz-dev \
    # Prepare to download and compile RISCV toolchain
    && export HOME_DIR=/home/root \
    && export RISCV_SRC_DIR=$HOME_DIR/riscv-gnu-toolchain \
    && export RISCV_DIR=$HOME_DIR/riscv-tools \
    && mkdir $HOME_DIR \
    && cd $HOME_DIR \
    && git clone --recursive https://github.com/riscv/riscv-gnu-toolchain -j 8\
    && cd $RISCV_SRC_DIR \
    # Checkout a specific hash to keep the output binaries consistent
    && git checkout 23a038856764808d75b6afe96f649980609ae4c6 \
    # Downloading the prereqs must be done in riscv-gcc folder
    && cd $RISCV_SRC_DIR/riscv-gcc \
    && ./contrib/download_prerequisites \
    && cd $RISCV_SRC_DIR \
    && ./configure --prefix=$RISCV_DIR \
    && make -j 32 \
    # Remove the source code
    && rm -rf $RISCV_SRC_DIR 

# Modify to compile
# For x86: gcc
# For ARM: arm-linux-gnueabi-gcc or arm-linux-gnueabihf-gcc ?
# For RISCV: $RISCV_DIR/bin/riscv64-unknown-elf-gcc
CMD ls
