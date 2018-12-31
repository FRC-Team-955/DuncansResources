#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdexcept>

#include <string.h>
#include <errno.h>

GLuint load_shaders(const char *vertex_file_path, const char *fragment_file_path);
