#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include <stdexcept>

#include <string.h>
#include <errno.h>

GLuint load_shaders(char *vertex_file_path, char *fragment_file_path);
GLuint load_shaders_local(char *vertex_source, char *fragment_source);
