# Tell CMake to output a compile_commands.json file, indicating to IDEs/Editors which compiler flags to use.
SET( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

# Minimum CMake version check, not too important for this project.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0 FATAL_ERROR)

# Declare project name
PROJECT(strip_detector)

# Find OpenCV libraries
FIND_PACKAGE(OpenCV)

# Create a variable called SOURCES that contains a list of all source files. 
# In this case, they're all in src/ and all end in '.cpp', so we use the 
# FILE(GLOB ...) command to match all of them, instead of creating a list 
# manually like cavemen.
FILE(GLOB SOURCES "src/*.cpp")

# Tell CMake where the headers are. Does not need globbing because it 
# knows to search the whole directory.
INCLUDE_DIRECTORIES("./inc")

# (Don't) Tell CMake to use the clang compiler instead of the default.
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Tell CMake to use C++11 standards. Can also be set to C++17, etc.
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

# Compile an executable from all of the files from the SOURCES variable and
# name it 'strip_detector'
ADD_EXECUTABLE(strip_detector ${SOURCES})

# Link the executable with... nothing. For now.
TARGET_LINK_LIBRARIES(strip_detector ${OpenCV_LIBS})
