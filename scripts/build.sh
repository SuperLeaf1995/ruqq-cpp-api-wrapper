cd..

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
sudo make install
cd ..
cd scripts
echo 'Script is done'
