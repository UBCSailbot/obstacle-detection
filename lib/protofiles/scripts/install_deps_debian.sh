#!/usr/bin/env bash
set -e
PROTOBUFVERSION="$(apt-cache show libprotobuf-dev | grep -m 1 -Po '(?<=Version: )[0-9]')";
echo Detected protobuf version $PROTOBUFVERSION
if [  "$PROTOBUFVERSION" -gt 2 ]; then
    sudo apt install libprotobuf-dev protobuf-compiler -y
else
    sudo apt-get remove libprotobuf-dev -y
    sudo add-apt-repository ppa:maarten-fonville/protobuf -y
    sudo apt-get update
    apt-cache policy protobuf-compiler
    apt-cache policy libprotobuf-dev
    sudo apt-get install protobuf-compiler=3.1.0-0ubuntu1~maarten0 libprotobuf-dev=3.1.0-0ubuntu1~maarten0 -y
fi
