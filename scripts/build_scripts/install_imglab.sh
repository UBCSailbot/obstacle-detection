cd lib/dlib/
git apply ../../resources/16bit.patch
cd tools/imglab/
mkdir build
cd build
cmake ..
sudo make install
cd ../../../
git reset --hard
cd ../../

