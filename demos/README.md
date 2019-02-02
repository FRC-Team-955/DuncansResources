# Demos

* `sockets/` - A simple async socket library executable
* `triangle/` - The common OpenGL example program, just draws a red triangle
* `spline_viewer/` - OpenGL application to show a spline on the screen
* `path_viewer/` - A quick and dirty viewer for generated motion paths
* `motion_profile_generation/` - Example of generating velocity data from a spline for tank drive motion
* `strip_detection/` - A simple OpenCV application to detect a strip.

# Installing libraries
```
sudo apt update
sudo apt install cmake libglew-dev libglfw3-dev
```

Optional: [Install OpenCV](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html)

# Compiling
To compile and run these examples, execute the following commands:

```
cd <project directory>

# Create a build directory
mkdir build
cd build

# Tell cmake to generate build files from CMakeLists.txt that MAKE can read and compile with
cmake ..

# Execute the make command to compile the source using the build files
# Note, '-j' enables make to compile using multiple threads. On large projects, this is extremely helpful.
make -j

# Run the executable
./<executable name>
```
