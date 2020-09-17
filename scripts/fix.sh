cd..

cd build
sudo cp libruqquscpp.so /usr/lib/libruqquscpp.so
cd ..
cd src
sudo mkdir -p /usr/include/ruqquscpp
sudo cp *.hpp /usr/include/ruqquscpp
sudo cp ruqqus/*.hpp /usr/include/ruqquscpp
cd ..
cd scripts
echo 'Script is done'
