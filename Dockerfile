FROM ubuntu:latest

COPY [".", "/csi-driver-chfs"]

# install chfs dependencies
RUN apt-get update && apt-get install -y \
    git wget \
    gcc automake cmake \
    libtool pkgconf \
    python3 bison fuse sudo curl \
    libfuse-dev pandoc \
    libopenmpi-dev libssl-dev \
    gdb numactl \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /csi-driver-chfs

ARG SOURCEDIR=/opt
ARG INSTALLDIR=/usr
RUN mkdir -p $INSTALLDIR/local \
    && git clone -c feature.manyFiles=true --depth 1 https://github.com/spack/spack.git $HOME/spack \
    && . $HOME/spack/share/spack/setup-env.sh \
    && spack external find automake autoconf libtool cmake m4 pkgconf bison \
    && spack install mochi-margo ^mercury~boostsys ^libfabric fabrics=rxm,sockets,tcp,udp

RUN git clone https://github.com/otatebe/chfs.git $SOURCEDIR/chfs \
    && cd $SOURCEDIR/chfs \
    && . $HOME/spack/share/spack/setup-env.sh \
    && spack load mochi-margo \
    && autoreconf -i \
    && ./configure --prefix $INSTALLDIR/local \
    && make clean \
    && make -j $(nproc) \
    && make install \
    && echo ". $HOME/spack/share/spack/setup-env.sh" >> $HOME/.bashrc

ENV LC_ALL C
ENV PATH $INSTALLDIR/local/bin:$PATH
ENV LD_LIBRARY_PATH $INSTALLDIR/local/lib:$LD_LIBRARY_PATH
ENV PKG_CONFIG_PATH $INSTALLDIR/local/lib/pkgconfig:$PKG_CONFIG_PATH

RUN . $HOME/spack/share/spack/setup-env.sh \
    && spack load mochi-margo \
    && cmake \
    -DCMAKE_BUILD_TYPE:STRING=Release \
    -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc \
    -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++ \
    -S/csi-driver-chfs \
    -B/csi-driver-chfs/build \
    -G "Unix Makefiles"

RUN . $HOME/spack/share/spack/setup-env.sh \
    && spack load mochi-margo \
    && cmake \
    --build /csi-driver-chfs/build \
    --config Release \
    --target install \
    -j $(nproc)

ENTRYPOINT ["chfsplugin"]