# Tell CMake to output a compile_commands.json file, indicating to IDEs/Editors which compiler flags to use.
SET( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

# Minimum CMake version check, not too important for this project.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0 FATAL_ERROR)

# Declare project name
PROJECT(path_viewer)

# Create a variable called SOURCES that contains a list of all source files. 
# In this case, they're all in src/ and all end in '.cpp', so we use the 
# FILE(GLOB ...) command to match all of them, instead of creating a list 
# manually like cavemen.
FILE(GLOB SOURCES "src/*.cpp")

# Tell CMake where the headers are. Does not need globbing because it 
# knows to search the whole directory.
INCLUDE_DIRECTORIES("./inc")

# Find the glfw3 package and add include it's headers
find_package(PkgConfig REQUIRED) # Use PkgConfig
pkg_search_module(GLFW REQUIRED glfw3) # Tell PkgConfig to find glfw3
include_directories(${GLFW_INCLUDE_DIRS}) # Include headers

# Find the GLEW package and add include it's headers
FIND_PACKAGE(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find the GLM package and add include it's headers
#FIND_PACKAGE(glm REQUIRED)
#include_directories(${GLM_INCLUDE_DIRS})

FIND_PACKAGE(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# (Don't) Tell CMake to use the clang compiler instead of the default.
#SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Tell CMake to use C++11 standards. Can also be set to C++17, etc.
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

# Compile an executable from all of the files from the SOURCES variable and
# name it 'path_viewer'
ADD_EXECUTABLE(path_viewer ${SOURCES})

# Link the executable with... nothing. For now.
#TARGET_LINK_LIBRARIES(path_viewer ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES} ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES(path_viewer ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
