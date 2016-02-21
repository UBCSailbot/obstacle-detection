#!/bin/bash
# debian-setup.sh

#
# This script takes care of installing all the dependencies required to
#  build the obstacle avoidance code. Read the comments below for more
#  specific details on what it does.
#
# REQUIREMENTS: 
#  - This script only works on Debian-based flavors of Linux, e.g. Ubuntu.
#  - It's assumed that you're starting from a freshly cloned copy of
#     the repository.
#  - It's assumed that this script is being run from within the top
#     directory of the repository.
#  - A working internet connection is needed to install any missing 
# 	  packages as well as the git submodules.
#
#  If you're having problems cloning git repos, check that ssh-agent
#   has your private key loaded. For reference, see e.g.
#   https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/
#

# Update package manager indices to latest available.
sudo apt-get update

# Program dependencies
sudo apt-get install libopencv-dev libqt4-dev libusb-1.0-0-dev libzmq-dev -y
# Optional optimized libraries for image processing, use by dlib
sudo apt-get install libopenblas-dev liblapack-dev -y

# CMake is needed to actually build the system
sudo apt-get install cmake -y

# Clone git submodules
git submodule update --init --recursive

# Set up build directory
mkdir bin
cd bin
cmake ..

# Build & run tests. This can take a while on the first build,
#  since you'll have to build, among other things, all of dlib.
make runCoreTests
./runCoreTests