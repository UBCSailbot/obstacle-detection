### obstacle-avoidance

# dependencies

- opencv 2.4
- QT 4.8
- libusb-1.0-0-dev

# How to build the system

```
  git clone https://github.com/UBCSailbot/obstacle-avoidance.git
  cd obstacle-avoidance
  git submodule update --init --recursive
  mkdir bin
  cd bin
  cmake ..
  make runCoreTests
  make rescale
  make rigRunner


```

# If you have problems
  If you have failed with your builds and they are still failing, try deleting the CmakeCache file and try building again
