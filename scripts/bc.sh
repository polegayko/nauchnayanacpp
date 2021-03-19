SCRIPT_PATH=$0
echo $SCRIPT_PATH

cd $SCRIPT_PATH
cd ..
rm build
mkdir build
cd build

cmake ..
cmake --build .
