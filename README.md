# Robotics examples

The repository is divided into a directories/files that cover certain subjects. 
They are as follows:

* `sockets/` - A simple async socket library and executable example
* `opengl/` - Examples of graphics manipulation
* `path_from_scratch/` - Documentation on how to use bezier curves for robot path planning (PDF)
* `jetson_internet.md` - A document demonstrating how to provide internet access to a remote device

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

If you've got more questions, you can email Duncan at:
duncan.freeman1@gmail.com
