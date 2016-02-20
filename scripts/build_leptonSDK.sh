#!/usr/bin/env bash

# This is a band-aid solution to suppressing annoying and useless output from the
#  make command to build leptonSDK. The Makefile for leptonSDK runs gcc / g++ with
#  the -fpermissive and -v flags. The former is only supported for g++, so gcc
#  complains every time a file is compiled with that flag. The -v flag provides lots
#  of useless output.
#
# This script then makes a copy of the Makefile, removes those flags from the file,
#  runs the modified makefile, then restores the original, unmodified makefile.
# Usage: buil

# Check for appropriate number of arguments
if [ $# -eq 0 ]
then
    echo "Usage: $0 [leptonSDKdir]"
    echo "...where leptonSDKdir is the top directory containing the Lepton SDK source files, and the Makefile to build them."
    exit
fi

# Remember our current directory so that we can switch back to it
CUR_DIR=$(pwd)
# cd to leptonSDK dir, as specified in command-line argument
cd $1

# Make a backup of the original Makefile
cp Makefile Makefile.bak

# Remove the offending flags, -v and -fpermissive
sed -i -e 's/-v //g' Makefile
sed -i -e 's/-fpermissive //g' Makefile

# Build leptonSDK with the modified Makefile. Without the -s flag,
#  make would print every command that it executes. We don't care for this.
make -s

# Restore the backup of the Makefile, deleting the modified one
mv Makefile.bak Makefile

# Return to starting directory
cd ${CUR_DIR}
