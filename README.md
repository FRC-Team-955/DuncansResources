# Robotics examples

To compile and these examples, cd into their directory and execute the following commands:

```
cd <project directory>

# Create a build directory
mkdir build
cd build

# Tell cmake to generate build files from CMakeLists.txt that MAKE can read and compile with
cmake ..

# Execute the make command to compile the source using the build files
make -j

# Run the executable
./<executable name>
```
