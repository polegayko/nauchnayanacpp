SCRIPT_PATH=$(dirname "$0")

cd $SCRIPT_PATH
cd ..
if [ -d $SCRIPT_PATH/build ]; then
  rm -rf $SCRIPT_PATH/build
fi
mkdir build
cd build

cmake ..
cmake --build .
