# install spack
mkdir -p $HOME/local
git clone -c feature.manyFiles=true --depth 1 https://github.com/spack/spack.git $HOME/spack
. $HOME/spack/share/spack/setup-env.sh
spack external find automake autoconf libtool cmake m4 pkgconf bison
spack install mochi-margo ^mercury~boostsys ^libfabric fabrics=rxm,sockets,tcp,udp

# download and install chfs
git clone https://github.com/otatebe/chfs.git $HOME/chfs 
cd $HOME/chfs 
spack load mochi-margo 
autoreconf -i 
./configure --prefix $HOME/local
make clean 
make -j $(nproc) 
make install

cat << EOS >> $HOME/.bashrc
export LC_ALL=C
. $HOME/spack/share/spack/setup-env.sh
export PATH=$HOME/local/bin:$PATH
export LD_LIBRARY_PATH=$HOME/local/lib:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=$HOME/local/lib/pkgconfig:$PKG_CONFIG_PATH
EOS