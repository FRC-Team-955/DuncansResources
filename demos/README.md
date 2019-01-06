# Demos

* `sockets/` - A simple async socket library executable
* `triangle/` - The common OpenGL example program, just draws a red triangle

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
