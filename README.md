### obstacle-avoidance

# dependencies

- opencv 3.0
- QT 4.8

# How to build the system

```
  git clone https://github.com/UBCSailbot/obstacle-avoidance.git
  cd obstacle-avoidance
  mkdir bin
  cd bin
  cmake ..
  make runCoreTests
  make rescale
  make rigRunner // Doesn't work currently - Josh 10/3/2015
```

# If you have problems
  If you have failed with your builds and they are still failing, try deleting the CmakeCache file and try building again
