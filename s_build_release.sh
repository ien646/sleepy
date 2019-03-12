echo "-- Initializing git submodules -- "
git submodule init
git submodule update
mkdir build_release
cd build_release
cmake -DCMAKE_BUILD_TYPE=Release .. -Wdev
cmake --build . --config Release
read -n1 -r -p "Press any key to continue..." key