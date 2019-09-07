# zmq

easy zmq wrapper for playing around. build and tested with bazel and gtest.

# install zmq
from https://github.com/zeromq/cppzmq#build-instructions

Build steps:

Build libzmq via cmake. This does an out of source build and installs the build files
+ download and unzip the lib, cd to directory
+ `mkdir build`
+ `cd build`
+ `cmake ..`
+ `sudo make -j4 install`

Build cppzmq via cmake. This does an out of source build and installs the build files
+ download and unzip the lib, cd to directory
+ `mkdir build`
+ `cd build`
+ `cmake ..`
+ `sudo make -j4 install`
