### obstacle-avoidance

# dependencies

Note that these are automatically installed for you by [debiansetup.sh](debiansetup.sh).

- opencv 2.4
- QT 5
- libusb-1.0-0-dev
- ZeroMQ 3.2

# How to build the system

## Cloning the repository

```
  git clone ssh://git@bitbucket.ubcsailbot.org:7999/fw/obstacle-avoidance.git
```

## If building on Ubuntu or other Debian flavor of Linux

Try running our setup script for debian systems, [debiansetup.sh](debiansetup.sh). NOTE: DO NOT run this script with `sudo`. That will cause pain and suffering.

```
  chmod +x debiansetup.sh
  ./debiansetup
```

## In general

```
  cd obstacle-avoidance
  git submodule update --init --recursive
  mkdir bin
  cd bin
  cmake ..
  make runCoreTests
  make rescale
  make rigRunner
```

Specific CMake flags for the Pi:

```
cmake -DDLIB_NO_GUI_SUPPORT=ON -DDLIB_LINK_WITH_SQLITE3=OFF ..
make liveFeeder
```  

Otherwise just

```
  make liveFeeder
```    

# If you have problems
 - check that you've initiated the git submodules
 - check that all dependencies are met
 - re-run `cmake ..`
 - if all else fails, delete your build directory and try again.

# Contributing
Please read the [contribution guide](CONTRIBUTING.md).


# Structure of the code
The directories `src` and `test` should mirror each other. That is, any unit testing code for
the file src/a/b.cpp should be in test/a/bTest.cpp.

-   **src/** - Source code. For more details, check out the README files in each sub-direcotry.
    -   **core/** - The foundation of obstacle avoidance. We avoid putting device-specific code
    here if we can, as it makes it easier to compile the fundamentals.
    -   **device/** - Drivers for sensors (e.g. Lepton ,LSM9DS0 IMU, USB display for Raspberry Pi, etc.)
    These can tend to be less platform-agnostic when it comes to compilation, so we leave them
    in their own compilation unit.
    -   **main/** - All the files that contain main functions and that are written more or less
     for their own end (as opposed to for testing).
-   **test/** - Testing, including both unit tests and manually-run tests.
    -   **support/** - Code files that don't run unit tests, but only exist in support of testing.
    -   Refer to documentation on **src/** for a guide to the other sub-directories here.
-   **config/** - Contains configuration files for sensors and software parameters
-   **extra/** - Miscellaneous non-testing files
-   **lib/** - Third-party libraries
-   **resources/** - A few files that are handy to have around, namely for testing
-   **scripts/** - Miscellaneous useful scripts, including those that run the "test rig" for collecting thermal imaging data.
      See the readme for [scripts](scripts/README.md)

# Running unit tests

We use [gtest](https://github.com/google/googletest) as our unit testing framework.
The target for running the unit tests is `runCoreTests`. Assuming you already have a
build directory in which cmake has been run, the followwing command will build and run
the unit test suite:

 ```
 make runCoreTests
 ./runCoreTests
 ```
