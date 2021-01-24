
rm BUILD/CMakeCache.txt

cmake -S . -B BUILD -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=~/app
cmake --build BUILD

