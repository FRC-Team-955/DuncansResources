# Demos

* `sockets/` - A simple async socket library executable
* `spline_viewer/` - OpenGL application to show a spline on the screen
* `path_viewer/` - A quick and dirty viewer for generated motion paths
* `motion_profile_generation/` - Example of generating velocity data from a spline for tank drive motion
* `strip_detection/` - A simple OpenCV application to detect a strip.
* `realsense_easy/` - Simple access to the Intel Realsense, and histogram

# Installing libraries
```
sudo apt update
sudo apt install libglew-dev libglfw3-dev meson ninja
```

[Install OpenCV](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html)

[Install Librealsense](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md)

# Compiling
To compile and run these examples, execute the following commands:

```
cd <project directory>

# Create a build directory and cd into it
meson build
cd build

# Run the compiler
ninja

# Run the executable
./<executable name>
```
