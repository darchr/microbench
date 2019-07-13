FROM ubuntu:18.04
RUN apt-get update \
    && apt-get install -y build-essential gcc-arm-linux-gnueabihf git\
    && export HOME_DIR=/home/root/ \
    && export RISCV_SRC_DIR=$HOME_DIR/riscv-gnu-toolchain/ \
    && export RISCV__DIR=$HOME_DIR/riscv-tools/ \
    && mkdir $HOME_DIR \
    && cd $HOME_DIR \
    && git clone --recursive https://github.com/riscv/riscv-gnu-toolchain \
    && git checkout 23a038856764808d75b6afe96f649980609ae4c6 \
    && $RISCV_SRC_DIR/riscv-gcc/contrib/download_prerequisites \
    && cd $RISCV_SRC_DIR \
    && ./configure --prefix=$RISCV_DIR \
    && make -j 32 \
    && rm -rf /home/root/riscv-gnu-toolchain \    
CMD ls
