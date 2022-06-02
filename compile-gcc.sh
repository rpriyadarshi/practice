
# https://solarianprogrammer.com/2017/05/04/building-gcc-wsl-windows-subsystem-linux/
sudo apt update
sudo apt upgrade

sudo apt install build-essential wget m4 flex bison

export GCCVERSION=gcc-10.3.0

cd ~
wget https://ftpmirror.gnu.org/gcc/${GCCVERSION}/${GCCVERSION}.tar.xz
tar xf ${GCCVERSION}.tar.xz
pushd ${GCCVERSION}
contrib/download_prerequisites

popd
mkdir ${GCCVERSION}-build
pushd ${GCCVERSION}-build
../${GCCVERSION}/configure -v \
    --build=x86_64-linux-gnu \
    --host=x86_64-linux-gnu \
    --target=x86_64-linux-gnu \
    --prefix=/usr/local/${GCCVERSION} \
    --enable-checking=release \
    --enable-languages=c,c++ \
    --disable-multilib \
#    --program-suffix=-10.3

make -j 8

sudo make install-strip

cd ~
echo `export GCCVERSION=gcc-10.3.0` >> .bashrc
echo 'export PATH=/usr/local/${GCCVERSION}/bin:$PATH' >> .bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/${GCCVERSION}/lib64:$LD_LIBRARY_PATH' >> .bashrc
source .bashrc
