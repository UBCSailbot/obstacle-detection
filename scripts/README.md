## obstacle-avoidance/scripts

This folder contains miscellaneous scripts used in the development and operation
 of obstacle-avoidance.

 ## Contents
 -   **build_scripts/** - Accessory scripts used in building various components of the code base,
      usually external libraries included as git submodules. **The relative paths to these are
      referenced directly from CMake and Bamboo, so please do not move them unless you really know what you are doing.**
 -   **python/** - A pot-pourri of Python scripts, some of which are written as modules to be imported by others.
     -   **expt/** - Scripts used in curating and exploring data collected from field experiments.
     -   **image_proc/** - Scripts that run various image processing operations.
     -   **rigRunner/** - Includes the script that runs the Obstacle Avoidance test rig.
          **Important to maintain for legacy purposes.**
     -   **shared/** - Contains variables and functions that are reused across different scripts.
     -   **video/** - Code that processes videos, including converting directories of images to videos.
